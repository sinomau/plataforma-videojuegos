#ifndef CATEGORIAARCHIVO_H_INCLUDED
#define CATEGORIAARCHIVO_H_INCLUDED
#include "Categoria.h"


class CategoriaArchivo
{
public:
    categoriaArchivo(const char* nombreArchivo);
    void escribirDisco(Categoria reg);
    Categoria leerDisco(int id);
    bool existe(int id);
    int getCantidadRegistros();

private:

    char _nombreArchivo[100];
};


#endif // CATEGORIAARCHIVO_H_INCLUDED
