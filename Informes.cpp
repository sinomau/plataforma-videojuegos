#include <iostream>
#include "Informes.h"
#include "CategoriaArchivo.h"
#include "Categoria.h"
#include "Juego.h"
#include "JuegoArchivo.h"
#include "CompraArchivo.h"
#include "Compra.h"
#include "Utils.h"

using namespace std;


void recaudacionPorCategoria() {
    Categoria regCat;
    CategoriaArchivo archCat;
    Juego regJuego;
    JuegoArchivo archJuego;
    CompraArchivo archCompra;

    int cantidadCat = archCat.getCantidadRegistros();
    if(cantidadCat == 0) {
        cout << "No hay categorias activas" << endl;
        return;
    }
    cout << "\n";
    cout << "========================================" << endl;
    cout << "       CATEGORIAS ACTIVAS PARA INFORME" << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < cantidadCat; i++) {
        regCat = archCat.leerDisco(i);

        if (regCat.getEstado()) {
            cout << "  [" << regCat.getId() << "] "
                 << regCat.getNombre() << endl;
        }
    }

    cout << "========================================" << endl;

    int idCategoria;
    cout << "\nIngrese el numero de la categoria que desea seleccionar: ";
    idCategoria = leerEntero();





    if(!archCat.existe(idCategoria)) {
        cout<<"El id de categoria ingresado no existe"<< endl;
        return;
    }

    regCat = archCat.buscarPorId(idCategoria);

    if(!regCat.getEstado()) {
        cout << "La categoria no esta activa" << endl;
        return;
    }

    int cantCompra = archCompra.getCantidadRegistros();
    if(cantCompra == 0) {
        cout << "No hay compras registradas" << endl;
        return;
    }


    int cantJuegos = archJuego.getCantidadRegistros();
    if(cantJuegos == 0) {
        cout << "No hay juegos registrados" << endl;
        return;
    }
    float recaudacion = 0;

//todas las compras, falta ver qeu juegos y que categorias son.
    for(int i = 0 ; i < cantCompra ; i++) {
        Compra regCompra = archCompra.leerDisco(i);

        for(int j = 0 ; j < cantJuegos ; j++ ) {
            regJuego = archJuego.leerDisco(j);
            if(regJuego.getId() == regCompra.getIdJuego()) {
                if(regJuego.getIdCategoria() == idCategoria) {
                    recaudacion += regCompra.getImporte();
                }
                break;
            }
        }


    }
    cout << "\n========================================" << endl;
    cout << "          INFORME DE RECAUDACION" << endl;
    cout << "========================================" << endl;
    cout << "Categoria: " << regCat.getNombre() << endl;
    cout << "Recaudacion total: $" << recaudacion << endl;
    cout << "========================================" << endl;







}

