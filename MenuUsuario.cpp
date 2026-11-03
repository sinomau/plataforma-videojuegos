#include <iostream>
#include <cstdlib>
#include "MenuUsuario.h"
#include "UsuarioManager.h"
#include "Utils.h"

using namespace std;

void menuUsuario(int idUsuario) {
    UsuarioManager manager;
    int opcion;

    do {
        system("cls");
        cout << "Menu Usuario" << endl;
        cout << "Opcion 1 : CARGAR SALDO" << endl;
        cout << "Opcion 2 : MIS DATOS" << endl;
        cout << "Opcion 0 : CERRAR SESION " << endl;
        cout << "Ingresa una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:
            manager.cargarSaldo(idUsuario);
            break;
        case 2:
            manager.mostrarDatos(idUsuario);
            break;
        case 0:
            return;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

        if (opcion != 0) {
            system("pause");
        }

    } while (opcion != 0);
}
