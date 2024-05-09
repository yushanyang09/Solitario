#include "lista.h"
#include "tablero.h"

const int TM = 20;

void redimensionarLista(ListaJuegos& lista,int nuevaCapacidad);

// Crea una lista vacía, sin elementos
void inicializar(ListaJuegos& lista) {
	lista.capacidad = TM;
	lista.cont = 0;
	lista.datos = new Juego[TM];//el tamaño puede crecer
}

// Libera la memoria utilizada por el array dinámico
void destruir(ListaJuegos& lista) {
	delete[]lista.datos;
	lista.datos = nullptr;
	lista.cont = lista.capacidad = 0;
}

// Añade el elemento elem al final de la lista, aumentando el tamaño
// del array dinámico si es necesario
void insertar(ListaJuegos& lista, Juego& juego) {
	if (lista.cont == lista.capacidad)
		redimensionarLista(lista, lista.capacidad * 2);
	lista.datos[lista.cont] = juego;
	lista.cont++;
}

// Modifica el tamaño del array dinámico
void redimensionarLista(ListaJuegos& lista,int nuevaCapacidad) {
	Juego* viejo = lista.datos;
	lista.capacidad = nuevaCapacidad;
	lista.datos = new Juego[lista.capacidad];
	for (int i = 0; i < lista.cont; i++)
		lista.datos[i] = viejo[i];
	delete[]viejo;
}

// Elimina el elemento en la posición i de la lista
void eliminar(ListaJuegos& lista, int pos) {
	for (int i = pos; i < lista.cont-1; i++) {
		lista.datos[i] = lista.datos[i + 1];
	}
	lista.cont--;
}

// Devuelve el elemento en la posición i de la lista, si existe
// Versión constante que devuelve el valor de i en referencia constante
Juego const& obtener(ListaJuegos const& lista, int i) {
	return lista.datos[i];
}

// Versión no constante que permite que i pueda ser modificada
Juego& obtener(ListaJuegos& lista, int i) {
	return lista.datos[i];
}

// Devuelve el número de elementos en la lista
int numElems(ListaJuegos const& lista) {
	return lista.cont;
}

// Devuelve cierto si la lista no tiene elementos y falso en caso contrario
bool esVacia(ListaJuegos const& lista) {
	return lista.cont == 0;
}

// Rellena la lista de juegos con la información en el flujo de entrada
//recibido como argumento
bool cargar(ListaJuegos& lista, std::istream&/*ent/sal*/ entrada) {
	int i = 0;
	bool cargado = false;
	while (i < lista.cont) {
		cargado = cargar(lista.datos[i].tablero, entrada);
		i++;
	}
	return cargado;
}

// Guarda en el flujo de salida la información en la lista de juegos con el
// formato descrito en el punto anterior
void guardar(ListaJuegos const& lista, std::ostream&/*ent/sal*/ salida) {
	int i = 0;
	while (i < lista.cont) {
		for (int j = 0; i < numFilas(lista.datos[i].tablero); i++) {
			for (int k = 0; i < numColumnas(lista.datos[i].tablero); k++)
				salida << leerCelda(lista.datos[i].tablero, j, k);
		}
		i++;
	}
}