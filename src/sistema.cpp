#include "sistema.h"
#include <algorithm>
#include <sstream>

Sistema::Sistema()
{
}

Sistema::Sistema(const Campo & c, const Secuencia<Drone>& ds)
		: _campo(c), _enjambre(ds), _estado(c.dimensiones())
{
    int i = 0;
    while(i < _enjambre.size()) {
        _enjambre[i].cambiarPosicionActual(posicionGranero());
        ++i;
    }
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

void Sistema::seExpandePlaga() {
    int y = 0;
    Secuencia<Posicion> plagados;
    while (_campo.dimensiones().largo > y) {
        int x = 0;
        while (_campo.dimensiones().ancho > x) {
            if (_estado.parcelas[x][y] == ConPlaga) {
                Posicion pos;
                pos.x = x;
                pos.y = y;
                plagados.push_back(pos);
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
	int i = 0;
	while (i < _enjambre.size()){
		if (_enjambre[i] == d){
            Posicion pos;
            pos.x = posicionGranero().x;
            pos.y = posicionGranero().y;
			if (parcelaLibre(posicionGranero().x, posicionGranero().y - 1)){
				--pos.y;
			} else if (parcelaLibre(posicionGranero().x + 1, posicionGranero().y)){
				++pos.x;
			} else if (parcelaLibre(posicionGranero().x, posicionGranero().y + 1)){
				++pos.y;
			} else if (parcelaLibre(posicionGranero().x - 1, posicionGranero().y)){
				--pos.x;
			}
            _enjambre[i].cambiarPosicionActual(pos);
		}
		++i;
	}
}
	//TODO que pasa con vuelo realizado?
	// d es const porque buscamos un dron que sea igual
	// d en sí no está en el enjambre

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
			_enjambre[i].cambiarPosicionActual(posicionGranero()); //posicionGranero es un aux de Sistema. ¿No se rompe?
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
	size_t i = 0;
	while(i < _enjambre.size()) {
		os << _enjambre[i] << std::endl;
		++i;
	}
    os << "Estado de los cultivos: " << std::endl;
    i = 0;
    while(i < _estado.parcelas.size()) {
        size_t j = 0;
        while(j < _estado.parcelas[i].size()) {
            os << _estado.parcelas[i][j];
            ++j;
            if(j != _estado.parcelas[i].size()) {
                os << "\t";
            }
        }
        os << std::endl;
        ++i;
    }
}

// TODO el formato no queda 100% claro del pdf
// los drones van todos en la misma linea?

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
	std::string campo;
	std::getline(is, campo);
	std::getline(is, campo);
	std::istringstream cs(campo);
	_campo.cargar(cs);

    _enjambre.clear();
	std::string listadrones;
	std::getline(is, listadrones);
    std::vector<std::string> drones = split(listadrones,'}');
    int i = 0;
    while(i < drones.size() - 1) {
        Drone d;
        std::istringstream ds(drones[i]);
        d.cargar(ds);
        _enjambre.push_back(d);
        ++i;
    }

    _estado = Grilla<EstadoCultivo>(_campo.dimensiones());
    std::string estadostr;
    std::getline(is, estadostr, '[');
    i = 0;
    while(i < _campo.dimensiones().ancho) {
        std::getline(is, estadostr, '[');
        int j = 0;
        while(j < _campo.dimensiones().largo) {
            if(_campo.dimensiones().largo - j == 1) {
                std::getline(is, estadostr, ']');
            } else {
                std::getline(is, estadostr, ',');
            }
            EstadoCultivo estado = NoSensado;
            if(estadostr == "RecienSembrado") estado = RecienSembrado;
            if(estadostr == "EnCrecimiento") estado = EnCrecimiento;
            if(estadostr == "ListoParaCosechar") estado = ListoParaCosechar;
            if(estadostr == "ConMaleza") estado = ConMaleza;
            if(estadostr == "ConPlaga") estado = ConPlaga;
            _estado.parcelas[i][j] = estado;
            ++j;
        }
        ++i;
    }
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
    Posicion pos;
    pos.x = x;
    pos.y = y;
    return enRango(x, y) && _estado[x][y] == ConPlaga;
}
Posicion Sistema::posicionGranero() const {
    Posicion posG;
    posG.x = 0;
    posG.y = 0;
    while(posG.x < _campo.dimensiones().ancho && _campo.contenido(posG) != Granero) {
        while(posG.y < _campo.dimensiones().ancho && _campo.contenido(posG) != Granero) {
            ++posG.y;
        }
        ++posG.x;
    }
	return posG;
}
bool Sistema::enRangoCultivable(int x, int y) const {
    Posicion pos;
    pos.x = x;
    pos.y = y;
    return enRango(x, y) && _campo.contenido(pos) == Cultivo);
}

bool Sistema::enRangoCultivableLibre(int x, int y) const {
    return enRangoCultivable (x, y) && parcelaLibre (x,y));
    // aca hay un problema: parcelaLibre y enRangoCultivableLibre hacen lo mismo, pero sería raro poner una "parcelaLibre" que no sea cultivo
    // de este modo, deberíamos reemplazar el criterio de "cultivable" o bien dar por hecho que un granero vacio es una "parcelaLibre"
}
bool Sistema::parcelaLibre(int x, int y) const {
    size_t i = 0;
    Posicion pos;
    pos.x = x;
    pos.y = y;
    bool libre = _campo.contenido(pos) == Cultivo;
    while(i < _enjambre.size() && libre) {
        Posicion posDrone = _enjambre[i].posicionActual();
        libre = (posDrone.x != x || posDrone.y != y);
        ++i;
    }
	return libre;
}
Posicion Sistema::vecinoAlOeste(const Posicion &p) {
    // FIXME implementar
	return Posicion();
}

bool Sistema::tieneUnProducto(const Secuencia<Producto> &ps, const Producto &productoABuscar) {
    size_t i = 0;
    while(i < ps.size() && ps[i] != productoABuscar) {
        ++i;
    }
    return i < ps.size();
}

// TODO estas ahora tienen sus headers en tipos.h
// está bien? tienen que ser globales

void split(const std::string &s, char delim, std::vector<std::string> &elems) {;
    elems.clear();
    elems.resize(1);
    size_t i = 0;
    while(i < s.size()) {
        if(s[i] == delim) {
            elems.push_back(std::string());
        } else {
            elems[elems.size() - 1].push_back(s[i]);
        }
        ++i;
    }
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
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
