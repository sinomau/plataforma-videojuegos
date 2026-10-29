#include <iostream>
#include "MenuAdmin.h"
#include "CategoriaArchivo.h"
#include "CategoriaManager.h"
#include "DesarrolladorManager.h"
#include "Utils.h"
#include <cstdlib>

using namespace std;


void menuCategorias() {
    CategoriaManager manager;
    int opcion;

    do {
        system("cls");
        cout << "Menu Categorias" << endl;
        cout << "Opcion 1 : CARGAR CATEGORIA" << endl;
        cout << "Opcion 2 : MODIFICAR CATEGORIA" << endl;
        cout << "Opcion 3 : ELIMINAR CATEGORIA" << endl;
        cout << "Opcion 4 : LISTAR CATEGORIAS" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingresa una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:
            manager.cargarCategoria();
            break;
        case 2:
            manager.modificarCategoria();
            break;
        case 3:
            manager.eliminarCategoria();
            break;
        case 4:
            manager.listarCategoria();
            break;
        case 0:
            return;
        default:
            break;
        }

        if(opcion != 0){
            system("pause");
        }

    } while (opcion != 0);




}


void menuDesarrolladores() {
    DesarrolladorManager manager;
    int opcion;

    do {
        system("cls");
        cout << "Menu Desarrolladores" << endl;
        cout << "Opcion 1 : CARGAR DESARROLLADORES" << endl;
        cout << "Opcion 2 : MODIFICAR DESARROLLADORES" << endl;
        cout << "Opcion 3 : ELIMINAR DESARROLLADORES" << endl;
        cout << "Opcion 4 : LISTAR DESARROLLADORES" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingresa una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:
            manager.cargarDesarrollador();
            break;
        case 2:
            manager.modificarDesarrollador();
            break;
        case 3:
            manager.eliminarDesarrollador();
            break;
        case 4:
            manager.listarDesarrollador();
            break;
        case 0:
            return;
        default:
            break;
        }

        if(opcion != 0){
            system("pause");
        }

    } while (opcion != 0);




}
