#include "listaOrdenada.h"

/*
 * ste módulo sirve para almacenar la información de los usuarios con partidas comenzadas. En concreto, mantendrá una lista de punteros a pares ⟨ usuario, partidas ⟩, ordenada
de menor a mayor por identificador de usuario, para que las búsquedas por usuario sean
eficientes.
El tipo de datos ListaUsuarios se implementa como un array de punteros a ”usuarios” dinámicos, y consta, al menos, de las siguientes operaciones públicas:

 */

// crea una lista vacía, sin elementos
void inicializar(ListaUsuarios& lista) {
	lista.cont = 0;
	lista.usuarios = new[] Usuario;
	for (int i = 0; i < TM; i++) {
		lista.usuarios[i] = new[] Usuario; // Inicializa todos los punteros a usuarios como nulos
	}

}


// libera la memoria dinámica utilizada por el array
void destruir(ListaUsuarios& lista) {
	/*delete lista.usuarios;
	lista.usuarios = nullptr;*/
	lista.cont = 0;

}

// añade un nuevo usuario con identificador user
bool insertar(ListaUsuarios& lista, std::string const& id, int& pos) {

	bool insertado = false;
	pos = 0;

	if (lista.cont < 20) {

		// Buscamos la posición en la que debemos insertar
		while (pos < lista.cont && lista.usuarios[pos]->user < id)
			pos++;

		// Desplazamos los usuarios una posición más adelante para hacer hueco
		for (int i = lista.cont; i > pos; i--) {
			lista.usuarios[i] = lista.usuarios[i - 1];
		}

		// Insertamos el nuevo usuario
		lista.usuarios[pos]->user = id;
		lista.cont++;
		insertado = true;

	}

	return insertado;

}

// Elimina el elemento en la posición i de la lista
void eliminar(ListaUsuarios& lista, int pos) {

}

// Se busca un usuario en la lista y devuelve true si lo encontró y la posición por ref
bool buscar(ListaUsuarios const& lista, std::string const& buscado, int& pos) {
	return false;
}

ListaJuegos& obtener(ListaUsuarios& lista, int i) {
	return lista.usuarios[i]->partidas;
}

ListaJuegos const& obtener(ListaUsuarios const& lista, int i) {
	return lista.usuarios[i]->partidas;
}

int numElems(ListaUsuarios const& lista) {

}

bool llena(ListaUsuarios const& lista) {

}

bool cargar(ListaUsuarios& lista, std::istream&/*ent/sal*/ entrada) {

}

void guardar(ListaUsuarios const& lista, ostream&/*ent/sal*/ salida) {

}