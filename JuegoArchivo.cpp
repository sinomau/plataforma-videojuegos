#include "JuegoArchivo.h"
#include <cstring>
#include <cstdio>

using namespace std;

JuegoArchivo::JuegoArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo) - 1);
    _nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
}

bool JuegoArchivo::escribirDisco(Juego reg) {
    FILE* pArchivo = fopen(_nombreArchivo, "ab");
    if (pArchivo == nullptr) {
        return false;
    }

    bool ok = fwrite(&reg, sizeof(Juego), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

Juego JuegoArchivo::leerDisco(int pos) {
    if (pos < 0 || pos >= getCantidadRegistros()) {
        return Juego();
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return Juego();
    }

    Juego reg;
    fseek(pArchivo, pos * sizeof(Juego), SEEK_SET);
    if (fread(&reg, sizeof(Juego), 1, pArchivo) != 1) {
        fclose(pArchivo);
        return Juego();
    }

    fclose(pArchivo);
    return reg;
}

int JuegoArchivo::buscarPosicion(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return -1;
    }

    Juego reg;
    int pos = 0;
    while (fread(&reg, sizeof(Juego), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return pos;
        }
        pos++;
    }

    fclose(pArchivo);
    return -1;
}

Juego JuegoArchivo::buscarPorId(int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return Juego();
    }
    return leerDisco(pos);
}

bool JuegoArchivo::modificarDisco(Juego reg, int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return false;
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb+");
    if (pArchivo == nullptr) {
        return false;
    }

    fseek(pArchivo, pos * sizeof(Juego), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Juego), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

int JuegoArchivo::getCantidadRegistros() {
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

    return tamanio / sizeof(Juego);
}

int JuegoArchivo::obtenerNuevoId() {
    return getCantidadRegistros() + 1;
}

bool JuegoArchivo::existe(int id) {
    return buscarPosicion(id) != -1;
}

bool JuegoArchivo::existeTitulo(const char* titulo) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return false;
    }

    Juego reg;
    while (fread(&reg, sizeof(Juego), 1, pArchivo) == 1) {
        if (reg.getEstado() == true && strcmp(reg.getTitulo(), titulo) == 0) {
            fclose(pArchivo);
            return true;
        }
    }

    fclose(pArchivo);
    return false;
}
