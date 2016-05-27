#include "sistema.h"
#include <algorithm>

Sistema::Sistema()
{
}

Sistema::Sistema(const Campo & c, const Secuencia<Drone>& ds)
		: _campo(c), _enjambre(ds), _estado(c.dimensiones())
{
}

const Campo & Sistema::campo() const
{
	return _campo;
}

EstadoCultivo Sistema::estadoDelCultivo(const Posicion & p) const
{
	return _estado.parcelas[p.x][p.y];
}

const Secuencia<Drone>& Sistema::enjambreDrones() const
{
	return _enjambre;
}

void Sistema::crecer()
{
	int y = 0;
	while (_campo.dimensiones().largo > y) {
		int x = 0;
		while (_campo.dimensiones().ancho > x) {
			if (_estado.parcelas[x][y] == RecienSembrado) {
				_estado.parcelas[x][y] = EnCrecimiento;
			} else if (_estado.parcelas[x][y] == EnCrecimiento) {
				_estado.parcelas[x][y] = ListoParaCosechar;
			}
			++x;
		}
		++y;
	}
}

void Sistema::seVinoLaMaleza(const Secuencia<Posicion>& ps)
{
	int i=0;
	while (i < ps.size()){
		_estado.parcelas[ps[i].x][ps[i].y] = ConMaleza;
		++i;
	}
}

void Sistema::seExpandePlaga()
{
	int y = 0;
	Secuencia<Posicion> plagados;
	while (_campo.dimensiones().largo > y) {
		int x = 0;
		while(_campo.dimensiones().ancho > x) {
			if(_estado.parcelas[x][y] == ConPlaga) {
				plagados.push_back(Posicion(x, y));
			}
			++x;
		}
		++y;
	}
	int i = 0;
	while (plagados.size() > i) {
		if (plagados[i].x != 0) {
			_estado.parcelas[plagados[i].x - 1][plagados[i].y] = ConMaleza;
		}
		if (plagados[i].x != _campo.dimensiones().ancho - 1) {
			_estado.parcelas[plagados[i].x + 1][plagados[i].y] = ConMaleza;
		}
		if (plagados[i].y != 0) {
			_estado.parcelas[plagados[i].x][plagados[i].y - 1] = ConMaleza;
		}
		if (plagados[i].y != _campo.dimensiones().largo - 1) {
			_estado.parcelas[plagados[i].x][plagados[i].y + 1] = ConMaleza;
		}
		++i;
	}
}	

void Sistema::despegar(const Drone & d)
{
	// d es const porque buscamos un dron que sea igual
	// d en sí no está en el enjambre
}

bool Sistema::listoParaCosechar() const
{
	int cantCosechables = 0;
	int cantCultivos = (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2;
	int y = 0;
	while (_campo.dimensiones().largo > y) {
		int x = 0;
		while(_campo.dimensiones().ancho > x) {
			if(_estado.parcelas[x][y] == ListoParaCosechar) {
				++cantCosechables;
			}
			++x;
		}
		++y;
	}
	return (cantCosechables /(float) cantCultivos >= 0.9);
}

void Sistema::aterrizarYCargarBaterias(Carga b)
{
	int i=0;
	while (_enjambre.size() > i){
		if (_enjambre[i].bateria() < b){
			_enjambre[i].setBateria(100);
			_enjambre[i].cambiarPosicionActual(posicionGranero());
			_enjambre[i].borrarVueloRealizado();
		}
	}
}

//TODO problema con los requiere de cambiarPosicionActual
// por qué requiere no(enVuelo)?

void Sistema::fertilizarPorFilas()
{
	// FIXME implementar
}

void Sistema::volarYSensar(const Drone & d)
{
	// FIXME implementar
}

void Sistema::mostrar(std::ostream & os) const
{
	os << "Sistema" << std::endl;
	os << "Campo del sistema: " << _campo << std::endl;
	os << "Lista de drones:" << std::endl;
	int i = 0;
	while(i < _enjambre.size()) {
		os << _enjambre[i] << std::endl;
		++i;
	}
}

void Sistema::guardar(std::ostream & os) const
{
	os << "{ S" << std::endl;
	_campo.guardar(os);
	os << std::endl << "[";
	int i = 0;
	while(i < _enjambre.size()) {
		_enjambre[i].guardar(os);
		++i;
	}
	os << "]" << std::endl << "[";
	i = 0;
	while(i < _estado.parcelas.size()) {
		os << "[";
		int j = 0;
		while(j < _estado.parcelas[i].size()) {
			os << _estado.parcelas[i][j];
			++j;
			if(j != _estado.parcelas[i].size()) {
				os << ",";
			}
		}
		os << "]";
		++i;
		if(i != _estado.parcelas.size()) {
			os << ", ";
		}
	}
	os << "]" << std::endl << "}";
}

void Sistema::cargar(std::istream & is)
{
	// FIXME completar
}

// TODO preguntar sobre implementación de estos métodos
// Cuando subieron la v3, estas implementaciones no estaban (ni vacías)
bool Sistema::enRango(int x, int y) const {
	return x < _campo.dimensiones().largo && y < _campo.dimensiones().ancho;
}
bool Sistema::enRango(const Posicion p) const {
	return enRango(p.x, p.y);
}
bool Sistema::enRangoConPlaga(int x, int y) const {
	return false;
}
Posicion Sistema::posicionGranero() const {
	return Posicion();
}
bool Sistema::enRangoCultivable(int x, int y) const {
	return false;
}
bool Sistema::enRangoCultivableLibre(int x, int y) const {
	return false;
}
bool Sistema::parcelaLibre(int x, int y) const {
	return false;
}
Posicion Sistema::vecinoAlOeste(const Posicion &p) {
	return Posicion();
}

bool Sistema::tieneUnProducto(const Secuencia<Producto> &ps, const Producto &productoABuscar) {
	return false;
}
void Sistema::split(const std::string &s, char delim, std::vector<std::string> &elems) {
}
std::vector<std::string> Sistema::split(const std::string &s, char delim) {
	return std::vector<std::string>();
}

bool Sistema::operator==(const Sistema & otroSistema) const
{
	// FIXME implementar mismoEnjambre
	bool iguales = _campo == otroSistema.campo() /* && mismoEnjambre(otroSistema) */;
	if(iguales) {
		// FIXME implementar comparaciones de estado de cultivo
	}
	return iguales;
}

std::ostream & operator<<(std::ostream & os, const Sistema & s)
{
	s.mostrar(os);
	return os;
}

static const char* TipoEstado[] = {"NoSensado", "RecienSembrado", "EnCrecimiento", "ListoParaCosechar", "ConMaleza", "ConPlaga"};
std::ostream & operator<<(std::ostream & os, const EstadoCultivo & e)
{
	std::string estring = TipoEstado[e];
	os << estring;
	return os;
}
