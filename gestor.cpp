#include "gestor.h"
#include <cassert>

void inicializar(Gestor& gestor) {
	gestor.usuario_activo = NOLOGIN;
	inicializar(gestor.usuarios);
}

void destruir(Gestor& gestor) {
	destruir(gestor.usuarios);
}

void login(Gestor& gestor, std::string const& usuario) {
	int pos = -1;
	if (buscar(gestor.usuarios,usuario,pos)) {
	    gestor.usuario_activo = pos;
	}
	else {
		insertar(gestor.usuarios, usuario, pos);
		gestor.usuario_activo = pos;
	}

}

void logout(Gestor& gestor) {
	assert(gestor.usuario_activo != NOLOGIN);
		if (!tienePartidas(gestor)) {
			eliminar(gestor.usuarios, gestor.usuario_activo);
			destruir(gestor.usuarios);
		}
		gestor.usuario_activo = NOLOGIN;
}

bool tienePartidas(Gestor const& gestor) {
	ListaJuegos const& partidas = obtener(gestor.usuarios, gestor.usuario_activo);
	return partidas.cont != 0;
}

void mostrarPartidas(Gestor const& gestor) {
	assert(gestor.usuario_activo != NOLOGIN);
	ListaJuegos partidas = obtener(gestor.usuarios, gestor.usuario_activo);
	std::cout << "Tus partidas empezadas: " << std::endl;
	for (int i = 0; i < partidas.cont; i++) {
		std::cout << i + 1 << " ";
		for (int j = 0; j < 20; j++) {
			std::cout << "-";
		}
		std::cout << std::endl;
		mostrar(partidas.datos[i]);
	}
}


int insertarAleatoria(Gestor& gestor, int pasos) {
	assert(gestor.usuario_activo != NOLOGIN);
	ListaJuegos& partidas = obtener(gestor.usuarios, gestor.usuario_activo);
	Juego nuevo_juego;
	generar(nuevo_juego, pasos);
	insertar(partidas, nuevo_juego);
	return partidas.cont  ;
}

Juego& partida(Gestor& gestor, int part) {
	assert(gestor.usuario_activo != NOLOGIN);
	ListaJuegos& partidas = obtener(gestor.usuarios, gestor.usuario_activo);
	assert(part >= 1 && part <= partidas.cont);
	return partidas.datos[part - 1];
}

void eliminarPartida(Gestor& gestor, int part) {
	assert(gestor.usuario_activo != NOLOGIN);
	ListaJuegos& partidas = obtener(gestor.usuarios, gestor.usuario_activo);
	assert(part >= 1 && part <= partidas.cont );
    eliminar(partidas, part - 1);
	
}
bool cargar(Gestor& gestor, std::istream&/*ent/sal*/ entrada) {
	bool cargado= cargar(gestor.usuarios, entrada);
	return cargado;
}
void guardar(Gestor const& gestor, std::ostream&/*ent/sal*/ salida) {
	guardar(gestor.usuarios, salida);
}