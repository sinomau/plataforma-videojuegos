#include <iostream>
#include "DesarrolladorManager.h"
#include "DesarrolladorArchivo.h"
#include "Desarrollador.h"
#include "Utils.h"
#include "Fecha.h"
#include <cstring>
using namespace std;



bool DesarrolladorManager::cargarDesarrollador() {
    DesarrolladorArchivo archivo;
    Desarrollador reg;
    Fecha anio;
    const int ANIOMINIMO = 1958;

    int id = archivo.obtenerNuevoId();
    char nombre[50];
    char pais[30];
    int anioFundacion;

    cout << "Ingrese el nombre del Desarrollador: ";
    leerCadena(nombre, 50);
    while (strlen(nombre) == 0 || archivo.existeNombre(nombre)) {
        if (strlen(nombre) == 0) {
            cout << "El nombre no puede estar vacio. Ingrese otro: ";
        } else {
            cout << "Ese nombre ya existe. Ingrese otro: ";
        }
        leerCadena(nombre, 50);
    }

    cout << "Ingrese el pais del Desarrollador: ";
    leerCadena(pais, 30);
    while (strlen(pais) == 0) {
        cout << "El pais no puede estar vacio. Ingrese otro: ";
        leerCadena(pais, 30);
    }

    cout << "Ingrese el anio de fundacion: ";
    anioFundacion = leerEntero();
    while (anioFundacion > anio.getAnioActual() || anioFundacion < ANIOMINIMO) {
        cout << "Ingrese un anio menor o igual al actual y mayor 1958: ";
        anioFundacion = leerEntero();
    }

    reg.cargar(id, nombre, pais, anioFundacion);
    if (archivo.escribirDisco(reg)) {
        mostrarExito("Desarrollador guardado correctamente.");
        return true;
    }

    mostrarError("No se pudo guardar el Desarrollador.");
    return false;
}



void DesarrolladorManager::buscarPorId() {
    DesarrolladorArchivo archivo;

    cout << "Ingrese el ID del Desarrollador: ";
    int id = leerEntero();

    Desarrollador reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        mostrarError("No existe un Desarrollador con ese ID.");
        return;
    }
    if (reg.getEstado() == false) {
        mostrarError("El Desarrollador con ese ID esta dado de baja.");
        return;
    }

    reg.mostrar();
}

void DesarrolladorManager::mostrarDesarrollador() {
    DesarrolladorArchivo archivo;
    char nombre[50];

    cout << "Ingrese el nombre del Desarrollador: ";
    leerCadena(nombre, 50);

    int cantidad = archivo.getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Desarrollador reg = archivo.leerDisco(i);
        if (reg.getEstado() == false) {
            continue;
        }

        if (strcmp(reg.getNombre(), nombre) == 0) {
            reg.mostrar();
            return;
        }
    }

    mostrarError("No se encontro un Desarrollador con ese nombre.");
}

bool DesarrolladorManager::modificarDesarrollador() {
    DesarrolladorArchivo archivo;

    cout << "Ingrese el id del Desarrollador a modificar" << endl;
    int id = leerEntero();
    Desarrollador reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        mostrarError("No existe un Desarrollador con ese ID.");
        return false;
    }
    if (reg.getEstado() == false) {
        mostrarError("No puede modificar un Desarrollador dado de baja.");
        return false;
    }

    Fecha anio;
    const int ANIOMINIMO = 1958;
    char nombre[50];
    char pais[30];
    int anioFundacion;

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

    cout << "Ingrese el nuevo pais: ";
    leerCadena(pais, 30);
    while (strlen(pais) == 0) {
        cout << "El pais no puede estar vacio. Ingrese otro: ";
        leerCadena(pais, 30);
    }

    cout << "Ingrese el nuevo anio de fundacion: ";
    anioFundacion = leerEntero();
    while (anioFundacion > anio.getAnioActual() || anioFundacion < ANIOMINIMO) {
        cout << "Ingrese un anio menor o igual al actual y mayor 1958: ";
        anioFundacion = leerEntero();
    }

    reg.setNombre(nombre);
    reg.setPais(pais);
    reg.setAnioFundacion(anioFundacion);

    if (archivo.modificarDisco(reg, id)) {
        mostrarExito("Desarrollador modificado correctamente.");
        return true;
    }

    mostrarError("No se pudo modificar el Desarrollador.");
    return false;
}


bool DesarrolladorManager::eliminarDesarrollador() {
    DesarrolladorArchivo archivo;

    cout << "Ingrese el id del Desarrollador a eliminar" << endl;
    int id = leerEntero();
    Desarrollador reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        mostrarError("No existe un Desarrollador con ese ID.");
        return false;
    }
    if (reg.getEstado() == false) {
        mostrarError("Este Desarrollador ya se encuentra eliminado.");
        return false;
    }

    reg.setEstado(false);

    if (archivo.modificarDisco(reg, id)) {
        mostrarExito("Desarrollador eliminado correctamente.");
        return true;
    }

    mostrarError("No se pudo eliminar el Desarrollador.");
    return false;
}

void DesarrolladorManager::listarDesarrollador() {
    DesarrolladorArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();
    int mostrados = 0;

    for (int i = 0; i < cantidad; i++) {
        Desarrollador reg = archivo.leerDisco(i);
        if (reg.getEstado()) {
            cout << "------------------------" << endl;
            reg.mostrar();
            mostrados++;
        }
    }

    if (mostrados == 0) {
        mostrarError("No hay Desarrolladores cargados.");
    }
}
