#include "tablero.h"
using namespace std;

void inicializa(Tablero& tab, int fil, int col, Celda inicial) {
	tab.numColumnas = col;
	tab.numFilas = fil;
	for (int i = 0; i < tab.numFilas; i++) {
		for (int j = 0; j < tab.numColumnas; j++) {
			tab.celdas[i][j] = inicial;
		}
	}

}

void inicializa(Tablero& tab) {
	tab.numColumnas = 0;
	tab.numFilas = 0;
}

bool cargar(Tablero&/*sal*/ tab, istream&/*ent/sal*/ entrada) {
	entrada >> tab.numFilas >> tab.numColumnas;
	
	for (int i = 0; i < tab.numFilas; i++) {
		for (int j = 0; j < tab.numColumnas; j++) {
			int valor;
			entrada >> valor;
			escribirCelda(tab, i, j, valor);
		}
	}
}

int numFilas(Tablero const& tab) {
	return tab.numFilas;
}
int numColumnas(Tablero const& tab) {
	return tab.numColumnas;
}

bool correcta(Tablero const& tab, int f, int c) {
	return (f >= 0 && f < tab.numFilas) && (c >= 0 && c < tab.numColumnas);
}
Celda leerCelda(Tablero const& tab, int f, int c) {
	return tab.celdas[f][c];
}
void escribirCelda(Tablero& tab, int f, int c, Celda valor) {
	tab.celdas[f][c] = valor;
}