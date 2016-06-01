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
enum EstadoCultivo {RecienSembrado, EnCrecimiento, ListoParaCosechar, ConMaleza, ConPlaga, NoSensado};

static const char* TipoParcela[] = {"Cultivo", "Granero", "Casa"};
static const char* TipoProducto[] = {"Fertilizante", "Plaguicida", "PlaguicidaBajoConsumo", "Herbicida", "HerbicidaLargoAlcance"};
static const char* TipoEstado[] = {"RecienSembrado", "EnCrecimiento", "ListoParaCosechar", "ConMaleza", "ConPlaga", "NoSensado"};

struct Posicion {
	int x;
	int y;
};

const bool operator==(const Posicion &p1, const Posicion &p2);

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

const bool operator==(const InfoVueloCruzado &a, const InfoVueloCruzado &b);

std::ostream & operator<<(std::ostream & os, const Parcela & p);
std::ostream & operator<<(std::ostream & os, const Producto & p);
std::ostream & operator<<(std::ostream & os, const EstadoCultivo & e);

#endif /*TIPOS_H*/
