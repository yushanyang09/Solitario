#include "lista.h"

void redimensionarLista(ListaJuegos& lista,int nuevaCapacidad);

void inicializar(ListaJuegos& lista) {
	lista.capacidad = TM;
	lista.cont = 0;
	lista.datos = new Juego[TM];//el tamaño puede crecer
}
void destruir(ListaJuegos& lista) {
	delete[]lista.datos;
	lista.datos = nullptr;
	lista.cont = lista.capacidad = 0;
}

void insertar(ListaJuegos& lista, Juego& juego) {
	if (lista.cont == lista.capacidad)
		redimensionarLista(lista, lista.capacidad * 2);
	lista.datos[lista.cont] = juego;
	lista.cont++;
}

void redimensionarLista(ListaJuegos& lista,int nuevaCapacidad) {
	Juego* viejo = lista.datos;
	lista.capacidad = nuevaCapacidad;
	lista.datos = new Juego[lista.capacidad];
	for (int i = 0; i < lista.cont; i++)
		lista.datos[i] = viejo[i];
	delete[]viejo;
}
void eliminar(ListaJuegos& lista, int pos) {
	for (int i = pos; i < lista.cont-1; i++) {
		lista.datos[i] = lista.datos[i + 1];
	}
	lista.cont--;
}

Juego& obtener(ListaJuegos& lista, int i) {
	return lista.datos[i];
}

Juego const& obtener(ListaJuegos const& lista, int i) {
	return lista.datos[i];
}

int numElems(ListaJuegos const& lista) {
	return lista.cont;
}

bool esVacia(ListaJuegos const& lista) {
	return lista.cont == 0;
}

bool cargar(ListaJuegos& lista, std::istream&/*ent/sal*/ entrada) {


}
void guardar(ListaJuegos const& lista, std::ostream&/*ent/sal*/ salida) {

}