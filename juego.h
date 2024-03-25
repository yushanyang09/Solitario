#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "movimiento.h"
using namespace std;

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
void mostrar(Juego const& juego);

// Privadas
void ejecuta_movimiento(Juego& juego, Movimiento const& mov);
void nuevo_estado(Juego& juego);
bool hay_ganador(Juego const& juego);
bool hay_movimientos(Juego const& juego);
void generar(Juego& juego, int pasos);//para la generación del tablero aleatorio
bool movimiento_inverso(Juego& juego);
#endif

