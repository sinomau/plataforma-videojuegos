#include <iostream>
#include "Informes.h"
#include "CategoriaArchivo.h"
#include "Categoria.h"
#include "Juego.h"
#include "JuegoArchivo.h"
#include "CompraArchivo.h"
#include "Compra.h"
#include "Fecha.h"
#include "Utils.h"

using namespace std;


void recaudacionPorCategoria() {
    Categoria regCat;
    CategoriaArchivo archCat;
    Juego regJuego;
    JuegoArchivo archJuego;
    CompraArchivo archCompra;

    int cantidadCat = archCat.getCantidadRegistros();
    int categoriasActivas = 0;

    for(int i = 0; i < cantidadCat; i++) {
        regCat = archCat.leerDisco(i);

        if(regCat.getEstado()) {
            categoriasActivas++;
        }
    }

    if(categoriasActivas == 0) {
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
    Fecha fechaInicial,fechaFinal;
    cout << "\nIngrese el numero de la categoria que desea seleccionar: " << endl;
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

    cout << "\nSeleccione el periodo:" << endl;
    cout << "0. Periodo actual" << endl;
    cout << "1. Ingresar periodo personalizado" << endl;
    cout << "Opcion: ";
    int opcion = leerEntero();

    if(opcion == 0) {
        fechaInicial.setDia(1);
        fechaInicial.setMes(1);
        fechaInicial.setAnio(2026);

        fechaFinal.setDia(31);
        fechaFinal.setMes(12);
        fechaFinal.setAnio(2026);
    } else if(opcion == 1) {
        cout << "\nIngrese fecha inicial del periodo a seleccionar "<< endl;
        fechaInicial.cargar();
        cout << "\nIngrese fecha final del periodo a seleccionar : "<< endl;
        fechaFinal.cargar();
    } else {
        cout << "Opcion incorrecta." << endl;
        return;
    }
    if(fechaInicial.toInt() > fechaFinal.toInt()) {
        cout << "La fecha inicial no puede ser mayor a la fecha final" << endl;
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
        if(!regCompra.getEstado()) {
            continue;   // las compras anuladas no suman
        }

        if(regCompra.getFechaCompra().toInt() < fechaInicial.toInt() ||
                regCompra.getFechaCompra().toInt() > fechaFinal.toInt()) {
            continue;
        }

        for(int j = 0 ; j < cantJuegos ; j++ ) {
            regJuego = archJuego.leerDisco(j);
            if(regJuego.getId() == regCompra.getIdJuego()) {
                if(regJuego.getEstado() && regJuego.getIdCategoria() == idCategoria) {
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
    cout << "----------------------------------------" << endl;
    cout << "Periodo: " << fechaInicial.toString()
         << " al " << fechaFinal.toString() << endl;
    cout << "========================================" << endl;






}




void recaudacionPorJuego() {
    Juego regJuego;
    JuegoArchivo archJuego;
    Compra regCompra;
    CompraArchivo archCompra;

    int cantidadJuegos = archJuego.getCantidadRegistros();
    if(cantidadJuegos == 0) {
        cout<<"No juegos registrados"<< endl;
        return;
    }

    cout << "\n";
    cout << "========================================" << endl;
    cout << "       JUEGOS ACTIVOS PARA INFORME" << endl;
    cout << "========================================" << endl;
    for(int i = 0; i < cantidadJuegos ; i++) {
        regJuego = archJuego.leerDisco(i);
        if(regJuego.getEstado()) {
            cout << "  [" << regJuego.getId() << "] "
                 << regJuego.getTitulo() << endl;
        }


    }
    cout << "========================================" << endl;

    int idJuego;

    Fecha fechaInicial,fechaFinal;
    cout << "\nIngrese el numero de juego que desea seleccionar: " << endl;
    idJuego = leerEntero();

    if(!archJuego.existe(idJuego)) {
        cout<<"El id del juego ingresado no existe"<< endl;
        return;
    }

    regJuego = archJuego.buscarPorId(idJuego);

    if(!regJuego.getEstado()) {
        cout << "El juego no esta activo" << endl;
        return;
    }

    cout << "\nSeleccione el periodo:" << endl;
    cout << "0. Periodo actual" << endl;
    cout << "1. Ingresar periodo personalizado" << endl;
    cout << "Opcion: ";
    int opcion = leerEntero();

    if(opcion == 0) {
        fechaInicial.setDia(1);
        fechaInicial.setMes(1);
        fechaInicial.setAnio(2026);

        fechaFinal.setDia(31);
        fechaFinal.setMes(12);
        fechaFinal.setAnio(2026);
    } else if(opcion == 1) {
        cout << "\nIngrese fecha inicial del periodo a seleccionar "<< endl;
        fechaInicial.cargar();
        cout << "\nIngrese fecha final del periodo a seleccionar : "<< endl;
        fechaFinal.cargar();
    } else {
        cout << "Opcion incorrecta." << endl;
        return;
    }
    if(fechaInicial.toInt() > fechaFinal.toInt()) {
        cout << "La fecha inicial no puede ser mayor a la fecha final" << endl;
        return;
    }


    int cantCompra = archCompra.getCantidadRegistros();
    if(cantCompra == 0) {
        cout<<"No hay compras registradas"<< endl;
        return;
    }

    float recaudacion = 0;

    for(int i = 0; i < cantCompra; i++) {
        regCompra = archCompra.leerDisco(i);
        if(regCompra.getEstado()) {
            if(regCompra.getIdJuego() == regJuego.getId() && regCompra.getFechaCompra().toInt() >= fechaInicial.toInt() && regCompra.getFechaCompra().toInt() <= fechaFinal.toInt()) {
                recaudacion += regCompra.getImporte();
            }
        }

    }
    cout << "\n========================================" << endl;
    cout << "          INFORME DE RECAUDACION" << endl;
    cout << "========================================" << endl;
    cout << "Juego: " << regJuego.getTitulo() << endl;
    cout << "Recaudacion total: $" << recaudacion << endl;
    cout << "========================================" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Periodo: " << fechaInicial.toString()
         << " al " << fechaFinal.toString() << endl;
    cout << "========================================" << endl;




}
