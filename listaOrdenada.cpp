#include "listaOrdenada.h"
#include "string"


/*
 * ste módulo sirve para almacenar la información de los usuarios con partidas comenzadas. En concreto, mantendrá una lista de punteros a pares ⟨ usuario, partidas ⟩, ordenada
de menor a mayor por identificador de usuario, para que las búsquedas por usuario sean
eficientes.
El tipo de datos ListaUsuarios se implementa como un array de punteros a ”usuarios” dinámicos, y consta, al menos, de las siguientes operaciones públicas:

 */

// crea una lista vacía, sin elementos
void inicializar(ListaUsuarios& lista) {
	lista.cont = 0;
	for (int i = 0; i < TM; i++) {
		lista.usuarios[i] = new Usuario; // Inicializa todos los punteros a usuarios como nulos
	}

}


// libera la memoria dinámica utilizada por el array
void destruir(ListaUsuarios& lista) {
	for (int i = 0; i < lista.cont; ++i) {
		delete lista.usuarios[i];
	}
	lista.cont = 0;

}

// Único procedimiento "privado" y propio del módulo listaOrdenada
void busqueda(ListaUsuarios const& lista,  std::string const& id, int inicio, int fin, int& pos) {

	// Caso base
	if (inicio > fin)
		pos = inicio; // Si no existe la ultima llamada devolverá la posición donde debería ir
	else {// Caso recursivo

		int medio = (inicio + fin) / 2;

		// Si encontramos al usuario, guardamos su posición, si no, buscamos por mitades
		if (lista.usuarios[medio]->user == id)
			pos = medio;
		else if (lista.usuarios[medio]->user < id)
			busqueda(lista, id, medio + 1, fin, pos);
		else
			busqueda(lista, id, inicio, medio - 1, pos);
	}

}

// añade un nuevo usuario con identificador user
bool insertar(ListaUsuarios& lista, std::string const& id, int& pos) {

	bool insertado = false;

	if (lista.cont < TM) {

		// Buscamos la posición en la que debemos insertar
		busqueda(lista, id, 0, lista.cont - 1, pos);

		// Desplazamos los usuarios una posición más adelante para hacer hueco
		for (int i = lista.cont; i > pos; i--) {
			lista.usuarios[i] = lista.usuarios[i - 1];
		}

		// Insertamos el nuevo usuario
		lista.usuarios[pos]->user = id;
		inicializar(lista.usuarios[pos]->partidas);
		lista.cont++;
		insertado = true;

	}

	return insertado;

}

// Elimina el elemento en la posición i de la lista
void eliminar(ListaUsuarios& lista, int pos) {

	assert(pos >= 0 && pos < lista.cont);

	delete lista.usuarios[pos];

	// Desplazamos los usuarios una posición hacia atrás para cerrar la posición vacía
	for (int i = pos; i < lista.cont - 1; i++) {
		lista.usuarios[i] = lista.usuarios[i + 1];
	}

	lista.usuarios[lista.cont-- - 1] = nullptr; // Eliminamos el puntero que quedó al final

}

// Se busca un usuario en la lista y devuelve true si lo encontró y la posición por ref
bool buscar(ListaUsuarios const& lista, std::string const& buscado, int& pos) {

	// Se busca el usuario empleando el procedimiento recursivo
	busqueda(lista, buscado, 0, lista.cont - 1, pos);

	// Si encontró el usuario pos tiene su posición, si no, pos tiene a otro user (donde debería ir ordenado)
	return lista.usuarios[pos]->user == buscado;

}

ListaJuegos& obtener(ListaUsuarios& lista, int i) {
	return lista.usuarios[i]->partidas;
}

ListaJuegos const& obtener(ListaUsuarios const& lista, int i) {
	return lista.usuarios[i]->partidas;
	
}

int numElems(ListaUsuarios const& lista) {
	return lista.cont;
}

// devuelve cierto si la lista ha llegado al tope de su capacidad y falso en caso contrario
bool llena(ListaUsuarios const& lista) {
	return lista.cont == TM;
}

// rellena la lista de pares con la información en el flujo de entrada recibido como argumento
bool cargar(ListaUsuarios& lista, std::istream&/*ent/sal*/ entrada) {
	int numUsuarios, pos;
	int numPartidas;
	bool cargado = true;
	entrada >> numUsuarios;
	std::string idUsuario;

	// Leemos a cada usuario mientras los anteriores lo hayan sido correctamente
	while (lista.cont < numUsuarios && cargado) {

		// Primero su identificador
		entrada >> idUsuario; 
		cargado = insertar(lista, idUsuario, pos);
		entrada >> numPartidas;

		// Y a continuación la información de las partidas del usuario
		if (cargado) { // (si logramos insertarlo)
			inicializar(lista.usuarios[pos]->partidas);
			while (lista.usuarios[pos]->partidas.cont < numPartidas) {
				Juego juego = lista.usuarios[pos]->partidas.datos[lista.usuarios[pos]->partidas.cont];
				cargado = cargar(juego, entrada);
				lista.usuarios[pos]->partidas.datos[lista.usuarios[pos]->partidas.cont] = juego;
				lista.usuarios[pos]->partidas.cont++;
			}
		}
		lista.cont++;
	}
	// Sera true solo si todos los usuarios han sido cargados con sus respectivas partidas
	return cargado;
}

// guarda en el flujo de salida la información en la lista de usuarios
void guardar(ListaUsuarios const& lista, std::ostream&/*ent/sal*/ salida) {

	// Primero guardamos el número de usuarios
	salida << lista.cont << '\n';

	// Y posteriormente a cada usuario con sus partidas
	for (int i = 0; i < lista.cont; ++i) {

		// Identificador del usuario
		salida << lista.usuarios[i]->user << '\n';

		// Las partidas del usuario
		salida << lista.usuarios[i]->partidas.cont << '\n';
		for (int j = 0; j < lista.usuarios[i]->partidas.cont; ++j) {
			guardar(lista.usuarios[i]->partidas.datos[j], salida);
		}
	}
}


// DUDAS: inicialiar a new o nullptr, eliminar e insertar (es correcto el assert)
// cargar: destruir si una lectura dio error?