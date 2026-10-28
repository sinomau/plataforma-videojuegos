#include <iostream>
#include "CategoriaManager.h"
#include "CategoriaArchivo.h"
#include "Categoria.h"
#include "Utils.h"
#include <limits>
#include <cstring>
using namespace std;



void CategoriaManager::cargarCategoria() {
    Categoria cat;
    CategoriaArchivo archivo("categorias.dat");

    int id = archivo.obtenerNuevoId();
    char nombre[50];
    char descripcion[200];

    cout << "Ingrese el nombre de la categoria: ";
    leerCadena(nombre,50);
    while(archivo.existeNombre(nombre)) {
        cout << "Ese nombre ya existe. Ingrese otro: ";
        leerCadena(nombre,50);
    }

    cout << "Ingrese la descripcion de la categoria: ";
    leerCadena(descripcion, 200);

    cat.cargar(id, nombre, descripcion);
    archivo.escribirDisco(cat);

}



void CategoriaManager::buscarPorId() {
    CategoriaArchivo archivo("categorias.dat");
    int id;

    cout << "Ingrese el ID de la categoria: ";
    id = leerEntero();

    if (!archivo.existe(id)) {
        cout << "No existe una categoria con ese ID." << endl;
        return;
    }

    Categoria cat = archivo.buscarPorId(id);
    cat.mostrar();
}

void CategoriaManager::mostrarCategoria() {
    CategoriaArchivo archivo("categorias.dat");
    char nombre[50];

    cout << "Ingrese el nombre de la categoria: ";
    leerCadena(nombre, 50);

    int cantidad = archivo.getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Categoria cat = archivo.leerDisco(i);

        if (strcmp(cat.getNombre(), nombre) == 0) {
            cat.mostrar();
            return;
        }
    }

    cout << "No se encontro una categoria con ese nombre." << endl;
}

bool CategoriaManager::modificarCategoria() {
    // TODO: buscar la categor¡a y modificar sus datos
    CategoriaArchivo archivo("categorias.dat");

    cout << "Ingrese el id de la categoria a modificar" << endl;
    int id = leerEntero();
    if (!archivo.existe(id)) {
        cout << "No existe una categoria con ese ID." << endl;
        return false;
    }
    Categoria reg = archivo.buscarPorId(id);

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
    CategoriaArchivo archivo("categorias.dat");
    Categoria reg;
    int cantidad = archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "No hay categorias cargadas." << endl;
        return false;
    }
    int id;
    cout << "Ingresa el id de la categoria a borrar" << endl;
    id = leerEntero();
    while(!archivo.existe(id)) {
        cout << "No existe la categoria con ese id. Ingrese ID correcto" << endl;
        id = leerEntero();
    }

    reg = archivo.buscarPorId(id);
    if(reg.getEstado() == false) {
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
    CategoriaArchivo archivo("categorias.dat");
    Categoria reg;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "No hay categorias cargadas." << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado()) {
            cout << "------------------------" << endl;
            reg.mostrar();
        }


    }
}
