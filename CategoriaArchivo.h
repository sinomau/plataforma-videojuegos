#ifndef CATEGORIAARCHIVO_H_INCLUDED
#define CATEGORIAARCHIVO_H_INCLUDED

#include "Categoria.h"

class CategoriaArchivo
{
public:
    CategoriaArchivo(const char* nombreArchivo = "categorias.dat");

    bool escribirDisco(Categoria reg);
    Categoria leerDisco(int pos);
    int buscarPosicion(int id);
    Categoria buscarPorId(int id);
    bool modificarDisco(Categoria reg, int id);

    int getCantidadRegistros();
    int obtenerNuevoId();
    bool existe(int id);
    bool existeNombre(const char* nombre);

private:
    char _nombreArchivo[100];
};

#endif // CATEGORIAARCHIVO_H_INCLUDED
