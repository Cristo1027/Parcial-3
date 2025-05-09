#ifndef CARTA_H
#define CARTA_H

#include <iostream>
#include <stdexcept> 

// Clase que representa una carta con un color y un número
class Carta {
private:
    std::string color; 
    int numero;        

public:
    // Constructor que inicializa una carta con un color y un número
    Carta(std::string color, int numero);

    // Métodos para obtener el color y el número de la carta
    std::string getColor() const;
    int getNumero() const;

    // Método para mostrar la carta
    void mostrar() const;
};

#endif
