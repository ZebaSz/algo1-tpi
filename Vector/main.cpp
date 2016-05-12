#include "vector.h"
#include <iostream>

using namespace std;

float distancia(Vector v1, Vector v2){
	v1.resta(v2);
    return v1.modulo();
	
}

int main(int argn, char* args[]) {
    float abscisa, ordenada;
    cout << "Ingrese el valor para abscisa: ";
    cin >> abscisa;
    cout << "Ingrese el valor para ordenada: ";
    cin >> ordenada;
    Vector v1(abscisa,ordenada);

    cout << "Ingrese el valor para abscisa: ";
    cin >> abscisa;
    cout << "Ingrese el valor para ordenada: ";
    cin >> ordenada;
    Vector v2(abscisa,ordenada);

    float dst = distancia(v1,v2);

    cout << endl << "La distancia es es " << dst << endl;
    return 0;
}

