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
    while (archivo.existeNombre(nombre)) {
        cout << "Ese nombre ya existe. Ingrese otro: ";
        leerCadena(nombre, 50);
    }

    cout << "Ingrese la descripcion de la categoria: ";
    leerCadena(descripcion, 200);

    reg.cargar(id, nombre, descripcion);
    if (archivo.escribirDisco(reg)) {
        cout << "Categoria guardada correctamente." << endl;
        return true;
    }

    cout << "No se pudo guardar la categoria." << endl;
    return false;
}



void CategoriaManager::buscarPorId() {
    CategoriaArchivo archivo;

    cout << "Ingrese el ID de la categoria: ";
    int id = leerEntero();

    Categoria reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        cout << "No existe una categoria con ese ID." << endl;
        return;
    }
    if (reg.getEstado() == false) {
        cout << "La categoria con ese ID esta dada de baja." << endl;
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

    cout << "No se encontro una categoria con ese nombre." << endl;
}

bool CategoriaManager::modificarCategoria() {
    CategoriaArchivo archivo;

    cout << "Ingrese el id de la categoria a modificar" << endl;
    int id = leerEntero();
    Categoria reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        cout << "No existe una categoria con ese ID." << endl;
        return false;
    }
    if (reg.getEstado() == false) {
        cout << "No puede modificar una categoria dada de baja." << endl;
        return false;
    }

    char nombre[50];
    char descripcion[200];

    cout << "Ingrese el nuevo nombre: ";
    leerCadena(nombre, 50);
    while (archivo.existeNombre(nombre) &&
            strcmp(reg.getNombre(), nombre) != 0) {
        cout << "Ese nombre ya existe. Ingrese otro: ";
        leerCadena(nombre, 50);
    }

    cout << "Ingrese la nueva descripcion: ";
    leerCadena(descripcion, 200);

    reg.setNombre(nombre);
    reg.setDescripcion(descripcion);

    if (archivo.modificarDisco(reg, id)) {
        cout << "Categoria modificada correctamente." << endl;
        return true;
    }

    cout << "No se pudo modificar la categoria." << endl;
    return false;
}


bool CategoriaManager::eliminarCategoria() {
    CategoriaArchivo archivo;

    cout << "Ingrese el id de la categoria a eliminar" << endl;
    int id = leerEntero();
    Categoria reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        cout << "No existe una categoria con ese ID." << endl;
        return false;
    }
    if (reg.getEstado() == false) {
        cout << "Esta categoria ya se encuentra eliminada." << endl;
        return false;
    }

    reg.setEstado(false);

    if (archivo.modificarDisco(reg, id)) {
        cout << "Categoria eliminada correctamente." << endl;
        return true;
    }

    cout << "No se pudo eliminar la categoria." << endl;
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
        cout << "No hay categorias cargadas." << endl;
    }
}
