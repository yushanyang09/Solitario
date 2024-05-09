#ifndef GESTOR_H
#define GESTOR_H
#include "string"
#include "juego.h"
#include "listaOrdenada.h"
#include "lista.h"
#include "memoryleaks.h"

const int NOLOGIN = -1;
struct Gestor {
	int usuario_activo; // posición del usuario que ha hecho login
	ListaUsuarios usuarios;
};


void inicializar(Gestor& gestor);
void destruir(Gestor& gestor);
void login(Gestor& gestor, std::string const& usuario);
void logout(Gestor& gestor);
bool tienePartidas(Gestor const& gestor);

void mostrarPartidas(Gestor const& gestor);
int insertarAleatoria(Gestor& gestor, int pasos);
Juego& partida(Gestor& gestor, int part);
void eliminarPartida(Gestor& gestor, int part);
bool cargar(Gestor& gestor, std::istream&/*ent/sal*/ entrada);
void guardar(Gestor const& gestor, std::ostream&/*ent/sal*/ salida);


#endif
