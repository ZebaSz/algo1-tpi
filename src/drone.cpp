#include "drone.h"

Drone::Drone()
{
}

Drone::Drone(ID i, const std::vector<Producto>& ps)
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
	return _trayectoria[_trayectoria.size() - 1];
}

const Secuencia<Producto>& Drone::productosDisponibles() const
{
	return _productos;
}

bool Drone::vueloEscalerado() const
{
	return false;
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
	return os;
}
