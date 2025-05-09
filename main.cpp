// main.cpp
#include <iostream>
#include <string>

void start_server();
void start_client();

int main() {
    int choice;
    std::cout << "Seleccione una opción:\n1. Iniciar Servidor\n2. Iniciar Cliente\n";
    std::cin >> choice;

    if (choice == 1) {
        start_server();
    } else if (choice == 2) {
        start_client();
    } else {
        std::cout << "Opción no válida.\n";
    }

    return 0;
}
