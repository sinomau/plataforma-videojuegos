#include "CategoriaArchivo.h"
#include <cstring>
#include <cstdio>

using namespace std;

CategoriaArchivo::CategoriaArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo) - 1);
    _nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
}

bool CategoriaArchivo::escribirDisco(Categoria reg) {
    FILE* pArchivo = fopen(_nombreArchivo, "ab");
    if (pArchivo == nullptr) {
        return false;
    }

    bool ok = fwrite(&reg, sizeof(Categoria), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

Categoria CategoriaArchivo::leerDisco(int pos) {
    if (pos < 0 || pos >= getCantidadRegistros()) {
        return Categoria();
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return Categoria();
    }

    Categoria reg;
    fseek(pArchivo, pos * sizeof(Categoria), SEEK_SET);
    if (fread(&reg, sizeof(Categoria), 1, pArchivo) != 1) {
        fclose(pArchivo);
        return Categoria();
    }

    fclose(pArchivo);
    return reg;
}

int CategoriaArchivo::buscarPosicion(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return -1;
    }

    Categoria reg;
    int pos = 0;
    while (fread(&reg, sizeof(Categoria), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return pos;
        }
        pos++;
    }

    fclose(pArchivo);
    return -1;
}

Categoria CategoriaArchivo::buscarPorId(int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return Categoria();
    }
    return leerDisco(pos);
}

bool CategoriaArchivo::modificarDisco(Categoria reg, int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return false;
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb+");
    if (pArchivo == nullptr) {
        return false;
    }

    fseek(pArchivo, pos * sizeof(Categoria), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Categoria), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

int CategoriaArchivo::getCantidadRegistros() {
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

    return tamanio / sizeof(Categoria);
}

int CategoriaArchivo::obtenerNuevoId() {
    return getCantidadRegistros() + 1;
}

bool CategoriaArchivo::existe(int id) {
    return buscarPosicion(id) != -1;
}

bool CategoriaArchivo::existeNombre(const char* nombre) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return false;
    }

    Categoria reg;
    while (fread(&reg, sizeof(Categoria), 1, pArchivo) == 1) {
        if (reg.getEstado() == true && strcmp(reg.getNombre(), nombre) == 0) {
            fclose(pArchivo);
            return true;
        }
    }

    fclose(pArchivo);
    return false;
}
