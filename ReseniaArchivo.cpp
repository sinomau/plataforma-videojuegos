#include <iostream>
#include <cstring>
#include <cstdio>

#include "ReseniaArchivo.h"
#include "JuegoArchivo.h"
#include "UsuarioArchivo.h"

ReseniaArchivo::ReseniaArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo) - 1);
    _nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
}


bool ReseniaArchivo::escribirDisco(Resenia reg) {
    FILE* pArchivo = fopen(_nombreArchivo,"ab");

    if(pArchivo == nullptr) {
        return false;
    }

    bool ok = fwrite(&reg,sizeof(Resenia),1,pArchivo) == 1;
    fclose(pArchivo);

    return ok;

}

Resenia ReseniaArchivo::leerDisco(int pos) {
    if (pos < 0 || pos >= getCantidadRegistros()) {
        return Resenia();
    }

    FILE* pArchivo = fopen(_nombreArchivo,"rb");

    if(pArchivo == nullptr) {
        return Resenia();
    }

    Resenia reg;
    fseek(pArchivo, pos * sizeof(Resenia), SEEK_SET);

    if (fread(&reg, sizeof(Resenia), 1, pArchivo) != 1) {
        fclose(pArchivo);
        return Resenia();
    }

    fclose(pArchivo);
    return reg;

}


int ReseniaArchivo::buscarPosicion(int id) {
    FILE* pArchivo = fopen(_nombreArchivo,"rb");
    if(pArchivo == nullptr) {
        return -1;
    }
    Resenia reg;
    int pos = 0;
    while(fread(&reg,sizeof(Resenia),1,pArchivo)==1) {
        if(reg.getId() == id) {
            fclose(pArchivo);
            return pos;
        }
        pos++;
    }
    fclose(pArchivo);
    return -1;

}


Resenia ReseniaArchivo::buscarPorId(int id) {
    int pos = buscarPosicion(id);
    if(pos == -1) {
        return Resenia();
    }
    return leerDisco(pos);
}

bool ReseniaArchivo::modificarDisco(Resenia reg,int id) {
    int pos = buscarPosicion(id);
    if(pos == -1) {
        return false;
    }
    FILE* pArchivo = fopen(_nombreArchivo,"rb+");
    if(pArchivo == nullptr) {
        return false;
    }
    fseek(pArchivo,pos * sizeof(Resenia),SEEK_SET);
    bool ok = fwrite(&reg,sizeof(Resenia),1,pArchivo) == 1;
    fclose(pArchivo);
    return ok;

}


int ReseniaArchivo::getCantidadRegistros() {
    FILE* pArchivo = fopen(_nombreArchivo,"rb");

    if(pArchivo == nullptr) {
        return 0;
    }

    fseek(pArchivo,0,SEEK_END);
    long tamanio = ftell(pArchivo);

    fclose(pArchivo);

    if (tamanio < 0) {
        return 0;
    }

    return tamanio / sizeof(Resenia);
}


int ReseniaArchivo::obtenerNuevoId() {
    return getCantidadRegistros() + 1;
}

bool ReseniaArchivo::existeResenia(int idUsuario,int idJuego) {
    int cantidad = getCantidadRegistros();

    for(int i = 0; i<cantidad; i++) {
        Resenia reg = leerDisco(i);
        if(reg.getIdUsuario() == idUsuario && reg.getIdJuego() == idJuego) {
            return true;
        }
    }
    return false;
}


