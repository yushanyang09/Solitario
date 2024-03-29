
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
	// Variables
	Juego solitario;
    ifstream archivo;
	Movimiento movimiento;
	char volver = 'N';
	char Modo;
	cout << "Quieres cargar un juego [C] o empezar con uno aleatorio [A]?";
	cin >> Modo;
	Modo = toupper(Modo);
	if (Modo == 'C') {
		// Gane o pierda, se volvería a iniciar el juego mientras el jugador quiera
		do {

			// Se inicializa el flujo (necesario para volver a cargar otra partida)
			archivo = ifstream();

			// Se crear el tablero vacio
			inicializa(solitario);

			// Se abre el archivo que contiene la información del tablero
			archivo.open("tablero5x5.txt");

			// Se avisa si no se ha encontrado el fichero
			if (!archivo.is_open()) {
				cout << "Archivo no encontrado" << endl;
			}
			else {

				// Se carga el juego
				if (cargar(solitario, archivo)) {

					// se muestra el estado inicial
					mostrar(solitario);

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
					cout << RESET << "\n\n";
					cout << "Quieres volver a jugar [S/N]? ";
					cin >> volver;
				}

			}

		} while (volver == 'S');
	}
	else if (Modo == 'A') {
	  do{
		int pasos;
		cout << "Indica el numero de pasos para crear el juego aleatorio:";
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
		cout << RESET << "\n\n";
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
