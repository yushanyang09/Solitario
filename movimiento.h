#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H
#include "movimiento.h"

// número de direcciones a considerar
const int NumDir = 4;
// vectores de direccion: {dif. fila, dif. columna}
const pair<int, int> dirs[NumDir] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
enum Direccion { ARRIBA, ABAJO, IZQUIERDA, DERECHA, INDETERMINADA };
string toString(Direccion d);
struct Movimiento {
	int fila, columna;
	Direccion dirActiva; // de todas las direcciones posibles, contiene la
	// direccion activa: la dirección que se va a ejecutar
	int cont; // número de direcciones a las que se puede mover
	Direccion direcciones[NumDir]; // direcciones a las que se puede mover
};
Movimiento inicializa(int f, int c);
void insertarDireccion(Movimiento& m, Direccion d);
// d pertece a direcciones[0..cont)
void fijarDireccionActiva(Movimiento& m, Direccion d);






#endif