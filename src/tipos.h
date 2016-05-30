#ifndef TIPOS_H
#define TIPOS_H

#include <iostream>
#include <vector>

typedef int ID;
typedef int Carga;
typedef int Ancho;
typedef int Largo;

#define Secuencia std::vector

enum Parcela {Cultivo, Granero, Casa};
enum Producto {Fertilizante, Plaguicida, PlaguicidaBajoConsumo, Herbicida, HerbicidaLargoAlcance};
enum EstadoCultivo {NoSensado, RecienSembrado, EnCrecimiento, ListoParaCosechar, ConMaleza, ConPlaga};

struct Posicion {
	int x;
	int y;
};

struct Dimension {
	Ancho ancho;
	Largo largo;
};

template<class T>
struct Grilla {
	Grilla() {}
	Grilla(Dimension d)	{
		parcelas.resize(size_t(d.ancho), std::vector<T>(size_t(d.largo), static_cast<T>(0)));
	}
	std::vector< std::vector<T> > parcelas;
};

struct InfoVueloCruzado {
	Posicion posicion;
	int cantidadCruces;
};

void split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif /*TIPOS_H*/
