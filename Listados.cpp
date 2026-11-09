#include <iostream>
#include "Listados.h"
#include "JuegoManager.h"
#include "JuegoArchivo.h"
#include "Juego.h"
#include "Categoria.h"
#include "CategoriaArchivo.h"
#include "Desarrollador.h"
#include "DesarrolladorArchivo.h"
#include "Resenia.h"
#include "ReseniaArchivo.h"
#include <cstring>

using namespace std;

// LISTADOS JUEGOS EMPIEZA
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

    // Ordenar por nombre de categoria
    for(int i = 0; i < contador - 1; i++) {
        for(int j = i + 1; j < contador; j++) {

            bool encontro1 = false;
            bool encontro2 = false;

            // Buscar categoria del juego i
            for(int k = 0; k < archCat.getCantidadRegistros(); k++) {
                cat1 = archCat.leerDisco(k);

                if(cat1.getEstado() && vec[i].getIdCategoria() == cat1.getId()) {
                    encontro1 = true;
                    break;
                }
            }

            // Buscar categoria del juego j
            for(int k = 0; k < archCat.getCantidadRegistros(); k++) {
                cat2 = archCat.leerDisco(k);

                if(cat2.getEstado() && vec[j].getIdCategoria() == cat2.getId()) {
                    encontro2 = true;
                    break;
                }
            }

            // Comparar nombres de categorias
            if(encontro1 && encontro2) {
                if(strcmp(cat1.getNombre(), cat2.getNombre()) > 0) {
                    aux = vec[i];
                    vec[i] = vec[j];
                    vec[j] = aux;
                }
            }
        }
    }

    // Mostrar juegos ordenados
    for(int i = 0; i < contador; i++) {
        vec[i].mostrar();
    }

    delete[] vec;
}

//LISTADO JUEGOS TERMINA

//LISTADO DESARROLLADORES EMPIEZA

void desarrolladoresPorNombre() {
    DesarrolladorArchivo archivo;
    Desarrollador reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == -1) {
        cout << "No hay juegos registrados" << endl;
        return;
    }
    int contador = 0;
    Desarrollador *vec = new Desarrollador[cantidad];
    for(int i = 0; i < cantidad ; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador] = reg;
            contador++;
        }
    }

    if(contador == 0) {
        cout << "No hay desarrolladores activos" << endl;
        delete[] vec;
        return;
    }
    Desarrollador aux;
    for(int i = 0 ; i < contador -1 ; i++) {
        for(int j = i + 1; j < contador ; j++) {
            if(strcmp(vec[i].getNombre(),vec[j].getNombre())>0) {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
    }

    for(int i = 0; i < contador ; i++) {
        vec[i].mostrar();
    }

    delete[]vec;

}

void desarrolladoresPorFecha() {

    DesarrolladorArchivo archivo;
    Desarrollador reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == -1) {
        cout << "No hay juegos registrados" << endl;
        return;
    }
    int contador = 0;
    Desarrollador *vec = new Desarrollador[cantidad];
    for(int i = 0 ; i < cantidad ; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador] = reg;
            contador++;
        }
    }

    if(contador == 0) {
        cout << "No hay desarrolladores activos" << endl;
        delete[] vec;
        return;
    }
    Desarrollador aux;
    for(int i = 0 ; i < contador -1 ; i++) {
        for(int j = i + 1; j < contador ; j++) {
            if(vec[i].getAnioFundacion() > vec[j].getAnioFundacion()) {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
    }


    for(int i = 0 ; i < contador ; i ++) {
        vec[i].mostrar();
    }


    delete[] vec;


}

//FIN LISTA DESARROLADORES

//INICIO LISTADO RESENIAS

void reseniasPorPuntaje() {

    ReseniaArchivo archivo;
    Resenia reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == -1) {
        cout << "No hay Resenias registradas" << endl;
        return;
    }

    int contador = 0 ;
    Resenia *vec = new Resenia[cantidad];
    for(int i = 0 ; i < cantidad; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador]=reg;
            contador++;
        }
    }
    if(contador == 0) {
        cout << "No hay rese¤as activas" << endl;
        delete[] vec;
        return;
    }

    Resenia aux;
    for(int i = 0 ; i < contador -1 ; i++) {
        for(int j= i + 1; j < contador; j++) {
            if(vec[i].getPuntaje() > vec[j].getPuntaje()) {
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

void reseniasPorFecha() {
    ReseniaArchivo archivo;
    Resenia reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == -1) {
        cout << "No hay Resenias registradas" << endl;
        return;
    }

    Resenia *vec = new Resenia[cantidad];
    int contador = 0;
    for(int i = 0 ; i < cantidad ; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador] = reg;
            contador++;
        }
    }

    if(contador == 0) {
        cout << "No hay rese¤as activas" << endl;
        delete[] vec;
        return;
    }
    Resenia aux;
    for(int i = 0; i<contador -1;i++){
        for(int j = i +1;j< contador; j++){
            if(vec[i].getFechaResenia().toInt() > vec[j].getFechaResenia().toInt()){
            aux = vec[i];
            vec[i] = vec[j];
            vec[j] = aux;
            }
        }
    }

    for(int i = 0 ; i < contador ; i++){
        vec[i].mostrar();

    }

    delete[] vec;

}

//FIN LISTADOS RESENIAS


