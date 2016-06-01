#include "sistema.h"
#include <algorithm>
#include <sstream>

Sistema::Sistema()
{
}

Sistema::Sistema(const Campo & c, const Secuencia<Drone>& ds)
		: _campo(c), _enjambre(ds), _estado(c.dimensiones())
{
    // TODO el test rompe si movemos los drones
    /*
    int i = 0;
    while(i < _enjambre.size()) {
        _enjambre[i].cambiarPosicionActual(posicionGranero());
        ++i;
    }
     */
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
            Posicion pos = posicionGranero();
			if (enRangoCultivableLibre(pos.x, pos.y - 1)){
				--pos.y;
			} else if (enRangoCultivableLibre(pos.x + 1, pos.y)){
				++pos.x;
			} else if (enRangoCultivableLibre(pos.x, pos.y + 1)){
				++pos.y;
			} else if (enRangoCultivableLibre(pos.x - 1, pos.y)) {
				--pos.x;
			}
            _enjambre[i].moverA(pos);
		}
		++i;
	}
}

bool Sistema::listoParaCosechar() const
{
	int cantCosechables = 0;
	int cantCultivos = (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2;
	int x = 0;
	while (_campo.dimensiones().ancho > x) {
		int y = 0;
		while(_campo.dimensiones().largo > y) {
			if(_estado.parcelas[x][y] == ListoParaCosechar) {
				++cantCosechables;
			}
			++y;
		}
		++x;
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
	}
}

void Sistema::fertilizarPorFilas()
{
	int d = 0;
	while (d < _enjambre.size() && _enjambre[d].enVuelo()){
		Posicion actual = _enjambre[d].posicionActual();
		while (actual.x > (-1) && cantProducto(_enjambre[d], Fertilizante) > 0  && _enjambre[d].bateria() > 0 && _campo.contenido(actual) == Cultivo){
			if (enRangoCultivable (actual.x, actual.y)){
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

//FIXME implementar aux despegar a parcela adyacente
void Sistema::volarYSensar(const Drone & d)
{ 
	int i = 0;
	srand (1);
	while (i < _enjambre.size()){
		if (_enjambre[i] == d){
            Posicion pos = _enjambre[i].posicionActual();
			if (enRangoCultivableLibre(pos.x, pos.y - 1)){
				--pos.y;
			} else if (enRangoCultivableLibre(pos.x + 1, pos.y)){
				++pos.x;
			} else if (enRangoCultivableLibre(pos.x, pos.y + 1)){
				++pos.y;
			} else if (enRangoCultivableLibre(pos.x - 1, pos.y)) {
				--pos.x;
			}
			_enjambre[i].moverA(pos);
			_enjambre[i].setBateria(_enjambre[i].bateria() - 1);
			if (_campo.contenido(pos) == Cultivo){
				switch (_estado.parcelas[pos.x][pos.y]){
					case NoSensado:
						_estado.parcelas[pos.x][pos.y] = static_cast<EstadoCultivo>(rand()%5); //esta cosa es aleatoria porque la especificacion no pide nada especifico (pun intended)
						break;
					case ConMaleza:
						if (cantProducto (_enjambre[i], Herbicida) > 0 && _enjambre[i].bateria() > 4){
							_estado.parcelas[pos.x][pos.y] = RecienSembrado;
							_enjambre[i].sacarProducto(Herbicida);
							_enjambre[i].setBateria(_enjambre[i].bateria() - 5);
						} else if (cantProducto(_enjambre[i], HerbicidaLargoAlcance) > 0 && _enjambre[i].bateria() > 4){
							_estado.parcelas[pos.x][pos.y] = RecienSembrado;
							int i = 0;
							Secuencia<Posicion> adyacentes = parcelasAdyacentes(pos);
							while (i < adyacentes.size()){
								if (_estado.parcelas[adyacentes[i].x][adyacentes[i].y] == ConMaleza){
									_estado.parcelas[adyacentes[i].x][adyacentes[i].y] = RecienSembrado;
								}
								++i;
							}
							_enjambre[i].sacarProducto(HerbicidaLargoAlcance);
							_enjambre[i].setBateria(_enjambre[i].bateria() - 5);
						}
						break;
					case ConPlaga:
						if (cantProducto (_enjambre[i], PlaguicidaBajoConsumo) > 0 && _enjambre[i].bateria() > 4){
							_estado.parcelas[pos.x][pos.y] = RecienSembrado;
							_enjambre[i].sacarProducto(PlaguicidaBajoConsumo);
							_enjambre[i].setBateria(_enjambre[i].bateria() - 5);
						} else if (cantProducto (_enjambre[i], Plaguicida) > 0 && _enjambre[i].bateria() > 9){
							_estado.parcelas[pos.x][pos.y] = RecienSembrado;
							_enjambre[i].sacarProducto(Plaguicida);
							_enjambre[i].setBateria(_enjambre[i].bateria() - 10);
						}
							break;
					case ListoParaCosechar:
						break;
					default: //RecienSembrado o EnCrecimiento
						if (cantProducto (_enjambre[i],Fertilizante) > 0) 
							_estado.parcelas[pos.x][pos.y] = ListoParaCosechar;
							_enjambre[i].sacarProducto(Fertilizante);
						break;
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

// FIXME el formato no debería depender del whitespacing
// buscar más sobre parsers

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
            EstadoCultivo estado = RecienSembrado;
            if(estadostr == "EnCrecimiento") estado = EnCrecimiento;
            if(estadostr == "ListoParaCosechar") estado = ListoParaCosechar;
            if(estadostr == "ConMaleza") estado = ConMaleza;
            if(estadostr == "ConPlaga") estado = ConPlaga;
            if(estadostr == "NoSensado") estado = NoSensado;
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
bool Sistema::enRangoConPlaga(int x, int y) const {
    return enRango(x, y) && _estado.parcelas[x][y] == ConPlaga;
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

bool Sistema::enRangoCultivableLibre(int x, int y) const {
    return enRangoCultivable (x,y) && parcelaLibre (x,y);
}
bool Sistema::parcelaLibre(int x, int y) const {
    size_t i = 0;
    Posicion parcela;
    parcela.x = x;
    parcela.y = y;
    bool libre = enRango(parcela);
    while(i < _enjambre.size() && libre) {
        libre = !(_enjambre[i].posicionActual() == parcela);
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

bool Sistema::enRangoFertilizable(int x, int y) const {
    Posicion pos;
    pos.x = x;
    pos.y = y;
    return enRango(x, y) && _campo.contenido(pos) == Cultivo && (_estado.parcelas[x][y] == RecienSembrado || _estado.parcelas[x][y] == EnCrecimiento);
}

int Sistema::cantProducto(const Drone &d, const Producto &p){
	int i = 0;
	int contador = 0;
	while (i < d.productosDisponibles().size()){
		if (d.productosDisponibles()[i] == p){
			++contador;
		}
		++i;
	}
}

Secuencia<Posicion> Sistema::parcelasAdyacentes (const Posicion &pos){
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