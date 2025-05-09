#include "carta.h"
#include <iostream>

// Constructor que inicializa una carta con un color y un número
Carta::Carta(std::string color, int numero) : color(color), numero(numero) {
    // Validar que el número esté en el rango permitido
    if (numero < 1 || numero > 9) {
        throw std::invalid_argument("El número de la carta debe estar entre 1 y 9.");
    }
}

// Método para obtener el color de la carta
std::string Carta::getColor() const {
    return color;
}

// Método para obtener el número de la carta
int Carta::getNumero() const {
    return numero;
}

// Método para mostrar la carta
void Carta::mostrar() const {
    std::cout << "Carta: " << color << " " << numero << std::endl;
}