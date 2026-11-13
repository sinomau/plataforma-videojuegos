#include <iostream>
#include "Listados.h"
#include "Utils.h"
#include "JuegoManager.h"
#include "JuegoArchivo.h"
#include "Juego.h"
#include "Categoria.h"
#include "CategoriaArchivo.h"
#include "Desarrollador.h"
#include "DesarrolladorArchivo.h"
#include "Resenia.h"
#include "ReseniaArchivo.h"
#include "Usuario.h"
#include "UsuarioArchivo.h"
#include <cstring>

using namespace std;

// LISTADOS JUEGOS EMPIEZA
void juegosPorTitulo() {
    JuegoArchivo arch;
    Juego reg;
    Juego aux;
    int cantidad = arch.getCantidadRegistros();


    if(cantidad == 0) {
        mostrarError("No hay juegos registrados");
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
        mostrarError("No hay juegos activos");
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
        cout << "------------------------" << endl;
    }

    delete[] vec;

}


void juegosPorPrecio() {

    JuegoArchivo archivo;
    Juego reg;

    int cantidad = archivo.getCantidadRegistros();

    if(cantidad == 0) {
        mostrarError("No hay juegos registrados");
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
        mostrarError("No hay juegos activos");
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
        cout << "------------------------" << endl;
        vec[i].mostrar();

    }

    delete[]vec;

}



void juegosPorFecha() {
    JuegoArchivo archivo;
    Juego reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay juegos registrados");
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
        mostrarError("No hay juegos activos");
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
        cout << "------------------------" << endl;
        vec[i].mostrar();
    }

    delete[]vec;



}


void juegosListadosPorCategoria() {
    JuegoArchivo archivo;
    CategoriaArchivo archCat;

    Juego reg, aux;

    int cantidad = archivo.getCantidadRegistros();

    if(cantidad == 0) {
        mostrarError("No hay juegos registrados");
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
        mostrarError("No hay juegos activos");
        delete[] vec;
        return;
    }

    // Buscar una sola vez la categoria de cada juego (vector paralelo a vec)
    Categoria *cats = new Categoria[contador];
    for(int i = 0; i < contador; i++) {
        cats[i] = archCat.buscarPorId(vec[i].getIdCategoria());
        if(cats[i].getId() == -1 || !cats[i].getEstado()) {
            cats[i].setNombre("(sin categoria)");
        }
    }

    // Ordenar por nombre de categoria (se intercambian los dos vectores juntos)
    for(int i = 0; i < contador - 1; i++) {
        for(int j = i + 1; j < contador; j++) {
            if(strcmp(cats[i].getNombre(), cats[j].getNombre()) > 0) {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;

                Categoria auxCat = cats[i];
                cats[i] = cats[j];
                cats[j] = auxCat;
            }
        }
    }

    // Mostrar juegos ordenados
    for(int i = 0; i < contador; i++) {
        vec[i].mostrar();
        cout << "Categoria: " << cats[i].getNombre() << endl;
        cout << "------------------------" << endl;
    }

    delete[] cats;
    delete[] vec;
}

//LISTADO JUEGOS TERMINA

//LISTADO DESARROLLADORES EMPIEZA

void desarrolladoresPorNombre() {
    DesarrolladorArchivo archivo;
    Desarrollador reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay Desarrolladores registrados");
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
        mostrarError("No hay desarrolladores activos");
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
        cout << "------------------------" << endl;
        vec[i].mostrar();
    }

    delete[]vec;

}

void desarrolladoresPorFecha() {

    DesarrolladorArchivo archivo;
    Desarrollador reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay Desarrolladores registrados");
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
        mostrarError("No hay desarrolladores activos");
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
        cout << "------------------------" << endl;
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
    if(cantidad == 0) {
        mostrarError("No hay Resenias registradas");
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
        mostrarError("No hay rese�as activas");
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
        cout << "------------------------" << endl;
        vec[i].mostrar();
    }


    delete[] vec;

}

void reseniasPorFecha() {
    ReseniaArchivo archivo;
    Resenia reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay Resenias registradas");
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
        mostrarError("No hay reseñas activas");
        delete[] vec;
        return;
    }
    Resenia aux;
    for(int i = 0; i<contador -1; i++) {
        for(int j = i +1; j< contador; j++) {
            if(vec[i].getFechaResenia().toInt() > vec[j].getFechaResenia().toInt()) {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
    }

    for(int i = 0 ; i < contador ; i++) {
        cout << "------------------------" << endl;
        vec[i].mostrar();

    }

    delete[] vec;

}

//FIN LISTADOS RESENIAS

//INICIO LISTADOS CATEGORIAS

void categoriasPorNombre(){
    CategoriaArchivo archivo;
    Categoria reg;

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay Categorias registradas");
        return;
    }
    int contador = 0;
    Categoria *vec = new Categoria[cantidad];

    for(int i = 0 ; i < cantidad ;i++){
        reg = archivo.leerDisco(i);
        if(reg.getEstado()){
            vec[contador] = reg;
            contador ++;
        }
    }

    if(contador == 0) {
        mostrarError("No hay Categorias activas");
        delete[] vec;
        return;
    }
    Categoria aux;
    for(int i = 0; i < contador; i++){
        for(int j = i + 1 ; j < contador ; j++){
            if(strcmp(vec[i].getNombre(),vec[j].getNombre()) > 0 ){
            aux = vec[i];
            vec[i] = vec[j];
            vec[j] = aux;
            }
        }
    }

    for(int i = 0 ; i < contador ; i++){
        cout << "------------------------" << endl;

        vec[i].mostrar();
    }


    delete[]vec;

}

//INICIO LISTADOS USUARIOS

void usuariosPorApellido() {
    UsuarioArchivo arch;
    Usuario reg;
    Usuario aux;
    int cantidad = arch.getCantidadRegistros();


    if(cantidad == 0) {
        mostrarError("No hay usuarios registrados");
        return;
    }

    Usuario *vec = new Usuario[cantidad];



    int contador = 0;
    for(int i = 0; i < cantidad; i++) {
        reg = arch.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador] = reg;
            contador++;

        }
    }

    if(contador == 0) {
        mostrarError("No hay usuarios activos");
        delete[] vec;
        return;
    }

    for(int i = 0; i < contador -1 ; i++) {
        for(int j = i + 1; j < contador ; j++) {
            if(strcmp(vec[i].getApellido(), vec[j].getApellido()) > 0) {
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }


        }


    }

    for(int i = 0 ; i < contador ; i++) {
        vec[i].mostrar();
        cout << "------------------------" << endl;
    }

    delete[] vec;

}

void usuariosPorFechaRegistro() {
    UsuarioArchivo arch;
    Usuario reg;

    int cantidad = arch.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay usuarios registrados");
        return;
    }

    int contador=0;
    Usuario *vec = new Usuario[cantidad];
    for(int i = 0; i<cantidad; i++) {
        reg = arch.leerDisco(i);
        if(reg.getEstado()) {
            vec[contador] = reg;
            contador++;
        }
    }
    if(contador == 0) {
        mostrarError("No hay usuarios activos");
        delete[] vec;
        return;
    }

    Usuario aux;
    for(int i = 0; i<contador -1; i++) {
        for(int j = i+1 ; j<contador; j++) {
            if(vec[i].getFechaRegistro().toInt() > vec[j].getFechaRegistro().toInt()) {
                aux= vec[i];
                vec[i]= vec[j];
                vec[j] = aux;
            }
        }
    }


    for(int i = 0; i<contador; i++) {
        cout << "------------------------" << endl;
        vec[i].mostrar();
    }

    delete[]vec;

}
