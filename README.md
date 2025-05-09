# README

## Descripción del Proyecto

Este proyecto es un juego de cartas en red diseñado para dos jugadores. Utiliza programación orientada a objetos y sockets para permitir la comunicación entre el cliente y el servidor. Los jugadores pueden jugar cartas y el juego determina un ganador en cada ronda.

## Estructura del Proyecto

El proyecto está organizado en varios archivos, cada uno de los cuales contiene una clase o funcionalidad específica:

- **`carta.h` / `carta.cpp`**: Define la clase `Carta`, que representa una carta con un color y un número.
- **`jugador.h` / `jugador.cpp`**: Define la clase `Jugador`, que representa a un jugador en el juego y maneja su mano de cartas y puntaje.
- **`mazo.h` / `mazo.cpp`**: Define la clase `Mazo`, que representa un mazo de cartas y proporciona métodos para barajar y repartir cartas.
- **`tablero.h` / `tablero.cpp`**: Define la clase `Tablero`, que maneja la lógica del juego y el flujo de las rondas.
- **`cliente.cpp`**: Contiene la funcionalidad del cliente, que se conecta al servidor y permite al jugador interactuar con el juego.
- **`server.cpp`**: Contiene la funcionalidad del servidor, que gestiona las conexiones de los jugadores y la lógica del juego.
- **`main.cpp`**: Punto de entrada del programa, donde se inicia el servidor o el cliente según la elección del usuario.

## Requisitos

- C++11 o superior
- Librerías estándar de C++
- Sistema operativo compatible con sockets (Linux, macOS, etc.)

## Compilación y Ejecución

1. **Compilación**: Utiliza un compilador de C++ para compilar los archivos. Por ejemplo, usando `g++`:

   ```bash
   g++ -o juego main.cpp cliente.cpp server.cpp jugador.cpp mazo.cpp tablero.cpp carta.cpp
   ```

2. **Ejecución**:
   - Para iniciar el servidor, ejecuta:

     ```bash
     ./juego
     ```

     Selecciona la opción para iniciar el servidor.

   - Para iniciar el cliente, ejecuta el mismo comando en otra terminal y selecciona la opción para iniciar el cliente.

## Uso

- Una vez que el servidor esté en funcionamiento, los jugadores pueden conectarse como clientes.
- Cada jugador verá su mano de cartas y podrá elegir una carta para jugar en cada ronda.
- El juego alterna turnos entre los jugadores y determina un ganador en cada ronda, mostrando los puntajes actuales.

## Contribuciones

Las contribuciones son bienvenidas. Si deseas contribuir, por favor sigue estos pasos:

1. Haz un fork del repositorio.
2. Crea una nueva rama (`git checkout -b feature/nueva-funcionalidad`).
3. Realiza tus cambios y haz commit (`git commit -m 'Añadir nueva funcionalidad'`).
4. Haz push a la rama (`git push origin feature/nueva-funcionalidad`).
5. Abre un Pull Request.

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## Contacto

Para preguntas o comentarios, por favor contacta a [tu nombre o correo electrónico].
