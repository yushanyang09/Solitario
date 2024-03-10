#include "juego.h"
#include "colores.h"
#include "tablero.h"
#include <iomanip>
using namespace std;
void mostrar(Juego const& juego);
void pintaCabecera(Juego const& juego);
void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, Juego const& juego);
void colorFondo(int color);
void pintaBordeCelda(int fila, Juego const& juego);
void pintaCentroCelda(int fila, Juego const& juego);

const char Horizontal = char(196);
const char UpperLeft = char(218);
const char UpperCross = char(194);
const char UpperRight = char(191);
const char Vertical = char(179);
const char MidLeft = char(195);
const char MidCross = char(197);
const char MidRight = char(180);
const char LowerLeft = char(192);
const char LowerCross = char(193);
const char LowerRight = char(217);
const char Square = char(219);

const int DEFAULT_COLOR = -1;


Direccion obtenerDireccion(int posicion);
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
	entrada >> juego.filaMeta >> juego.colMeta;

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
	mov.cont = 0;
	for (int i = 0; i < NumDir; i++) {
		if (mov.fila == dirs[i].first && mov.columna == dirs[i].second) {
			Direccion dir = obtenerDireccion(i);
			mov.direcciones[mov.cont] = dir;
		}
	}

}

Estado estado(Juego const& juego) {
	return juego.estado;
}

void jugar(Juego& juego, Movimiento const& mov) {

}
void mostrar(Juego const& juego) {
    system("cls"); // borrar consola (clear en Linux)
	cout << RESET;

	// borde superior
	pintaCabecera(juego);
	pintaLinea(UpperLeft, UpperCross, UpperRight,juego);

	// para cada fila
	for (int fil = 0; fil < juego.tablero.numFilas; fil++) {
		if (fil == juego.filaMeta) {

		}
		// primera línea
		pintaBordeCelda(fil,juego);
		// segunda línea, con la meta posiblemente
		pintaCentroCelda(fil,juego);
		// tercera línea
		pintaBordeCelda(fil,juego);
		// separación entre filas
		if (fil <juego.tablero.numFilas - 1)
			pintaLinea(MidLeft, MidCross, MidRight,juego);
		else
			pintaLinea(LowerLeft, LowerCross, LowerRight,juego);
	}


}

// Privadas
void ejecuta_movimiento(Juego& juego, Movimiento const& mov) {

}

void nuevo_estado(Juego& juego) {

}

bool hay_ganador(Juego const& juego) {
	return false;
}

bool hay_movimientos(Juego const& juego) {
	return true;

}
Direccion obtenerDireccion(int posicion) {
	switch (posicion) {
	case 0:
		return ARRIBA;
	case 1:
		return ABAJO;
	case 2:
		return IZQUIERDA;
	case 3:
		return DERECHA;
	}
	return INDETERMINADA;
}

void pintaCabecera(Juego const& juego) {
	cout << setw(2) << "    "; // margen inicial
	cout << setw(5) << 1;

	for (int i = 2; i <= juego.tablero.numColumnas; i++)
		cout << setw(7) << i;

	cout << '\n';
}

void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, Juego const& juego) {
	cout << "    "; // margen inicial
	cout << esquinaIzda;

	for (int i = 0; i < juego.tablero.numColumnas - 1; i++)
		cout << string(6, Horizontal) << cruce;

	cout << string(6, Horizontal) << esquinaDer << '\n';
}
void colorFondo(int color) {
	if (color == DEFAULT_COLOR)
		cout << RESET;
	else if (color == NULA)
		cout << BG_BLACK;
	else if (color == FICHA)
		cout << BG_LBLUE;
	else // color == VACIA
		cout << BG_ORANGE;
}


void pintaBordeCelda(int fila,Juego const& juego) {
	cout << "    "; // margen inicial

	for (int k = 0; k < juego.tablero.numColumnas; k++) { // cada columna
		cout << Vertical;
		colorFondo(juego.tablero.celdas[fila][k]);
		cout << "      ";
		colorFondo(DEFAULT_COLOR);
	}

	cout << Vertical << '\n'; // lateral derecho
}

void pintaCentroCelda(int fila,Juego const& juego) {
	cout << "  " << setw(2) << fila + 1; // margen inicial

	for (int k = 0; k < juego.tablero.numColumnas; k++) { // cada columna
		cout << Vertical;
		// el color de fondo depende del contenido
		colorFondo(juego.tablero.celdas[fila][k]);

		if (fila == juego.filaMeta && k == juego.colMeta) { // meta
			cout << YELLOW;
			cout << "  " << Square << Square << "  ";
		}
		else
			cout << "      ";

		colorFondo(DEFAULT_COLOR);
	}

	cout << Vertical << '\n'; // lateral derecho
}