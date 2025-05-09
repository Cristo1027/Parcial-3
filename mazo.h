#ifndef MAZO_H
#define MAZO_H

#include "carta.h"
#include <vector>
#include <algorithm>
#include <random>

// Clase que representa un mazo de cartas
class Mazo {
private:
    std::vector<Carta> cartas; 

public:
    // Constructor que inicializa el mazo con cartas
    Mazo();

    // Método para barajar las cartas
    void barajar();

    // Método para repartir cartas
    std::vector<Carta> repartirCartas(int cantidad);

    // Método para verificar si el mazo está vacío
    bool estaVacio() const;
};

#endif
