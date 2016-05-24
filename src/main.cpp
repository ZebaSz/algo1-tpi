#include <iostream>
#include <fstream>
#include "campo.h"
using namespace std;

int main()
{
    Posicion posG;
    posG.x = 25;
    posG.y = 10;
    Posicion posC;
    posC.x = 14;
    posC.y = 22;

    Campo campo(posG, posC);
    cout << campo << endl;

    Campo otroCampo(posG, posC);

    if(campo == otroCampo) {
        cout << "Son el mismo" << endl;
    } else {
        cout << "No son el mismo" << endl;
    }

    ofstream out("test.txt");
    if(out.is_open()) {
        campo.guardar(out);
        out.close();
    }
    

    return 0;
}
