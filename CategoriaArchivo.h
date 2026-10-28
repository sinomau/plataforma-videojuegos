#ifndef CATEGORIAARCHIVO_H_INCLUDED
#define CATEGORIAARCHIVO_H_INCLUDED

#include "Categoria.h"

class CategoriaArchivo
{
public:
    CategoriaArchivo(const char* nombreArchivo);

    void escribirDisco(Categoria reg);
    Categoria leerDisco(int posicion);
    Categoria buscarPorId(int id);

    bool existe(int id);
    bool existeNombre(const char* nombre);
    int getCantidadRegistros();
    bool modificarDisco(Categoria registro, int id);
    int obtenerNuevoId();

private:
    char _nombreArchivo[100];
};

#endif // CATEGORIAARCHIVO_H_INCLUDED
