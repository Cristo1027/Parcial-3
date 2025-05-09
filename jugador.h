#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include <iostream>
#include "carta.h"

// Clase que representa a un jugador en el juego
class Jugador {
private:
    std::string nombre; 
    std::vector<Carta> mano; 
    int puntos; 

public:
    // Constructor que inicializa un jugador con un nombre
    Jugador(std::string nombre);

    // Método para jugar una carta elegida por el jugador
    Carta jugarCarta(int indice);

    // Método para verificar si la mano está vacía
    bool manoVacia() const;

    // Métodos para recibir cartas
    void recibirCarta(const Carta& carta);
    void recibirCartas(const std::vector<Carta>& nuevas_cartas);

    // Método para mostrar las cartas en la mano
    void mostrarMano() const;

    // Métodos para obtener información del jugador
    int getNumeroCartas() const;
    void ganarPunto();
    int getPuntos() const;
    std::string getNombre() const;

    // Método para obtener la mano de cartas
    const std::vector<Carta>& getMano() const; 
};

#endif 
