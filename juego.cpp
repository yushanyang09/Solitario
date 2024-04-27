#include "juego.h"
#include "tablero.h"
#include "colores.h"
#include <cstdlib>   // Para la función rand()
#include <ctime>     // Para la semilla

using namespace std;

void selecciona_ficha_aleatoria(Juego const& juego, int& f, int& c);
void posibles_movimientos_inv(Juego const& juego, Movimiento& m);
int generar_dim_aleatoriamente();
bool elige_movimiento_inv(Juego const& juego, Movimiento& mov);
void ejecuta_movimiento_inv(Juego& juego, Movimiento const& mov);
void selecciona_meta_aleatoria(Juego& juego);


// Públicas

// Procedimiento que crea un juego bloqueado con un tablero vacío
void inicializa(Juego& juego) {

	Tablero tab;
	// Se bloquea el juego y se añade el tablero
	juego.estado = Estado(2);

	inicializa(tab);
	juego.tablero = tab;

}

// Función que da valor al juego a partir del contenido del flujo de entrada.
// Primero se construye el tablero, luego se fija la meta y se establece el estado jugando.
bool cargar(Juego&/*sal*/ juego, istream&/*ent/sal*/ entrada) {

	// Variables
	bool todoCorrecto;

	// Se construye el tablero
	todoCorrecto = cargar(juego.tablero, entrada);

	// Se lee e inserta la meta
	entrada >> juego.filaMeta >> juego.colMeta;

	// Se establece el estado del juego
	juego.estado = Estado(0);

	return todoCorrecto;
}

// Función booleana en cuanto a posición correcta y con ficha
bool posicionValida(Juego const& juego, int f, int c) {

	// Variables
	bool valida;
	Celda celda;

	// Se comprueban las dimensiones
	valida = correcta(juego.tablero, f, c);

	// Si se encuentra dentro del tablero;
	if (valida) {
		celda = leerCelda(juego.tablero, f, c);
		valida = celda == Celda(2); // Hay ficha
	}

	return valida;

}

// Procedimiento que completa el movimiento con las direcciones posibles de la ficha
void posiblesMovimientos(Juego const& juego, Movimiento& mov) {

	// Variables
	Movimiento movAux;

	// Comprobaremos cada tipo de movimiento y añadiremos los posibles
	mov.cont = 0;
	// i = 0 -> Arriba
	// i = 1 -> Abajo
	// i = 2 -> Izquierda
	// i = 3 -> Derecha
	for (int i = 0; i < NumDir; i++) {

		// La siguiente casilla en direccion i debe tener una ficha
		movAux = inicializa(fila(mov) + dirs[i].first, columna(mov) + dirs[i].second);

		if (leerCelda(juego.tablero, fila(movAux), columna(movAux)) == Celda(2)) {

			// La siguiente casilla en dirección i debe estar vacía
			movAux = inicializa(fila(movAux) + dirs[i].first, columna(movAux) + dirs[i].second);

			if (leerCelda(juego.tablero, fila(movAux), columna(movAux)) == Celda(1)) {
				insertarDireccion(mov, Direccion(i));
			}
		}
	}

	// Si solo hubiese una dirección posible se establece como la activa
	if (numDirs(mov) == 1)
		fijarDireccionActiva(mov, mov.direcciones[0]);

}

// Función que devuelve el tipo estado del juego
Estado estado(Juego const& juego) {
	return juego.estado;
}

// Modifica el juego aplicando el movimiento
void jugar(Juego& juego, Movimiento const& mov) {

	// Variables
	Movimiento movPosibles = mov;
	int opcion = 0;

	// Obtenemos las posibles direcciones que puede tomar el movimiento
	posiblesMovimientos(juego, movPosibles);

	// Casos especiales
	if (leerCelda(juego.tablero, fila(mov), columna(mov)) != Celda(2))
		cout << "\nCelda incorrecta o sin ficha\n";
	else if (numDirs(movPosibles) == 0) // No tiene ninguna dirección posible
		cout << "\nEsa ficha no se puede mover\n";
	else if (numDirs(movPosibles) == 1) { // Solo tiene una dirección posible
		ejecuta_movimiento(juego, movPosibles);
		mostrar(juego);
	} // Tiene varias opciones
	else {

		// Se solicita la direccion deseada, hasta que seleccione una valida
		do {

			cout << "Selecciona direccion:\n";
			for (int i = 1; i <= numDirs(movPosibles); i++) {
				cout << "\t" << i << " - " << toString(movPosibles.direcciones[i-1]) << '\n';
			}
			cin >> opcion;

			if (opcion < 1 || opcion > numDirs(movPosibles))
				cout << "Direccion invalida\n";
			else {
				fijarDireccionActiva(movPosibles, movPosibles.direcciones[opcion-1]);
				ejecuta_movimiento(juego, movPosibles);
				mostrar(juego);
			}

		} while (opcion < 1 || opcion > numDirs(movPosibles));

	}

	// Se actualiza el estado del juego
	nuevo_estado(juego);

}



// Privadas

// Procedimiento que se encarga de ejecutar un movimiento, es decir, de actualizar el contenido de las casillas afectadas
void ejecuta_movimiento(Juego& juego, Movimiento const& mov) {

	// La casilla del movimiento se vacia
	escribirCelda(juego.tablero, fila(mov), columna(mov), Celda(1));

	// La casilla sobre la que se salta se vacia
	escribirCelda(juego.tablero, fila(mov) + dirs[mov.dirActiva].first, columna(mov) + dirs[mov.dirActiva].second, Celda(1));

	// La casilla destino recibe la fichaa
	escribirCelda(juego.tablero, fila(mov) + dirs[mov.dirActiva].first * 2, columna(mov) + dirs[mov.dirActiva].second * 2, Celda(2));

}

// Procedimiento que se encarga de actualizar el estado del juego
void nuevo_estado(Juego& juego) {
	if (hay_ganador(juego)){
		juego.estado = Estado(1);
	}
	else if (hay_movimientos(juego)) {
		juego.estado = Estado(0);
	}
	else {
		juego.estado = Estado(2);
	}
}

// Función booleana en función de la victoria del jugador, es decir, cuando solo quede una ficha y sea la meta
bool hay_ganador(Juego const& juego) {

	// Variables
	int num_fichas = 0;
	bool victoria = false;

	// Se recorre el tablero entero en búsqueda de fichas y se cuentan
	for (int i = 0; i < numFilas(juego.tablero); i++) {
		for (int j = 0; j < numColumnas(juego.tablero); j++) {
			if (leerCelda(juego.tablero,i,j) == FICHA) {
				num_fichas++;
			}
		}
	}

	// Si solo quedó una ficha y es la meta el jugador ganó
	if (num_fichas == 1) {
		if (leerCelda(juego.tablero, juego.filaMeta, juego.colMeta) == Celda(2)) {
			victoria = true;
		}
	}

	return victoria;
	
}


// Función booleana en función de la existencia de posibles movimientos de cualquier ficha en el tablero
bool hay_movimientos(Juego const& juego) {

	// Variables
	Movimiento mov;
	bool existen = false;
	int fila = 0, columna;

	// Se recorre el tablero en búsqueda de alguna ficha con al menos un movimiento
	while (fila < numFilas(juego.tablero) && !existen) {

		columna = 0;
		while (columna < numColumnas(juego.tablero) && !existen) {

			if (leerCelda(juego.tablero, fila, columna) == Celda(2) ) {
				mov = inicializa(fila, columna);

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

	// Variables
	int numPasos = 0;
	bool pasoExitoso = true;
	int dim = generar_dim_aleatoriamente();

	// Generamos el tablero con su meta aleatoria
	inicializa(juego.tablero, dim, dim, Celda(0));
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

	// Variables
	Movimiento mov;
	int f, c;
	bool movEncontrado = false;
	Movimiento fichActual;

	// Seleccionamos una ficha, buscamos sus posibles movimientos inversos y escogemos uno, de forma aleatoria
	selecciona_ficha_aleatoria(juego, f, c);
	fichActual.columna = c;
	fichActual.fila = f;
	posibles_movimientos_inv(juego, fichActual);
	movEncontrado = elige_movimiento_inv(juego, fichActual);

	// Devolvemos false si no se encontró ningún movimiento inverso
	if (movEncontrado)
		ejecuta_movimiento_inv(juego, fichActual);//si se encuentra ejecutamos el movimiento

    return movEncontrado;
}

// Procedimiento que se encarga de establecer la meta del juego aleatoriamente
void selecciona_meta_aleatoria(Juego & juego) {
	juego.filaMeta = rand() % numFilas(juego.tablero);
	juego.colMeta = rand() % numColumnas(juego.tablero);
	escribirCelda(juego.tablero, juego.filaMeta, juego.colMeta, Celda(2));
}

// Procedimiento que se encarga de buscar una ficha en el tablero aleatoriamente
void selecciona_ficha_aleatoria(Juego const& juego, int& f, int& c) {

	// Variables
	int filas = numFilas(juego.tablero);
	int columnas = numColumnas(juego.tablero);

	// Buscamos una ficha
	do {
		f = rand() % filas;
		c = rand() % columnas;
	} while (leerCelda(juego.tablero, f, c) != Celda(2));

}

// Función que genera las dimensiones del tablero aleatoriamente y la devuelve
int generar_dim_aleatoriamente() {

	// Variables
	int min = 4;
	int max = 9;
	int dimension;

	// Generar un número aleatorio [4, 6]
	dimension = rand() % (max - min + 1) + min;

	return dimension;
}


// Procedimiento que completa el movimiento con las direcciones posibles de la ficha
void posibles_movimientos_inv(Juego const& juego, Movimiento& mov) {

	// Variables
	Movimiento movAux;
	mov.cont = 0;

	// i = 0 -> Arriba
	// i = 1 -> Abajo
	// i = 2 -> Izquierda
	// i = 3 -> Derecha
	for (int i = 0; i < NumDir; i++) {

		// La siguiente casilla en direccion i NO debe tener una ficha
		movAux = inicializa(fila(mov) + dirs[i].first, columna(mov) + dirs[i].second);

		if (correcta(juego.tablero, fila(movAux), columna(movAux))) {
			if (leerCelda(juego.tablero, fila(movAux), columna(movAux)) != Celda(2)) {

				// La siguiente casilla en dirección i NO debe tener una ficha
				movAux = inicializa(fila(movAux) + dirs[i].first, columna(movAux) + dirs[i].second);

				if (correcta(juego.tablero, fila(movAux), columna(movAux))) {
					if (leerCelda(juego.tablero, fila(movAux), columna(movAux)) != Celda(2)) {
						insertarDireccion(mov, Direccion(i));
					}
				}
			}
		}
	}

	// Si solo hubiese una dirección posible se establece como la activa
	if (numDirs(mov))
		fijarDireccionActiva(mov, mov.direcciones[0]);

}

// Función booleana que elige la direccción de un movimiento de forma aleatoria, si es que hay. Devuelve su exito o false si no había movimientos
bool elige_movimiento_inv(Juego const& juego, Movimiento& mov) {

	// Variables
	bool movimientos = true;
	if (numDirs(mov) > 0) {
		int dir = rand() % numDirs(mov);
		fijarDireccionActiva(mov, mov.direcciones[dir]);
	}
	else {
		movimientos = false; //no hay movimientos
	}

	return movimientos;

}

// Procedimiento que se encarga de cambiar el estado de las celdas al ejecutar un movimiento inverso
void ejecuta_movimiento_inv(Juego& juego, Movimiento const& mov) {
	// La casilla del movimiento se vacia
	escribirCelda(juego.tablero, fila(mov), columna(mov), Celda(1));

	// La casilla sobre la que se salta se pone ficha
	escribirCelda(juego.tablero, fila(mov) + dirs[mov.dirActiva].first, columna(mov) + dirs[mov.dirActiva].second, Celda(2));

	// La casilla destino recibe la ficha
	escribirCelda(juego.tablero, fila(mov) + dirs[mov.dirActiva].first * 2, columna(mov) + dirs[mov.dirActiva].second * 2, Celda(2));
}