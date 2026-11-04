#ifndef RESENIA_H_INCLUDED
#define RESENIA_H_INCLUDED
#include "Fecha.h"

class Resenia
{
public:
    Resenia()
    {
        _id = -1;
        _estado = true;
    }

    void setId(int id);
    int getId();

    void setIdUsuario(int idUsuario);
    int getIdUsuario();

    void setIdJuego(int idJuego);
    int getIdJuego();

    void setPuntaje(int puntaje);
    int getPuntaje();

    void setComentario(const char* comentario);
    const char* getComentario();

    void setFechaResenia(Fecha fechaResenia);
    Fecha getFechaResenia();

    void setEstado(bool estado);
    bool getEstado();

    void cargar(int id,int idUsuario,int idJuego,int puntaje,const char* comentario,Fecha fechaResenia);
    void mostrar();



protected:
private:
    int _id;
    int _idUsuario;
    int _idJuego;
    int _puntaje;
    char _comentario[200];
    Fecha _fechaResenia;
    bool _estado;
};


#endif // RESENIA_H_INCLUDED
