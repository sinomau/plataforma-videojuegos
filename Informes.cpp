#include <iostream>
#include "Informes.h"
#include "CategoriaArchivo.h"
#include "Categoria.h"
#include "DesarrolladorArchivo.h"
#include "Desarrollador.h"
#include "Juego.h"
#include "JuegoArchivo.h"
#include "CompraArchivo.h"
#include "Compra.h"
#include "ReseniaArchivo.h"
#include "Resenia.h"
#include "Fecha.h"
#include "Utils.h"

using namespace std;


void recaudacionPorCategoria() {
    Categoria regCat;
    CategoriaArchivo archCat;
    Juego regJuego;
    JuegoArchivo archJuego;
    Compra regCompra;
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

    Fecha fechaInicial,fechaFinal;

    cout << "\nSeleccione el periodo:" << endl;
    cout << "0. Anio actual" << endl;
    cout << "1. Ingresar periodo personalizado" << endl;
    cout << "Opcion: ";
    int opcion = leerEntero();

    if(opcion == 0) {
        int anio = fechaInicial.getAnioActual();

        fechaInicial.setDia(1);
        fechaInicial.setMes(1);
        fechaInicial.setAnio(anio);

        fechaFinal.setDia(31);
        fechaFinal.setMes(12);
        fechaFinal.setAnio(anio);
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

    cout << "\n========================================" << endl;
    cout << "RECAUDACION POR CATEGORIA ENTRE " << fechaInicial.toString()
         << " AL " << fechaFinal.toString() << endl;
    cout << "========================================" << endl;
    cout << "CATEGORIA | TOTAL | CANTIDAD DE JUEGOS VENDIDOS" << endl;
    cout << "------------------------" << endl;

    for(int i = 0; i < cantidadCat; i++) {
        regCat = archCat.leerDisco(i);
        if(!regCat.getEstado()) {
            continue;
        }

        float recaudacion = 0;
        int cantidad = 0;

        for(int j = 0; j < cantCompra; j++) {
            regCompra = archCompra.leerDisco(j);
            if(!regCompra.getEstado()) {
                continue;   // las compras anuladas no suman
            }
            if(regCompra.getFechaCompra().toInt() < fechaInicial.toInt() ||
                    regCompra.getFechaCompra().toInt() > fechaFinal.toInt()) {
                continue;
            }

            regJuego = archJuego.buscarPorId(regCompra.getIdJuego());
            if(regJuego.getIdCategoria() == regCat.getId()) {
                recaudacion += regCompra.getImporte();
                cantidad++;
            }
        }

        cout << regCat.getNombre() << " | $ " << recaudacion << " | " << cantidad << endl;
    }
    cout << "========================================" << endl;
}




void recaudacionPorJuego() {
    Juego regJuego;
    JuegoArchivo archJuego;
    Categoria regCat;
    CategoriaArchivo archCat;
    Desarrollador regDes;
    DesarrolladorArchivo archDes;
    Compra regCompra;
    CompraArchivo archCompra;

    int cantidadJuegos = archJuego.getCantidadRegistros();
    if(cantidadJuegos == 0) {
        cout << "No hay juegos registrados" << endl;
        return;
    }

    Fecha fechaInicial,fechaFinal;

    cout << "\nSeleccione el periodo:" << endl;
    cout << "0. Anio actual" << endl;
    cout << "1. Ingresar periodo personalizado" << endl;
    cout << "Opcion: ";
    int opcion = leerEntero();

    if(opcion == 0) {
        int anio = fechaInicial.getAnioActual();

        fechaInicial.setDia(1);
        fechaInicial.setMes(1);
        fechaInicial.setAnio(anio);

        fechaFinal.setDia(31);
        fechaFinal.setMes(12);
        fechaFinal.setAnio(anio);
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

    cout << "\n========================================" << endl;
    cout << "RECAUDACION POR JUEGO ENTRE " << fechaInicial.toString()
         << " AL " << fechaFinal.toString() << endl;
    cout << "========================================" << endl;
    cout << "TITULO | CATEGORIA | DESARROLLADOR | TOTAL | CANTIDAD" << endl;
    cout << "------------------------" << endl;

    for(int i = 0; i < cantidadJuegos; i++) {
        regJuego = archJuego.leerDisco(i);
        if(!regJuego.getEstado()) {
            continue;
        }

        float recaudacion = 0;
        int cantidad = 0;

        for(int j = 0; j < cantCompra; j++) {
            regCompra = archCompra.leerDisco(j);
            if(regCompra.getEstado() && regCompra.getIdJuego() == regJuego.getId() &&
                    regCompra.getFechaCompra().toInt() >= fechaInicial.toInt() &&
                    regCompra.getFechaCompra().toInt() <= fechaFinal.toInt()) {
                recaudacion += regCompra.getImporte();
                cantidad++;
            }
        }

        regCat = archCat.buscarPorId(regJuego.getIdCategoria());
        regDes = archDes.buscarPorId(regJuego.getIdDesarrollador());

        cout << regJuego.getTitulo() << " | " << regCat.getNombre() << " | "
             << regDes.getNombre() << " | $ " << recaudacion << " | " << cantidad << endl;
    }
    cout << "========================================" << endl;
}


void valoracionPromedioPorJuego() {
    Juego regJuego;
    JuegoArchivo archJuego;
    Resenia regResenia;
    ReseniaArchivo archResenia;

    int cantidadJuegos = archJuego.getCantidadRegistros();
    if(cantidadJuegos == 0) {
        cout << "No hay juegos registrados" << endl;
        return;
    }

    int cantResenias = archResenia.getCantidadRegistros();

    cout << "\n========================================" << endl;
    cout << "     VALORACION PROMEDIO POR JUEGO" << endl;
    cout << "========================================" << endl;
    cout << "TITULO | PUNTAJE PROMEDIO | CANTIDAD DE RESENIAS" << endl;
    cout << "------------------------" << endl;

    for(int i = 0; i < cantidadJuegos; i++) {
        regJuego = archJuego.leerDisco(i);
        if(!regJuego.getEstado()) {
            continue;
        }

        int suma = 0;
        int cantidad = 0;

        for(int j = 0; j < cantResenias; j++) {
            regResenia = archResenia.leerDisco(j);
            if(regResenia.getEstado() && regResenia.getIdJuego() == regJuego.getId()) {
                suma += regResenia.getPuntaje();
                cantidad++;
            }
        }

        cout << regJuego.getTitulo() << " | ";
        if(cantidad == 0) {
            cout << "Sin valoracion";
        } else {
            cout << (float)suma / cantidad;
        }
        cout << " | " << cantidad << endl;
    }
    cout << "========================================" << endl;
}
