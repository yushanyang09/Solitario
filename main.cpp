#include <iostream>
#include <ctime>     // Para la semilla 
#include <fstream>
#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
#include "colores.h"
#include "listaOrdenada.h"
#include "gestor.h"

using namespace std;

// Es posible que esta función pertenezca al módulo tablero
bool leerMovimiento(Juego solitario, Movimiento &mov);
void mostrarEstado(Juego const& juego);
bool leerPosicion(int& f, int& c);
bool RecibirMov(Juego& juego);
int leerPartida();

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // Inicializa la semilla de generación de números aleatorios
    srand(time(nullptr));
    ifstream archivo;
	Gestor gestor;
    char volver = 'N';
    char Modo;
	string id;
	int pasos;

	do {

		// Solitud del id
		cout << "Usuario (FIN para terminar): ";
		cin >> id;

		if (id != "FIN") {

			// Inicializamos el gestor 
			
			inicializar(gestor);
			archivo.open("partidas.txt");
			system("cls");

				if (cargar(gestor, archivo)){
					archivo.close();

					login(gestor, id);
					if (tienePartidas(gestor)) {
						mostrarPartidas(gestor);
						int opcion = leerPartida();
						if (opcion !=0) {
							Juego& partida_actual = partida(gestor, opcion);
							if (RecibirMov(partida_actual)) {
								if (estado(partida_actual) != JUGANDO) {
									mostrarEstado(partida_actual);
									eliminarPartida(gestor, opcion);
								
								}
							}
						}
						else {
							cout << "Indica el numero de pasos para crear el tablero aleatorio: ";
							cin >> pasos;
							int opcion= insertarAleatoria(gestor, pasos);
							Juego& partida_actual = partida(gestor, opcion);
							if (RecibirMov(partida_actual)) {
								if (estado(partida_actual) != JUGANDO) {
									mostrarEstado(partida_actual);
									eliminarPartida(gestor, gestor.usuario_activo);

								}
							}


						}
					}
					else {
						cout << "No tienes partidas comenzadas.Vamos a crear un juego aleatorio.";
						cout << "Indica el numero de pasos para crear el tablero aleatorio: ";
						cin >> pasos;
						int opcion=insertarAleatoria(gestor, pasos);
						Juego& partida_actual = partida(gestor, opcion);
						if (RecibirMov(partida_actual)) {
							if (estado(partida_actual) != JUGANDO) {
								mostrarEstado(partida_actual);
								eliminarPartida(gestor, gestor.usuario_activo);

							}
						}
					}
					
					cout << "Quieres seguir jugando [S/N]? ";
					cin >> volver;

				} while (volver != 'N');

			cout << "Quieres seguir jugando [S/N]? ";
			cin >> volver;
			
	    } while (volver != 'N');


	} while (!(id == "FIN"));
	destruir(gestor);
}

int leerPartida() {
	int partida;
	cout<<" Elige una partida o 0 para crear una nueva aleatoria : ";
    cin >> partida; 
	return partida;
}
// Función que se encarga de leer los movimientos del usuario
bool leerMovimiento(Juego solitario, Movimiento& mov) {
	cout << "Selecciona una FICHA (fila y columna, 0 para salir):";
	int fila, columna;
	if (!leerPosicion(fila, columna))  // Si no se pudieron leer las coordenadas
		return false;  // Salir de la función
	if (fila == 0)  // Si el usuario ingresa 0 para ambas coordenadas
		return false;  // Salir de la función
	mov = inicializa(fila, columna);
	return true;
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