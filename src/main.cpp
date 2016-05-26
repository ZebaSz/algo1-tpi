#include <iostream>
#include <fstream>
#include "campo.h"
#include "drone.h"

using namespace std;

int main()
{
    // Inicializar posiciones para un campo
    Posicion posG;
    posG.x = 15;
    posG.y = 3;
    Posicion posC;
    posC.x = 5;
    posC.y = 7;

    // Crear campo, mostrar en pantalla, guardar
    Campo campo(posG, posC);
    cout << campo << endl;

    ofstream campoout("campo.txt");
    if(campoout.is_open()) {
        campo.guardar(campoout);
        campoout.close();
    }

    // Cargar mismo campo en otroCampo, mostrar, comparar
    ifstream campoin("campo.txt");
    Campo otroCampo;
    otroCampo.cargar(campoin);
    cout << campo << endl;

    if(campo == otroCampo) {
        cout << "Son el mismo" << endl;
    } else {
        cout << "No son el mismo" << endl;
    }

    cout << endl;

    // Cargar drone de archivo, mostrar
    Drone drone;
    ifstream dronein("drone-test.txt");
    drone.cargar(dronein);
    cout << drone << endl;

    cout << "El dron tiene vuelo ";
    if(!drone.vueloEscalerado()) {
        cout << "NO ";
    }
    cout << "escalerado" << endl;


    // Cargar drone de archivo, mostrar
    Drone otroDrone;
    ifstream otrodronein("drone-test-2.txt");
    otroDrone.cargar(otrodronein);
    cout << otroDrone << endl;

    Secuencia<Drone> listadrones;
    listadrones.push_back(drone);
    listadrones.push_back(otroDrone);

    Secuencia<InfoVueloCruzado> cruces = Drone::vuelosCruzados(listadrones);
    for (int i = 0; i < cruces.size(); ++i) {
        cout << "[" << cruces[i].posicion.x << "," << cruces[i].posicion.y << "] - " << cruces[i].cantidadCruces << endl;
    }

    return 0;
}
