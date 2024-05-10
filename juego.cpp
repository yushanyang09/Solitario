// YUSHAN YANG XU
// BRYAN XAVIER QUILUMBA FARINANGO

#include "juego.h"
#include "tablero.h"
#include "movimiento.h"
#include "colores.h"
#include <cstdlib>   // Para la función rand()
#include <ctime>     // Para la semilla

using namespace std;

// Privadas (las públicas son las del header)
void ejecuta_movimiento(Juego& juego, Movimiento const& mov);
void nuevo_estado(Juego& juego);
bool hay_ganador(Juego const& juego);
bool hay_movimientos(Juego const& juego);
bool movimiento_inverso(Juego& juego);
pair<int,int> selecciona_ficha_aleatoria(Juego const& juego);
void posibles_movimientos_inv(Juego const& juego, Movimiento& m);
pair<int, int> generar_dim_aleatoriamente();
bool elige_movimiento_inv(Juego const& juego, Movimiento& mov);
void ejecuta_movimiento_inv(Juego& juego, Movimiento const& mov);
void selecciona_meta_aleatoria(Juego& juego);

//Crea un juego bloqueado con un tablero vacío
void inicializa(Juego& juego) {

	Tablero tab;
	// Se bloquea el juego y se añade el tablero
	juego.estado = BLOQUEO;

	inicializa(tab);
	juego.tablero = tab;

}

// Función que da valor al juego a partir del contenido del flujo de entrada.
// Primero se construye el tablero, luego se fija la meta y se establece el estado jugando.
bool cargar(Juego&/*sal*/ juego, istream&/*ent/sal*/ entrada) {

	// Se construye el tablero
	inicializa(juego);
	bool todoCorrecto = cargar(juego.tablero, entrada);

	if (todoCorrecto) {
		// Se lee e inserta la meta
		entrada >> juego.filaMeta >> juego.colMeta;

		// Se establece el estado del juego
		juego.estado = JUGANDO;
	}

	return todoCorrecto;
}

// Función booleana en cuanto a posición correcta y con ficha
bool posicionValida(Juego const& juego, int f, int c) {

	return correcta(juego.tablero, f, c) && leerCelda(juego.tablero, f, c) == FICHA;

}

// Procedimiento que completa el movimiento con las direcciones posibles de la ficha
void posiblesMovimientos(Juego const& juego, Movimiento& mov) {
	// i = 0 -> Arriba
	// i = 1 -> Abajo
	// i = 2 -> Izquierda
	// i = 3 -> Derecha
	for (int i = 0; i < NumDir; i++) {

		if (leerCelda(juego.tablero, fila(mov) + dirs[i].first, columna(mov) + dirs[i].second) == FICHA) {
			if (leerCelda(juego.tablero, fila(mov) + dirs[i].first*2, columna(mov)+ dirs[i].second*2) == VACIA) {
				insertarDireccion(mov, Direccion(i));
			}
		}
	}

	// Si solo hubiese una dirección posible se establece como la activa
	if (numDirs(mov) == 1)
		fijarDireccionActiva(mov, direccion(mov, 0));

}

// Función que devuelve el tipo estado del juego
Estado estado(Juego const& juego) {
	return juego.estado;
}

// Modifica el juego aplicando el movimiento
void jugar(Juego& juego, Movimiento const& mov) {
  ejecuta_movimiento(juego, mov);
  mostrar(juego);
  nuevo_estado(juego);

}
// guarda en el flujo de salida la información de la partida
void guardar(Juego const& juego, std::ostream& salida) {
	// Guardamos las dimensiones del tablero
	salida << juego.tablero.numFilas << ' ' << juego.tablero.numColumnas<< '\n';

	// Guardamos el tablero
	for (int i = 0; i < juego.tablero.numFilas; ++i) {
		for (int j = 0; j < juego.tablero.numColumnas; ++j) {
			salida << juego.tablero.celdas[i][j] << ' ';
		}
		salida << '\n';
	}

}
// Procedimiento que se encarga de ejecutar un movimiento, es decir, de actualizar el contenido de las casillas afectadas
void ejecuta_movimiento(Juego& juego, Movimiento const& mov) {
	// La casilla del movimiento se vacia
	escribirCelda(juego.tablero, fila(mov), columna(mov), VACIA);
	DecrementNumFichas(juego.tablero);

	// La casilla sobre la que se salta se vacia
	escribirCelda(juego.tablero, fila(mov) + dirs[mov.dirActiva].first, columna(mov) + dirs[mov.dirActiva].second, VACIA);
	DecrementNumFichas(juego.tablero);
	// La casilla destino recibe la fichaa
	escribirCelda(juego.tablero, fila(mov) + dirs[mov.dirActiva].first * 2, columna(mov) + dirs[mov.dirActiva].second * 2, FICHA);
	IncrementNumFichas(juego.tablero);
}

// Procedimiento que se encarga de actualizar el estado del juego
void nuevo_estado(Juego& juego) {
	if (hay_ganador(juego)){
		juego.estado = GANADOR;
	}
	else if (hay_movimientos(juego)) {
		juego.estado = JUGANDO;
	}
	else {
		juego.estado = BLOQUEO;
	}
}

// Función booleana en función de la victoria del jugador, es decir, cuando solo quede una ficha y sea la meta
bool hay_ganador(Juego const& juego) {
	// Si solo quedó una ficha y es la meta el jugador ganó
	return (juego.tablero.numFichas == 1 && leerCelda(juego.tablero, juego.filaMeta, juego.colMeta) == FICHA);
	
}


// Función booleana en función de la existencia de posibles movimientos de cualquier ficha en el tablero
bool hay_movimientos(Juego const& juego) {

	bool existen = false;
	int fila = 0, columna;

	// Se recorre el tablero en búsqueda de alguna ficha con al menos un movimiento
	while (fila < numFilas(juego.tablero) && !existen) {
		columna = 0;
		while (columna < numColumnas(juego.tablero) && !existen) {
			if (leerCelda(juego.tablero, fila, columna) == FICHA ) {
				Movimiento mov = inicializa(fila, columna);
				// Calcular los posibles movimientos desde esta celda
				posiblesMovimientos(juego, mov);

				// Si hay al menos un movimiento posible
				if (numDirs(mov) > 0) {
					existen = true;
				}
			}
			columna++;
		}
		fila++;
	}

	return existen;

}
// PROCEDIMIENTOS Y FUNCIONES PARA LA GENERACIÓN INVERSA DEL TABLERO

// Procedimiento que se encarga de generar el tablero
void generar(Juego& juego, int pasos) {
	int numPasos = 0;
	bool pasoExitoso = true;
	juego.estado = JUGANDO;
	pair<int,int>dim = generar_dim_aleatoriamente();

	// Generamos el tablero con su meta aleatoria
	inicializa(juego.tablero, dim.first, dim.second, NULA);
	selecciona_meta_aleatoria(juego);
	// Mientras no hayamos realizado los pasos solicitados y sea posible realizarlos, ejecutamos movimientos
	while (numPasos <= pasos && pasoExitoso) {
		pasoExitoso = movimiento_inverso(juego);
		numPasos++;
	}
	mostrar(juego);

}

// Función booleana que ejecuta un movimiento inverso si es posible
bool movimiento_inverso(Juego& juego) {
	// Seleccionamos una ficha, buscamos sus posibles movimientos inversos y escogemos uno, de forma aleatoria
	pair<int, int>ficha= selecciona_ficha_aleatoria(juego);
	Movimiento fichActual=inicializa(ficha.first, ficha.second);
	posibles_movimientos_inv(juego, fichActual);
	bool movEncontrado = elige_movimiento_inv(juego, fichActual);

	// Devolvemos false si no se encontró ningún movimiento inverso
	if (movEncontrado) 
		ejecuta_movimiento_inv(juego, fichActual);//si se encuentra ejecutamos el movimiento

    return movEncontrado;
}

// Procedimiento que se encarga de establecer la meta del juego aleatoriamente
void selecciona_meta_aleatoria(Juego & juego) {
	juego.filaMeta = rand() % numFilas(juego.tablero);
	juego.colMeta = rand() % numColumnas(juego.tablero);
	escribirCelda(juego.tablero, juego.filaMeta, juego.colMeta, FICHA);
	IncrementNumFichas(juego.tablero);
}

// Procedimiento que se encarga de buscar una ficha en el tablero aleatoriamente
pair<int,int> selecciona_ficha_aleatoria(Juego const& juego) {

	// Variables
	int filas = numFilas(juego.tablero);
	int columnas = numColumnas(juego.tablero);
	int f, c;

	do {
		f = rand() % filas;
		c = rand() % columnas;
	} while (leerCelda(juego.tablero, f, c) != FICHA);
	
	return { f,c };
}

// Función que genera las dimensiones del tablero aleatoriamente y la devuelve
pair<int,int> generar_dim_aleatoriamente() {
	int minFilas = 4;
	int maxFilas = 6;

	int minColumnas = 4;
	int maxColumnas = 8;

	int filas = rand() % (maxFilas - minFilas + 1) + minFilas;
	int columnas = rand() % (maxColumnas - minColumnas + 1) + minColumnas;

	return { filas,columnas };
}


// Procedimiento que completa el movimiento con las direcciones posibles de la ficha
void posibles_movimientos_inv(Juego const& juego, Movimiento& mov) {
	// i = 0 -> Arriba
	// i = 1 -> Abajo
	// i = 2 -> Izquierda
	// i = 3 -> Derecha
	for (int i = 0; i < NumDir; i++) {

		// La siguiente casilla en direccion i NO debe tener una ficha
		Movimiento movAux = inicializa(fila(mov) + dirs[i].first, columna(mov) + dirs[i].second);

		if (correcta(juego.tablero, fila(movAux), columna(movAux))){
			if (leerCelda(juego.tablero, fila(movAux), columna(movAux)) != FICHA) {

				// La siguiente casilla en dirección i NO debe tener una ficha
				movAux = inicializa(fila(movAux) + dirs[i].first, columna(movAux) + dirs[i].second);

				if (correcta(juego.tablero, fila(movAux), columna(movAux))) {
					if (leerCelda(juego.tablero, fila(movAux), columna(movAux)) != FICHA)
						insertarDireccion(mov, Direccion(i));
				}
			}
		}

	}
	// Si solo hubiese una dirección posible se establece como la activa
	if (numDirs(mov))
		fijarDireccionActiva(mov, direccion(mov, 0));

}

// Función booleana que elige la direccción de un movimiento de forma aleatoria, si es que hay. Devuelve su exito o false si no había movimientos
bool elige_movimiento_inv(Juego const& juego, Movimiento& mov) {

	bool movimientos = numDirs(mov) > 0;

	if (movimientos)
		fijarDireccionActiva(mov, direccion(mov, rand() % numDirs(mov)));

	return movimientos;

}

// Procedimiento que se encarga de cambiar el estado de las celdas al ejecutar un movimiento inverso
void ejecuta_movimiento_inv(Juego& juego, Movimiento const& mov) {
	// La casilla del movimiento se vacia
	escribirCelda(juego.tablero, fila(mov), columna(mov), VACIA);
	DecrementNumFichas(juego.tablero);

	// La casilla sobre la que se salta se pone ficha
	escribirCelda(juego.tablero, fila(mov) + dirs[mov.dirActiva].first, columna(mov) + dirs[mov.dirActiva].second, FICHA);
	IncrementNumFichas(juego.tablero);

	// La casilla destino recibe la ficha
	escribirCelda(juego.tablero, fila(mov) + dirs[mov.dirActiva].first * 2, columna(mov) + dirs[mov.dirActiva].second * 2, FICHA);
	IncrementNumFichas(juego.tablero);
}