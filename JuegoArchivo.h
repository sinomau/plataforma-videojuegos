#ifndef JUEGOARCHIVO_H_INCLUDED
#define JUEGOARCHIVO_H_INCLUDED
#include "Juego.h"

class JuegoArchivo
{
public:
    JuegoArchivo(const char* nombreArchivo = "juegos.dat");

    bool escribirDisco(Juego reg);
    Juego leerDisco(int pos);
    int buscarPosicion(int id);
    Juego buscarPorId(int id);
    bool modificarDisco(Juego reg, int id);

    int getCantidadRegistros();
    int obtenerNuevoId();
    bool existe(int id);
    bool existeTitulo(const char* titulo);

private:
    char _nombreArchivo[100];
};



#endif // JUEGOARCHIVO_H_INCLUDED
