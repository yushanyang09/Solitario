#ifndef LISTA_H
#define LISTA_H
#include "juego.h"
const int TM = 5;
struct ListaJuegos {
	Juego* datos;
	int cont;
	int capacidad;
};
void inicializar(ListaJuegos& lista);
void destruir(ListaJuegos& lista);
void insertar(ListaJuegos& lista, Juego& juego);
void eliminar(ListaJuegos& lista, int pos);
Juego& obtener(ListaJuegos& lista, int i);
Juego const& obtener(ListaJuegos const& lista, int i);
int numElems(ListaJuegos const& lista);
bool esVacia(ListaJuegos const& lista);
bool cargar(ListaJuegos& lista, std::istream&/*ent/sal*/ entrada);
void guardar(ListaJuegos const& lista, std::ostream&/*ent/sal*/ salida);

#endif // !LISTA_H

