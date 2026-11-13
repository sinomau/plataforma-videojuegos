#include <iostream>
#include "Consultas.h"
#include "Juego.h"
#include "JuegoArchivo.h"
#include "Categoria.h"
#include "CategoriaArchivo.h"
#include "CategoriaManager.h"
#include "DesarrolladorArchivo.h"
#include "DesarrolladorManager.h"
#include "Desarrollador.h"
#include "ReseniaArchivo.h"
#include "Resenia.h"
#include "Usuario.h"
#include "UsuarioArchivo.h"
#include "Fecha.h"
#include "Utils.h"


using namespace std;

// INICIO CONSULTAS JUEGOS
void juegosPorCategoria() {
    JuegoArchivo archivo;
    Juego reg;

    CategoriaArchivo archivoCat;
    CategoriaManager managerCat;
    cout << "Categorias disponibles"<< endl;
    if(managerCat.listarCategoria() == 0) {
        return;
    }
    cout << "Seleccione del listado la categoria de los juegos a visualizar"<< endl;
    int opcion;
    bool categoriaValida = false;
    while(!categoriaValida) {
        opcion = leerEntero();
        Categoria cat = archivoCat.buscarPorId(opcion);
        categoriaValida = cat.getId() != -1 && cat.getEstado();

        if(!categoriaValida) {
            mostrarError("Categoria inexistente o inactiva.");
            cout << "Ingrese 0 para salir u otro numero para reintentar: ";
            if(leerEntero() == 0) {
                return;
            }
            cout << "Ingrese el ID de la categoria: ";
        }
    }

    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay juegos en los registros");
        return;
    }

    int contador = 0;
    Juego *vec = new Juego[cantidad];
    for(int i = 0; i < cantidad ; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado() && reg.getIdCategoria() == opcion) {
            vec[contador] = reg;
            contador++;
        }
    }

    if(contador == 0) {
        mostrarError("No hay juegos de la categoria seleccionada");
        delete[] vec;
        return;
    }

    for(int i = 0 ; i < contador; i++) {
        vec[i].mostrar();
        cout << "========================================" << endl;
    }


    delete[]vec;

}


void juegosPorDesarrollador() {
    JuegoArchivo archivo;
    Juego reg;
    DesarrolladorArchivo archDes;
    Desarrollador regDes;
    DesarrolladorManager managerDes;

    int cantidadDes = 0;
    cantidadDes = archDes.getCantidadRegistros();
    if(cantidadDes == 0) {
        mostrarError("No hay desarrolladores disponibles");
        return;
    }
    int activos = 0;
    for(int i = 0; i<cantidadDes; i++) {
        regDes = archDes.leerDisco(i);
        if(regDes.getEstado()) {
            if(activos == 0) {
                cout << "Desarrolladores disponibles" << endl;
            }
            cout << regDes.getId() << " - " << regDes.getNombre() << endl;
            activos++;
        }

    }
    if(activos == 0) {
        mostrarError("No hay desarrolladores activos");
        return;
    }

    int opcion;
    bool desarrolladorValido = false;
    while(!desarrolladorValido) {
        cout << "Ingrese el numero de desarrollador a elegir"<<endl;
        opcion = leerEntero();
        Desarrollador des = archDes.buscarPorId(opcion);
        desarrolladorValido = des.getEstado() && des.getId() != -1;
        if(!desarrolladorValido) {
            mostrarError("Desarrollador inexistente o inactivo.");
            cout << "Ingrese 0 para salir u otro numero para reintentar: ";
            if(leerEntero() == 0) {
                return;
            }
        }

    }

    int cantJuegos = archivo.getCantidadRegistros();
    if(cantJuegos == 0) {
        mostrarError("No hay Juegos disponibles");
        return;
    }

    bool hayJuegos = false;

    for(int i= 0 ; i < cantJuegos; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado() && reg.getIdDesarrollador() == opcion) {
            if(!hayJuegos) {
                mostrarTitulo("JUEGOS DEL DESARROLLADOR");
                hayJuegos = true;
            }
            reg.mostrar();
            cout << "========================================" << endl;
        }
    }

    if(!hayJuegos) {
        mostrarError("No hay juegos del desarrollador seleccionado");
    }
}



void juegosPorRangoPrecio() {
    JuegoArchivo archivo;
    Juego reg;
    int cantidad = 0;
    float vInicial = 0;
    float vFinal = 0;
    int contador = 0;

    cantidad = archivo.getCantidadRegistros();

    if(cantidad == 0) {
        mostrarError("No hay Juegos disponibles");
        return;
    }
    Juego *vec = new Juego[cantidad];
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

    cout << "Ingrese los valores para el rango de precios" << endl;
    cout << "Ingrese el precio inicial"<< endl;
    vInicial = leerFloat();
    cout << "Ingrese el precio final"<<endl;
    vFinal = leerFloat();
    if(vInicial < 0 || vFinal < 0) {
        mostrarError("Los precios no pueden ser negativos.");
        delete[] vec;
        return;
    }
    if(vInicial > vFinal) {
        mostrarError("El rango de precios es incorrecto.");
        delete[] vec;
        return;
    }
    bool encontrado = false;
    for(int i = 0 ; i < contador ; i++) {
        if(vec[i].getPrecio() <= vFinal && vec[i].getPrecio() >= vInicial) {
            vec[i].mostrar();
            cout << "========================================" << endl;
            encontrado = true;
        }

    }
    if(!encontrado) {
        mostrarError("No hay juegos en ese rango de precios");
    }
    delete[]vec;

}

void juegosPorFechaLanzamiento() {
    JuegoArchivo archivo;
    Juego reg;


    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay Juegos disponibles");
        return;
    }

    cout << "Ingrese la fecha de lanzamiento del juego a buscar" << endl;
    cout << "Ingrese el dia" << endl;
    int dia = leerEntero();

    cout << "Ingrese el mes" << endl;
    int mes = leerEntero();

    cout << "Ingrese el anio" << endl;
    int anio = leerEntero();
    Fecha fecha(dia,mes,anio);

    if(!fecha.esValida(dia,mes,anio)) {
        mostrarError("La fecha ingresada es incorrecta.");
        return;
    }

    bool encontrado = false;
    for(int i = 0; i < cantidad ; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado() && reg.getFechaLanzamiento().toInt() == fecha.toInt()) {
            reg.mostrar();
            cout << "========================================" << endl;
            encontrado = true;
        }

    }
    if(!encontrado) {
        mostrarError("No hay juegos con la fecha de lanzamiento informada");
    }


}
// FIN CONSULTAS JUEGOS


// INICIO CONSULTAS RESENIAS


void reseniasPorJuego() {
    ReseniaArchivo archivo;
    Resenia regRes;
    JuegoArchivo archJuego;
    Juego regJuego;

    int cantidad = archivo.getCantidadRegistros();

    if(cantidad == 0) {
        mostrarError("No hay Resenias disponibles");
        return;
    }

    int cantJuegos = archJuego.getCantidadRegistros();

    if(cantJuegos == 0) {
        mostrarError("No hay Juegos disponibles");
        return;
    }

    mostrarTitulo("JUEGOS");

    for(int i = 0; i < cantJuegos; i++) {
        regJuego = archJuego.leerDisco(i);

        if(regJuego.getEstado()) {
            cout << regJuego.getId() << " - " << regJuego.getTitulo() << endl;
        }
    }

    int opcion;

    cout << "Ingrese el id del juego a ver las resenias" << endl;
    opcion = leerEntero();

    if(!archJuego.existe(opcion)) {
        mostrarError("El juego ingresado no existe");
        return;
    }

    regJuego = archJuego.buscarPorId(opcion);

    if(!regJuego.getEstado()) {
        mostrarError("El juego esta inactivo");
        return;
    }

    // Buscamos las resenias del juego seleccionado
    bool encontrado = false;

    for(int i = 0; i < cantidad; i++) {
        regRes = archivo.leerDisco(i);

        if(regRes.getEstado() && regRes.getIdJuego() == opcion) {

            if(!encontrado) {
                mostrarTitulo("RESENIAS DEL JUEGO");
                cout << "Titulo Juego: " << regJuego.getTitulo() << endl;
            }
            cout << "Resenia Puntaje: " << regRes.getPuntaje() << endl;
            cout << "Resenia Comentario: " << regRes.getComentario() << endl;
            cout << "========================================" << endl;

            encontrado = true;
        }
    }

    if(!encontrado) {
        mostrarError("No existen resenias para el juego seleccionado");
    }
}


void reseniaPorUsuario() {

    ReseniaArchivo archivoResenia;
    Resenia regResenia;
    UsuarioArchivo archivoUsuario;
    Usuario regUsuario;
    JuegoArchivo archJuego;
    Juego regJuego;

    int cantidadRes = archivoResenia.getCantidadRegistros();
    if(cantidadRes == 0) {
        mostrarError("No hay resenias disponibles");
        return;
    }

    int cantUsuarios = archivoUsuario.getCantidadRegistros();
    if(cantUsuarios == 0) {
        mostrarError("No hay Usuarios disponibles");
        return;
    }

    //muestro usuarios
    int activos = 0;
    for (int i = 0 ; i < cantUsuarios ; i++) {
        regUsuario = archivoUsuario.leerDisco(i);
        if(regUsuario.getEstado()) {
            if(activos == 0) {
                cout << "USUARIOS" << endl;
            }
            cout << regUsuario.getId() << " - " << regUsuario.getNombreUsuario() << endl;
            activos++;
        }
    }
    if(activos == 0) {
        mostrarError("No hay usuarios activos");
        return;
    }

    int opcion;
    cout << "Ingrese el numero de usuario para ver sus resenias" << endl;
    opcion = leerEntero();


    if(!archivoUsuario.existe(opcion)) {
        mostrarError("Usuario ingresado no existe");
        return;
    }

    regUsuario = archivoUsuario.buscarPorId(opcion);

    if(!regUsuario.getEstado()) {
        mostrarError("El usuario esta inactivo");
        return;
    }
    //busco resenias.
    bool existeResenia = false;
    for (int i = 0 ; i < cantidadRes ; i++) {
        regResenia = archivoResenia.leerDisco(i);
        if(regResenia.getEstado() && regResenia.getIdUsuario() == opcion) {
            regJuego = archJuego.buscarPorId(regResenia.getIdJuego());

            if(regJuego.getId() != -1 && regJuego.getEstado()) {
                cout << "Juego: " << regJuego.getTitulo() << endl;
            } else {
                cout << "Juego no disponible" << endl;
            }
            cout << "Resenia Puntaje: " << regResenia.getPuntaje() << endl;
            cout << "Resenia Comentario: " << regResenia.getComentario() << endl;
            cout << "========================================" << endl;
            existeResenia = true;

        }

    }
    if(!existeResenia) {
        mostrarError("El usuario ingresado no ha reseniado ningun juego");
    }



}








