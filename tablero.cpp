#include "tablero.h"
using namespace std;
Celda asignarValorACelda(int valor);

// Procedimiento que se encarga de construir el tablero y sus atributos con los valores pasados por parámetro
void inicializa(Tablero& tab, int fil, int col, Celda inicial) {
	tab.numColumnas = col;
	tab.numFilas = fil;
	for (int i = 0; i < tab.numFilas; i++) {
		for (int j = 0; j < tab.numColumnas; j++) {
			tab.celdas[i][j] = inicial;
		}
	}

}

// Procedimiento que se encarga de construir un tablero vacío
void inicializa(Tablero& tab) {
	tab.numColumnas = 0;
	tab.numFilas = 0;
}

// Función booleana que trata de carga el tablero desde el flujo de entrada pasado por parámetro
bool cargar(Tablero&/*sal*/ tab, istream&/*ent/sal*/ entrada) {
	int valor;
	bool cargado = true;

	if(!(entrada >> tab.numFilas >> tab.numColumnas)) return false;

	// Y se procede leer casilla por casilla los valores de estas
	for (int i = 0; i < tab.numFilas; i++) {
		for (int j = 0; j < tab.numColumnas; j++) {
			entrada >> valor;
			escribirCelda(tab, i, j, asignarValorACelda(valor));
		}
	}

	return cargado;

}

// Función que devuelve el número de filas del tablero
int numFilas(Tablero const& tab) {
	return tab.numFilas;
}

// Función que devuelve el número de columnas del tablero
int numColumnas(Tablero const& tab) {
	return tab.numColumnas;
}

// Función booleana que comprueba que una posición se encuentre dentro de las dimensiones del tablero
bool correcta(Tablero const& tab, int f, int c) {
	return (f >= 0 && f <tab.numFilas) && (c >= 0 && c < tab.numColumnas);
}

// Función que devuelve la Celda que se encuentra en cierta posición pasada por parámetro
Celda leerCelda(Tablero const& tab, int f, int c) {
	return tab.celdas[f][c];
}

// Procedimiento que se encarga de instanciar el contenido de una casilla del tablero con la Celda pasada por parámetro
void escribirCelda(Tablero& tab, int f, int c, Celda valor) {
	tab.celdas[f][c] = valor;
}


Celda asignarValorACelda(int valor) {
	Celda celda = NULA;
	switch (valor) {
	case 0:
		celda=NULA;
		break;
	case 1:
		celda=VACIA;
		break;
	case 2:
		celda = FICHA;
		break;
	}
	return celda;
}

