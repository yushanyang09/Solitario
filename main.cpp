#include <iostream>
#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
using namespace std;

// Es posible que esta función pertenezca al módulo tablero
Movimiento leerMovimiento(Juego solitario);
void leerPosicion(int &f, int &c);

//comentario
int main() {

   ifstream archivo;

   Juego solitario;
	if (cargar(solitario, archivo)) {
		mostrar(solitario); // se muestra el estado inicial
		// empezamos a jugar
		do {
			Movimiento movimiento = leerMovimiento(solitario);
			jugar(solitario, movimiento);
			mostrar(solitario);
		} while (estado(solitario) == JUGANDO);
		// mostrar resultado de la partida (ganador o bloqueo)
	}
}


