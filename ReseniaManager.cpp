#include <iostream>
#include <cstring>
#include "Resenia.h"
#include "ReseniaManager.h"
#include "ReseniaArchivo.h"
#include "Juego.h"
#include "JuegoArchivo.h"
#include "Usuario.h"
#include "UsuarioArchivo.h"
#include "Utils.h"
#include "Fecha.h"

using namespace std;

/**
 *
 * @param idUsuario
 * @return
 */
bool ReseniaManager::cargarResenia(int idUsuario) {
	ReseniaArchivo archivo;
	Resenia reg;
	int id = archivo.obtenerNuevoId(), idJuego, puntaje;
	char comentario[200];
	Fecha fechaResenia;
	JuegoArchivo archJuego;
	bool juegoValido = false;
	while(!juegoValido) {
		cout << "Ingrese el ID del juego: ";
		idJuego = leerEntero();
		Juego juego = archJuego.buscarPorId(idJuego);
		juegoValido = juego.getId() != -1 && juego.getEstado();
		if(!juegoValido) {
			cout << "Juego inexistente o inactivo." << endl;
			cout << "Ingrese 0 para salir u otro numero para reintentar: ";
			if(leerEntero() == 0) {
				cout << "Carga cancelada." << endl;
				return false;
			}
		}
	}
	// TODO: validar con existeCompra(idUsuario, idJuego) cuando Compra este hecha
	if(archivo.existeResenia(idUsuario, idJuego)) {
		cout << "Ya dejaste una resenia para ese juego." << endl;
		return false;
	}
	cout << "Ingrese el puntaje (1 a 5): ";
	puntaje = leerEntero();
	while(puntaje < 1 || puntaje > 5) {
		cout << "Puntaje invalido. Ingrese un puntaje entre 1 y 5: ";
		puntaje = leerEntero();
	}
	cout << "Ingrese su comentario: ";
	leerCadena(comentario, 200);
	while(strlen(comentario) == 0) {
		cout << "El comentario no puede estar vacio. Ingrese otro: ";
		leerCadena(comentario, 200);
	}
	fechaResenia.setFechaActual();
	reg.cargar(id, idUsuario, idJuego, puntaje, comentario, fechaResenia);
	if(archivo.escribirDisco(reg)) {
		cout << "Resenia cargada correctamente." << endl;
		return true;
	}
	cout << "No se pudo cargar la resenia." << endl;
	return false;
}

/**
 *
 */
void ReseniaManager::buscarPorId() {
	ReseniaArchivo archivo;
	Resenia reg;
	cout << "Ingresa el identificador de la Resenia a buscar" << endl;
	int id = leerEntero();
	reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No existe una Resenia con ese ID." << endl;
		return;
	}
	if(reg.getEstado() == false) {
		cout << "La Resenia con ese ID esta dada de baja." << endl;
		return;
	}
	reg.mostrar();
	return;
}

/// Solo el autor de la resenia puede modificarla. El juego no se cambia.
bool ReseniaManager::modificarResenia(int idUsuario) {
	ReseniaArchivo archivo;
	cout << "Ingrese el ID de la resenia a modificar: ";
	int id = leerEntero();
	Resenia reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No existe una resenia con ese ID." << endl;
		return false;
	}
	if(reg.getEstado() == false) {
		cout << "La resenia con ese ID esta dada de baja." << endl;
		return false;
	}
	if(reg.getIdUsuario() != idUsuario) {
		cout << "Solo puede modificar sus propias resenias." << endl;
		return false;
	}

	cout << "Ingrese el nuevo puntaje (1 a 5): ";
	int puntaje = leerEntero();
	while(puntaje < 1 || puntaje > 5) {
		cout << "Puntaje invalido. Ingrese un puntaje entre 1 y 5: ";
		puntaje = leerEntero();
	}

	char comentario[200];
	cout << "Ingrese el nuevo comentario: ";
	leerCadena(comentario, 200);
	while(strlen(comentario) == 0) {
		cout << "El comentario no puede estar vacio. Ingrese otro: ";
		leerCadena(comentario, 200);
	}

	Fecha fechaResenia;
	fechaResenia.setFechaActual();

	reg.setPuntaje(puntaje);
	reg.setComentario(comentario);
	reg.setFechaResenia(fechaResenia);

	if(archivo.modificarDisco(reg, id)) {
		cout << "Resenia modificada correctamente." << endl;
		return true;
	}
	cout << "No se pudo modificar la resenia." << endl;
	return false;
}

/// El usuario elimina sus propias resenias; el administrador puede eliminar cualquiera.
bool ReseniaManager::eliminarResenia(int idUsuario) {
	ReseniaArchivo archivo;
	UsuarioArchivo archUsuario;
	cout << "Ingrese el ID de la resenia a eliminar: ";
	int id = leerEntero();
	Resenia reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No existe una resenia con ese ID." << endl;
		return false;
	}
	if(reg.getEstado() == false) {
		cout << "Esta resenia ya se encuentra eliminada." << endl;
		return false;
	}
	bool esAdmin = archUsuario.buscarPorId(idUsuario).getRol() == ROL_ADMIN;
	if(!esAdmin && reg.getIdUsuario() != idUsuario) {
		cout << "Solo puede eliminar sus propias resenias." << endl;
		return false;
	}

	reg.setEstado(false);
	if(archivo.modificarDisco(reg, id)) {
		cout << "Resenia eliminada correctamente." << endl;
		return true;
	}
	cout << "No se pudo eliminar la resenia." << endl;
	return false;
}

/**
 *
 */
void ReseniaManager::listarResenias() {
	ReseniaArchivo archivo;
	Resenia reg;
	bool hayResenias = false;
	int cantidad = archivo.getCantidadRegistros();
	for(int i = 0; i < cantidad; ++i) {
		reg = archivo.leerDisco(i);
		if(reg.getEstado() == true) {
			cout << "------------------------" << endl;
			reg.mostrar();
			hayResenias = true;
		}
	}
	if(hayResenias == false) {
		cout << "No hay Resenias en el archivo" << endl;
		return;
	}
	return;
}

/// Muestra todas las resenias activas de un juego.
void ReseniaManager::mostrarReseniasJuego() {
	ReseniaArchivo archivo;
	JuegoArchivo archJuego;
	cout << "Ingrese el ID del juego: ";
	int idJuego = leerEntero();
	Juego juego = archJuego.buscarPorId(idJuego);
	if(juego.getId() == -1 || juego.getEstado() == false) {
		cout << "Juego inexistente o inactivo." << endl;
		return;
	}

	cout << "Resenias de " << juego.getTitulo() << ":" << endl;
	int cantidad = archivo.getCantidadRegistros();
	int mostradas = 0;
	for(int i = 0; i < cantidad; i++) {
		Resenia reg = archivo.leerDisco(i);
		if(reg.getEstado() && reg.getIdJuego() == idJuego) {
			cout << "------------------------" << endl;
			reg.mostrar();
			mostradas++;
		}
	}
	if(mostradas == 0) {
		cout << "Ese juego todavia no tiene resenias." << endl;
	}
}
