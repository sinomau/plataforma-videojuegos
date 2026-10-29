#include "DesarrolladorArchivo.h"
#include <cstring>
#include <cstdio>

using namespace std;

DesarrolladorArchivo::DesarrolladorArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo) - 1);
    _nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
}

bool DesarrolladorArchivo::escribirDisco(Desarrollador reg) {
    FILE* pArchivo = fopen(_nombreArchivo, "ab");
    if (pArchivo == nullptr) {
        return false;
    }

    bool ok = fwrite(&reg, sizeof(Desarrollador), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

Desarrollador DesarrolladorArchivo::leerDisco(int pos) {
    if (pos < 0 || pos >= getCantidadRegistros()) {
        return Desarrollador();
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return Desarrollador();
    }

    Desarrollador reg;
    fseek(pArchivo, pos * sizeof(Desarrollador), SEEK_SET);
    if (fread(&reg, sizeof(Desarrollador), 1, pArchivo) != 1) {
        fclose(pArchivo);
        return Desarrollador();
    }

    fclose(pArchivo);
    return reg;
}

int DesarrolladorArchivo::buscarPosicion(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return -1;
    }

    Desarrollador reg;
    int pos = 0;
    while (fread(&reg, sizeof(Desarrollador), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return pos;
        }
        pos++;
    }

    fclose(pArchivo);
    return -1;
}

Desarrollador DesarrolladorArchivo::buscarPorId(int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return Desarrollador();
    }
    return leerDisco(pos);
}

bool DesarrolladorArchivo::modificarDisco(Desarrollador reg, int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return false;
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb+");
    if (pArchivo == nullptr) {
        return false;
    }

    fseek(pArchivo, pos * sizeof(Desarrollador), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Desarrollador), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
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

int DesarrolladorArchivo::obtenerNuevoId() {
    return getCantidadRegistros() + 1;
}

bool DesarrolladorArchivo::existe(int id) {
    return buscarPosicion(id) != -1;
}

bool DesarrolladorArchivo::existeNombre(const char* nombre) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return false;
    }

    Desarrollador reg;
    while (fread(&reg, sizeof(Desarrollador), 1, pArchivo) == 1) {
        if (reg.getEstado() == true && strcmp(reg.getNombre(), nombre) == 0) {
            fclose(pArchivo);
            return true;
        }
    }

    fclose(pArchivo);
    return false;
}
