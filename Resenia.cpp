#include <iostream>
#include "Resenia.h"
#include <cstring>

using namespace std;

void Resenia::setId(int id) {
    _id = id;
}


int Resenia::getId() {
    return _id;
}

void Resenia::setIdUsuario(int idUsuario) {
    _idUsuario = idUsuario;
}

int Resenia::getIdUsuario() {
    return _idUsuario;

}

void Resenia::setIdJuego(int idJuego) {
    idJuego = idJuego;
}


int Resenia::getIdJuego() {
    return _idJuego;
}


void Resenia::setPuntaje(int puntaje) {
    _puntaje = puntaje;
}


int Resenia::getPuntaje() {
    return _puntaje;
}


void Resenia::setComentario(const char* comentario) {
    strncpy(_comentario,comentario,sizeof(_comentario)-1);
    _comentario[sizeof(_comentario) - 1] = '\0';
}

const char* Resenia::getComentario() {
    return _comentario;
}


void Resenia::setFechaResenia(Fecha fechaResenia) {
    _fechaResenia = fechaResenia;
}

Fecha Resenia::getFechaResenia() {
    return _fechaResenia;

}

void Resenia::setEstado(bool estado) {
    _estado = estado;
}

bool Resenia::getEstado() {
    return _estado;
}


