#include <iostream>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include "jugador.h"
#include "tablero.h"
#include "mazo.h"

const int PORT = 12345;

// Función para iniciar el servidor
void start_server() {
    int server_fd, new_socket[2];
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    std::vector<Jugador> jugadores;

    // Crear socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        std::cerr << "Error al crear el socket.\n";
        return;
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular el socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Error al vincular el socket.\n";
        return;
    }
    listen(server_fd, 2); // Escuchar hasta 2 conexiones

    std::cout << "Esperando conexiones...\n";
    for (int i = 0; i < 2; ++i) {
        new_socket[i] = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket[i] < 0) {
            std::cerr << "Error al aceptar la conexión.\n";
            return;
        }
        std::cout << "Jugador " << (i + 1) << " conectado.\n";
        std::string nombre = "Jugador " + std::to_string(i + 1);
        jugadores.push_back(Jugador(nombre));
    }

    // Crear el mazo y barajarlo
    Mazo mazo;
    mazo.barajar();

    // Repartir cartas
    int cartasPorJugador = 36 / 2; // Suponiendo 2 jugadores
    for (auto& jugador : jugadores) {
        jugador.recibirCartas(mazo.repartirCartas(cartasPorJugador));
    }

    // Lógica del juego
    Tablero tablero(jugadores);
    while (!tablero.juegoTerminado()) {
        // Llamamos a jugarRonda una sola vez, pasando el arreglo completo de sockets
        tablero.jugarRonda(new_socket); // Pasar el arreglo de sockets
    }

    // Cerrar los sockets de los jugadores
    for (int i = 0; i < 2; ++i) {
        close(new_socket[i]);
    }
    
    // Cerrar el socket del servidor
    close(server_fd);
}

// Función principal
//int main() {
//    start_server(); // Iniciar el servidor
//    return 0;
//}
