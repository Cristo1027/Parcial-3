
#include "tablero.h"
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdlib>

// Constructor que inicializa el tablero con los jugadores
Tablero::Tablero(const std::vector<Jugador>& jugadores_)
    : jugadores(jugadores_), juegoFinalizado(false), turnoActual(0) {}

// Verifica si el juego ha terminado
bool Tablero::juegoTerminado() const {
    return juegoFinalizado;
}

// Muestra los puntajes actuales de los jugadores
void Tablero::mostrarPuntajes() const {
    std::cout << "\n--- Puntajes Actuales ---\n";
    for (const auto& jugador : jugadores) {
        std::cout << jugador.getNombre() << ": " << jugador.getPuntos() << " puntos\n";
    }
    std::cout << "-------------------------\n";
}

// Juega una ronda del juego alternando el jugador que inicia
void Tablero::jugarRonda(int sockets[2]) {
    static int ronda = 1;
    std::cout << "\n--- Ronda " << ronda++ << " ---\n";

    if (verificarFinDelJuego()) return;

    std::vector<Carta> cartasJugadas;
    std::string color_base;
    int mayor_valor = -1;
    int ganador_idx = -1;

    // Determinar el orden de los jugadores esta ronda
    int primero = turnoActual;
    int segundo = (turnoActual + 1) % 2;

    // Enviar información y mano a cada jugador
    for (int i = 0; i < 2; ++i) {
        int idx = (i == 0) ? primero : segundo;
        std::string mensaje = "Ronda actual: " + std::to_string(ronda - 1) + "\n";
        mensaje += (i == 0) ? "Eres el primer jugador en esta ronda.\n" : "Eres el segundo jugador en esta ronda.\n";
        mensaje += obtenerManoJugador(idx);
        send(sockets[idx], mensaje.c_str(), mensaje.size(), 0);
    }

    // Recibir jugadas de ambos jugadores en orden
    for (int i = 0; i < 2; ++i) {
        int idx = (i == 0) ? primero : segundo;

        int indice = leerOpcionJugador(sockets[idx], jugadores[idx].getNumeroCartas());
        if (indice == -1) {
            juegoFinalizado = true;
            return;
        }

        Carta carta_jugada = jugadores[idx].jugarCarta(indice);
        cartasJugadas.push_back(carta_jugada);

        if (i == 0) {
            color_base = carta_jugada.getColor();
            mayor_valor = carta_jugada.getNumero();
            ganador_idx = idx;
        } else if (carta_jugada.getColor() == color_base && carta_jugada.getNumero() > mayor_valor) {
            mayor_valor = carta_jugada.getNumero();
            ganador_idx = idx;
        }
    }

    // Asignar punto al jugador ganador
    jugadores[ganador_idx].ganarPunto();

    // Enviar resultado de la ronda a ambos jugadores
    std::string resultado = "\nEl ganador de la ronda es: " + jugadores[ganador_idx].getNombre() + "\n";
    for (int i = 0; i < 2; ++i) {
        send(sockets[i], resultado.c_str(), resultado.size(), 0);
    }

    // Mostrar los puntajes en el servidor
    mostrarPuntajes();

    // Alternar el turno inicial para la siguiente ronda
    turnoActual = (turnoActual + 1) % 2;
}

// Verifica si el juego ha terminado (si algún jugador no tiene cartas)
bool Tablero::verificarFinDelJuego() {
    for (const auto& jugador : jugadores) {
        if (jugador.manoVacia()) {
            std::cout << jugador.getNombre() << " no tiene más cartas. Fin del juego.\n";
            juegoFinalizado = true;
            return true;
        }
    }
    return false;
}

// Devuelve una cadena con la mano del jugador
std::string Tablero::obtenerManoJugador(int jugador_idx) {
    const std::vector<Carta>& mano = jugadores[jugador_idx].getMano();
    std::string mano_str = "Tu mano es:\n";
    for (size_t j = 0; j < mano.size(); ++j) {
        mano_str += std::to_string(j + 1) + ". " + mano[j].getColor() + " " + std::to_string(mano[j].getNumero()) + "\n";
    }
    return mano_str;
}

// Lee la opción de carta seleccionada por el jugador desde el socket
int Tablero::leerOpcionJugador(int socket, int cantidad_cartas) {
    char buffer[1024] = {0};
    ssize_t valread = recv(socket, buffer, sizeof(buffer), 0);
    if (valread <= 0) {
        std::cerr << "Error leyendo la opción del cliente o cliente desconectado.\n";
        return -1;
    }

    int indice = atoi(buffer) - 1;
    if (indice < 0 || indice >= cantidad_cartas) {
        std::cerr << "Índice de carta inválido recibido.\n";
        return -1;
    }

    return indice;
}
