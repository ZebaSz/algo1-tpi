#include "drone.h"

Drone::Drone()
{
}

Drone::Drone(ID i, const std::vector<Producto>& ps)
		: _id(i), _productos(ps), _bateria(100), _enVuelo(false)
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
	return _posicionActual;
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
				++i;
			}
		}
	}
	return escalerado;
}

Secuencia<InfoVueloCruzado> Drone::vuelosCruzados(const Secuencia<Drone>& ds)
{
	int i = 0;
	size_t n = ds[0].vueloRealizado().size();
	Secuencia<InfoVueloCruzado> crucesTotales;
	while(i < n) {
		Secuencia<InfoVueloCruzado> crucesEnMomento;
		int d = 0;
		while(d < ds.size()) {
			Posicion pos = ds[d].vueloRealizado()[i];
			int cruce = posEnLista(pos, crucesEnMomento);
			if(cruce == -1) {
				InfoVueloCruzado infoCruce;
				infoCruce.posicion = pos;
				infoCruce.cantidadCruces = 1;
				crucesEnMomento.push_back(infoCruce);
			} else {
				++crucesEnMomento[cruce].cantidadCruces;
			}
			++d;
		}
		size_t c = 0;
		while(c < crucesEnMomento.size()) {
			if(crucesEnMomento[c].cantidadCruces == 1) {
				crucesEnMomento.erase(crucesEnMomento.begin() + c);
			} else {
				size_t j = 0;
				while (j < crucesTotales.size()){
					if(crucesEnMomento[c].posicion == crucesTotales[j].posicion){
						crucesTotales[j].cantidadCruces == crucesTotales[j].cantidadCruces + crucesEnMomento[c].cantidadCruces;
						crucesEnMomento.erase(crucesEnMomento.begin() + c);
					} else {
					++c;
					}
				}
			}
		}		
		crucesTotales.insert(crucesTotales.end(), crucesEnMomento.begin(), crucesEnMomento.end());
		++i;
	}
	return crucesTotales;
}
//FIXME tiene que estar ordenado por la cant de choques

int Drone::posEnLista(const Posicion& p, const Secuencia<InfoVueloCruzado>& cruces)
{
	int i = 0;
	int encontrado = -1;
	while(i < cruces.size() && encontrado == -1) {
		if(cruces[i].posicion.x == p.x && cruces[i].posicion.y == p.y) encontrado = i;
		++i;
	}
	return encontrado;
}

void Drone::mostrar(std::ostream & os) const
{
	os << "Drone ID " << _id << std::endl;
	os << "Carga: " << _bateria << std::endl;
	os << "En vuelo? ";
	if(_enVuelo) {
		os << "SI";
	} else {
		os << "NO";
	}
	os << std::endl;
	os << "Posición actual: [" << _posicionActual.x << "," << _posicionActual.y << "]" << std::endl;
	os << "Viaje realizado: ";
	int i = 0;
	while (i < _trayectoria.size()) {
		os << "[" << _trayectoria[i].x << "," << _trayectoria[i].y << "]";
		++i;
		if(i != _trayectoria.size()) {
			os << " -> ";
		}
	}
	os << std::endl;
	os << "Productos disponibles: ";
	i = 0;
	while (i < _productos.size()) {
		os << _productos[i];
		++i;
		if(i != _productos.size()) {
			os << ", ";
		}
	}
	os << std::endl;
}

void Drone::guardar(std::ostream & os) const
{
	os << "{ D ";
	os << _id << " ";
	os << _bateria << " ";
	os << "[";
	int i = 0;
	while(i < _trayectoria.size()) {
		os << "[" << _trayectoria[i].x << "," << _trayectoria[i].y << "]";
		++i;
		if(i != _trayectoria.size()) {
			os << ",";
		}
	}
	os << "] [";
	i = 0;
	while(i < _productos.size()) {
		os << _productos[i];
		++i;
		if(i != _productos.size()) {
			os << ",";
		}
	}
	os << "] ";
	if(_enVuelo) {
		os << "true";
	} else {
		os << "false";
	}
	os << " [" << _posicionActual.x << "," << _posicionActual.y << "]}";
}

void Drone::cargar(std::istream & is)
{
	std::string id;
	std::getline(is, id, 'D');
	std::getline(is, id, ' ');
	std::getline(is, id, ' ');
	_id = atoi(id.c_str());
	std::string bateria;
	std::getline(is, bateria, ' ');
	_bateria = atoi(bateria.c_str());

	_trayectoria.clear();
	std::string posicion;
	std::getline(is, posicion, ']');
	while(posicion.length() == 5) {
		Posicion pos;
		pos.x = atoi(&posicion.at(2));
		pos.y = atoi(&posicion.at(4));
		_trayectoria.push_back(pos);
		std::getline(is, posicion, ']');
	}

	_productos.clear();
	std::string listaprods;
	std::getline(is, listaprods, '[');
	std::getline(is, listaprods, ']');

	std::vector<std::string> prods = split(listaprods,',');

	size_t i = 0;
	while(i < prods.size()) {
		if(prods[i][0] == ' ') prods[i] = prods[i].substr(1);
		Producto prod = Fertilizante;
		if(prods[i] == "Herbicida") prod = Herbicida;
		if(prods[i] == "HerbicidaLargoAlcance") prod = HerbicidaLargoAlcance;
		if(prods[i] == "Plaguicida") prod = Plaguicida;
		if(prods[i] == "PlaguicidaBajoConsumo") prod = PlaguicidaBajoConsumo;

		_productos.push_back(prod);

		++i;
	}

	std::string volando;
	std::getline(is, volando, ' ');
	std::getline(is, volando, ' ');
	if(volando == "true") _enVuelo = true;
	else _enVuelo = false;

	std::string posact;
	std::getline(is, posact, ']');
	_posicionActual.x = atoi(&posact[1]);
	_posicionActual.y = atoi(&posact[3]);
}


void Drone::moverA(const Posicion pos)
{
	_enVuelo = true;
	_trayectoria.push_back(pos);
	_posicionActual = pos;
}

void Drone::setBateria(const Carga c)
{
	_bateria = c;
}

void Drone::borrarVueloRealizado()
{
	_trayectoria.clear();
	_enVuelo = false;
}

void Drone::cambiarPosicionActual(const Posicion p)
{
	_posicionActual = p;
}

void Drone::sacarProducto(const Producto p)
{
	int i = 0;
	while(i < _productos.size() && _productos[i] != p) {
		++i;
	}
	if(i < _productos.size()) {
		_productos.erase(_productos.begin() + i);
	}
}

bool Drone::operator==(const Drone & otroDrone) const
{
	bool iguales = _id == otroDrone.id() && _bateria == otroDrone.bateria()
				   && _enVuelo == otroDrone.enVuelo() && _posicionActual.x == otroDrone.posicionActual().x
				   && _posicionActual.y == otroDrone.posicionActual().y;
	if(iguales) {
		iguales = mismosProductos(otroDrone.productosDisponibles());
		if(_enVuelo) {
			if(_trayectoria.size() == otroDrone.vueloRealizado().size()) {
				int i = 0;
				while(i < _trayectoria.size() && iguales) {
					if(_trayectoria[i].x != otroDrone.vueloRealizado()[i].x
					   || _trayectoria[i].y != otroDrone.vueloRealizado()[i].y) {
						iguales = false;
					}
					++i;
				}
			} else {
				iguales = false;
			}
		}
	}
	return iguales;
}

std::ostream & operator<<(std::ostream & os, const Drone & d)
{
	d.mostrar(os);
	return os;
}

bool Drone::mismosProductos(Secuencia<Producto> otraLista) const
{
	bool iguales = _productos.size() == otraLista.size();
	if(iguales) {
		Secuencia<int> cuentaLista(5, 0);
		Secuencia<int> cuentaOtraLista(5, 0);
		int i = 0;
		while(i < _productos.size()) {
			++cuentaLista[_productos[i]];
			++cuentaOtraLista[otraLista[i]];
			++i;
		}
		i = 0;
		while(iguales && i < 5) {
			if(cuentaLista[i] != cuentaOtraLista[i]) iguales = false;
			++i;
		}
	}
	return iguales;
}