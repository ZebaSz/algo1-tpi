#include "vector.h"
#include <cmath>

Vector::Vector(){
	abscisa = 0;
	ordenada = 0;
}

Vector::Vector(float a, float o){
	abscisa = a;
	ordenada = o;
}

float Vector::getAbscisa() const{
	return abscisa;
}
float Vector::getOrdenada() const{
	return ordenada;
}

bool Vector::igualX(const Vector v){
	return v.getAbscisa() == abscisa;
}

bool Vector::igualY(const Vector v){
	return v.getOrdenada() == ordenada;
}

float Vector::modulo() const{
	return sqrt(pow(abscisa,2)+pow(ordenada,2));
}

float Vector::prodEscalar(const Vector v) const{
	return v.getAbscisa() * abscisa + v.getOrdenada() * ordenada;
}

void Vector::resta(const Vector v){
	abscisa = abscisa - v.getAbscisa();
	ordenada = ordenada - v.getOrdenada();
}

