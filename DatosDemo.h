#ifndef DATOSDEMO_H_INCLUDED
#define DATOSDEMO_H_INCLUDED

#include "UsuarioArchivo.h"
#include "CategoriaArchivo.h"
#include "DesarrolladorArchivo.h"
#include "JuegoArchivo.h"
#include "CompraArchivo.h"
#include "ReseniaArchivo.h"
#include "Fecha.h"

class DatosDemo {
public:
    void cargarDatosDemo();

private:
    void addUsuario(UsuarioArchivo& a, const char* nom, const char* ape, const char* mail,
                    const char* user, const char* pass, int rol, float saldo, Fecha f);
    void addCategoria(CategoriaArchivo& a, const char* nombre, const char* desc);
    void addDesarrollador(DesarrolladorArchivo& a, const char* nombre, const char* pais, int anio);
    void addJuego(JuegoArchivo& a, const char* titulo, int idCat, int idDes, float precio, Fecha f);
    void addCompra(CompraArchivo& a, int idUsuario, int idJuego, float importe, Fecha f);
    void addResenia(ReseniaArchivo& a, int idUsuario, int idJuego, int puntaje, const char* com, Fecha f);
};

#endif // DATOSDEMO_H_INCLUDED
