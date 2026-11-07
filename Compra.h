#ifndef COMPRA_H_INCLUDED
#define COMPRA_H_INCLUDED
#include "Fecha.h"

class Compra
{
public:
    Compra() {
        _id = -1;
        _idUsuario = -1;
        _idJuego = -1;
        _importe = 0;
        _estado = true;
    }

    void setId(int id);
    int getId();

    void setIdUsuario(int idUsuario);
    int getIdUsuario();

    void setIdJuego(int idJuego);
    int getIdJuego();

    void setImporte(float importe);
    float getImporte();

    void setFechaCompra(Fecha fecha);
    Fecha getFechaCompra();

    void setEstado(bool estado);
    bool getEstado();

    void cargar(int id, int idUsuario, int idJuego, float importe);
    void mostrar();

protected:
private:
    int _id;
    int _idUsuario;
    int _idJuego;
    float _importe;
    Fecha _fechaCompra;
    bool _estado;
};

#endif // COMPRA_H_INCLUDED
