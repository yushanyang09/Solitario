#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H

#include "lista.h"
#include <cassert>
#include "memoryleaks.h"
/*
 * ste módulo sirve para almacenar la información de los usuarios con partidas comenzadas. En concreto, mantendrá una lista de punteros a pares ⟨ usuario, partidas ⟩, ordenada
de menor a mayor por identificador de usuario, para que las búsquedas por usuario sean
eficientes.
El tipo de datos ListaUsuarios se implementa como un array de punteros a ”usuarios” dinámicos, y consta, al menos, de las siguientes operaciones públicas:

 */
const int TM = 20;

struct Usuario {
	std::string user;
	ListaJuegos partidas;
};
struct ListaUsuarios {
	Usuario* usuarios[TM];
	int cont;
};

void inicializar(ListaUsuarios& lista);
void destruir(ListaUsuarios& lista);

bool insertar(ListaUsuarios& lista, std::string const& id, int& pos);
void eliminar(ListaUsuarios& lista, int pos);
bool buscar(ListaUsuarios const& lista, std::string const& buscado, int& pos);

ListaJuegos& obtener(ListaUsuarios& lista, int i);
ListaJuegos const& obtener(ListaUsuarios const& lista, int i);

int numElems(ListaUsuarios const& lista);
bool llena(ListaUsuarios const& lista);
bool cargar(ListaUsuarios& lista, std::istream&/*ent/sal*/ entrada);
void guardar(ListaUsuarios const& lista, ostream&/*ent/sal*/ salida);

#endif //LISTAORDENADA_H
