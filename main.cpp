#include <iostream>
#include <ctime>     // Para la semilla 
#include <fstream>
#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
#include "colores.h"
#include "listaOrdenada.h"

using namespace std;

// Es posible que esta función pertenezca al módulo tablero
bool leerMovimiento(Juego solitario, Movimiento &mov);
void mostrarEstado(Juego const& juego);
bool leerPosicion(int& f, int& c);
bool RecibirMov(Juego& juego);

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // Inicializa la semilla de generación de números aleatorios
    srand(time(nullptr));
    Juego solitario;
	ListaUsuarios listaUsuarios;
    ifstream archivo;
    char volver = 'N';
    char Modo;
	string id;
	int pos, partida, pasos;

	do {

		// Solitud del id
		cout << "Usuario (FIN para terminar): ";
		cin >> id;

		if (id != "FIN") {

			// Inicializamos y cargamos los usuarios
			inicializar(listaUsuarios);
			archivo.open("partidas.txt");
			system("cls");

			do {

				if (cargar(listaUsuarios, archivo))
				{
					archivo.close();

					// Una vez estan cargados los usuarios, buscamos las partidas
					// Pero antes comprobamos si tiene
					if (buscar(listaUsuarios, id, pos)) {
						// Si existe es seguro que tiene partidas
						cout << "Tus partidas empezadas:\n";
						ListaJuegos partidas = listaUsuarios.usuarios[pos]->partidas;
						for (int i = 0; i < partidas.cont; i++) {
							cout << i + 1 << "  --------------------------------------\n";
							mostrar(obtener(partidas, i));
						}

						// Una vez mostradas se pregunta por cuál quiere jugar

						do {
							cout << "Elige una partida o 0 para crear una nueva aleatoria: ";
							cin >>  partida;

							// Modo aleatorio
							if (!partida) {
								int pasos;
								cout << "Indica el numero de pasos para crear el juego aleatorio: ";
								cin >> pasos;
								generar(solitario, pasos);
								// empezamos a jugar
								RecibirMov(solitario);
								// mostrar resultado de la partida (ganador o bloqueo)
								mostrarEstado(solitario);
							} else {
								// Cargamos partida
								solitario = obtener(partidas, partida);
								mostrar(solitario);

								if (RecibirMov(solitario))
									mostrarEstado(solitario);
								if (estado(solitario) != JUGANDO)
									eliminar(partidas, partida);
								if (partidas.cont < 1) {
									eliminar(listaUsuarios, pos);
									partida = -1;
								}
							}


						} while (partida < 0 || partida > partidas.cont);


					} else {
						// Usuario no encontrado
						cout << "Indica el numero de pasos para crear el juego aleatorio: ";
						cin >> pasos;
						generar(solitario, pasos);
						// empezamos a jugar
						RecibirMov(solitario);
						// mostrar resultado de la partida (ganador o bloqueo)
						mostrarEstado(solitario);
					}

				}
				cout << "Quieres seguir jugando [S/N]? ";
				cin >> volver;

			} while (volver != 'N');

		}
	} while (!(id == "FIN"));

}


//Funcion que se encarga de leer los movimientos del usuario
bool leerMovimiento(Juego solitario, Movimiento &mov) {

    cout << "Selecciona una FICHA (fila y columna, 0 para salir):";
    int fila, columna;
    if (leerPosicion(fila, columna)) {
		mov = inicializa(fila, columna);
		return true;
	}
    return false;

}
//funcion que se encarga de leer la fila y columna elegida del jugador
bool leerPosicion(int& f, int& c) {
    cin >> f;
	if (!f)
		return false;
	cin >> c;
	f--;
	c--;
	return true;
}

void mostrarEstado(Juego const& juego) {
    if (estado(juego) == GANADOR)
        cout << "\t\t ! ! HAS GANADO ! ! ";
    else
        cout << "\t NO PUEDES MOVER FICHAS. HAS PERDIDO ";
}
bool RecibirMov(Juego& juego) {

    int opcion;
	bool salir = false;

    do {
        Movimiento movimiento;

		if (leerMovimiento(juego, movimiento)) {
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
		} else {
			salir = true;
		}

    } while (estado(juego) == JUGANDO && !salir);
	return salir;
}