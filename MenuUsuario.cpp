#include <iostream>
#include <cstdlib>
#include "MenuUsuario.h"
#include "UsuarioManager.h"
#include "ReseniaManager.h"
#include "Utils.h"

using namespace std;

void menuUsuario(int idUsuario) {
    UsuarioManager manager;
    ReseniaManager reseniaManager;
    int opcion;

    do {
        system("cls");
        cout << "Menu Usuario" << endl;
        cout << "Opcion 1 : CARGAR SALDO" << endl;
        cout << "Opcion 2 : MIS DATOS" << endl;
        cout << "Opcion 3 : DEJAR RESENIA" << endl;
        cout << "Opcion 4 : MODIFICAR RESENIA" << endl;
        cout << "Opcion 5 : ELIMINAR RESENIA" << endl;
        cout << "Opcion 6 : VER RESENIAS DE UN JUEGO" << endl;
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
        case 3:
            reseniaManager.cargarResenia(idUsuario);
            break;
        case 4:
            reseniaManager.modificarResenia(idUsuario);
            break;
        case 5:
            reseniaManager.eliminarResenia(idUsuario);
            break;
        case 6:
            reseniaManager.mostrarReseniasJuego();
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
