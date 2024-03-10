
/*
* Este es un ejemplo de cómo pintar un tablero constante
* con el mismo formato que aparece en el enunciado de la
* práctica.

* Los subprogramas que aparecen a continuación hacen uso de
* varias constantes, para el tablero y sus dimensiones,
* o la posición de la meta.

* En la práctica, esos subprogramas seguramente pertenezcan a
* un módulo con acceso a esos datos del juego que no serán
* constantes.
*
* Y necesitarán parámetro(s).
*/

#include <iostream>
#include <fstream>
#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
 #include "colores.h"
using namespace std;

// Es posible que esta función pertenezca al módulo tablero
Movimiento leerMovimiento(Juego solitario);
void leerPosicion(int& f, int& c);

int main() {
    ifstream archivo;
    archivo.open("tablero_enunciado.txt");
    if (!archivo.is_open()) {
        cout << "Archivo no encontrado" << endl;
    }
    else {
        Juego solitario;
        if (cargar(solitario, archivo)) {
            mostrar(solitario); // se muestra el estado inicial
            // empezamos a jugar
            do {
                Movimiento movimiento = leerMovimiento(solitario);
                jugar(solitario, movimiento);
                mostrar(solitario);
            } while (estado(solitario) == JUGANDO);
            // mostrar resultado de la partida (ganador o bloqueo)
        }
    }
}
Movimiento leerMovimiento(Juego solitario) {
    cout << "Selecciona una FICHA (fila y columna):";
    int fila, columna;
    leerPosicion(fila, columna);
    Movimiento mov = inicializa(fila, columna);
    return mov;
}
void leerPosicion(int& f, int& c) {
    cin >> f>> c;
}
