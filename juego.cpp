#include "juego.h"
#include "colores.h"
#include "tablero.h"
#include <iomanip>
#include <cstdlib>   // Para la función rand()
#include <ctime>     // Para la semilla

using namespace std;

// PROTOTIPOS
void mostrar(Juego const& juego);
void pintaCabecera(Juego const& juego);
void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, Juego const& juego);
void colorFondo(int color);
void pintaBordeCelda(int fila, Juego const& juego);
void pintaCentroCelda(int fila, Juego const& juego);
void selecciona_ficha_aleatoria(Juego const& juego, int& f, int& c);
void posibles_movimientos_inv(Juego const& juego, Movimiento& m);
int generar_dim_aleatoriamente();
bool elige_movimiento_inv(Juego const& juego, Movimiento& mov);
void ejecuta_movimiento_inv(Juego& juego, Movimiento const& mov);
void selecciona_meta_aleatoria(Juego& juego);

// CONSTANTES
const char Horizontal = char(196);
const char UpperLeft = char(218);
const char UpperCross = char(194);
const char UpperRight = char(191);
const char Vertical = char(179);
const char MidLeft = char(195);
const char MidCross = char(197);
const char MidRight = char(180);
const char LowerLeft = char(192);
const char LowerCross = char(193);
const char LowerRight = char(217);
const char Square = char(219);

const int DEFAULT_COLOR = -1;

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
		movAux = inicializa(mov.fila + dirs[i].first, mov.columna + dirs[i].second);

		if (leerCelda(juego.tablero, movAux.fila, movAux.columna) == Celda(2)) {

			// La siguiente casilla en dirección i debe estar vacía
			movAux = inicializa(movAux.fila + dirs[i].first, movAux.columna + dirs[i].second);

			if (leerCelda(juego.tablero, movAux.fila, movAux.columna) == Celda(1)) {
				mov.direcciones[mov.cont] = Direccion(i);
				mov.cont++;
			}
		}
	}

	// Si solo hubiese una dirección posible se establece como la activa
	if (mov.cont == 1)
		mov.dirActiva = mov.direcciones[0];

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
	// No tiene ninguna dirección posible
	if (movPosibles.cont == 0) {
		cout << endl;
		cout << "Esa ficha no se puede mover"<<endl;
	} // Solo tiene una dirección posible
	else if (movPosibles.cont == 1) {
		ejecuta_movimiento(juego, movPosibles);
		mostrar(juego);
	} // Tiene varias opciones
	else {

		// Se solicita la direccion deseada, hasta que seleccione una valida
		do {

			cout << "Selecciona direccion:\n";
			for (int i = 1; i <= movPosibles.cont; i++) {
				cout << "\t" << i << " - " << toString(movPosibles.direcciones[i-1]) << '\n';
			}
			cin >> opcion;

			if (opcion < 1 || opcion > movPosibles.cont)
				cout << "Direccion invalida\n";
			else {
				fijarDireccionActiva(movPosibles, movPosibles.direcciones[opcion-1]);
				ejecuta_movimiento(juego, movPosibles);
				mostrar(juego);
			}

		} while (opcion < 1 || opcion > movPosibles.cont);

	}

	// Se actualiza el estado del juego
	nuevo_estado(juego);

}

// Procedimiento que se encarga de mostrar el tablero
void mostrar(Juego const& juego) {
    system("cls"); // borrar consola (clear en Linux)
	cout << RESET;

	// borde superior
	pintaCabecera(juego);
	pintaLinea(UpperLeft, UpperCross, UpperRight,juego);

	// para cada fila
	for (int fil = 0; fil < juego.tablero.numFilas; fil++) {
		if (fil == juego.filaMeta) {

		}
		// primera línea
		pintaBordeCelda(fil,juego);
		// segunda línea, con la meta posiblemente
		pintaCentroCelda(fil,juego);
		// tercera línea
		pintaBordeCelda(fil,juego);
		// separación entre filas
		if (fil <juego.tablero.numFilas - 1)
			pintaLinea(MidLeft, MidCross, MidRight,juego);
		else
			pintaLinea(LowerLeft, LowerCross, LowerRight,juego);
	}


}

// Privadas

// Procedimiento que se encarga de ejecutar un movimiento, es decir, de actualizar el contenido de las casillas afectadas
void ejecuta_movimiento(Juego& juego, Movimiento const& mov) {

	// La casilla del movimiento se vacia
	escribirCelda(juego.tablero, mov.fila, mov.columna, Celda(1));

	// La casilla sobre la que se salta se vacia
	escribirCelda(juego.tablero, mov.fila + dirs[mov.dirActiva].first, mov.columna + dirs[mov.dirActiva].second, Celda(1));

	// La casilla destino recibe la fichaa
	escribirCelda(juego.tablero, mov.fila + dirs[mov.dirActiva].first * 2, mov.columna + dirs[mov.dirActiva].second * 2, Celda(2));

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
	for (int i = 0; i < juego.tablero.numFilas; i++) {
		for (int j = 0; j < juego.tablero.numColumnas; j++) {
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
	while (fila < juego.tablero.numFilas && !existen) {

		columna = 0;
		while (columna < juego.tablero.numColumnas && !existen) {

			if (leerCelda(juego.tablero, fila, columna) == Celda(2) ) {
				mov = inicializa(fila, columna);

				// Calcular los posibles movimientos desde esta celda
				posiblesMovimientos(juego, mov);

				// Si hay al menos un movimiento posible
				if (mov.cont > 0) {
					existen = true;
				}
			}
			columna++;
		}
		fila++;
	}

	return existen;

}
// PROCEDIMIENTOS ENCARGADOS DE PINTAR EL TABLERO
void pintaCabecera(Juego const& juego) {
	cout << setw(2) << "    "; // margen inicial
	cout << setw(5) << 1;

	for (int i = 2; i <= juego.tablero.numColumnas; i++)
		cout << setw(7) << i;

	cout << '\n';
}

void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, Juego const& juego) {
	cout << "    "; // margen inicial
	cout << esquinaIzda;

	for (int i = 0; i < juego.tablero.numColumnas - 1; i++)
		cout << string(6, Horizontal) << cruce;

	cout << string(6, Horizontal) << esquinaDer << '\n';
}
void colorFondo(int color) {
	if (color == DEFAULT_COLOR)
		cout << RESET;
	else if (color == NULA)
		cout << BG_BLACK;
	else if (color == FICHA)
		cout << BG_LBLUE;
	else // color == VACIA
		cout << BG_ORANGE;
}


void pintaBordeCelda(int fila,Juego const& juego) {
	cout << "    "; // margen inicial

	for (int k = 0; k < juego.tablero.numColumnas; k++) { // cada columna
		cout << Vertical;
		colorFondo(juego.tablero.celdas[fila][k]);
		cout << "      ";
		colorFondo(DEFAULT_COLOR);
	}

	cout << Vertical << '\n'; // lateral derecho
}

void pintaCentroCelda(int fila,Juego const& juego) {
	cout << "  " << setw(2) << fila + 1; // margen inicial

	for (int k = 0; k < juego.tablero.numColumnas; k++) { // cada columna
		cout << Vertical;
		// el color de fondo depende del contenido
		colorFondo(juego.tablero.celdas[fila][k]);

		if (fila == juego.filaMeta && k == juego.colMeta) { // meta
			cout << YELLOW;
			cout << "  " << Square << Square << "  ";
		}
		else
			cout << "      ";

		colorFondo(DEFAULT_COLOR);
	}

	cout << Vertical << '\n'; // lateral derecho
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

	do {
		selecciona_ficha_aleatoria(juego, f, c);
		fichActual.columna = c;
		fichActual.fila = f;
		posibles_movimientos_inv(juego, fichActual);
		movEncontrado = elige_movimiento_inv(juego, fichActual);
	} while (!movEncontrado);

	// Devolvemos false si no se encontró ningún movimiento inverso
	if (!movEncontrado) {
		return false;
	}

    ejecuta_movimiento_inv(juego, fichActual);//si se encuentra ejecutamos el movimiento
    return true;
}

// Procedimiento que se encarga de establecer la meta del juego aleatoriamente
void selecciona_meta_aleatoria(Juego & juego) {
	juego.filaMeta = rand() % juego.tablero.numFilas;
	juego.colMeta = rand() % juego.tablero.numColumnas;
	escribirCelda(juego.tablero, juego.filaMeta, juego.colMeta, Celda(2));
}

// Procedimiento que se encarga de buscar una ficha en el tablero aleatoriamente
void selecciona_ficha_aleatoria(Juego const& juego, int& f, int& c) {

	// Variables
	int filas = juego.tablero.numFilas;
	int columnas = juego.tablero.numColumnas;

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
		movAux = inicializa(mov.fila + dirs[i].first, mov.columna + dirs[i].second);

		if (correcta(juego.tablero, movAux.fila, movAux.columna)) {
			if (leerCelda(juego.tablero, movAux.fila, movAux.columna) != Celda(2)) {

				// La siguiente casilla en dirección i NO debe tener una ficha
				movAux = inicializa(movAux.fila + dirs[i].first, movAux.columna + dirs[i].second);

				if (correcta(juego.tablero, movAux.fila, movAux.columna)) {
					if (leerCelda(juego.tablero, movAux.fila, movAux.columna) != Celda(2)) {
						mov.direcciones[mov.cont] = Direccion(i);
						mov.cont++;
					}
				}
			}
		}
	}

	// Si solo hubiese una dirección posible se establece como la activa
	if (mov.cont == 1)
		mov.dirActiva = mov.direcciones[0];

}

// Función booleana que elige la direccción de un movimiento de forma aleatoria, si es que hay. Devuelve su exito o false si no había movimientos
bool elige_movimiento_inv(Juego const& juego, Movimiento& mov) {

	// Variables
	bool movimientos = true;
	if (mov.cont > 0) {
		int dir = rand() % mov.cont;
		mov.dirActiva = mov.direcciones[dir];
	}
	else {
		movimientos = false; //no hay movimientos
	}

	return movimientos;

}

// Procedimiento que se encarga de cambiar el estado de las celdas al ejecutar un movimiento inverso
void ejecuta_movimiento_inv(Juego& juego, Movimiento const& mov) {
	// La casilla del movimiento se vacia
	escribirCelda(juego.tablero, mov.fila, mov.columna, Celda(1));

	// La casilla sobre la que se salta se pone ficha
	escribirCelda(juego.tablero, mov.fila + dirs[mov.dirActiva].first, mov.columna + dirs[mov.dirActiva].second, Celda(2));

	// La casilla destino recibe la ficha
	escribirCelda(juego.tablero, mov.fila + dirs[mov.dirActiva].first * 2, mov.columna + dirs[mov.dirActiva].second * 2, Celda(2));
}