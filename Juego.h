#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "Fecha.h"

class Juego
{
public:
    Juego() {
    _id = -1;
    _estado = true;
}
    void setId(int id);
    int getId();

    void setTitulo(const char* titulo);
    const char* getTitulo();

    void setIdCategoria(int id);
    int getIdCategoria();

    void setIdDesarrollador(int id);
    int getIdDesarrollador();

    void setPrecio(float precio);
    float getPrecio();

    void setFechaLanzamiento(Fecha fecha);
    Fecha getFechaLanzamiento();

    void setEstado(bool estado);
    bool getEstado();

    void cargar(int id, const char* titulo,int idCategoria,int idDesarrollador,float precio,Fecha fechaLanzamiento);
    void mostrar();

protected:
private:
    int _id;
    char _titulo[50];
    int _idCategoria;
    int _idDesarrollador;
    float _precio;
    Fecha _fechaLanzamiento;
    bool _estado;


};



#endif // JUEGO_H_INCLUDED
