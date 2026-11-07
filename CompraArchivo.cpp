#include "CompraArchivo.h"
#include <cstring>
#include <cstdio>

using namespace std;

CompraArchivo::CompraArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo) - 1);
    _nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
}

bool CompraArchivo::escribirDisco(Compra reg) {
    FILE* pArchivo = fopen(_nombreArchivo, "ab");
    if (pArchivo == nullptr) {
        return false;
    }

    bool ok = fwrite(&reg, sizeof(Compra), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

Compra CompraArchivo::leerDisco(int pos) {
    if (pos < 0 || pos >= getCantidadRegistros()) {
        return Compra();
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return Compra();
    }

    Compra reg;
    fseek(pArchivo, pos * sizeof(Compra), SEEK_SET);
    if (fread(&reg, sizeof(Compra), 1, pArchivo) != 1) {
        fclose(pArchivo);
        return Compra();
    }

    fclose(pArchivo);
    return reg;
}

int CompraArchivo::buscarPosicion(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return -1;
    }

    Compra reg;
    int pos = 0;
    while (fread(&reg, sizeof(Compra), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return pos;
        }
        pos++;
    }

    fclose(pArchivo);
    return -1;
}

Compra CompraArchivo::buscarPorId(int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return Compra();
    }
    return leerDisco(pos);
}

bool CompraArchivo::modificarDisco(Compra reg, int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return false;
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb+");
    if (pArchivo == nullptr) {
        return false;
    }

    fseek(pArchivo, pos * sizeof(Compra), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Compra), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

int CompraArchivo::getCantidadRegistros() {
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

    return tamanio / sizeof(Compra);
}

int CompraArchivo::obtenerNuevoId() {
    return getCantidadRegistros() + 1;
}

bool CompraArchivo::existe(int id) {
    return buscarPosicion(id) != -1;
}

bool CompraArchivo::existeCompra(int idUsuario, int idJuego) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return false;
    }

    Compra reg;
    while (fread(&reg, sizeof(Compra), 1, pArchivo) == 1) {
        if (reg.getEstado() == true &&
                reg.getIdUsuario() == idUsuario &&
                reg.getIdJuego() == idJuego) {
            fclose(pArchivo);
            return true;
        }
    }

    fclose(pArchivo);
    return false;
}
