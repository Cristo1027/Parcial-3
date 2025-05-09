#include "mazo.h"
#include <ctime>

// Constructor que inicializa el mazo con cartas
Mazo::Mazo() {
    const std::string colores[] = {"Rojo", "Azul", "Verde", "Amarillo"};
    for (const auto& color : colores) {
        for (int num = 1; num <= 9; ++num) {
            cartas.push_back(Carta(color, num));
        }
    }
}

// Método para barajar las cartas
void Mazo::barajar() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartas.begin(), cartas.end(), g);
}

// Método para repartir cartas
std::vector<Carta> Mazo::repartirCartas(int cantidad) {
    std::vector<Carta> mano;
    for (int i = 0; i < cantidad && !cartas.empty(); ++i) {
        mano.push_back(cartas.back());
        cartas.pop_back();
    }
    return mano;
}

// Método para verificar si el mazo está vacío
bool Mazo::estaVacio() const {
    return cartas.empty();
}