#include <iostream>
#include "MenuAdmin.h"
#include "CategoriaManager.h"
#include "DesarrolladorManager.h"
#include "JuegoManager.h"
#include "CompraManager.h"
#include "Listados.h"
#include "Consultas.h"
#include "Informes.h"
#include "Utils.h"
#include <cstdlib>

using namespace std;


void menuAdmin() {
    CompraManager compraManager;
    int opcion;

    do {
        system("cls");
        cout << "Menu Administrador" << endl;
        cout << "Opcion 1 : CATEGORIAS" << endl;
        cout << "Opcion 2 : DESARROLLADORES" << endl;
        cout << "Opcion 3 : JUEGOS" << endl;
        cout << "Opcion 4 : ANULAR COMPRA" << endl;
        cout << "Opcion 5 : LISTADOS" << endl;
        cout << "Opcion 6 : CONSULTAS" << endl;
        cout << "Opcion 7 : INFORMES" << endl;
        cout << "Opcion 0 : CERRAR SESION" << endl;
        cout << "Ingrese una opcion" << endl;

        opcion = leerEntero();

        switch (opcion) {
        case 1:
            menuCategorias();
            break;
        case 2:
            menuDesarrolladores();
            break;
        case 3:
            menuJuegos();
            break;
        case 4:
            system("cls");
            compraManager.eliminarCompra();
            system("pause");
            break;
        case 5:
            menuListados();
            break;
        case 6:
            menuConsultas();
            break;
        case 7:
            menuInformes();
            break;
        case 0:
            return;
        default:
            cout << "Opcion invalida." << endl;
            system("pause");
            break;
        }

    } while (opcion != 0);
}
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
        cout << "Ingrese una opcion " << endl;
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
            cout << "Opcion invalida." << endl;
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
        cout << "Ingrese una opcion " << endl;
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
            cout << "Opcion invalida." << endl;
            break;
        }

        if(opcion != 0){
            system("pause");
        }

    } while (opcion != 0);




}

void menuJuegos() {
    JuegoManager manager;
    int opcion;

    do {
        system("cls");
        cout << "Menu Juegos" << endl;
        cout << "Opcion 1 : CARGAR JUEGOS" << endl;
        cout << "Opcion 2 : MODIFICAR JUEGOS" << endl;
        cout << "Opcion 3 : ELIMINAR JUEGOS" << endl;
        cout << "Opcion 4 : LISTAR JUEGOS" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingrese una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:
            manager.cargarJuego();
            break;
        case 2:
            manager.modificarJuego();
            break;
        case 3:
            manager.eliminarJuego();
            break;
        case 4:
            manager.listarJuego();
            break;
        case 0:
            return;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

        if(opcion != 0){
            system("pause");
        }

    } while (opcion != 0);




}

void menuListados() {
    int opcion;
    do {
        system("cls");
        cout << "Menu Listados" << endl;
        cout << "Opcion 1 : USUARIOS ORDENADOS POR APELLIDO" << endl;
        cout << "Opcion 2 : USUARIOS ORDENADOS POR FECHA DE REGISTRO" << endl;
        cout << "Opcion 3 : JUEGOS ORDENADOS POR TITULO" << endl;
        cout << "Opcion 4 : JUEGOS ORDENADOS POR PRECIO" << endl;
        cout << "Opcion 5 : JUEGOS ORDENADOS POR FECHA DE LANZAMIENTO" << endl;
        cout << "Opcion 6 : JUEGOS ORDENADOS POR CATEGORIA" << endl;
        cout << "Opcion 7 : DESARROLLADORES ORDENADOS POR NOMBRE" << endl;
        cout << "Opcion 8 : DESARROLLADORES ORDENADOS POR FECHA DE FUNDACION" << endl;
        cout << "Opcion 9 : COMPRAS ORDENADAS POR FECHA" << endl;
        cout << "Opcion 10 : RESE¥AS ORDENADAS POR PUNTAJE" << endl;
        cout << "Opcion 11 : RESE¥AS ORDENADAS POR FECHA" << endl;
        cout << "Opcion 12 : CATEGORIAS ORDENADAS POR NOMBRE" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingrese una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:
            usuariosPorApellido();
            break;
        case 2:
            usuariosPorFechaRegistro();
            break;
        case 3:
            juegosPorTitulo();
            break;
        case 4:
            juegosPorPrecio();
            break;
        case 5:
            juegosPorFecha();
            break;
        case 6:
            juegosListadosPorCategoria();
            break;
        case 7:
            desarrolladoresPorNombre();
            break;
        case 8:
            desarrolladoresPorFecha();
            break;
        case 9:

            break;
        case 10:
            reseniasPorPuntaje();
            break;
        case 11:
            reseniasPorFecha();
            break;
        case 12:
            categoriasPorNombre();
            break;
        case 0:
            return;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

        if(opcion != 0){
            system("pause");
        }

    } while (opcion != 0);

}


void menuConsultas() {
    int opcion;
    do {
        system("cls");
        cout << "Menu Consultas" << endl;
        cout << "Opcion 1 : USUARIOS POR NOMBRE DE USUARIO" << endl;
        cout << "Opcion 2 : USUARIOS POR RANGO DE FECHAS DE REGISTRO" << endl;
        cout << "Opcion 3 : JUEGOS POR CATEGORIAS" << endl;
        cout << "Opcion 4 : JUEGOS POR DESARROLLADOR" << endl;
        cout << "Opcion 5 : JUEGOS POR RANGO DE PRECIOS" << endl;
        cout << "Opcion 6 : JUEGOS POR FECHA DE LANZAMIENTO" << endl;
        cout << "Opcion 7 : COMPRAS POR RANGO DE FECHAS" << endl;
        cout << "Opcion 8 : COMPRAS POR USUARIO" << endl;
        cout << "Opcion 9 : COMPRAS POR JUEGO" << endl;
        cout << "Opcion 10 : RESE¥AS POR JUEGO" << endl;
        cout << "Opcion 11 : RESE¥AS POR USUARIO" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingrese una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:

            break;
        case 2:

            break;
        case 3:
            juegosPorCategoria();
            break;
        case 4:
            juegosPorDesarrollador();
            break;
        case 5:
            juegosPorRangoPrecio();
            break;
        case 6:
            juegosPorFechaLanzamiento();
            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        case 10:
            reseniasPorJuego();
            break;
        case 11:
            reseniaPorUsuario();
            break;
        case 0:
            return;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

        if(opcion != 0){
            system("pause");
        }

    } while (opcion != 0);

}


void menuInformes() {
    int opcion;
    do {
        system("cls");
        cout << "Menu Informes" << endl;
        cout << "Opcion 1 : RECAUDACION POR CATEGORIAS" << endl;
        cout << "Opcion 2 : RECAUDACION POR JUEGO" << endl;
        cout << "Opcion 3 : VALORACION PROMEDIO POR JUEGO" << endl;
        cout << "Opcion 4 : RECAUDACION ANUAL" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingrese una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:
            recaudacionPorCategoria();
            break;
        case 2:
            recaudacionPorJuego();
            break;
        case 3:
            valoracionPromedioPorJuego();
            break;
        case 4:

            break;
        case 0:
            return;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

        if(opcion != 0){
            system("pause");
        }

    } while (opcion != 0);

}


