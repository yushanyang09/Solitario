#include <iostream>
#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
using namespace std;

int main() {
   ifstream archivo;
	// pruen
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