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
	int x = 0;
	int y = 0;
	while (campo.dimensiones().largo > y) {
				while (campo.dimensiones().ancho > x) {
					if (estadoDelCultivo(x,y) == RecienSembrado) {
						estadoDelCultivo(x,y) = EnCrecimiento;
					} else {
						if (estadoDelCultivo(x,y) == EnCrecimiento) {
							estadoDelCultivo(x, y) = ListoParaCosechar;
							}
						}
					x++;
				}
		x = 0;
		y++;
	}
	// TODO revisar :)
}

void Sistema::seVinoLaMaleza(const Secuencia<Posicion>& ps)
{
	int i=0;
	while (i < ps.size()){
		estadoDelCultivo(ps[i]) = ConMaleza;
		i++;
	}
	// TODO revisar :)
}

void Sistema::seExpandePlaga()
{
	// TODO implementar
}

void Sistema::despegar(const Drone & d)
{
	// TODO implementar
}

bool Sistema::listoParaCosechar() const
{
	// TODO implementar
	return false;
}

void Sistema::aterrizarYCargarBaterias(Carga b)
{
	// TODO implementar
}

void Sistema::fertilizarPorFilas()
{
	// TODO implementar
}

void Sistema::volarYSensar(const Drone & d)
{
	// TODO implementar
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
static Posicion Sistema::vecinoAlOeste(const Posicion &p) {
	return Posicion();
}

static bool Sistema::tieneUnProducto(const Secuencia<Producto> &ps, const Producto &productoABuscar) {
	return false;
}
void Sistema::split(const std::string &s, char delim, std::vector<std::string> &elems) {
}
std::vector<std::string> Sistema::split(const std::string &s, char delim) {
	return std::vector<std::string>();
}

bool Sistema::operator==(const Sistema & otroSistema) const
{
	// TODO implementar mismoEnjambre
	bool iguales = _campo == otroSistema.campo() /* && mismoEnjambre(otroSistema) */;
	if(iguales) {
		// TODO implementar comparaciones de estado de cultivo
	}
	return iguales;
}

std::ostream & operator<<(std::ostream & os, const Sistema & s)
{
	s.mostrar(os);
	return os;
}
