#include <iostream>
#include "Listados.h"
#include "JuegoManager.h"
#include "JuegoArchivo.h"
#include "Juego.h"
#include "Categoria.h"
#include "CategoriaArchivo.h"
#include <cstring>

using namespace std;

void juegosPorTitulo() {
    JuegoArchivo arch;
    Juego reg;
    Juego aux;
    int cantidad = arch.getCantidadRegistros();


    if(cantidad == -1) {
        cout << "No hay juegos registrados" << endl;
        return;
    }

    Juego *vec = new Juego[cantidad];



    int contador = 0;
    for(int i = 0; i < cantidad; i++) {
        reg = arch.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador] = reg;
            contador++;

        }
    }

    if(contador == 0) {
        cout << "No hay juegos activos" << endl;
        delete[] vec;
        return;
    }

    for(int i = 0; i < contador -1 ; i++) {
        for(int j = i + 1; j < contador ; j++) {
            if(strcmp(vec[i].getTitulo(),vec[j].getTitulo())>0) {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }


        }


    }

    for(int i = 0 ; i < contador ; i++) {
        vec[i].mostrar();
    }

    delete[] vec;

}


void juegosPorPrecio() {

    JuegoArchivo archivo;
    Juego reg;

    int cantidad = archivo.getCantidadRegistros();

    if(cantidad == -1) {
        cout << "No hay juegos registrados" << endl;
        return;
    }

    Juego *vec = new Juego[cantidad];
    int contador = 0;
    for(int i = 0 ; i< cantidad; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador]= reg;
            contador++;
        }
    }

    if(contador == 0) {
        cout << "No hay juegos activos" << endl;
        delete[] vec;
        return;
    }

    Juego aux;
    for(int i=0; i<contador -1; i++) {
        for(int j = i +1; j<contador; j++) {
            if(vec[i].getPrecio() > vec[j].getPrecio()) {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }

    }

    for(int i=0; i<contador; i++) {
        vec[i].mostrar();

    }

    delete[]vec;

}



void juegosPorFecha() {
    JuegoArchivo archivo;
    Juego reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == -1) {
        cout << "No hay juegos registrados" << endl;
        return;
    }

    int contador=0;
    Juego *vec = new Juego[cantidad];
    for(int i = 0; i<cantidad; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador] = reg;
            contador++;
        }
    }
    if(contador == 0) {
        cout << "No hay juegos activos" << endl;
        delete[] vec;
        return;
    }

    Juego aux;
    for(int i = 0; i<contador -1; i++) {
        for(int j = i+1 ; j<contador; j++) {
            if(vec[i].getFechaLanzamiento().toInt() > vec[j].getFechaLanzamiento().toInt()) {
                aux= vec[i];
                vec[i]= vec[j];
                vec[j] = aux;
            }
        }
    }


    for(int i = 0; i<contador; i++) {
        vec[i].mostrar();
    }

    delete[]vec;



}


void juegosPorCategoria() {
    JuegoArchivo archivo;
    CategoriaArchivo archCat;

    Juego reg, aux;
    Categoria cat1, cat2;

    int cantidad = archivo.getCantidadRegistros();

    if(cantidad == -1) {
        cout << "No hay juegos registrados" << endl;
        return;
    }

    Juego *vec = new Juego[cantidad];

    int contador = 0;

    // Cargar juegos activos
    for(int i = 0; i < cantidad; i++) {
        reg = archivo.leerDisco(i);

        if(reg.getEstado()) {
            vec[contador] = reg;
            contador++;
        }
    }

    if(contador == 0) {
        cout << "No hay juegos activos" << endl;
        delete[] vec;
        return;
    }

    // Ordenar por nombre de categoría
    for(int i = 0; i < contador - 1; i++) {
        for(int j = i + 1; j < contador; j++) {

            // Buscar categoría del juego i
            for(int k = 0; k < archCat.getCantidadRegistros(); k++) {
                cat1 = archCat.leerDisco(k);

                if(vec[i].getIdCategoria() == cat1.getId()) {
                    break;
                }
            }

            // Buscar categoría del juego j
            for(int k = 0; k < archCat.getCantidadRegistros(); k++) {
                cat2 = archCat.leerDisco(k);

                if(vec[j].getIdCategoria() == cat2.getId()) {
                    break;
                }
            }

            // Comparar nombres
            if(strcmp(cat1.getNombre(), cat2.getNombre()) > 0) {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
    }

    // Mostrar juegos ordenados
    for(int i = 0; i < contador; i++) {
        vec[i].mostrar();
    }

    delete[] vec;
}
