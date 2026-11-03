#ifndef USUARIOMANAGER_H_INCLUDED
#define USUARIOMANAGER_H_INCLUDED

class UsuarioManager {
public:
    bool cargarUsuario();
    int iniciarSesion();
    bool cargarSaldo(int idUsuario);
    void mostrarDatos(int idUsuario);
protected:
private:
};

#endif // USUARIOMANAGER_H_INCLUDED
