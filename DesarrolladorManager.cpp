#include <iostream>
#include "DesarrolladorManager.h"
#include "DesarrolladorArchivo.h"
#include "Desarrollador.h"
#include "Utils.h"
#include "Fecha.h"
#include <limits>
#include <cstring>
using namespace std;



void DesarrolladorManager::cargarDesarrollador() {
    Desarrollador reg;
    DesarrolladorArchivo archivo("Desarrolladores.dat");
    Fecha anio;
    int id = archivo.obtenerNuevoId();
    char nombre[50];
    char pais[30];
    int anioFundacion;

    cout << "Ingrese el nombre del Desarrollador: ";
    leerCadena(nombre,50);
    while(archivo.existeNombre(nombre)) {
        cout << "Ese nombre ya existe. Ingrese otro: ";
        leerCadena(nombre,50);
    }

    cout << "Ingrese el pais del Desarrollador: ";
    leerCadena(pais, 30);

    cout << "Ingrese el anio de fundacion: ";
    anioFundacion = leerEntero();

    while(anioFundacion > anio.getAnioActual() || anioFundacion < 1958) {
        cout << "Ingrese un anio anterior al actual o mayor a 1958: ";
        anioFundacion = leerEntero();
    }


    reg.cargar(id, nombre, pais,anioFundacion);
    archivo.escribirDisco(reg);

}



void DesarrolladorManager::buscarPorId() {
    DesarrolladorArchivo archivo("Desarrolladores.dat");
    int id;

    cout << "Ingrese el ID del Desarrollador: ";
    id = leerEntero();

    if (!archivo.existe(id)) {
        cout << "No existe un Desarrollador con ese ID." << endl;
        return;
    }

    Desarrollador reg = archivo.buscarPorId(id);
    reg.mostrar();
}

void DesarrolladorManager::mostrarDesarrollador() {
    DesarrolladorArchivo archivo("Desarrolladores.dat");
    char nombre[50];

    cout << "Ingrese el nombre del Desarrollador: ";
    leerCadena(nombre, 50);

    int cantidad = archivo.getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Desarrollador reg = archivo.leerDisco(i);

        if (strcmp(reg.getNombre(), nombre) == 0) {
            reg.mostrar();
            return;
        }
    }

    cout << "No se encontro un Desarrollador con ese nombre." << endl;
}

bool DesarrolladorManager::modificarDesarrollador() {
    // TODO: buscar la categor¡a y modificar sus datos
    DesarrolladorArchivo archivo("Desarrolladores.dat");


    cout << "Ingrese el id del Desarrollador a modificar" << endl;
    int id = leerEntero();
    if (!archivo.existe(id)) {
        cout << "No existe un Desarrollador con ese ID." << endl;
        return false;
    }


    Desarrollador reg = archivo.buscarPorId(id);
    if(reg.getEstado() == false) {
        cout << "No puede modificar un Desarrollador eliminado" << endl;
        return false;
    }
    Fecha anio;
    char nombre[50];
    char pais[30];
    int anioFundacion;

    cout << "Ingrese el nuevo nombre: ";
    leerCadena(nombre, 50);

    while (archivo.existeNombre(nombre) &&
            strcmp(reg.getNombre(), nombre) != 0) {
        cout << "Ese nombre ya existe. Ingrese otro: ";
        leerCadena(nombre, 50);
    }

    cout << "Ingrese el nuevo pais: ";
    leerCadena(pais, 30);
    cout << "Ingrese el nuevo anio de fundacion: ";
    anioFundacion = leerEntero();
    while(anioFundacion > anio.getAnioActual() || anioFundacion < 1958) {
        cout << "Ingrese un anio anterior al actual o mayor a 1958: ";
        anioFundacion = leerEntero();
    }


    reg.setNombre(nombre);
    reg.setPais(pais);

    if (archivo.modificarDisco(reg, id)) {
        cout << "Desarrollador modificado correctamente." << endl;
        return true;
    }

    cout << "No se pudo modificar el Desarrollador." << endl;
    return false;
}


bool DesarrolladorManager::eliminarDesarrollador() {
    DesarrolladorArchivo archivo("Desarrolladores.dat");
    Desarrollador reg;
    int cantidad = archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "No hay Desarrolladores cargados." << endl;
        return false;
    }
    int id;
    cout << "Ingresa el id del Desarrollador a borrar" << endl;
    id = leerEntero();
    while(!archivo.existe(id)) {
        cout << "No existe el Desarrollador con ese id. Ingrese ID correcto" << endl;
        id = leerEntero();
    }

    reg = archivo.buscarPorId(id);
    if(reg.getEstado() == false) {
        cout << "Este Desarrollador ya se encuentra eliminado." << endl;
        return false;
    }
    reg.setEstado(false);
    if (archivo.modificarDisco(reg, id)) {
        cout << "Desarrollador eliminado correctamente." << endl;
        return true;
    }
    cout << "No se pudo eliminar el Desarrollador." << endl;
    return false;
}

void DesarrolladorManager::listarDesarrollador() {
    DesarrolladorArchivo archivo("Desarrolladores.dat");
    Desarrollador reg;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "No hay Desarrolladores cargados." << endl;
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
