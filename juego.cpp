#include "juego.h"
using namespace std;

// Públicas

// Procedimiento que crea un juego bloqueado con un tablero vacío
void inicializa(Juego& juego) {

	// Variables
	Tablero tab;

	// Se bloquea el juego y se añade el tablero
	juego.estado = Estado(2);
	inicializa(tab); // Tablero con dimensiones pero vacío
	juego.tablero = tab;

}

// Función que da valor al juego a partir del contenido del flujo de entrada.
// Primero se construye el tablero, luego se fija la meta y se establece el estado jugando.
bool cargar(Juego&/*sal*/ juego, istream&/*ent/sal*/ entrada) {

	// Variables
	bool todoCorrecto;

	// Se construye el tablero
	todoCorrecto = cargar(juego.tablero, entrada);

	// Se lee e inserta la meta
	cin >> juego.filaMeta >> juego.colMeta;

	// Se establece el estado del juego
	juego.estado = Estado(0);

	return todoCorrecto;
}

// Función booleana en cuanto a posición correcta y con ficha
bool posicionValida(Juego const& juego, int f, int c) {

	// Variables
	bool valida;
	Celda celda;

	// Se comprueban las dimensiones
	valida = correcta(juego.tablero, f, c);

	// Si se encuentra dentro del tablero;
	if (valida) {
		celda = leerCelda(juego.tablero, f, c);
		valida = celda == Celda(2); // Hay ficha
	}

	return valida;

}

// Procedimiento que completa el movimiento con las direcciones posibles de la ficha
void posiblesMovimientos(Juego const& juego, Movimiento& mov) {

	// Variables
	Direccion listDir[] = {Direccion(0), Direccion(1), Direccion(2), Direccion(3)};


	// Se contemplan todas las direcciones y se añaden las posibles
	// for (pair<int, int> dir: dirs) {}


}

Estado estado(Juego const& juego) {

}

void jugar(Juego& juego, Movimiento const& mov) {

}
void mostrar(Juego const& juego) {


}

// Privadas
void ejecuta_movimiento(Juego& juego, Movimiento const& mov) {

}

void nuevo_estado(Juego& juego) {

}

bool hay_ganador(Juego const& juego) {

}

bool hay_movimientos(Juego const& juego) {


}