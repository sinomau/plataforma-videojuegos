#ifndef CATEGORIA_H_INCLUDED
#define CATEGORIA_H_INCLUDED

class Categoria
{
public:
    Categoria() {
    _id = -1;
    _estado = true;
}
    void setId(int id);
    int getId();

    void setNombre(const char* nombre);
    const char* getNombre();

    void setDescripcion(const char* descripcion);
    const char* getDescripcion();

    void setEstado(bool estado);
    bool getEstado();

    void cargar(int id, const char* nombre, const char* descripcion);
    void mostrar();

protected:
private:
    int _id;
    char _nombre[50];
    char _descripcion[200];
    bool _estado;


};


#endif // CATEGORIA_H_INCLUDED
