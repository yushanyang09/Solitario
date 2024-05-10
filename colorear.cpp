// YUSHAN YANG XU
// BRYAN XAVIER QUILUMBA FARINANGO

#include "colores.h"

using namespace std;

// privados
void pintaCabecera(Juego const& juego);
void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, Juego const& juego);
void colorFondo(int color);
void pintaBordeCelda(int fila, Juego const& juego);
void pintaCentroCelda(int fila, Juego const& juego);


// Procedimiento que se encarga de mostrar el tablero
void mostrar(Juego const& juego) {
	cout << RESET;

	// borde superior
	pintaCabecera(juego);
	pintaLinea(UpperLeft, UpperCross, UpperRight, juego);

	// para cada fila
	for (int fil = 0; fil < numFilas(juego.tablero); fil++) {
		if (fil == juego.filaMeta) {

		}
		// primera línea
		pintaBordeCelda(fil, juego);
		// segunda línea, con la meta posiblemente
		pintaCentroCelda(fil, juego);
		// tercera línea
		pintaBordeCelda(fil, juego);
		// separación entre filas
		if (fil < numFilas(juego.tablero) - 1)
			pintaLinea(MidLeft, MidCross, MidRight, juego);
		else {
			pintaLinea(LowerLeft, LowerCross, LowerRight, juego);
		}
	}


}

// PROCEDIMIENTOS ENCARGADOS DE PINTAR EL TABLERO
void pintaCabecera(Juego const& juego) {
	cout << setw(2) << "    "; // margen inicial
	cout << setw(5) << 1;

	for (int i = 2; i <= numColumnas(juego.tablero); i++)
		cout << setw(7) << i;

	cout << '\n';
}

void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, Juego const& juego) {
	cout << "    "; // margen inicial
	cout << esquinaIzda;

	for (int i = 0; i < numColumnas(juego.tablero) - 1; i++)
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


void pintaBordeCelda(int fila, Juego const& juego) {
	cout << "    "; // margen inicial

	for (int k = 0; k < numColumnas(juego.tablero); k++) { // cada columna
		cout << Vertical;
		colorFondo(juego.tablero.celdas[fila][k]);
		cout << "      ";
		colorFondo(DEFAULT_COLOR);
	}

	cout << Vertical << '\n'; // lateral derecho
}

void pintaCentroCelda(int fila, Juego const& juego) {
	cout << "  " << setw(2) << fila + 1; // margen inicial

	for (int k = 0; k < numColumnas(juego.tablero); k++) { // cada columna
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
