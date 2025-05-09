
#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include "jugador.h"
#include "carta.h"

class Tablero {
private:
    std::vector<Jugador> jugadores;
    bool juegoFinalizado;
    int turnoActual; // Alterna quién comienza cada ronda

public:
    // Constructor
    Tablero(const std::vector<Jugador>& jugadores);

    // Lógica del juego
    void jugarRonda(int sockets[2]);
    bool juegoTerminado() const;
    void mostrarPuntajes() const;
    bool verificarFinDelJuego();

    // Funciones auxiliares
    std::string obtenerManoJugador(int jugador_idx);
    int leerOpcionJugador(int socket, int cantidad_cartas);
};

#endif // TABLERO_H
