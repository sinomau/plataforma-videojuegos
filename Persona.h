#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

class Persona
{
public:
    Persona();

    void setNombre(const char* nombre);
    const char* getNombre();

    void setApellido(const char* apellido);
    const char* getApellido();

    void setEmail(const char* email);
    const char* getEmail();

    void cargar(const char* nombre, const char* apellido, const char* email);
    void mostrar();

protected:
private:
    char _nombre[30];
    char _apellido[30];
    char _email[50];
};

#endif // PERSONA_H_INCLUDED
