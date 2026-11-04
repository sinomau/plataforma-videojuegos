#ifndef RESENIAARCHIVO_H_INCLUDED
#define RESENIAARCHIVO_H_INCLUDED
#include "Resenia.h"



class ReseniaArchivo
{
public:

    ReseniaArchivo(const char* nombreArchivo = "resenias.dat");
    bool escribirDisco(Resenia reg);
    Resenia leerDisco(int pos);
    int buscarPosicion(int id);
    Resenia buscarPorId(int id);
    bool modificarDisco(Resenia reg, int id);

    int getCantidadRegistros();
    int obtenerNuevoId();
    bool existeResenia(int idUsuario, int idJuego);


private:
    char _nombreArchivo[100];
};


#endif // RESENIAARCHIVO_H_INCLUDED
