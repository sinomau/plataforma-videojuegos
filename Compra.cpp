#include <iostream>
#include "Compra.h"
using namespace std;

void Compra::setId(int id) {
    _id = id;
}

int Compra::getId() {
    return _id;
}

void Compra::setIdUsuario(int idUsuario) {
    _idUsuario = idUsuario;
}

int Compra::getIdUsuario() {
    return _idUsuario;
}

void Compra::setIdJuego(int idJuego) {
    _idJuego = idJuego;
}

int Compra::getIdJuego() {
    return _idJuego;
}

void Compra::setImporte(float importe) {
    if (importe >= 0) {
        _importe = importe;
    }
}

float Compra::getImporte() {
    return _importe;
}

void Compra::setFechaCompra(Fecha fechaCompra) {
    _fechaCompra = fechaCompra;
}

Fecha Compra::getFechaCompra() {
    return _fechaCompra;
}

void Compra::setEstado(bool estado) {
    _estado = estado;
}

bool Compra::getEstado() {
    return _estado;
}

void Compra::cargar(int id, int idUsuario, int idJuego, float importe) {
    Fecha hoy;
    hoy.setFechaActual();

    setId(id);
    setIdUsuario(idUsuario);
    setIdJuego(idJuego);
    setImporte(importe);
    setFechaCompra(hoy);
    setEstado(true);
}

void Compra::mostrar() {
    cout << "Id compra :" << _id << endl;
    cout << "Id usuario :" << _idUsuario << endl;
    cout << "Id juego :" << _idJuego << endl;
    cout << "Importe :" << _importe << endl;
    cout << "Fecha de compra :" << _fechaCompra.toString() << endl;
    cout << "Estado :";
    if (_estado == true) {
        cout << "Activa" << endl;
    } else {
        cout << "Anulada" << endl;
    }
}
