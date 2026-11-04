#include <iostream>
#include <cstring>
#include "Resenia.h"
#include "ReseniaManager.h"
#include "ReseniaArchivo.h"
#include "Juego.h"
#include "JuegoArchivo.h"
#include "Usuario.h"
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

/**
 *
 * @return
 */
bool ReseniaManager::modificarResenia() {
	ReseniaArchivo archivo;
	Resenia reg;
	cout << "Ingresa el identificador de la Resenia a modificar" << endl;
	int id = leerEntero();
	reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No existe una Resenia con ese ID." << endl;
		return false;
	}
	if(reg.getEstado() == false) {
		cout << "La Resenia con ese ID esta dada de baja." << endl;
		return false;
	}
	cout << "Ingresa el juego" << endl;
	int idJuego = leerEntero();
	cout << "Ingresa el nuevo puntaje" << endl;
	int puntaje = leerEntero();
	cout << "Ingresa el nuevo comentario" << endl;
	char comentario[200];
	leerCadena(comentario, 200);
	cout << "Ingresa la fecha de resenia" << endl;
	Fecha fechaResenia;
	fechaResenia.cargar();
	reg.setIdJuego(idJuego);
	reg.setPuntaje(puntaje);
	reg.setComentario(comentario);
	reg.setFechaResenia(fechaResenia);
	return archivo.modificarDisco(reg, id);
}

/**
 *
 * @return
 */
bool ReseniaManager::eliminarResenia() {
	ReseniaArchivo archivo;
	Resenia reg;
	cout << "Ingresa el identificador de la Resenia a eliminar" << endl;
	int id = leerEntero();
	reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No existe una Resenia con ese ID." << endl;
		return false;
	}
	if(reg.getEstado() == false) {
		cout << "La Resenia con ese ID esta dada de baja." << endl;
		return false;
	}
	reg.setEstado(false);
	return archivo.modificarDisco(reg, id);
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

/**
 *
 */
void ReseniaManager::mostrarResenia() {
	ReseniaArchivo archivo;
	Resenia reg;
	cout << "Ingrese identificador de resena" << endl;
	int id = leerEntero();
	reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No hay Resenias con ese identificador" << endl;
		return;
	}
	if(reg.getEstado() == false) {
		cout << "La resenia fue eliminada" << endl;
		return;
	}
	reg.mostrar();
	return;
}
