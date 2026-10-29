#ifndef DESARROLLADORARCHIVO_H_INCLUDED
#define DESARROLLADORARCHIVO_H_INCLUDED
#include "Desarrollador.h"


class DesarrolladorArchivo
{
public:
    DesarrolladorArchivo(const char* nombreArchivo);

    void escribirDisco(Desarrollador reg);
    Desarrollador leerDisco(int posicion);
    Desarrollador buscarPorId(int id);

    bool existe(int id);
    bool existeNombre(const char* nombre);
    int getCantidadRegistros();
    bool modificarDisco(Desarrollador registro, int id);
    int obtenerNuevoId();

private:
    char _nombreArchivo[100];
};


#endif // DESARROLLADORARCHIVO_H_INCLUDED
