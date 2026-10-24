#include "Utils.h"
#include <iostream>
#include <limits>

using namespace std;

int leerEntero() {
    int numero;

    while (true) {
        cin >> numero;

        if (!cin.fail()) {
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
            return numero;
        }

        cout << "Error. Ingrese un numero flotante: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}



void leerCadena(char destino[], int tamanio) {
    if (cin.peek() == '\n') {
        cin.ignore();
    }

    cin.getline(destino, tamanio);

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


