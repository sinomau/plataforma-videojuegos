#include <iostream>
#include "Desarrollador.h"
#include <cstring>

using namespace std;

void Desarrollador::setId(int id) {
    _id = id;
}

int Desarrollador::getId() {
    return _id;
}

void Desarrollador::setNombre(const char* nombre) {
    strncpy(_nombre,nombre,sizeof(_nombre)-1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

const char* Desarrollador::getNombre() {
    return _nombre;

}

void Desarrollador::setPais(const char* pais) {
    strncpy(_pais,pais,sizeof(_pais)-1);
    _pais[sizeof(_pais) -1] = '\0';
}

const char* Desarrollador::getPais() {
    return _pais;
}

void Desarrollador::setAnioFundacion(int anio) {
    _anioFundacion = anio;
}

int Desarrollador::getAnioFundacion() {
    return _anioFundacion;
}

void Desarrollador::setEstado(bool estado) {
    _estado = estado;
}

bool Desarrollador::getEstado() {
    return _estado;

}

void Desarrollador::cargar(int id, const char* nombre,
                           const char* pais,int anio) {
    setId(id);
    setNombre(nombre);
    setPais(pais);
    setAnioFundacion(anio);
    setEstado(true);
}


void Desarrollador::mostrar() {
    cout<< "Id :"<<_id << endl;
    cout<< "Nombre :"<<_nombre << endl;
    cout<< "Pais :"<<_pais << endl;
    cout<< "Anio :"<<_anioFundacion << endl;
    cout<< "Estado :";

    if(_estado == true) {
        cout<<"Activo"<<endl;
    } else {
        cout<< "Inactivo"<<endl;
    }


}


