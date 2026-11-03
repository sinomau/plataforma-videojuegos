#include <iostream>
#include <cstring>
#include "Usuario.h"

using namespace std;

void Usuario::setId(int id) {
    _id = id;
}

int Usuario::getId() {
    return _id;
}

void Usuario::setNombreUsuario(const char* nombreUsuario) {
    strncpy(_nombreUsuario, nombreUsuario, sizeof(_nombreUsuario) - 1);
    _nombreUsuario[sizeof(_nombreUsuario) - 1] = '\0';
}

const char* Usuario::getNombreUsuario() {
    return _nombreUsuario;
}

void Usuario::setContrasenia(const char* contrasenia) {
    strncpy(_contrasenia, contrasenia, sizeof(_contrasenia) - 1);
    _contrasenia[sizeof(_contrasenia) - 1] = '\0';
}

const char* Usuario::getContrasenia() {
    return _contrasenia;
}

void Usuario::setRol(int rol) {
    if (rol == ROL_ADMIN || rol == ROL_USUARIO) {
        _rol = rol;
    }
}

int Usuario::getRol() {
    return _rol;
}

void Usuario::setSaldo(float saldo) {
    if (saldo >= 0) {
        _saldo = saldo;
    }
}

float Usuario::getSaldo() {
    return _saldo;
}

void Usuario::setFechaRegistro(Fecha fecha) {
    _fechaRegistro = fecha;
}

Fecha Usuario::getFechaRegistro() {
    return _fechaRegistro;
}

void Usuario::setEstado(bool estado) {
    _estado = estado;
}

bool Usuario::getEstado() {
    return _estado;
}

void Usuario::cargar(int id, const char* nombre, const char* apellido, const char* email,
                     const char* nombreUsuario, const char* contrasenia, int rol) {
    Fecha hoy;
    hoy.setFechaActual();

    Persona::cargar(nombre, apellido, email);
    setId(id);
    setNombreUsuario(nombreUsuario);
    setContrasenia(contrasenia);
    setRol(rol);
    setSaldo(0);
    setFechaRegistro(hoy);
    setEstado(true);
}

void Usuario::mostrar() {
    cout << "Id :" << _id << endl;
    cout << "Usuario :" << _nombreUsuario << endl;
    Persona::mostrar();
    cout << "Rol :";
    if (_rol == ROL_ADMIN) {
        cout << "Administrador" << endl;
    } else {
        cout << "Usuario" << endl;
    }
    cout << "Saldo :$" << _saldo << endl;
    cout << "Fecha de registro :" << _fechaRegistro.toString() << endl;
    cout << "Estado :";
    if (_estado == true) {
        cout << "Activo" << endl;
    } else {
        cout << "Inactivo" << endl;
    }
}
