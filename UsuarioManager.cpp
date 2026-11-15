#include <iostream>
#include <cstring>
#include "UsuarioManager.h"
#include "UsuarioArchivo.h"
#include "Usuario.h"
#include "Utils.h"
#include "rlutil.h"

using namespace std;


bool UsuarioManager::cargarUsuario() {
    UsuarioArchivo archivo;
    Usuario reg;

    int id = archivo.obtenerNuevoId();
    char nombre[30];
    char apellido[30];
    char email[50];
    char nombreUsuario[30];
    char contrasenia[30];
    int rol = ROL_USUARIO;

    if (archivo.getCantidadRegistros() == 0) {
        rol = ROL_ADMIN;
        cout << "Es el primer usuario del sistema: se registrara como ADMINISTRADOR." << endl;
    }

    cout << "Ingrese su nombre: ";
    leerCadena(nombre, 30);
    while (strlen(nombre) == 0) {
        cout << "El nombre no puede estar vacio. Ingrese otro: ";
        leerCadena(nombre, 30);
    }

    cout << "Ingrese su apellido: ";
    leerCadena(apellido, 30);
    while (strlen(apellido) == 0) {
        cout << "El apellido no puede estar vacio. Ingrese otro: ";
        leerCadena(apellido, 30);
    }

    cout << "Ingrese su email: ";
    leerCadena(email, 50);
    while (strchr(email, '@') == nullptr) {
        cout << "Email invalido (debe tener @). Ingrese otro: ";
        leerCadena(email, 50);
    }

    cout << "Ingrese un nombre de usuario: ";
    leerCadena(nombreUsuario, 30);
    while (strlen(nombreUsuario) == 0 || archivo.existeNombreUsuario(nombreUsuario)) {
        if (strlen(nombreUsuario) == 0) {
            cout << "El nombre de usuario no puede estar vacio. Ingrese otro: ";
        } else {
            cout << "Ese nombre de usuario ya existe. Ingrese otro: ";
        }
        leerCadena(nombreUsuario, 30);
    }

    cout << "Ingrese una contrasenia: ";
    leerCadena(contrasenia, 30);
    while (strlen(contrasenia) == 0) {
        cout << "La contrasenia no puede estar vacia. Ingrese otra: ";
        leerCadena(contrasenia, 30);
    }

    reg.cargar(id, nombre, apellido, email, nombreUsuario, contrasenia, rol);
    if (archivo.escribirDisco(reg)) {
        mostrarExito("Usuario registrado correctamente.");
        return true;
    }

    mostrarError("No se pudo registrar el usuario.");
    return false;
}


int UsuarioManager::iniciarSesion() {
    UsuarioArchivo archivo;
    char nombreUsuario[30];
    char contrasenia[30];

    if (archivo.getCantidadRegistros() == 0) {
        mostrarError("Todavia no hay usuarios registrados. Registrese primero.");
        return -1;
    }

    cout << "Usuario: ";
    leerCadena(nombreUsuario, 30);
    cout << "Contrasenia: ";
    leerCadena(contrasenia, 30);

    Usuario reg = archivo.buscarPorNombreUsuario(nombreUsuario);
    if (reg.getId() == -1 || strcmp(reg.getContrasenia(), contrasenia) != 0) {
        mostrarError("Usuario o contrasenia incorrectos.");
        return -1;
    }

    cout << "Bienvenido/a " << reg.getNombre() << "!" << endl;
    return reg.getId();
}

bool UsuarioManager::cargarSaldo(int idUsuario) {
    UsuarioArchivo archivo;
    Usuario reg = archivo.buscarPorId(idUsuario);

    if (reg.getId() == -1 || reg.getEstado() == false) {
        mostrarError("No se encontro el usuario.");
        return false;
    }

    cout << "Saldo actual: $" << reg.getSaldo() << endl;
    cout << "Ingrese el monto a cargar: ";
    float monto = leerFloat();
    while (monto <= 0) {
        cout << "El monto debe ser mayor a 0. Ingrese otro: ";
        monto = leerFloat();
    }

    reg.setSaldo(reg.getSaldo() + monto);

    if (archivo.modificarDisco(reg, idUsuario)) {
        rlutil::saveDefaultColor();
        rlutil::setColor(rlutil::LIGHTGREEN);
        cout << "Saldo cargado correctamente. Saldo nuevo: $" << reg.getSaldo() << endl;
        rlutil::resetColor();
        return true;
    }

    mostrarError("No se pudo cargar el saldo.");
    return false;
}

void UsuarioManager::mostrarDatos(int idUsuario) {
    UsuarioArchivo archivo;
    Usuario reg = archivo.buscarPorId(idUsuario);

    if (reg.getId() == -1) {
        mostrarError("No se encontro el usuario.");
        return;
    }

    reg.mostrar();
}
