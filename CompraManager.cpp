#include <iostream>
#include "CompraManager.h"
#include "CompraArchivo.h"
#include "Compra.h"
#include "Utils.h"
#include "rlutil.h"
#include "JuegoArchivo.h"
#include "Juego.h"
#include "UsuarioArchivo.h"
#include "Usuario.h"
#include "CategoriaArchivo.h"
#include "Categoria.h"

using namespace std;


bool CompraManager::cargarCompra(int idUsuario){
    CompraArchivo archivoCompra;
    JuegoArchivo archivoJuego;
    UsuarioArchivo archivoUsuario;
    Juego juego;
    int idJuego=0;

    int cantidad=archivoJuego.getCantidadRegistros();
    int mostrados=0;
    cout<<"Juegos disponibles: "<<endl;
    for(int x=0; x<cantidad; x++)
    {
        Juego reg=archivoJuego.leerDisco(x);
        if(reg.getEstado())
        {
            cout<<reg.getId()<<" - "<<reg.getTitulo()<<" - $"<<reg.getPrecio()<<endl;
            mostrados++;
        }
    }
    if(mostrados==0)
    {
        cout<<"No hay juegos disponibles"<<endl;
        return false;
    }
    bool juegoValido=false;
    while(!juegoValido)
    {
        cout << "Ingrese el ID del juego a comprar: ";
        idJuego=leerEntero();
        juego=archivoJuego.buscarPorId(idJuego);
        juegoValido=juego.getId() !=-1 && juego.getEstado();
        if(!juegoValido)
        {
            cout << "Juego inexistente o inactivo" << endl;
            cout << "Ingrese 0 para salir u otro numero para reintentar: ";
            if (leerEntero() == 0)
            {
                cout << "Compra cancelada." << endl;
                return false;
            }
        }
    }
    if(archivoCompra.existeCompra(idUsuario, idJuego)){
        cout<<"Ya tenes este juego en tu biblioteca"<<endl;
        return false;
    }
    Usuario usuario = archivoUsuario.buscarPorId(idUsuario);
    float precio = juego.getPrecio();
    if(usuario.getSaldo()<precio){
        cout << "Saldo insuficiente. Saldo: $" << usuario.getSaldo()
             << " - Precio: $" << precio << endl;
        return false;
    }
    usuario.setSaldo(usuario.getSaldo() - precio);
    if (!archivoUsuario.modificarDisco(usuario, idUsuario)) {
        cout << "No se pudo realizar la compra." << endl;
        return false;
    }

    Compra reg;
    reg.cargar(archivoCompra.obtenerNuevoId(), idUsuario, idJuego, precio);
    if (!archivoCompra.escribirDisco(reg)) {
        usuario.setSaldo(usuario.getSaldo() + precio);
        archivoUsuario.modificarDisco(usuario, idUsuario);
        cout << "No se pudo grabar la compra. Se reintegro el saldo" << endl;
        return false;
    }

    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "Compra realizada. Saldo restante: $" << usuario.getSaldo() << endl;
    rlutil::resetColor();
    return true;

}

void CompraManager::verBiblioteca(int idUsuario){
    CompraArchivo archivoCompra;
    JuegoArchivo archivoJuego;
    CategoriaArchivo archivoCategoria;

    int cantidad = archivoCompra.getCantidadRegistros();
    int mostrados = 0;

    cout << "Mi biblioteca" << endl;
    for(int x = 0; x < cantidad; x++)
    {
        Compra compra = archivoCompra.leerDisco(x);
        if(compra.getIdUsuario() == idUsuario && compra.getEstado())
        {
            Juego juego = archivoJuego.buscarPorId(compra.getIdJuego());
            Categoria categoria = archivoCategoria.buscarPorId(juego.getIdCategoria());

            cout << "------------------------" << endl;
            cout << "Titulo: " << juego.getTitulo() << endl;
            cout << "Categoria: " << categoria.getNombre() << endl;
            cout << "Fecha de compra: " << compra.getFechaCompra().toString() << endl;
            cout << "Importe pagado: $" << compra.getImporte() << endl;
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "No hay juegos en tu biblioteca" << endl;
    }
}

bool CompraManager::eliminarCompra(){
    CompraArchivo archivoCompra;
    JuegoArchivo archivoJuego;
    UsuarioArchivo archivoUsuario;

    int cantidad = archivoCompra.getCantidadRegistros();
    int mostrados = 0;

    cout << "Compras activas:" << endl;
    for(int x = 0; x < cantidad; x++)
    {
        Compra reg = archivoCompra.leerDisco(x);
        if(reg.getEstado())
        {
            Usuario usuario = archivoUsuario.buscarPorId(reg.getIdUsuario());
            Juego juego = archivoJuego.buscarPorId(reg.getIdJuego());
            cout << reg.getId() << " - " << usuario.getNombreUsuario() << " - "
                 << juego.getTitulo() << " - $" << reg.getImporte() << endl;
            mostrados++;
        }
    }
    if(mostrados == 0)
    {
        cout << "No hay compras activas." << endl;
        return false;
    }

    cout << "Ingrese el id de la compra a anular: ";
    int id = leerEntero();
    Compra compra = archivoCompra.buscarPorId(id);
    if(compra.getId() == -1)
    {
        cout << "No existe una compra con ese ID." << endl;
        return false;
    }
    if(compra.getEstado() == false)
    {
        cout << "Esta compra ya se encuentra anulada." << endl;
        return false;
    }

    compra.setEstado(false);
    if(!archivoCompra.modificarDisco(compra, id))
    {
        cout << "No se pudo anular la compra." << endl;
        return false;
    }

    Usuario usuario = archivoUsuario.buscarPorId(compra.getIdUsuario());
    usuario.setSaldo(usuario.getSaldo() + compra.getImporte());
    if(!archivoUsuario.modificarDisco(usuario, usuario.getId()))
    {
        compra.setEstado(true);
        archivoCompra.modificarDisco(compra, id);
        cout << "No se pudo reintegrar el saldo. La compra no fue anulada." << endl;
        return false;
    }

    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "Compra anulada. Se reintegraron $" << compra.getImporte()
         << " a " << usuario.getNombreUsuario() << endl;
    rlutil::resetColor();
    return true;
}
