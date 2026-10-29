#include <iostream>
#include "DesarrolladorArchivo.h"
#include <cstring>
#include <cstdio>

using namespace std;


DesarrolladorArchivo::DesarrolladorArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo,nombreArchivo,sizeof(_nombreArchivo)-1);
    _nombreArchivo[sizeof(_nombreArchivo)-1] = '\0';

}

Desarrollador DesarrolladorArchivo::buscarPorId(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");

    if (pArchivo == nullptr){
        cout << "Error al abrir el archivo."<<endl;
        return Desarrollador();
    }

    Desarrollador reg;

    while (fread(&reg, sizeof(Desarrollador), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return reg;
        }
    }

    fclose(pArchivo);
    return Desarrollador();
}

int DesarrolladorArchivo::obtenerNuevoId() {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");

    if (pArchivo == nullptr){
        cout << "Error al abrir el archivo."<<endl;
        return 1;
    }

    Desarrollador reg;
    int cantidad = 0;

    while (fread(&reg, sizeof(Desarrollador), 1, pArchivo) == 1) {
        cantidad++;
    }

    fclose(pArchivo);

    return cantidad + 1;
}


void DesarrolladorArchivo::escribirDisco(Desarrollador reg) {

    FILE* pArchivo = fopen(_nombreArchivo,"ab");
    if(pArchivo == nullptr) {

        return;
    }
    if (fwrite(&reg, sizeof(Desarrollador), 1, pArchivo) != 1) {
        cout << "Error al escribir el registro." << endl;
    }
    fclose(pArchivo);


}

Desarrollador DesarrolladorArchivo::leerDisco(int id) {
    FILE* pArchivo = fopen(_nombreArchivo,"rb");
    if(pArchivo == nullptr) {
        cout << "Error al abrir el archivo."<<endl;
        return Desarrollador();
    }
    Desarrollador reg;
    fseek(pArchivo,id * sizeof(Desarrollador),SEEK_SET);

    if (fread(&reg, sizeof(Desarrollador), 1, pArchivo) != 1) {
        cout << "Error al leer el registro." << endl;
        fclose(pArchivo);
        return Desarrollador();
    }

    fclose(pArchivo);

    return reg;


}


bool DesarrolladorArchivo::existe(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr){
        cout << "Error al abrir el archivo."<<endl;
        return false;
    }

    Desarrollador reg;
    while (fread(&reg, sizeof(Desarrollador), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return true;
        }
    }
    fclose(pArchivo);
    return false;
}


bool DesarrolladorArchivo::existeNombre(const char* nombre) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) return false;

    Desarrollador reg;

     while (fread(&reg, sizeof(Desarrollador), 1, pArchivo) == 1) {
        if (strcmp(reg.getNombre(),nombre) == 0) {
            fclose(pArchivo);
            return true;
        }
    }
    fclose(pArchivo);
    return false;
}



int DesarrolladorArchivo::getCantidadRegistros() {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");

    if (pArchivo == nullptr) {
        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);
    long tamanio = ftell(pArchivo);

    fclose(pArchivo);

    if (tamanio < 0) {
        return 0;
    }

    return tamanio / sizeof(Desarrollador);
}

bool DesarrolladorArchivo::modificarDisco(Desarrollador reg, int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb+");

    if (pArchivo == nullptr) {
        cout << "Error al abrir el archivo" << endl;
        return false;
    }

    Desarrollador aux;
    bool encontrado = false;

    while (fread(&aux, sizeof(Desarrollador), 1, pArchivo) == 1) {
        if (aux.getId() == id) {
            fseek(pArchivo, -sizeof(Desarrollador), SEEK_CUR);

            fwrite(&reg, sizeof(Desarrollador), 1, pArchivo);
            encontrado = true;
            break;
        }
    }

    fclose(pArchivo);
    return encontrado;
}


