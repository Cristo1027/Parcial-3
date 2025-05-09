#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "jugador.h"
#include "tablero.h"
#include "mazo.h"

const char* SERVER_IP = "127.0.0.1";
const int PORT = 12345;

void start_client() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "❌ Error al crear el socket.\n";
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        std::cerr << "❌ Dirección IP no válida.\n";
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "❌ Error al conectar al servidor.\n";
        return;
    }

    std::cout << "✅ Conectado al servidor. Esperando instrucciones...\n";

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        int valread = recv(sock, buffer, sizeof(buffer), 0);
        if (valread <= 0) {
            std::cerr << "❌ Error al recibir datos del servidor o conexión cerrada.\n";
            break;
        }

        std::cout << "\n" << buffer << std::endl;

        int cartaElegida;
        std::cout << "Elige una carta (número): ";
        std::cin >> cartaElegida;

        std::string cartaStr = std::to_string(cartaElegida);
        if (send(sock, cartaStr.c_str(), cartaStr.size(), 0) < 0) {
            std::cerr << "❌ Error al enviar la carta al servidor.\n";
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        valread = recv(sock, buffer, sizeof(buffer), 0);
        if (valread > 0) {
            std::cout << buffer << std::endl;
        } else {
            std::cerr << "❌ Error al recibir el resultado de la ronda.\n";
            break;
        }
    }

    close(sock);
    std::cout << "🔌 Conexión cerrada.\n";
}
