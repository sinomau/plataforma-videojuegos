#include "Utils.h"
#include <iostream>
#include <limits>
#include "rlutil.h"

using namespace std;

int leerEntero() {
    int numero;

    while (true) {
        cin >> numero;

        if (!cin.fail()) {
            // Descartar el resto de la linea: cin >> deja el '\n' en el buffer
            // y cualquier getchar() posterior (rlutil::anykey) lo leeria como
            // si fuera una tecla, sin esperar al usuario.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }

        cout << "Error. Ingrese un numero entero: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


float leerFloat() {
    float numero;

    while (true) {
        cin >> numero;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }

        cout << "Error. Ingrese un numero flotante: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}



void leerCadena(char destino[], int tamanio) {
    cin.getline(destino, tamanio);

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}



void mostrarTitulo(string titulo) {
    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << titulo << endl;
    cout << "========================================" << endl;
    rlutil::resetColor();
}

void mostrarError(string mensaje) {
    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::LIGHTRED);
    cout << mensaje << endl;
    rlutil::resetColor();
}

void mostrarExito(string mensaje) {
    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << mensaje << endl;
    rlutil::resetColor();
}
