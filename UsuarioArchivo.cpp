#include "UsuarioArchivo.h"
#include <cstring>
#include <cstdio>

using namespace std;

UsuarioArchivo::UsuarioArchivo(const char* nombreArchivo) {
    strncpy(_nombreArchivo, nombreArchivo, sizeof(_nombreArchivo) - 1);
    _nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
}

bool UsuarioArchivo::escribirDisco(Usuario reg) {
    FILE* pArchivo = fopen(_nombreArchivo, "ab");
    if (pArchivo == nullptr) {
        return false;
    }

    bool ok = fwrite(&reg, sizeof(Usuario), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

Usuario UsuarioArchivo::leerDisco(int pos) {
    if (pos < 0 || pos >= getCantidadRegistros()) {
        return Usuario();
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return Usuario();
    }

    Usuario reg;
    fseek(pArchivo, pos * sizeof(Usuario), SEEK_SET);
    if (fread(&reg, sizeof(Usuario), 1, pArchivo) != 1) {
        fclose(pArchivo);
        return Usuario();
    }

    fclose(pArchivo);
    return reg;
}

int UsuarioArchivo::buscarPosicion(int id) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return -1;
    }

    Usuario reg;
    int pos = 0;
    while (fread(&reg, sizeof(Usuario), 1, pArchivo) == 1) {
        if (reg.getId() == id) {
            fclose(pArchivo);
            return pos;
        }
        pos++;
    }

    fclose(pArchivo);
    return -1;
}

Usuario UsuarioArchivo::buscarPorId(int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return Usuario();
    }
    return leerDisco(pos);
}

/// Devuelve el usuario ACTIVO con ese nombre de usuario.
Usuario UsuarioArchivo::buscarPorNombreUsuario(const char* nombreUsuario) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr) {
        return Usuario();
    }

    Usuario reg;
    while (fread(&reg, sizeof(Usuario), 1, pArchivo) == 1) {
        if (reg.getEstado() == true &&
                strcmp(reg.getNombreUsuario(), nombreUsuario) == 0) {
            fclose(pArchivo);
            return reg;
        }
    }

    fclose(pArchivo);
    return Usuario();
}

bool UsuarioArchivo::modificarDisco(Usuario reg, int id) {
    int pos = buscarPosicion(id);
    if (pos == -1) {
        return false;
    }

    FILE* pArchivo = fopen(_nombreArchivo, "rb+");
    if (pArchivo == nullptr) {
        return false;
    }

    fseek(pArchivo, pos * sizeof(Usuario), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Usuario), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

int UsuarioArchivo::getCantidadRegistros() {
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

    return tamanio / sizeof(Usuario);
}

int UsuarioArchivo::obtenerNuevoId() {
    return getCantidadRegistros() + 1;
}

bool UsuarioArchivo::existe(int id) {
    return buscarPosicion(id) != -1;
}

bool UsuarioArchivo::existeNombreUsuario(const char* nombreUsuario) {
    return buscarPorNombreUsuario(nombreUsuario).getId() != -1;
}
