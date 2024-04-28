#include "movimiento.h"
using namespace std;

// Función que convierte una dir. en un string
string toString(Direccion d) {

    string dir;
    switch (d) {
    case 0:
        dir = "ARRIBA";
        break;
    case 1:
        dir = "ABAJO";
        break;
    case 2:
        dir = "IZQUIERDA";
        break;
    case 3:
        dir = "DERECHA";
        break;
    case 4:
        dir = "INDETERMINADA";
        break;
    }

    return dir;

}

// Función que devuelve un Movimiento con la posición de su ficha
Movimiento inicializa(int f, int c) {
	Movimiento mov;
	mov.fila = f;
	mov.columna = c;
	mov.cont = 0;

	return mov;
}

// Procedimiento que añade una a una las posibles direcciones
void insertarDireccion(Movimiento& m, Direccion d) {

	// Se inserta la dirección en la lista y se aumenta el contador
	m.direcciones[m.cont] = d;
	m.cont++;

}

// Procedimiento que fija la dirección a aplaicar
void fijarDireccionActiva(Movimiento& m, Direccion d) {
	m.dirActiva = d;
}

// Función que devuelve la fila de la ficha del movimiento
int fila(Movimiento const& m) {
	return m.fila;
}

// Función que devuelve la columna de la ficha del movimiento
int columna(Movimiento const& m) {
	return m.columna;
}

// Función que devuelve la dirección activa del movimiento
Direccion direccionActiva(Movimiento const& m) {
	return m.dirActiva;
}

// Función que devuelve el número de direcciones posibles
int numDirs(Movimiento const& m) {
	return m.cont;
}

// Función que devuelve la dirección i de la lista de direcciones
Direccion direccion(Movimiento const& m, int i) {
	return m.direcciones[i];
}

