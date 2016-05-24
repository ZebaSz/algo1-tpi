#include <iostream>
#include <fstream>
#include "campo.h"
#include "drone.h"

using namespace std;

int main()
{
    Posicion posG;
    posG.x = 15;
    posG.y = 3;
    Posicion posC;
    posC.x = 5;
    posC.y = 7;

    Campo campo(posG, posC);
    cout << campo << endl;

    ofstream out("test.txt");
    if(out.is_open()) {
        campo.guardar(out);
        out.close();
    }

    ifstream in("test.txt");

    Campo otroCampo;
    otroCampo.cargar(in);
    cout << campo << endl;

    if(campo == otroCampo) {
        cout << "Son el mismo" << endl;
    } else {
        cout << "No son el mismo" << endl;
    }

    Drone drone(1, std::vector<Producto>());

    if(!drone.vueloEscalerado()) {
        cout << "Vuelo no escalerado" << endl;
    }


    return 0;
}
