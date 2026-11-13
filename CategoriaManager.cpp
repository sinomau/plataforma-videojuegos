#include <iostream>
#include "CategoriaManager.h"
#include "CategoriaArchivo.h"
#include "Categoria.h"
#include "Utils.h"
#include <cstring>
using namespace std;



bool CategoriaManager::cargarCategoria() {
    CategoriaArchivo archivo;
    Categoria reg;

    int id = archivo.obtenerNuevoId();
    char nombre[50];
    char descripcion[200];

    cout << "Ingrese el nombre de la categoria: ";
    leerCadena(nombre, 50);
    while (strlen(nombre) == 0 || archivo.existeNombre(nombre)) {
        if (strlen(nombre) == 0) {
            cout << "El nombre no puede estar vacio. Ingrese otro: ";
        } else {
            cout << "Ese nombre ya existe. Ingrese otro: ";
        }
        leerCadena(nombre, 50);
    }

    cout << "Ingrese la descripcion de la categoria: ";
    leerCadena(descripcion, 200);

    reg.cargar(id, nombre, descripcion);
    if (archivo.escribirDisco(reg)) {
        mostrarExito("Categoria guardada correctamente.");
        return true;
    }

    mostrarError("No se pudo guardar la categoria.");
    return false;
}



void CategoriaManager::buscarPorId() {
    CategoriaArchivo archivo;

    cout << "Ingrese el ID de la categoria: ";
    int id = leerEntero();

    Categoria reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        mostrarError("No existe una categoria con ese ID.");
        return;
    }
    if (reg.getEstado() == false) {
        mostrarError("La categoria con ese ID esta dada de baja.");
        return;
    }

    reg.mostrar();
}

void CategoriaManager::mostrarCategoria() {
    CategoriaArchivo archivo;
    char nombre[50];

    cout << "Ingrese el nombre de la categoria: ";
    leerCadena(nombre, 50);

    int cantidad = archivo.getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Categoria reg = archivo.leerDisco(i);
        if (reg.getEstado() == false) {
            continue;
        }

        if (strcmp(reg.getNombre(), nombre) == 0) {
            reg.mostrar();
            return;
        }
    }

    mostrarError("No se encontro una categoria con ese nombre.");
}

bool CategoriaManager::modificarCategoria() {
    CategoriaArchivo archivo;

    cout << "Ingrese el id de la categoria a modificar" << endl;
    int id = leerEntero();
    Categoria reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        mostrarError("No existe una categoria con ese ID.");
        return false;
    }
    if (reg.getEstado() == false) {
        mostrarError("No puede modificar una categoria dada de baja.");
        return false;
    }

    char nombre[50];
    char descripcion[200];

    cout << "Ingrese el nuevo nombre: ";
    leerCadena(nombre, 50);
    while (strlen(nombre) == 0 ||
            (archivo.existeNombre(nombre) && strcmp(reg.getNombre(), nombre) != 0)) {
        if (strlen(nombre) == 0) {
            cout << "El nombre no puede estar vacio. Ingrese otro: ";
        } else {
            cout << "Ese nombre ya existe. Ingrese otro: ";
        }
        leerCadena(nombre, 50);
    }

    cout << "Ingrese la nueva descripcion: ";
    leerCadena(descripcion, 200);

    reg.setNombre(nombre);
    reg.setDescripcion(descripcion);

    if (archivo.modificarDisco(reg, id)) {
        mostrarExito("Categoria modificada correctamente.");
        return true;
    }

    mostrarError("No se pudo modificar la categoria.");
    return false;
}


bool CategoriaManager::eliminarCategoria() {
    CategoriaArchivo archivo;

    cout << "Ingrese el id de la categoria a eliminar" << endl;
    int id = leerEntero();
    Categoria reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        mostrarError("No existe una categoria con ese ID.");
        return false;
    }
    if (reg.getEstado() == false) {
        mostrarError("Esta categoria ya se encuentra eliminada.");
        return false;
    }

    reg.setEstado(false);

    if (archivo.modificarDisco(reg, id)) {
        mostrarExito("Categoria eliminada correctamente.");
        return true;
    }

    mostrarError("No se pudo eliminar la categoria.");
    return false;
}

void CategoriaManager::listarCategoria() {
    CategoriaArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();
    int mostrados = 0;

    for (int i = 0; i < cantidad; i++) {
        Categoria reg = archivo.leerDisco(i);
        if (reg.getEstado()) {
            cout << "------------------------" << endl;
            reg.mostrar();
            mostrados++;
        }
    }

    if (mostrados == 0) {
        mostrarError("No hay categorias cargadas.");
    }
}
