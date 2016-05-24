#include "drone.h"

Drone::Drone()
{
}

Drone::Drone(ID i, const std::vector<Producto>& ps) : _id(i), _productos(ps), _bateria(100), _enVuelo(false)
{
}

ID Drone::id() const
{
	return _id;
}

Carga Drone::bateria() const
{
	return _bateria;
}

bool Drone::enVuelo() const
{
	return _enVuelo;
}

const Secuencia<Posicion>& Drone::vueloRealizado() const
{
	return _trayectoria;
}

Posicion Drone::posicionActual() const
{
	// TODO y si no hay trayectoria?
	return _trayectoria.back();
}

const Secuencia<Producto>& Drone::productosDisponibles() const
{
	return _productos;
}

bool Drone::vueloEscalerado() const
{
	bool escalerado = _enVuelo;
	if(_trayectoria.size() > 2) {
		int dirx = _trayectoria[0].x - _trayectoria[2].x;
		int diry = _trayectoria[0].y - _trayectoria[2].y;
		if(dirx == 0 || diry == 0) {
			escalerado = false;
		} else {
			int i = 0;
			while(i < _trayectoria.size() - 2) {
				if(_trayectoria[i].x - _trayectoria[i + 2].x != dirx) escalerado = false;
				if(_trayectoria[i].y - _trayectoria[i + 2].y != diry) escalerado = false;
			}
		}
	}
	return escalerado;
}

Secuencia<InfoVueloCruzado> Drone::vuelosCruzados(const Secuencia<Drone>& ds)
{
	return Secuencia<InfoVueloCruzado>();
}

void Drone::mostrar(std::ostream & os) const
{
}

void Drone::guardar(std::ostream & os) const
{
}

void Drone::cargar(std::istream & is)
{
}

bool Drone::operator==(const Drone & otroDrone) const
{
	return false;
}

std::ostream & operator<<(std::ostream & os, const Drone & d)
{
	d.mostrar(os);
	return os;
}
