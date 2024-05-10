// YUSHAN YANG XU
// BRYAN XAVIER QUILUMBA FARINANGO

#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "movimiento.h"

enum Estado { JUGANDO, GANADOR, BLOQUEO };

struct Juego {
	int filaMeta, colMeta;
	Tablero tablero;
	Estado estado;
	
};

// Públicas
void inicializa(Juego& juego);
bool cargar(Juego&/*sal*/ juego, istream&/*ent/sal*/ entrada);
bool posicionValida(Juego const& juego, int f, int c);
void posiblesMovimientos(Juego const& juego, Movimiento& mov);
Estado estado(Juego const& juego);
void jugar(Juego& juego, Movimiento const& mov);
void generar(Juego& juego, int pasos);//para la generación del tablero aleatorio
void guardar(Juego const& juego, ostream& salida);

#endif

