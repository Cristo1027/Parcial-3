#include "jugador.h"

// Constructor que inicializa un jugador con un nombre
Jugador::Jugador(std::string nombre) : nombre(nombre), puntos(0) {}

// Método para jugar una carta elegida por el jugador
Carta Jugador::jugarCarta(int indice) {
    if (mano.empty()) {
        std::cerr << "Error: " << nombre << " no tiene cartas.\n";
        return Carta("Error", -1);  // Retornar una carta de error
    }
    if (indice < 0 || indice >= static_cast<int>(mano.size())) {
        std::cerr << "Índice inválido.\n";
        return Carta("Error", -1);
    }

    Carta carta_jugada = mano[indice];
    mano.erase(mano.begin() + indice); // Eliminar la carta de la mano
    return carta_jugada;
}

// Método para verificar si la mano está vacía
bool Jugador::manoVacia() const {
    return mano.empty();
}

// Método para recibir una sola carta
void Jugador::recibirCarta(const Carta& carta) {
    mano.push_back(carta);
}

// Método para recibir múltiples cartas
void Jugador::recibirCartas(const std::vector<Carta>& nuevas_cartas) {
    mano.insert(mano.end(), nuevas_cartas.begin(), nuevas_cartas.end());
}

// Método para mostrar cartas en la mano
void Jugador::mostrarMano() const {
    std::cout << "Mano de " << nombre << ":\n";
    for (size_t i = 0; i < mano.size(); ++i) {
        std::cout << i + 1 << ". ";
        mano[i].mostrar();  // Mostrar cada carta con su número
    }
    std::cout << "\n";
}

// Método para obtener la cantidad de cartas en la mano
int Jugador::getNumeroCartas() const {
    return mano.size();
}

// Método para sumar un punto al jugador
void Jugador::ganarPunto() {
    puntos++;
}

// Método para obtener el puntaje del jugador
int Jugador::getPuntos() const {
    return puntos;
}

// Método para obtener el nombre del jugador
std::string Jugador::getNombre() const {
    return nombre;
}

// Método para obtener la mano de cartas
const std::vector<Carta>& Jugador::getMano() const {
    return mano; // Devuelve una referencia constante a la mano
}
