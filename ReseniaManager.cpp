#include <iostream>
#include <cstring>
#include "Resenia.h"
#include "ReseniaManager.h"
#include "ReseniaArchivo.h"
#include "JuegoManager.h"
#include "Usuario.h"
#include "Utils.h"
#include "Fecha.h"

using namespace std;



bool ReseniaManager::cargarResenia(int idUsuario) {
    ReseniaArchivo archivo;
    Resenia reg;

    int id = archivo.obtenerNuevoId();
    int idJuego;
    int puntaje;
    char comentario[200];
    Fecha fechaResenia;

    // Solicitar los datos de la rese¤a
    // ...
    cout << "Ingrese el ID del juego: ";
    idJuego = leerEntero();
    while(idJuego <= 0) {
        cout << "El ID del juego debe ser mayor a 0. Ingrese otro: ";
        idJuego = leerEntero();
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


    cout << "Ingrese la fecha de la resenia:" << endl;
    fechaResenia.cargar();


    reg.cargar(id, idUsuario, idJuego, puntaje, comentario, fechaResenia);

    if(archivo.escribirDisco(reg)) {
        cout << "Rese¤a cargada correctamente." << endl;
        return true;
    }

    cout << "No se pudo cargar la rese¤a." << endl;
    return false;
}

void ReseniaManager::buscarPorId() {
    ReseniaArchivo archivo;
    Resenia reg;
    cout<<"Ingresa el identificador de la Rese¤a a buscar"<<endl;
    int id = leerEntero();
    reg = archivo.buscarPorId(id);
    if(reg.getId() == -1) {
        cout << "No existe una Rese¤a con ese ID." << endl;
        return;
    }
    if(reg.getEstado() == false) {
        cout << "La Rese¤a con ese ID esta dada de baja." << endl;
        return;
    }
    reg.mostrar();

};

bool ReseniaManager::modificarResenia() {
    ReseniaArchivo archivo;
    Resenia reg;
    cout<<"Ingresa el identificador de la Rese¤a a modificar"<<endl;
    int id = leerEntero();
    reg = archivo.buscarPorId(id);
    if(reg.getId() == -1) {
        cout << "No existe una Rese¤a con ese ID." << endl;
        return false;
    }
    if(reg.getEstado() == false) {
        cout << "La Rese¤a con ese ID esta dada de baja." << endl;
        return false;
    }

    cout<<"Ingresa el juego"<<endl;
    int idJuego = leerEntero();
    cout<<"Ingresa el nuevo puntaje"<<endl;
    int puntaje = leerEntero();
    cout<<"Ingresa el nuevo comentario"<<endl;
    char comentario[200];
    leerCadena(comentario,200);
    cout<<"Ingresa la fecha de resenia"<<endl;
    Fecha fechaResenia;
    fechaResenia.cargar();

    reg.setIdJuego(idJuego);
    reg.setPuntaje(puntaje);
    reg.setComentario(comentario);
    reg.setFechaResenia(fechaResenia);

    return archivo.modificarDisco(reg, id);
};

bool ReseniaManager::eliminarResenia() {
    ReseniaArchivo archivo;
    Resenia reg;

    cout<<"Ingresa el identificador de la Rese¤a a eliminar"<<endl;
    int id = leerEntero();
    reg = archivo.buscarPorId(id);

    if(reg.getId() == -1) {
        cout << "No existe una Rese¤a con ese ID." << endl;
        return false;
    }
    if(reg.getEstado() == false) {
        cout << "La Rese¤a con ese ID esta dada de baja." << endl;
        return false;
    }

    reg.setEstado(false);
    return archivo.modificarDisco(reg, id);

};


void ReseniaManager::listarResenias() {
    ReseniaArchivo archivo;
    Resenia reg;
    bool hayResenias = false;
    int cantidad = archivo.getCantidadRegistros();
    for(int i = 0 ; i < cantidad ; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado() == true) {
            cout << "------------------------" << endl;
            reg.mostrar();

            hayResenias = true;
        }

    }
    if(hayResenias == false) {
        cout << "No hay Rese¤as en el archivo" << endl;
        return;
    }


};


void ReseniaManager::mostrarResenia() {
    ReseniaArchivo archivo;
    Resenia reg;
    cout<< "Ingrese identificador de resena" <<endl;
    int id = leerEntero();
    reg = archivo.buscarPorId(id);
    if(reg.getId() == -1) {
        cout << "No hay Rese¤as con ese identificador" << endl;
        return;
    }
    if(reg.getEstado() == false) {
        cout << "La resenia fue eliminada" << endl;
        return;
    }

    reg.mostrar();



};
