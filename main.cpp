
#include <iostream>
#include <ctime>     // Para la semilla 
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
    // Inicializa la semilla de generación de números aleatorios
    srand(time(nullptr));
    Juego solitario;
    ifstream archivo;
    Movimiento movimiento;
    char volver = 'N';
    char Modo;
    cout << "Quieres cargar un juego [C] o empezar con uno aleatorio [A]? ";
    cin >> Modo;
    Modo = toupper(Modo);

    if (Modo == 'C') {
        do {
            inicializa(solitario);
            string nombreArchivo;
            cout << "Introduzca el nombre del archivo del tablero: ";
            cin >> nombreArchivo;
            archivo.open(nombreArchivo);
                if (cargar(solitario, archivo)) {
                    // se muestra el estado inicial
                    archivo.close();
                    mostrar(solitario);

                    // empezamos a jugar
                    do {
                        movimiento = leerMovimiento(solitario);
                        jugar(solitario, movimiento);
                    } while (estado(solitario) == JUGANDO);
                }
 
  
        } while (!archivo.is_open());
    }
    else if (Modo == 'A') {
        do {
            int pasos;
            cout << "Indica el numero de pasos para crear el juego aleatorio: ";
            cin >> pasos;
            generar(solitario, pasos);
            // empezamos a jugar
            do {
                movimiento = leerMovimiento(solitario);
                jugar(solitario, movimiento);
            } while (estado(solitario) == JUGANDO);

            // mostrar resultado de la partida (ganador o bloqueo)
            if (estado(solitario) == GANADOR)
                cout << "\t\t ! ! HAS GANADO ! ! ";
            else
                cout << "\t NO PUEDES MOVER FICHAS. HAS PERDIDO ";
            cout << "\n\n";
            cout << "Quieres volver a jugar [S/N]? ";
            cin >> volver;
        } while (volver == 'S' || volver == 's');
    }

}


//Funcion que se encarga de leer los movimientos del usuario
Movimiento leerMovimiento(Juego solitario) {

    cout << "Selecciona una FICHA (fila y columna):";
    int fila, columna;
    leerPosicion(fila, columna);
    Movimiento mov = inicializa(fila, columna);
    return mov;

}
//funcion que se encarga de leer la fila y columna elegida del jugador
void leerPosicion(int& f, int& c) {
    cin >> f >> c;
	f--;
	c--;
}

