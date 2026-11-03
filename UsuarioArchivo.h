#ifndef USUARIOARCHIVO_H_INCLUDED
#define USUARIOARCHIVO_H_INCLUDED

#include "Usuario.h"

class UsuarioArchivo
{
public:
    UsuarioArchivo(const char* nombreArchivo = "usuarios.dat");

    bool escribirDisco(Usuario reg);
    Usuario leerDisco(int pos);
    int buscarPosicion(int id);
    Usuario buscarPorId(int id);
    Usuario buscarPorNombreUsuario(const char* nombreUsuario);
    bool modificarDisco(Usuario reg, int id);

    int getCantidadRegistros();
    int obtenerNuevoId();
    bool existe(int id);
    bool existeNombreUsuario(const char* nombreUsuario);

private:
    char _nombreArchivo[100];
};

#endif // USUARIOARCHIVO_H_INCLUDED
