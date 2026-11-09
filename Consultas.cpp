#include <iostream>
#include "Consultas.h"
#include "Juego.h"
#include "JuegoArchivo.h"
#include "Categoria.h"
#include "CategoriaArchivo.h"
#include "CategoriaManager.h"
#include "Utils.h"


using namespace std;


void juegosPorCategoria() {
    JuegoArchivo archivo;
    Juego reg;

    CategoriaArchivo archivoCat;
    CategoriaManager managerCat;
    cout << "Categorias disponibles"<< endl;
    managerCat.listarCategoria();
    cout << "Seleccione del listado la categoria de los juegos a visualizar"<< endl;
    int id = leerEntero();
    while(!archivoCat.existe(id)) {
        cout << "La categoria seleccionada no existe. Ingrese nuevamente:" << endl;

        id = leerEntero();

    }

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        cout << "No hay juegos en los registros"<< endl;
        return;
    }

    int contador = 0;
    Juego *vec = new Juego[cantidad];
    for(int i = 0; i < cantidad ; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getIdCategoria() == id) {
            vec[contador] = reg;
            contador++;
        }
    }

    if(contador == 0) {
        cout << "No hay juegos de la categoria seleccionada"<< endl;
        delete[] vec;
        return;
    }

    for(int i = 0 ; i < contador; i++) {
        cout << "==================================="<< endl;
        vec[i].mostrar();
    }


    delete[]vec;

}



