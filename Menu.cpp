#include <iostream>
#include <cstdlib>
#include "Menu.h"
#include "MenuAdmin.h"
#include "MenuUsuario.h"
#include "UsuarioManager.h"
#include "UsuarioArchivo.h"
#include "Usuario.h"
#include "Utils.h"
#include "rlutil.h"

using namespace std;


void menuInicio() {
    UsuarioManager manager;
    int opcion;

    do {
        rlutil::cls();
        mostrarTitulo("PLATAFORMA DE VIDEOJUEGOS");
        cout << "Opcion 1 : INGRESAR" << endl;
        cout << "Opcion 2 : REGISTRARSE" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingrese una opcion " << endl;
        opcion = leerEntero();
        rlutil::cls();
        switch (opcion) {
        case 1: {
            int idUsuario = manager.iniciarSesion();
            if (idUsuario != -1) {
                rlutil::anykey("Presione una tecla para continuar...\n");
                menuSegunRol(idUsuario);
            } else {
                rlutil::anykey("Presione una tecla para continuar...\n");
            }
            break;
        }
        case 2:
            manager.cargarUsuario();
            rlutil::anykey("Presione una tecla para continuar...\n");
            break;
        case 0:
            cout << "Hasta luego!" << endl;
            break;
        default:
            mostrarError("Opcion invalida.");
            rlutil::anykey("Presione una tecla para continuar...\n");
            break;
        }

    } while (opcion != 0);
}

void menuSegunRol(int idUsuario) {
    UsuarioArchivo archivo;
    Usuario reg = archivo.buscarPorId(idUsuario);

    if (reg.getRol() == ROL_ADMIN) {
        menuAdmin();
    } else {
        menuUsuario(idUsuario);
    }
}
