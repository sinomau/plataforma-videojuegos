#include <iostream>
#include "Juego.h"
#include <cstring>

using namespace std;

void Juego::setId(int id) {
    _id = id;
}

int Juego::getId() {
    return _id;
}

void Juego::setTitulo(const char* titulo) {
    strncpy(_titulo,titulo,sizeof(_titulo)-1);
    _titulo[sizeof(_titulo) - 1] = '\0';
}

const char* Juego::getTitulo() {
    return _titulo;

}

void Juego::setIdCategoria(int id) {
    _idCategoria = id;

}

int Juego::getIdCategoria() {
    return _idCategoria;

}

void Juego::setIdDesarrollador(int id) {
    _idDesarrollador = id;

};

int Juego::getIdDesarrollador() {
    return _idDesarrollador;

}


void Juego::setPrecio(float precio) {
    _precio = precio;
}

float Juego::getPrecio() {
    return _precio;

}


void Juego::setFechaLanzamiento(Fecha fecha) {
    _fechaLanzamiento = fecha;
}

Fecha Juego::getFechaLanzamiento() {
    return _fechaLanzamiento;

}



void Juego::setEstado(bool estado) {
    _estado = estado;
}

bool Juego::getEstado() {
    return _estado;

}

void Juego::cargar(int id, const char* titulo,int idCategoria,int idDesarrollador,float precio,Fecha fechaLanzamiento) {
    setId(id);
    setTitulo(titulo);
    setIdCategoria(idCategoria);
    setIdDesarrollador(idDesarrollador);
    setPrecio(precio);
    setFechaLanzamiento(fechaLanzamiento);
    setEstado(true);
}


void Juego::mostrar() {
    cout<< "Id :"<<_id << endl;
    cout<< "Titulo :"<<_titulo << endl;
    cout<< "Precio :"<<_precio << endl;
    cout<< "Fecha de lanzamiento :"; _fechaLanzamiento.mostrar();
    cout<< "Estado :";
    if(_estado == true) {
        cout<<"Activo"<<endl;
    } else {
        cout<< "Inactivo"<<endl;
    }


}


