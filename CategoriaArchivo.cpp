#include <iostream>
#include "CategoriaArchivo.h"
#include <cstring>
#include <cstdio>

using namespace std;

CategoriaArchivo::categoriaArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo,nombreArchivo,sizeof(_nombreArchivo)-1);
    _nombreArchivo[sizeof(_nombreArchivo)-1] = '\0';

}


void CategoriaArchivo::escribirDisco(Categoria reg) {

    FILE* pArchivo = fopen(_nombreArchivo,"ab");
    if(pArchivo == nullptr) {
        cout << "Error al abrir el archivo para escribir." << endl;
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
        cout << "Error al abri el archivo para escribir."<<endl;
        return Categoria();
    }
    Categoria reg;
    fseek(pArchivo,id * sizeof(Categoria),SEEK_SET);

    fread(&reg,sizeof(Categoria),1,pArchivo);

    fclose(pArchivo);

    return reg;


}


bool CategoriaArchivo::existe(int id) {

    int cantidad = getCantidadRegistros();
    Categoria reg;

    for(int i = 0 ; i < cantidad ; i++) {
        reg = leerDisco(i);
        if(reg.getId() == id) {
            return true;
        }
    }
    return false;

}



int CategoriaArchivo::getCantidadRegistros() {
    FILE* pArchivo = fopen(_nombreArchivo,"rb");
    if(pArchivo==nullptr) {
        cout<< "Error al abrir el archivo " << endl;
    }
    fseek(pArchivo,0,SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Categoria);

    fclose(pArchivo);
    return cantidad;

}


