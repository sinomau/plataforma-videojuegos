#include <iostream>
#include "JuegoManager.h"
#include "JuegoArchivo.h"
#include "Juego.h"
#include "Utils.h"
#include "Fecha.h"
#include "Categoria.h"
#include "CategoriaArchivo.h"
#include "Desarrollador.h"
#include "DesarrolladorArchivo.h"
#include <cstring>

using namespace std;

/**
 *
 * @return
 */
bool JuegoManager::cargarJuego() {
	JuegoArchivo archivo;
	Juego reg;
	Fecha fechaLanzamiento;
	Categoria cat;
	CategoriaArchivo archCat;
	Desarrollador des;
	DesarrolladorArchivo archDes;
	int id = archivo.obtenerNuevoId();
	char titulo[50];
	int idCategoria = 0, idDesarrollador = 0;
	float precio = 0;
	cout << "Ingrese el titulo del Juego: ";
	leerCadena(titulo, 50);
	while(archivo.existeTitulo(titulo)) {
		cout << "Ese titulo ya existe. Ingrese otro: ";
		leerCadena(titulo, 50);
	}
	int cantidad = archCat.getCantidadRegistros();
	cout << "Categorias disponibles:" << endl;
	for(int i = 0; i < cantidad; ++i) {
		cat = archCat.leerDisco(i);
		if(cat.getEstado()) cout << cat.getId() << " - " << cat.getNombre() << endl;
	}
	bool categoriaValida = false;
	while(!categoriaValida) {
		cout << "Ingrese el ID de la categoria: ";
		idCategoria = leerEntero();
		Categoria cat = archCat.buscarPorId(idCategoria);
		categoriaValida = cat.getId() != -1 && cat.getEstado();
		if(!categoriaValida) {
			cout << "Categoria inexistente o inactiva." << endl;
			cout << "Ingrese 0 para salir u otro numero para reintentar: ";
			if(leerEntero() == 0) {
				cout << "Carga cancelada." << endl;
				return false;
			}
		}
	}
	int cantDesarrollador = archDes.getCantidadRegistros();
	cout << "Desarrolladores disponibles: " << endl;
	for(int i = 0; i < cantDesarrollador; ++i) {
		des = archDes.leerDisco(i);
		if(des.getEstado()) cout << des.getId() << " - " << des.getNombre() << endl;
	}
	bool desarrolladorValido = false;
	while(!desarrolladorValido) {
		cout << "Ingrese el ID del desarrollador: ";
		idDesarrollador = leerEntero();
		Desarrollador des = archDes.buscarPorId(idDesarrollador);
		desarrolladorValido = des.getId() != -1 && des.getEstado();
		if(!desarrolladorValido) {
			cout << "Desarrollador inexistente o inactivo." << endl;
			cout << "Ingrese 0 para salir u otro numero para reintentar: ";
			if(leerEntero() == 0) {
				cout << "Carga cancelada." << endl;
				return false;
			}
		}
	}
	cout << "Ingrese el precio del juego: ";
	precio = leerFloat();
	while(precio < 0) {
		cout << "El precio no puede ser negativo. Ingrese otro: ";
		precio = leerFloat();
	}
	cout << "Ingrese la fecha de lanzamiento: ";
	fechaLanzamiento.cargar();
	reg.cargar(id, titulo, idCategoria, idDesarrollador, precio, fechaLanzamiento);
	if(archivo.escribirDisco(reg)) {
		cout << "Juego guardado correctamente." << endl;
		return true;
	}
	cout << "No se pudo guardar el Juego." << endl;
	return false;
}

/**
 *
 */
void JuegoManager::buscarPorId() {
	JuegoArchivo archivo;
	CategoriaArchivo archCat;
	DesarrolladorArchivo archDes;
	cout << "Ingrese el ID del Juego: ";
	int id = leerEntero();
	Juego reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No existe un Juego con ese ID." << endl;
		return;
	}
	if(reg.getEstado() == false) {
		cout << "El Juego con ese ID esta dado de baja." << endl;
		return;
	}
	reg.mostrar();
	Categoria cat = archCat.buscarPorId(reg.getIdCategoria());
	cout << "Categoria: " << cat.getNombre() << endl;
	Desarrollador des = archDes.buscarPorId(reg.getIdDesarrollador());
	cout << "Desarrollador: " << des.getNombre() << endl;
	return;
}

/**
 *
 */
void JuegoManager::mostrarJuego() {
	JuegoArchivo archivo;
	CategoriaArchivo archCat;
	DesarrolladorArchivo archDes;
	char titulo[50];
	cout << "Ingrese el titulo del Juego: ";
	leerCadena(titulo, 50);
	int cantidad = archivo.getCantidadRegistros();
	for(int i = 0; i < cantidad; ++i) {
		Juego reg = archivo.leerDisco(i);
		if(reg.getEstado() == false) continue;
		if(strcmp(reg.getTitulo(), titulo) == 0) {
			reg.mostrar();
			Categoria cat = archCat.buscarPorId(reg.getIdCategoria());
			cout << "Categoria: " << cat.getNombre() << endl;
			Desarrollador des = archDes.buscarPorId(reg.getIdDesarrollador());
			cout << "Desarrollador: " << des.getNombre() << endl;
			return;
		}
	}
	cout << "No se encontro un Juego con ese titulo." << endl;
	return;
}

/**
 *
 * @return
 */
bool JuegoManager::modificarJuego() {
	Fecha fechaLanzamiento;
	JuegoArchivo archivo;
	Categoria cat;
	CategoriaArchivo archCat;
	Desarrollador des;
	DesarrolladorArchivo archDes;
	cout << "Ingrese el id del Juego a modificar" << endl;
	int id = leerEntero();
	Juego reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No existe un Juego con ese ID." << endl;
		return false;
	}
	if(reg.getEstado() == false) {
		cout << "No puede modificar un Juego dado de baja." << endl;
		return false;
	}
	char titulo[50];
	int idCategoria = 0, idDesarrollador = 0;
	float precio = 0;
	cout << "Ingrese el titulo del Juego: ";
	leerCadena(titulo, 50);
	while(archivo.existeTitulo(titulo) && strcmp(titulo, reg.getTitulo()) != 0) {
		cout << "Ese titulo ya existe. Ingrese otro: ";
		leerCadena(titulo, 50);
	}
	int cantidad = archCat.getCantidadRegistros();
	cout << "Categorias disponibles:" << endl;
	for(int i = 0; i < cantidad; ++i) {
		cat = archCat.leerDisco(i);
		if(cat.getEstado()) cout << cat.getId() << " - " << cat.getNombre() << endl;
	}
	bool categoriaValida = false;
	while(!categoriaValida) {
		cout << "Ingrese el ID de la categoria: ";
		idCategoria = leerEntero();
		Categoria cat = archCat.buscarPorId(idCategoria);
		categoriaValida = cat.getId() != -1 && cat.getEstado();
		if(!categoriaValida) {
			cout << "Categoria inexistente o inactiva." << endl;
			cout << "Ingrese 0 para salir u otro numero para reintentar: ";
			if(leerEntero() == 0) {
				cout << "Modificacion cancelada." << endl;
				return false;
			}
		}
	}
	int cantDesarrollador = archDes.getCantidadRegistros();
	cout << "Desarrolladores disponibles: " << endl;
	for(int i = 0; i < cantDesarrollador; ++i) {
		des = archDes.leerDisco(i);
		if(des.getEstado()) cout << des.getId() << " - " << des.getNombre() << endl;
	}
	bool desarrolladorValido = false;
	while(!desarrolladorValido) {
		cout << "Ingrese el ID del desarrollador: ";
		idDesarrollador = leerEntero();
		Desarrollador des = archDes.buscarPorId(idDesarrollador);
		desarrolladorValido = des.getId() != -1 && des.getEstado();
		if(!desarrolladorValido) {
			cout << "Desarrollador inexistente o inactivo." << endl;
			cout << "Ingrese 0 para salir u otro numero para reintentar: ";
			if(leerEntero() == 0) {
				cout << "Modificacion cancelada." << endl;
				return false;
			}
		}
	}
	cout << "Ingrese el precio del juego: ";
	precio = leerFloat();
	while(precio < 0) {
		cout << "El precio no puede ser negativo. Ingrese otro: ";
		precio = leerFloat();
	}
	cout << "Ingrese la fecha de lanzamiento: ";
	fechaLanzamiento.cargar();
	reg.setTitulo(titulo);
	reg.setIdCategoria(idCategoria);
	reg.setIdDesarrollador(idDesarrollador);
	reg.setPrecio(precio);
	reg.setFechaLanzamiento(fechaLanzamiento);
	if(archivo.modificarDisco(reg, id)) {
		cout << "Juego modificado correctamente." << endl;
		return true;
	}
	cout << "No se pudo modificar el Juego." << endl;
	return false;
}

/**
 *
 * @return
 */
bool JuegoManager::eliminarJuego() {
	JuegoArchivo archivo;
	cout << "Ingrese el id del Juego a eliminar" << endl;
	int id = leerEntero();
	Juego reg = archivo.buscarPorId(id);
	if(reg.getId() == -1) {
		cout << "No existe un Juego con ese ID." << endl;
		return false;
	}
	if(reg.getEstado() == false) {
		cout << "Este Juego ya se encuentra eliminado." << endl;
		return false;
	}
	reg.setEstado(false);
	if(archivo.modificarDisco(reg, id)) {
		cout << "Juego eliminado correctamente." << endl;
		return true;
	}
	cout << "No se pudo eliminar el Juego." << endl;
	return false;
}

/**
 *
 */
void JuegoManager::listarJuego() {
	JuegoArchivo archivo;
	CategoriaArchivo archCat;
	Categoria cat;
	Desarrollador des;
	DesarrolladorArchivo archDes;
	int cantidad = archivo.getCantidadRegistros(), mostrados = 0;
	for(int i = 0; i < cantidad; ++i) {
		Juego reg = archivo.leerDisco(i);
		if(reg.getEstado()) {
			cout << "------------------------" << endl;
			reg.mostrar();
			int cantCat = archCat.getCantidadRegistros();
			for(int j = 0; j < cantCat; ++j) {
				cat = archCat.leerDisco(j);
				if(reg.getIdCategoria() == cat.getId()) {
					cout << "Categoria: " << cat.getNombre() << endl;
					break;
				}
			}
			int cantDes = archDes.getCantidadRegistros();
			for(int k = 0; k < cantDes; ++k) {
				des = archDes.leerDisco(k);
				if(reg.getIdDesarrollador() == des.getId()) {
					cout << "Desarrollador: " << des.getNombre() << endl;
					break;
				}
			}
			++mostrados;
		}
	}
	if(mostrados == 0) cout << "No hay Juegos cargados." << endl;
	return;
}
