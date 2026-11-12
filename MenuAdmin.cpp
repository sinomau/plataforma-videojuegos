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
        cout << "Ingresa una opcion" << endl;

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
        cout << "Ingresa una opcion " << endl;
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
        cout << "Opcion 1 : JUEGOS POR ORDENADOS POR TITULO" << endl;
        cout << "Opcion 2 : JUEGOS POR ORDENADOS POR PRECIO" << endl;
        cout << "Opcion 3 : JUEGOS POR ORDENADOS POR FECHA DE LANZAMIENTO" << endl;
        cout << "Opcion 4 : JUEGOS POR ORDENADOS POR CATEGORIA" << endl;
        cout << "Opcion 5 : DESARROLLADORES ORDENADOS POR NOMBRE" << endl;
        cout << "Opcion 6 : DESARROLLADORES ORDENADOS POR FECHA DE FUNDACION" << endl;
        cout << "Opcion 7 : RESEÃ‘AS ORDENADAS POR PUNTAJE" << endl;
        cout << "Opcion 8 : RESEÃ‘AS ORDENADAS POR FECHA" << endl;
        cout << "Opcion 9 : CATEGORIAS ORDENADAS POR NOMBRE" << endl;
        cout << "Opcion 10 : USUARIOS ORDENADOS POR APELLIDO" << endl;
        cout << "Opcion 11 : USUARIOS ORDENADOS POR FECHA DE REGISTRO" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingresa una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:
            juegosPorTitulo();
            break;
        case 2:
            juegosPorPrecio();
            break;
        case 3:
            juegosPorFecha();
            break;
        case 4:
            juegosListadosPorCategoria();
            break;
        case 5:
            desarrolladoresPorNombre();
            break;
        case 6:
            desarrolladoresPorFecha();
            break;
        case 7:
            reseniasPorPuntaje();
            break;
        case 8:
            reseniasPorFecha();
            break;
        case 9:
            categoriasPorNombre();
            break;

        case 10:
            usuariosPorApellido();
            break;
        case 11:
            usuariosPorFechaRegistro();
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
        cout << "Ingresa una opcion " << endl;
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
        cout << "Opcion 2 : -" << endl;
        cout << "Opcion 3 : -" << endl;
        cout << "Opcion 4 : -" << endl;
        cout << "Opcion 5 : -" << endl;
        cout << "Opcion 6 : -" << endl;
        cout << "Opcion 7 : -" << endl;
        cout << "Opcion 8 : -" << endl;
        cout << "Opcion 9 : -" << endl;
        cout << "Opcion 10 : -" << endl;
        cout << "Opcion 11 : -" << endl;
        cout << "Opcion 0 : SALIR " << endl;
        cout << "Ingresa una opcion " << endl;
        opcion = leerEntero();
        system("cls");
        switch (opcion) {
        case 1:
            recaudacionPorCategoria();
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        case 10:

            break;
        case 11:

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


