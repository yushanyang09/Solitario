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
void mostrarEstado(Juego const& juego);
void leerPosicion(int& f, int& c);
void RecibirMov(Juego& juego);

int main() {
    // Inicializa la semilla de generación de números aleatorios
    srand(time(nullptr));
    Juego solitario;
    ifstream archivo;
    char volver = 'N';
    char Modo;
    cout << "Quieres cargar un juego [C] o empezar con uno aleatorio [A]? ";
    cin >> Modo;
    Modo = toupper(Modo);

    if (Modo == 'C') {
        do{
            inicializa(solitario);
            string nombreArchivo;
            do {
                cout << "Nombre del archivo con el juego: ";
                cin >> nombreArchivo;
                archivo.open(nombreArchivo);
                system("cls");
            } while (!archivo.is_open());
            if (cargar(solitario, archivo)) {
                archivo.close();
                mostrar(solitario);
                RecibirMov(solitario);
                mostrarEstado(solitario);
                cout << "\n\n";
                cout << "Quieres volver a jugar [S/N]? ";
                cin >> volver;
            }
        } while (volver == 'S' || volver == 's');
     
              
    }
    else if (Modo == 'A') {
        do {
            int pasos;
            cout << "Indica el numero de pasos para crear el juego aleatorio: ";
            cin >> pasos;
            generar(solitario, pasos);
            // empezamos a jugar
            RecibirMov(solitario);
            // mostrar resultado de la partida (ganador o bloqueo)
            mostrarEstado(solitario);
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

void mostrarEstado(Juego const& juego) {
    if (estado(juego) == GANADOR)
        cout << "\t\t ! ! HAS GANADO ! ! ";
    else
        cout << "\t NO PUEDES MOVER FICHAS. HAS PERDIDO ";
}
void RecibirMov(Juego& juego) {
    int opcion;
    do {
        Movimiento movimiento = leerMovimiento(juego);
        posiblesMovimientos(juego, movimiento);
        if (leerCelda(juego.tablero, fila(movimiento), columna(movimiento)) != FICHA)
            cout << "\nCelda incorrecta o sin ficha\n";
        else if (numDirs(movimiento) == 0) // No tiene ninguna dirección posible
            cout << "\nEsa ficha no se puede mover\n";
        else if (numDirs(movimiento) == 1) // Solo tiene una dirección posible
            jugar(juego, movimiento);
        else {
            // Se solicita la direccion deseada, hasta que seleccione una valida
            do {

                cout << "Selecciona direccion:\n";
                for (int i = 1; i <= numDirs(movimiento); i++) {
                    cout << "\t" << i << " - " << toString(movimiento.direcciones[i - 1]) << '\n';
                }
                cin >> opcion;

                if (opcion < 1 || opcion > numDirs(movimiento))
                    cout << "Direccion invalida\n";
                else {
                    fijarDireccionActiva(movimiento, movimiento.direcciones[opcion - 1]);
                    jugar(juego, movimiento);
                    mostrar(juego);
                }

            } while (opcion < 1 || opcion > numDirs(movimiento));
        }
    } while (estado(juego) == JUGANDO);
}