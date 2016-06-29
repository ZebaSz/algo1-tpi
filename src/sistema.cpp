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
            _estado.parcelas[plagados[i].x - 1][plagados[i].y] = ConPlaga;
        }
        if (plagados[i].x != _campo.dimensiones().ancho - 1) {
            _estado.parcelas[plagados[i].x + 1][plagados[i].y] = ConPlaga;
        }
        if (plagados[i].y != 0) {
            _estado.parcelas[plagados[i].x][plagados[i].y - 1] = ConPlaga;
        }
        if (plagados[i].y != _campo.dimensiones().largo - 1) {
            _estado.parcelas[plagados[i].x][plagados[i].y + 1] = ConPlaga;
        }
        ++i;
    }
}

void Sistema::despegar(const Drone & d)
{
	int i = 0;
	while (i < _enjambre.size()){
		if (_enjambre[i] == d){
            Posicion pos = elegirParcelaAdyacente(posicionGranero());
            _enjambre[i].moverA(pos);
		}
		++i;
	}
}

bool Sistema::listoParaCosechar() const
{
	int cantCosechables = 0;
	int cantCultivos = (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2;
	int i = 0;
	while (_campo.dimensiones().ancho * _campo.dimensiones().largo > i) {
		if(_estado.parcelas[i/_campo.dimensiones().largo][i % _campo.dimensiones().largo] == ListoParaCosechar) {
			++cantCosechables;
		}
		++i;
	}
	return (cantCosechables /(double) cantCultivos >= 0.9);
}

void Sistema::aterrizarYCargarBaterias(Carga b)
{
	int i=0;
	while (_enjambre.size() > i){
		if (_enjambre[i].bateria() < b){
			_enjambre[i].setBateria(100);
			_enjambre[i].borrarVueloRealizado();
			_enjambre[i].cambiarPosicionActual(posicionGranero());
		}
		i++;
	}
}

void Sistema::fertilizarPorFilas()
{
	int d = 0;
	while (d < _enjambre.size() && _enjambre[d].enVuelo()){
		Posicion actual = _enjambre[d].posicionActual();
		while (actual.x > (-1) && tieneUnProducto(_enjambre[d].productosDisponibles(), Fertilizante) && _enjambre[d].bateria() > 0 && _campo.contenido(actual) == Cultivo){
			if (enRangoCultivable (actual.x, actual.y)){
			if (enRangoCultivable (actual.x, actual.y) && (_estado.parcelas[actual.x][actual.y] == RecienSembrado || _estado.parcelas[actual.x][actual.y] == EnCrecimiento)){
				_estado.parcelas[actual.x][actual.y] = ListoParaCosechar;
				_enjambre[d].sacarProducto(Fertilizante);
			}
			_enjambre[d].setBateria(_enjambre[d].bateria() - 1);
			_enjambre[d].moverA(actual);
			--actual.x;
		}
		++d; 
	}
}

void Sistema::volarYSensar(const Drone & d)
{ 
	int i = 0;
	while (i < _enjambre.size()) {
		if (_enjambre[i] == d) {
            Posicion pos = elegirParcelaAdyacente(_enjambre[i].posicionActual());
			_enjambre[i].moverA(pos);
			_enjambre[i].setBateria(_enjambre[i].bateria() - 1);

			EstadoCultivo parcelaASensar = _estado.parcelas[pos.x][pos.y];
			if(parcelaASensar == NoSensado) {
				_estado.parcelas[pos.x][pos.y] = static_cast<EstadoCultivo>(rand() % 5);
			} else if(parcelaASensar == ConMaleza) {
				if (tieneUnProducto(_enjambre[i].productosDisponibles(), Herbicida) && _enjambre[i].bateria() > 4) {
					_estado.parcelas[pos.x][pos.y] = RecienSembrado;
					_enjambre[i].sacarProducto(Herbicida);
					_enjambre[i].setBateria(_enjambre[i].bateria() - 5);
				} else if (tieneUnProducto(_enjambre[i].productosDisponibles(), HerbicidaLargoAlcance)
						   && _enjambre[i].bateria() > 4) {
					_estado.parcelas[pos.x][pos.y] = RecienSembrado;
					int j = 0;
					Secuencia<Posicion> adyacentes = parcelasAdyacentes(pos);
					while (j < adyacentes.size()) {
						if (_estado.parcelas[adyacentes[j].x][adyacentes[j].y] == ConMaleza) {
							_estado.parcelas[adyacentes[j].x][adyacentes[j].y] = RecienSembrado;
						}
						++j;
					}
					_enjambre[j].sacarProducto(HerbicidaLargoAlcance);
					_enjambre[j].setBateria(_enjambre[j].bateria() - 5);
				}
			} else if(parcelaASensar == ConPlaga) {
				if (tieneUnProducto(_enjambre[i].productosDisponibles(), PlaguicidaBajoConsumo) &&
					_enjambre[i].bateria() > 4) {
					_estado.parcelas[pos.x][pos.y] = RecienSembrado;
					_enjambre[i].sacarProducto(PlaguicidaBajoConsumo);
					_enjambre[i].setBateria(_enjambre[i].bateria() - 5);
				} else if (tieneUnProducto(_enjambre[i].productosDisponibles(), Plaguicida) &&
						   _enjambre[i].bateria() > 9) {
					_estado.parcelas[pos.x][pos.y] = RecienSembrado;
					_enjambre[i].sacarProducto(Plaguicida);
					_enjambre[i].setBateria(_enjambre[i].bateria() - 10);
				}
			} else if (parcelaASensar == RecienSembrado || parcelaASensar == EnCrecimiento) {
				if (tieneUnProducto(_enjambre[i].productosDisponibles(), Fertilizante)) {
					_estado.parcelas[pos.x][pos.y] = ListoParaCosechar;
					_enjambre[i].sacarProducto(Fertilizante);
				}
			}
		}
		++i;
	}
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

bool Sistema::enRango(int x, int y) const {
	return x >= 0 && y >= 0 && x < _campo.dimensiones().ancho && y < _campo.dimensiones().largo;
}

bool Sistema::enRango(const Posicion p) const {
	return enRango(p.x, p.y);
}

Posicion Sistema::posicionGranero() const {
    Posicion posG = {0,0};
    while(posG.x < _campo.dimensiones().ancho && _campo.contenido(posG) != Granero) {
        while(posG.y < _campo.dimensiones().largo && _campo.contenido(posG) != Granero) {
            ++posG.y;
        }
        if(posG.y == _campo.dimensiones().largo) posG.y = 0;
        if(_campo.contenido(posG) != Granero) ++posG.x;
    }
	return posG;
}

bool Sistema::enRangoCultivable(int x, int y) const {
    return enRango(x, y) && _campo.contenido({x,y}) == Cultivo;
}

bool Sistema::parcelaLibre(int x, int y) const {
    size_t i = 0;
    Posicion parcela = {x,y};
    bool libre = enRango(parcela);
    while(i < _enjambre.size() && libre) {
        libre = !(_enjambre[i].posicionActual() == parcela);
        ++i;
    }
	return libre;
}

Posicion Sistema::elegirParcelaAdyacente(const Posicion & pos) const {
	Secuencia<Posicion> adyacentes = parcelasAdyacentes(pos);
	Posicion ady = {-1,-1};
	size_t i = 0;
	while(i < adyacentes.size() && ady.x == -1) {
		if(parcelaLibre(adyacentes[i].x, adyacentes[i].y)) {
			ady = adyacentes[i];
		}
		++i;
	}
	return ady;
}

bool Sistema::tieneUnProducto(const Secuencia<Producto> &ps, const Producto &productoABuscar) {
    size_t i = 0;
    while(i < ps.size() && ps[i] != productoABuscar) {
        ++i;
    }
    return i < ps.size();
}

Secuencia<Posicion> Sistema::parcelasAdyacentes (const Posicion &pos) const {
	Secuencia<Posicion> parcelas;
	if (enRangoCultivable(pos.x, pos.y - 1)){
		Posicion adyacente;
		adyacente.x = pos.x;
		adyacente.y = pos.y - 1;
		parcelas.push_back(adyacente);
	}
	if (enRangoCultivable(pos.x + 1, pos.y)){
		Posicion adyacente;
		adyacente.x = pos.x + 1;
		adyacente.y = pos.y;
		parcelas.push_back(adyacente);
	}
	if (enRangoCultivable(pos.x, pos.y + 1)){
		Posicion adyacente;
		adyacente.x = pos.x;
		adyacente.y = pos.y + 1;
		parcelas.push_back(adyacente);
	}
	if (enRangoCultivable(pos.x - 1, pos.y)) {
		Posicion adyacente;
		adyacente.x = pos.x - 1;
		adyacente.y = pos.y;
		parcelas.push_back(adyacente);
	}
	return parcelas;
}

bool Sistema::operator==(const Sistema & otroSistema) const
{
	bool iguales = _campo == otroSistema.campo() && mismos<Drone>(_enjambre, otroSistema.enjambreDrones());
	int i = 0;
	while(iguales && i < _estado.parcelas.size()) {
		int j = 0;
		while(iguales && j < _estado.parcelas[i].size()) {
			Posicion pos = {i, j};
			iguales = _estado.parcelas[i][j] == otroSistema.estadoDelCultivo(pos);
			++j;
		}
		++i;
	}
	return iguales;
}

std::ostream & operator<<(std::ostream & os, const Sistema & s)
{
	s.mostrar(os);
	return os;
}