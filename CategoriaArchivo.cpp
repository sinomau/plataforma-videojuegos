#include <iostream>
#include "CategoriaArchivo.h"
#include <cstring>
#include <cstdio>

using namespace std;

CategoriaArchivo::CategoriaArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo,nombreArchivo,sizeof(_nombreArchivo)-1);
    _nombreArchivo[sizeof(_nombreArchivo)-1] = '\0';

}
Categoria CategoriaArchivo::buscarPorId(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");

    if (pArchivo == nullptr) {
        return Categoria();
    }

    Categoria reg;

    while (fread(&reg, sizeof(Categoria), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return reg;
        }
    }

    fclose(pArchivo);
    return Categoria();
}

int CategoriaArchivo::obtenerNuevoId() {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");

    if (pArchivo == nullptr) {
        return 1;
    }

    Categoria reg;
    int cantidad = 0;

    while (fread(&reg, sizeof(Categoria), 1, pArchivo) == 1) {
        cantidad++;
    }

    fclose(pArchivo);

    return cantidad + 1;
}


void CategoriaArchivo::escribirDisco(Categoria reg) {

    FILE* pArchivo = fopen(_nombreArchivo,"ab");
    if(pArchivo == nullptr) {
       cout << "Error al abrir el archivo."<<endl;
        return;
    }
    if (fwrite(&reg, sizeof(Categoria), 1, pArchivo) != 1) {
        cout << "Error al escribir el registro." << endl;
    }
    fclose(pArchivo);


}

Categoria CategoriaArchivo::leerDisco(int id) {
    FILE* pArchivo = fopen(_nombreArchivo,"rb");
    if(pArchivo == nullptr) {
        cout << "Error al abrir el archivo."<<endl;
        return Categoria();
    }
    Categoria reg;
    fseek(pArchivo,id * sizeof(Categoria),SEEK_SET);

    if (fread(&reg, sizeof(Categoria), 1, pArchivo) != 1) {
        cout << "Error al leer el registro." << endl;
        fclose(pArchivo);
        return Categoria();
    }

    fclose(pArchivo);

    return reg;


}


bool CategoriaArchivo::existe(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == nullptr) {
        cout << "Error al abrir el archivo."<<endl;
        return false;
    }

    Categoria reg;
    while (fread(&reg, sizeof(Categoria), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return true;
        }
    }
    fclose(pArchivo);
    return false;
}


bool CategoriaArchivo::existeNombre(const char* nombre) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
        if(pArchivo == nullptr) {
        cout << "Error al abrir el archivo."<<endl;
        return false;
    }

    Categoria reg;

     while (fread(&reg, sizeof(Categoria), 1, pArchivo) == 1) {
        if (strcmp(reg.getNombre(),nombre) == 0) {
            fclose(pArchivo);
            return true;
        }
    }
    fclose(pArchivo);
    return false;
}



int CategoriaArchivo::getCantidadRegistros() {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");

      if(pArchivo == nullptr) {
        cout << "Error al abrir el archivo."<<endl;
        return -1;
    }

    fseek(pArchivo, 0, SEEK_END);
    long tamanio = ftell(pArchivo);

    fclose(pArchivo);

    if (tamanio < 0) {
        return 0;
    }

    return tamanio / sizeof(Categoria);
}

bool CategoriaArchivo::modificarDisco(Categoria reg, int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb+");

    if (pArchivo == nullptr) {
        cout << "Error al abrir el archivo" << endl;
        return false;
    }

    Categoria aux;
    bool encontrado = false;

    while (fread(&aux, sizeof(Categoria), 1, pArchivo) == 1) {
        if (aux.getId() == id) {
            fseek(pArchivo, -sizeof(Categoria), SEEK_CUR);

            fwrite(&reg, sizeof(Categoria), 1, pArchivo);
            encontrado = true;
            break;
        }
    }

    fclose(pArchivo);
    return encontrado;
}



