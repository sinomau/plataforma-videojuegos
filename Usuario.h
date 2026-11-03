#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include "Persona.h"
#include "Fecha.h"

/// pense estos roles, despues los charlamos
const int ROL_ADMIN = 1;
const int ROL_USUARIO = 2;

class Usuario : public Persona
{
public:
    Usuario() {
        _id = -1;
        _nombreUsuario[0] = '\0';
        _contrasenia[0] = '\0';
        _rol = ROL_USUARIO;
        _saldo = 0;
        _estado = true;
    }

    void setId(int id);
    int getId();

    void setNombreUsuario(const char* nombreUsuario);
    const char* getNombreUsuario();

    void setContrasenia(const char* contrasenia);
    const char* getContrasenia();

    void setRol(int rol);
    int getRol();

    void setSaldo(float saldo);
    float getSaldo();

    void setFechaRegistro(Fecha fecha);
    Fecha getFechaRegistro();

    void setEstado(bool estado);
    bool getEstado();

    void cargar(int id, const char* nombre, const char* apellido, const char* email,
                const char* nombreUsuario, const char* contrasenia, int rol);
    void mostrar();

protected:
private:
    int _id;
    char _nombreUsuario[30];
    char _contrasenia[30];
    int _rol;
    float _saldo;
    Fecha _fechaRegistro;
    bool _estado;
};

#endif // USUARIO_H_INCLUDED
