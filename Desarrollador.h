#ifndef DESARROLLADOR_H_INCLUDED
#define DESARROLLADOR_H_INCLUDED

class Desarrollador
{
public:
    Desarrollador() {
    _id = -1;
    _estado = true;
}
    void setId(int id);
    int getId();

    void setNombre(const char* nombre);
    const char* getNombre();

    void setPais(const char* pais);
    const char* getPais();

    void setEstado(bool estado);
    bool getEstado();

    void setAnioFundacion(int anio);
    int getAnioFundacion();

    void cargar(int id, const char* nombre, const char* pais, int anioFundacion);
    void mostrar();

protected:
private:
    int _id;
    char _nombre[50];
    char _pais[30];
    int _anioFundacion;
    bool _estado;


};
#endif // DESARROLLADOR_H_INCLUDED
