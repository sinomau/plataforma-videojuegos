#include <iostream>
#include <cstring>
#include "Persona.h"

using namespace std;

Persona::Persona() {
    _nombre[0] = '\0';
    _apellido[0] = '\0';
    _email[0] = '\0';
}

void Persona::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

const char* Persona::getNombre() {
    return _nombre;
}

void Persona::setApellido(const char* apellido) {
    strncpy(_apellido, apellido, sizeof(_apellido) - 1);
    _apellido[sizeof(_apellido) - 1] = '\0';
}

const char* Persona::getApellido() {
    return _apellido;
}

void Persona::setEmail(const char* email) {
    strncpy(_email, email, sizeof(_email) - 1);
    _email[sizeof(_email) - 1] = '\0';
}

const char* Persona::getEmail() {
    return _email;
}

void Persona::cargar(const char* nombre, const char* apellido, const char* email) {
    setNombre(nombre);
    setApellido(apellido);
    setEmail(email);
}

void Persona::mostrar() {
    cout << "Nombre :" << _nombre << endl;
    cout << "Apellido :" << _apellido << endl;
    cout << "Email :" << _email << endl;
}
