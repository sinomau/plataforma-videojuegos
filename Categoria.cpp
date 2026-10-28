#include <iostream>
#include "Categoria.h"
#include <cstring>

using namespace std;

void Categoria::setId(int id) {
    _id = id;
}

int Categoria::getId() {
    return _id;
}

void Categoria::setNombre(const char* nombre) {
    strncpy(_nombre,nombre,sizeof(_nombre)-1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

const char* Categoria::getNombre() {
    return _nombre;

}

void Categoria::setDescripcion(const char* descripcion) {
    strncpy(_descripcion,descripcion,sizeof(_descripcion)-1);
    _descripcion[sizeof(_descripcion) -1] = '\0';
}

const char* Categoria::getDescripcion() {
    return _descripcion;
}


void Categoria::setEstado(bool estado) {
    _estado = estado;
}

bool Categoria::getEstado() {
    return _estado;

}

void Categoria::cargar(int id, const char* nombre,
                       const char* descripcion) {
    setId(id);
    setNombre(nombre);
    setDescripcion(descripcion);
    setEstado(true);
}


void Categoria::mostrar() {
    cout<< "Id :"<<_id << endl;
    cout<< "Nombre :"<<_nombre << endl;
    cout<< "Descripcion :"<<_descripcion << endl;
    cout<< "Estado :";
    if(_estado == true) {
        cout<<"Activo"<<endl;
    } else {
        cout<< "Inactivo"<<endl;
    }


}


