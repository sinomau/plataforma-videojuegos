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
        mostrarError("No hay juegos disponibles");
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
            mostrarError("Juego inexistente o inactivo");
            cout << "Ingrese 0 para salir u otro numero para reintentar: ";
            if (leerEntero() == 0)
            {
                cout << "Compra cancelada." << endl;
                return false;
            }
        }
    }
    if(archivoCompra.existeCompra(idUsuario, idJuego)){
        mostrarError("Ya tiene este juego en su biblioteca");
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
        mostrarError("No se pudo realizar la compra.");
        return false;
    }

    Compra reg;
    reg.cargar(archivoCompra.obtenerNuevoId(), idUsuario, idJuego, precio);
    if (!archivoCompra.escribirDisco(reg)) {
        usuario.setSaldo(usuario.getSaldo() + precio);
        archivoUsuario.modificarDisco(usuario, idUsuario);
        mostrarError("No se pudo grabar la compra. Se reintegro el saldo");
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
        mostrarError("No hay juegos en su biblioteca");
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
        mostrarError("No hay compras activas.");
        return false;
    }

    cout << "Ingrese el id de la compra a anular: ";
    int id = leerEntero();
    Compra compra = archivoCompra.buscarPorId(id);
    if(compra.getId() == -1)
    {
        mostrarError("No existe una compra con ese ID.");
        return false;
    }
    if(compra.getEstado() == false)
    {
        mostrarError("Esta compra ya se encuentra anulada.");
        return false;
    }

    compra.setEstado(false);
    if(!archivoCompra.modificarDisco(compra, id))
    {
        mostrarError("No se pudo anular la compra.");
        return false;
    }

    Usuario usuario = archivoUsuario.buscarPorId(compra.getIdUsuario());
    usuario.setSaldo(usuario.getSaldo() + compra.getImporte());
    if(!archivoUsuario.modificarDisco(usuario, usuario.getId()))
    {
        compra.setEstado(true);
        archivoCompra.modificarDisco(compra, id);
        mostrarError("No se pudo reintegrar el saldo. La compra no fue anulada.");
        return false;
    }

    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "Compra anulada. Se reintegraron $" << compra.getImporte()
         << " a " << usuario.getNombreUsuario() << endl;
    rlutil::resetColor();
    return true;
}
