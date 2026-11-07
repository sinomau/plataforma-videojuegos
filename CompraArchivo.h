#ifndef COMPRAARCHIVO_H_INCLUDED
#define COMPRAARCHIVO_H_INCLUDED

#include "Compra.h"

class CompraArchivo
{
public:
    CompraArchivo(const char* nombreArchivo = "compras.dat");

    bool escribirDisco(Compra reg);
    Compra leerDisco(int pos);
    int buscarPosicion(int id);
    Compra buscarPorId(int id);
    bool modificarDisco(Compra reg, int id);

    int getCantidadRegistros();
    int obtenerNuevoId();
    bool existe(int id);
    bool existeCompra(int idUsuario, int idJuego);

private:
    char _nombreArchivo[100];
};

#endif // COMPRAARCHIVO_H_INCLUDED
