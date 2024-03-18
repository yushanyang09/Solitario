#include "juego.h"
#include "colores.h"
#include "tablero.h"
#include <iomanip>

using namespace std;
void mostrar(Juego const& juego);
void pintaCabecera(Juego const& juego);
void pintaLinea(char esquinaIzda, char cruce, char esquinaDer, Juego const& juego);
void colorFondo(int color);
void pintaBordeCelda(int fila, Juego const& juego);
void pintaCentroCelda(int fila, Juego const& juego);

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

	// Variables
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
	nuevo_estado(juego);

}

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
void ejecuta_movimiento(Juego& juego, Movimiento const& mov) {

	// La casilla del movimiento se vacia
	escribirCelda(juego.tablero, mov.fila, mov.columna, Celda(1));

	// La casilla sobre la que se salta se vacia
	escribirCelda(juego.tablero, mov.fila + dirs[mov.dirActiva].first, mov.columna + dirs[mov.dirActiva].second, Celda(1));

	// La casilla destino recibe la fichaa
	escribirCelda(juego.tablero, mov.fila + dirs[mov.dirActiva].first * 2, mov.columna + dirs[mov.dirActiva].second * 2, Celda(2));

}

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

bool hay_ganador(Juego const& juego) {
	int num_fichas = 0;

	for (int i = 0; i < juego.tablero.numFilas; i++) {
		for (int j = 0; j < juego.tablero.numColumnas; j++) {
			if (leerCelda(juego.tablero,i,j) == FICHA) {
				num_fichas++;
			}
		}
	}
	if (num_fichas == 1) {
		if (leerCelda(juego.tablero, juego.filaMeta, juego.colMeta) == Celda(2)) {
			return true;
		}
	}
	return false;
	
}

bool hay_movimientos(Juego const& juego) {
	for (int fila = 0; fila < juego.tablero.numFilas; fila++) {
		for (int columna = 0; columna < juego.tablero.numColumnas; columna++) {
			if (leerCelda(juego.tablero, fila, columna) == Celda(2)) {
				Movimiento mov;
				mov.fila = fila;
				mov.columna = columna;
				mov.cont = 0;

				// Calcular los posibles movimientos desde esta celda
				posiblesMovimientos(juego, mov);

				// Si hay al menos un movimiento posible
				if (mov.cont > 0) {
					return true;
				}
			}
		}
	}
	return false;

}

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