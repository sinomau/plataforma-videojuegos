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
    int idCategoria = 0;
    int idDesarrollador = 0;
    float precio = 0;


    cout << "Ingrese el titulo del Juego: ";
    leerCadena(titulo, 50);
    while (archivo.existeTitulo(titulo)) {
        cout << "Ese titulo ya existe. Ingrese otro: ";
        leerCadena(titulo, 50);
    }


    int cantidad = archCat.getCantidadRegistros();

    cout << "Categorias disponibles:" << endl;

    for (int i = 0; i < cantidad; i++) {
        cat = archCat.leerDisco(i);

        if (cat.getEstado()) {
            cout << cat.getId() << " - " << cat.getNombre() << endl;
        }
    }

    bool categoriaValida = false;

    while (!categoriaValida) {
        cout << "Ingrese el ID de la categoria: ";
        idCategoria = leerEntero();

        for (int i = 0; i < cantidad; i++) {
            cat = archCat.leerDisco(i);

            if (cat.getId() == idCategoria && cat.getEstado()) {
                categoriaValida = true;
                break;
            }
        }

        if (!categoriaValida) {
            cout << "Categoria inexistente o inactiva. Intente nuevamente." << endl;
        }
    }


    int cantDesarrollador = archDes.getCantidadRegistros();
    cout << "Desarrolladores disponibles: "<<endl;
    for(int i = 0; i < cantDesarrollador ; i++) {
        des = archDes.leerDisco(i);
        if(des.getEstado()) {
            cout << des.getId() << " - " <<des.getNombre() << endl;

        }

    }

    bool desarrolladorValido = false;
    while(!desarrolladorValido) {
        cout << "Ingrese el ID del desarrollador: ";
        idDesarrollador = leerEntero();


        for(int i = 0 ; i< cantDesarrollador ; i++) {
            des = archDes.leerDisco(i);
            if(des.getId() == idDesarrollador && des.getEstado()) {
                desarrolladorValido = true;
                break;
            }
        }
        if (!desarrolladorValido) {
            cout << "Desarrollador inexistente o inactiva. Intente nuevamente." << endl;
        }
    }

    cout << "Ingrese el precio del  juego : ";
    precio = leerFloat();

    cout << "Ingrese la fecha de lanzamiento: ";
    fechaLanzamiento.cargar();

    reg.cargar(id, titulo, idCategoria, idDesarrollador,precio,fechaLanzamiento);
    if (archivo.escribirDisco(reg)) {
        cout << "Juego guardado correctamente." << endl;
        return true;
    }

    cout << "No se pudo guardar el Juego." << endl;
    return false;
}



void JuegoManager::buscarPorId() {
    JuegoArchivo archivo;

    cout << "Ingrese el ID del Juego: ";
    int id = leerEntero();

    Juego reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        cout << "No existe un Juego con ese ID." << endl;
        return;
    }
    if (reg.getEstado() == false) {
        cout << "El Juego con ese ID esta dado de baja." << endl;
        return;
    }

    reg.mostrar();
}

void JuegoManager::mostrarJuego() {
    JuegoArchivo archivo;
    char titulo[50];

    cout << "Ingrese el nombre del Juego: ";
    leerCadena(titulo, 50);

    int cantidad = archivo.getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Juego reg = archivo.leerDisco(i);
        if (reg.getEstado() == false) {
            continue;
        }

        if (strcmp(reg.getTitulo(), titulo) == 0) {
            reg.mostrar();
            return;
        }
    }

    cout << "No se encontro un Juego con ese nombre." << endl;
}

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
    if (reg.getId() == -1) {
        cout << "No existe un Juego con ese ID." << endl;
        return false;
    }
    if (reg.getEstado() == false) {
        cout << "No puede modificar un Juego dado de baja." << endl;
        return false;
    }


    char titulo[50];
    int idCategoria = 0;
    int idDesarrollador = 0;
    float precio = 0;

    cout << "Ingrese el titulo del Juego: ";
    leerCadena(titulo, 50);
    while (archivo.existeTitulo(titulo) &&
            strcmp(titulo, reg.getTitulo()) != 0) {

        cout << "Ese titulo ya existe. Ingrese otro: ";
        leerCadena(titulo, 50);
    }

    int cantidad = archCat.getCantidadRegistros();

    cout << "Categorias disponibles:" << endl;

    for (int i = 0; i < cantidad; i++) {
        cat = archCat.leerDisco(i);

        if (cat.getEstado()) {
            cout << cat.getId() << " - " << cat.getNombre() << endl;
        }
    }

    bool categoriaValida = false;

    while (!categoriaValida) {
        cout << "Ingrese el ID de la categoria: ";
        idCategoria = leerEntero();

        for (int i = 0; i < cantidad; i++) {
            cat = archCat.leerDisco(i);

            if (cat.getId() == idCategoria && cat.getEstado()) {
                categoriaValida = true;
                break;
            }
        }

        if (!categoriaValida) {
            cout << "Categoria inexistente o inactiva. Intente nuevamente." << endl;
        }
    }

    int cantDesarrollador = archDes.getCantidadRegistros();
    cout << "Desarrolladores disponibles: "<<endl;
    for(int i = 0; i < cantDesarrollador ; i++) {
        des = archDes.leerDisco(i);
        if(des.getEstado()) {
            cout << des.getId() << " - " <<des.getNombre() << endl;

        }

    }

    bool desarrolladorValido = false;
    while(!desarrolladorValido) {
        cout << "Ingrese el ID del desarrollador: ";
        idDesarrollador = leerEntero();


        for(int i = 0 ; i< cantDesarrollador ; i++) {
            des = archDes.leerDisco(i);
            if(des.getId() == idDesarrollador && des.getEstado()) {
                desarrolladorValido = true;
                break;
            }
        }
        if (!desarrolladorValido) {
            cout << "Desarrollador inexistente o inactiva. Intente nuevamente." << endl;
        }
    }

    cout << "Ingrese el precio del  juego : ";
    precio = leerFloat();

    cout << "Ingrese la fecha de lanzamiento: ";
    fechaLanzamiento.cargar();

    reg.setTitulo(titulo);
    reg.setIdCategoria(idCategoria);
    reg.setIdDesarrollador(idDesarrollador);
    reg.setPrecio(precio);
    reg.setFechaLanzamiento(fechaLanzamiento);


    if (archivo.modificarDisco(reg, id)) {
        cout << "Juego modificado correctamente." << endl;
        return true;
    }

    cout << "No se pudo modificar el Juego." << endl;
    return false;
}


bool JuegoManager::eliminarJuego() {
    JuegoArchivo archivo;

    cout << "Ingrese el id del Juego a eliminar" << endl;
    int id = leerEntero();
    Juego reg = archivo.buscarPorId(id);
    if (reg.getId() == -1) {
        cout << "No existe un Juego con ese ID." << endl;
        return false;
    }
    if (reg.getEstado() == false) {
        cout << "Este Juego ya se encuentra eliminado." << endl;
        return false;
    }

    reg.setEstado(false);

    if (archivo.modificarDisco(reg, id)) {
        cout << "Juego eliminado correctamente." << endl;
        return true;
    }

    cout << "No se pudo eliminar el Juego." << endl;
    return false;
}

void JuegoManager::listarJuego() {
    JuegoArchivo archivo;
    CategoriaArchivo archCat;
    Categoria cat;
    Desarrollador des;
    DesarrolladorArchivo archDes;
    int cantidad = archivo.getCantidadRegistros();
    int mostrados = 0;

    for (int i = 0; i < cantidad; i++) {
        Juego reg = archivo.leerDisco(i);
        if (reg.getEstado()) {
            cout << "------------------------" << endl;
            reg.mostrar();
            int cantCat = archCat.getCantidadRegistros();
            for(int j = 0; j < cantCat ; j++) {
                cat = archCat.leerDisco(j);
                if(reg.getIdCategoria() == cat.getId()) {
                    cout << "Categoria: " << cat.getNombre() << endl;
                    break;
                }

            }
            int cantDes = archDes.getCantidadRegistros();
            for(int k = 0; k<cantDes ; k++) {
                des = archDes.leerDisco(k);

                if(reg.getIdDesarrollador() == des.getId()) {
                    cout << "Desarrollador: " << des.getNombre() << endl;
                    break;
                }

            }

            mostrados++;
        }
    }

    if (mostrados == 0) {
        cout << "No hay Juegos cargados." << endl;
    }
}
