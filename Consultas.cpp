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
#include "Compra.h"
#include "CompraArchivo.h"
#include "Utils.h"
#include "rlutil.h"


using namespace std;

// INICIO CONSULTAS JUEGOS
void juegosPorCategoria() {
    system("cls");
    JuegoArchivo archivo;
    Juego reg;

    CategoriaArchivo archivoCat;
    CategoriaManager managerCat;
    mostrarTitulo("CATEGORIAS DISPONIBLES");
    if(managerCat.listarCategoria() == 0) {
        return;
    }
    cout << "Seleccione la categoria de los juegos a visualizar." << endl;
    int opcion;
    Categoria categoria;
    bool categoriaValida = false;
    while(!categoriaValida) {
        cout << "Ingrese el ID de la categoria (0 para salir): ";
        opcion = leerEntero();
        if(opcion == 0) {
            return;
        }
        categoria = archivoCat.buscarPorId(opcion);
        categoriaValida = categoria.getId() != -1 && categoria.getEstado();

        if(!categoriaValida) {
            mostrarError("Categoria inexistente o inactiva.");
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

    mostrarTitulo("JUEGOS DE LA CATEGORIA");
    cout << "Categoria :" << categoria.getNombre() << endl;

    for(int i = 0 ; i < contador; i++) {
        cout << "------------------------" << endl;
        vec[i].mostrar();
    }

    cout << contador << (contador == 1 ? " juego encontrado." : " juegos encontrados.") << endl;

    delete[]vec;

}


void juegosPorDesarrollador() {
    system("cls");
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
            activos++;
        }
    }
    if(activos == 0) {
        mostrarError("No hay desarrolladores activos");
        return;
    }

    mostrarTitulo("DESARROLLADORES DISPONIBLES");
    for(int i = 0; i<cantidadDes; i++) {
        regDes = archDes.leerDisco(i);
        if(regDes.getEstado()) {
            cout << regDes.getId() << " - " << regDes.getNombre() << endl;
        }
    }

    int opcion;
    Desarrollador des;
    bool desarrolladorValido = false;
    while(!desarrolladorValido) {
        cout << "Ingrese el ID del desarrollador (0 para salir): ";
        opcion = leerEntero();
        if(opcion == 0) {
            return;
        }
        des = archDes.buscarPorId(opcion);
        desarrolladorValido = des.getEstado() && des.getId() != -1;
        if(!desarrolladorValido) {
            mostrarError("Desarrollador inexistente o inactivo.");
        }

    }

    int cantJuegos = archivo.getCantidadRegistros();
    if(cantJuegos == 0) {
        mostrarError("No hay Juegos disponibles");
        return;
    }

    mostrarTitulo("JUEGOS DEL DESARROLLADOR");
    cout << "Desarrollador :" << des.getNombre() << endl;

    int contador = 0;

    for(int i= 0 ; i < cantJuegos; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado() && reg.getIdDesarrollador() == opcion) {
            cout << "------------------------" << endl;
            reg.mostrar();
            contador++;
        }
    }

    if(contador == 0) {
        mostrarError("No hay juegos del desarrollador seleccionado");
    } else {
        cout << contador << (contador == 1 ? " juego encontrado." : " juegos encontrados.") << endl;
    }
}



void juegosPorRangoPrecio() {
    system("cls");
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

    cout << "Ingrese los valores para el rango de precios." << endl;
    cout << "Ingrese el precio inicial: ";
    vInicial = leerFloat();
    cout << "Ingrese el precio final: ";
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
    mostrarTitulo("JUEGOS EN EL RANGO DE PRECIOS");
    cout << "Rango :$" << vInicial << " - $" << vFinal << endl;
    cout << "Ordenados por precio ascendente" << endl;

    int encontrados = 0;
    for(int i = 0 ; i < contador ; i++) {
        if(vec[i].getPrecio() <= vFinal && vec[i].getPrecio() >= vInicial) {
            cout << "------------------------" << endl;
            vec[i].mostrar();
            encontrados++;
        }

    }
    if(encontrados == 0) {
        mostrarError("No hay juegos en ese rango de precios");
    } else {
        cout << encontrados << (encontrados == 1 ? " juego encontrado." : " juegos encontrados.") << endl;
    }
    delete[]vec;

}

void juegosPorFechaLanzamiento() {
    system("cls");
    JuegoArchivo archivo;
    Juego reg;


    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay Juegos disponibles");
        return;
    }

    cout << "Ingrese la fecha de lanzamiento del juego a buscar." << endl;
    cout << "Ingrese el dia: ";
    int dia = leerEntero();

    cout << "Ingrese el mes: ";
    int mes = leerEntero();

    cout << "Ingrese el anio: ";
    int anio = leerEntero();
    Fecha fecha(dia,mes,anio);

    if(!fecha.esValida(dia,mes,anio)) {
        mostrarError("La fecha ingresada es incorrecta.");
        return;
    }

    mostrarTitulo("JUEGOS EN LA FECHA DE LANZAMIENTO");
    cout << "Fecha :";
    fecha.mostrar();

    int encontrados = 0;
    for(int i = 0; i < cantidad ; i++) {
        reg = archivo.leerDisco(i);
        if(reg.getEstado() && reg.getFechaLanzamiento().toInt() == fecha.toInt()) {
            cout << "------------------------" << endl;
            reg.mostrar();
            encontrados++;
        }

    }
    if(encontrados == 0) {
        mostrarError("No hay juegos con la fecha de lanzamiento informada");
    } else {
        cout << encontrados << (encontrados == 1 ? " juego encontrado" : " juegos encontrados") << endl;
    }


}
// FIN CONSULTAS JUEGOS


// INICIO CONSULTAS RESENIAS


void reseniasPorJuego() {
    system("cls");
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

    mostrarTitulo("JUEGOS DISPONIBLES");

    for(int i = 0; i < cantJuegos; i++) {
        regJuego = archJuego.leerDisco(i);

        if(regJuego.getEstado()) {
            cout << regJuego.getId() << " - " << regJuego.getTitulo() << endl;
        }
    }

    int opcion;

    cout << "Ingrese el ID del juego: ";
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
    mostrarTitulo("RESENIAS DEL JUEGO");
    cout << "Titulo :" << regJuego.getTitulo() << endl;

    int encontrados = 0;

    for(int i = 0; i < cantidad; i++) {
        regRes = archivo.leerDisco(i);

        if(regRes.getEstado() && regRes.getIdJuego() == opcion) {
            cout << "------------------------" << endl;
            regRes.mostrar();
            encontrados++;
        }
    }

    if(encontrados == 0) {
        mostrarError("No existen resenias para el juego seleccionado");
    } else {
        cout << encontrados << (encontrados == 1 ? " resenia encontrada" : " resenias encontradas") << endl;
    }
}


void reseniaPorUsuario() {
    system("cls");
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
            activos++;
        }
    }
    if(activos == 0) {
        mostrarError("No hay usuarios activos");
        return;
    }

    mostrarTitulo("USUARIOS DISPONIBLES");
    for (int i = 0 ; i < cantUsuarios ; i++) {
        regUsuario = archivoUsuario.leerDisco(i);
        if(regUsuario.getEstado()) {
            cout << regUsuario.getId() << " - " << regUsuario.getNombreUsuario() << endl;
        }
    }

    int opcion;
    cout << "Ingrese el ID del usuario: ";
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
    mostrarTitulo("RESENIAS DEL USUARIO");
    cout << "Usuario :" << regUsuario.getNombreUsuario() << endl;

    int encontrados = 0;
    for (int i = 0 ; i < cantidadRes ; i++) {
        regResenia = archivoResenia.leerDisco(i);
        if(regResenia.getEstado() && regResenia.getIdUsuario() == opcion) {
            regJuego = archJuego.buscarPorId(regResenia.getIdJuego());

            cout << "------------------------" << endl;
            if(regJuego.getId() != -1 && regJuego.getEstado()) {
                cout << "Juego :" << regJuego.getTitulo() << endl;
            } else {
                cout << "Juego no disponible" << endl;
            }
            regResenia.mostrar();
            encontrados++;

        }

    }
    if(encontrados == 0) {
        mostrarError("El usuario ingresado no ha reseniado ningun juego");
    } else {
        cout << encontrados << (encontrados == 1 ? " resenia encontrada" : " resenias encontradas") << endl;
    }



}

void usuariosPorNombreUsuario(){
    system("cls");
    UsuarioArchivo archivo;

if (archivo.getCantidadRegistros()==0){
    mostrarError("No hay usuarios registrados");
    return;
}
char nombre[30];
cout<<"Ingresa el nombre del usuario a buscar: ";
leerCadena(nombre, 30);

Usuario reg = archivo.buscarPorNombreUsuario(nombre);
if(reg.getId()==-1){
    mostrarError("No existe un usuario con ese nombre");
    return;
}
mostrarTitulo("Usuario encontrado");
reg.mostrar();
}

void usuariosPorRangoFechaRegistro(){
UsuarioArchivo archivo;
int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay usuarios registrados");
        return;
    }
Fecha desde, hasta;
 cout << "Fecha DESDE" << endl;
 desde.cargar();
 cout << "Fecha HASTA" << endl;
 hasta.cargar();

 if(desde.toInt()>hasta.toInt()){
    mostrarError("La fecha desde no puede ser posterior a la fecha hasta.");
    return;
 }
 mostrarTitulo("USUARIOS REGISTRADOS ENTRE " + desde.toString() + " Y " + hasta.toString());

 int encontrados = 0;
    for(int i = 0; i < cantidad; i++) {
        Usuario reg = archivo.leerDisco(i);
        int fecha = reg.getFechaRegistro().toInt();
        if(reg.getEstado() && fecha >= desde.toInt() && fecha <= hasta.toInt()) {
            cout << "------------------------" << endl;
            reg.mostrar();
            encontrados++;
        }
    }

    if(encontrados == 0) {
        mostrarError("No hay usuarios registrados en ese rango.");
    } else {
        cout << encontrados << (encontrados == 1 ? " usuario encontrado" : " usuarios encontrados") << endl;
    }

}

// INICIO CONSULTAS COMPRAS
void mostrarDetalleCompra(Compra compra) {
    system("cls");
    UsuarioArchivo archUsuario;
    JuegoArchivo archJuego;
    Usuario usuario = archUsuario.buscarPorId(compra.getIdUsuario());
    Juego juego = archJuego.buscarPorId(compra.getIdJuego());

    cout << "------------------------" << endl;
    cout << "Fecha: " << compra.getFechaCompra().toString() << endl;
    cout << "Usuario: " << usuario.getNombreUsuario() << endl;
    cout << "Juego: " << juego.getTitulo() << endl;
    cout << "Importe: $" << compra.getImporte() << endl;
}

void comprasPorRangoFecha(){
CompraArchivo archivo;
int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay compras registradas");
        return;
    }
Fecha desde, hasta;
 cout << "Fecha DESDE" << endl;
 desde.cargar();
 cout << "Fecha HASTA" << endl;
 hasta.cargar();

 if(desde.toInt()>hasta.toInt()){
    mostrarError("La fecha desde no puede ser posterior a la fecha hasta");
    return;
 }
 mostrarTitulo("COMPRAS REALIZADAS ENTRE " + desde.toString() + " Y " + hasta.toString());

 int encontrados = 0;
    for(int i = 0; i < cantidad; i++) {
        Compra reg = archivo.leerDisco(i);
        int fecha = reg.getFechaCompra().toInt();
        if(reg.getEstado() && fecha >= desde.toInt() && fecha <= hasta.toInt()) {
            mostrarDetalleCompra(reg);
            encontrados++;
        }
    }

    if(encontrados == 0) {
        mostrarError("No hay compras en ese rango");
    } else {
        cout << encontrados << (encontrados == 1 ? " compra encontrada" : " compras encontradas") << endl;
    }



}

void comprasPorUsuario(){
    system("cls");
CompraArchivo archivo;
int cantidad = archivo.getCantidadRegistros();
if(cantidad==0){
    mostrarError("No hay compras realizadas");
    return;
}

UsuarioArchivo archUsuario;
char nombre [30];
cout<<"Ingresa el nombre del usuario: ";
leerCadena(nombre, 30);
Usuario usuario = archUsuario.buscarPorNombreUsuario(nombre);
if(usuario.getId()== -1){
    mostrarError("No existe un usuario con ese nombre");
    return;
}

mostrarTitulo("COMPRAS DE " + string(usuario.getNombreUsuario()));

int encontrados=0;
float total =0;
for(int x=0;x<cantidad;x++){
    Compra reg = archivo.leerDisco(x);
    if(reg.getEstado()&&reg.getIdUsuario()==usuario.getId()){
        mostrarDetalleCompra(reg);
        total+=reg.getImporte();
        encontrados++;
    }
}

if(encontrados == 0) {
        mostrarError("El usuario no tiene compras");
    } else {
        cout << encontrados << (encontrados == 1 ? " compra encontrada" : " compras encontradas") << endl;
        cout << "Total gastado: $" << total << endl;
    }
}

void comprasPorJuego(){
    system("cls");
    CompraArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();
    if(cantidad == 0) {
        mostrarError("No hay compras realizadas");
        return;
    }

    JuegoArchivo archJuego;
    cout << "Ingrese el ID del juego: ";
    int idJuego = leerEntero();
    Juego juego = archJuego.buscarPorId(idJuego);
    if(juego.getId() == -1) {
        mostrarError("No existe un juego con ese ID");
        return;
    }

    mostrarTitulo("COMPRAS DE " + string(juego.getTitulo()));

    int encontrados = 0;
    float total = 0;
    for(int x = 0; x < cantidad; x++) {
        Compra reg = archivo.leerDisco(x);
        if(reg.getEstado() && reg.getIdJuego() == idJuego) {
            mostrarDetalleCompra(reg);
            total += reg.getImporte();
            encontrados++;
        }
    }

    if(encontrados == 0) {
        mostrarError("El juego no tiene compras");
    } else {
        cout << encontrados << (encontrados == 1 ? " compra encontrada" : " compras encontradas") << endl;
        cout << "Total recaudado: $" << total << endl;
    }
}








