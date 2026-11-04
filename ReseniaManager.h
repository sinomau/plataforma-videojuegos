#ifndef RESENIAMANAGER_H_INCLUDED
#define RESENIAMANAGER_H_INCLUDED

class ReseniaManager {
public:
    bool cargarResenia(int idUsuario);
    void buscarPorId();
    bool modificarResenia(int idUsuario);
    bool eliminarResenia(int idUsuario);
    void listarResenias();
    void mostrarReseniasJuego();



private:

};



#endif // RESENIAMANAGER_H_INCLUDED
