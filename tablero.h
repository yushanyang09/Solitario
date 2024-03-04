#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <fstream>
using namespace std;

enum Celda { NULA, VACIA, FICHA };

const int MaxDim = 10;

struct Tablero {
	int numFilas, numColumnas;
	Celda celdas[MaxDim][MaxDim];
};

// Creación
void inicializa(Tablero& tab, int fil, int col, Celda inicial);
void inicializa(Tablero& tab);
bool cargar(Tablero&/*sal*/ tab, istream&/*ent/sal*/ entrada);

// Consulta
int numFilas(Tablero const& tab);
int numColumnas(Tablero const& tab);
Celda leerCelda(Tablero const& tab, int f, int c);
bool correcta(Tablero const& tab, int f, int c);

// Modificación
void escribirCelda(Tablero& tab, int f, int c, Celda valor);

#endif 

