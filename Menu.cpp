#include <iostream>
#include <cstdlib>
#include "Menu.h"
#include "MenuAdmin.h"
#include "MenuUsuario.h"
#include "UsuarioManager.h"
#include "UsuarioArchivo.h"
#include "Usuario.h"
#include "Utils.h"

using namespace std;


void menuInicio() {
    UsuarioManager manager;
    int opcion;

    do {
        system("cls");
        cout << "PLATAFORMA DE VIDEOJUEGOS" << endl;
        cout << "Opcion 1 : INGRESAR" << endl;
        cout << "Opcion 2 : REGISTRARSE" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingresa una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1: {
            int idUsuario = manager.iniciarSesion();
            if (idUsuario != -1) {
                system("pause");
                menuSegunRol(idUsuario);
            } else {
                system("pause");
            }
            break;
        }
        case 2:
            manager.cargarUsuario();
            system("pause");
            break;
        case 0:
            cout << "Hasta luego!" << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
            system("pause");
            break;
        }

    } while (opcion != 0);
}
/// Rol Usuario
void menuSegunRol(int idUsuario) {
    UsuarioArchivo archivo;
    Usuario reg = archivo.buscarPorId(idUsuario);

    if (reg.getRol() == ROL_ADMIN) {
        menuAdmin();
    } else {
        menuUsuario(idUsuario);
    }
}
