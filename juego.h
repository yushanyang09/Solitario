#ifndef JUEGO_H
#define JUEGO_H
#include "juego.h"
using namespace std;
enum Estado { JUGANDO, GANADOR, BLOQUEO };
// Holap
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

#endif

