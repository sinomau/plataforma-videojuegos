#ifndef DESARROLLADORARCHIVO_H_INCLUDED
#define DESARROLLADORARCHIVO_H_INCLUDED

#include "Desarrollador.h"

class DesarrolladorArchivo
{
public:
    DesarrolladorArchivo(const char* nombreArchivo = "desarrolladores.dat");

    bool escribirDisco(Desarrollador reg);
    Desarrollador leerDisco(int pos);
    int buscarPosicion(int id);
    Desarrollador buscarPorId(int id);
    bool modificarDisco(Desarrollador reg, int id);

    int getCantidadRegistros();
    int obtenerNuevoId();
    bool existe(int id);
    bool existeNombre(const char* nombre);

private:
    char _nombreArchivo[100];
};

#endif // DESARROLLADORARCHIVO_H_INCLUDED
