#include "campo.h"

Campo::Campo()
{
}

Campo::Campo(const Posicion &posG, const Posicion &posC)
{
	_dimension.ancho = std::max(posG.x, posC.x) + 1;
	_dimension.largo = std::max(posG.y, posC.y) + 1;

	_grilla = Grilla<Parcela>(_dimension);

	_grilla.parcelas[posG.x][posG.y] = Granero;
	_grilla.parcelas[posC.x][posC.y] = Casa;

}

Dimension Campo::dimensiones() const
{
	return _dimension;
}

Parcela Campo::contenido(const Posicion & p) const
{
	return _grilla.parcelas[p.x][p.y];
}

void Campo::mostrar(std::ostream & os) const
{
	os << "Campo con dimensiones [" << _dimension.ancho << "," << _dimension.largo << "]:" << std::endl;
	int i = 0;
	while(i < _grilla.parcelas.size()) {
		int j = 0;
		while(j < _grilla.parcelas[i].size()) {
			os << _grilla.parcelas[i][j];
			if(_dimension.largo - j > 1) {
				os << "\t";
			}
			++j;
		}
		os << std::endl;
		++i;
	}
}

void Campo::guardar(std::ostream & os) const
{
	os << "{ C [" << _dimension.ancho << "," << _dimension.largo << "] [";
	int i = 0;
	while(i < _grilla.parcelas.size()) {
		os << "[";
		int j = 0;
		while(j < _grilla.parcelas[i].size()) {
			os << _grilla.parcelas[i][j];
			if(_dimension.largo - j > 1) {
				os << ",";
			}
			++j;
		}
		os << "]";
		if(_dimension.ancho - i > 1) {
			os << ", ";
		}
		++i;
	}
	os << "] }";
}

void Campo::cargar(std::istream & is)
{
	// TODO implementar
	std::string dimen;
	std::getline(is, dimen, '[');
	std::getline(is, dimen, ',');
	_dimension.ancho = atoi (dimen.c_str());
	std::getline(is, dimen, ']');
	_dimension.largo = atoi (dimen.c_str());

	_grilla = Grilla<Parcela>(_dimension);

	std::string parcelastr;
	std::getline(is, parcelastr, '[');
	int i = 0;
	while(i < _dimension.ancho) {
		std::getline(is, parcelastr, '[');
		int j = 0;
		while(j < _dimension.largo) {
			if(_dimension.largo - j == 1) {
				std::getline(is, parcelastr, ']');
			} else {
				std::getline(is, parcelastr, ',');
			}
			Parcela parcela;
			if(parcelastr == "Cultivo") {
				parcela = Cultivo;
			} else if(parcelastr == "Casa") {
				parcela = Casa;
			} else if(parcelastr == "Granero") {
				parcela = Granero;
			}
			_grilla.parcelas[i][j] = parcela;
			++j;
		}
		++i;
	}
}

bool Campo::operator==(const Campo & otroCampo) const
{
	if(this == &otroCampo) {
		return true;
	}
	if(_dimension.ancho != otroCampo.dimensiones().ancho
	   || _dimension.largo != otroCampo.dimensiones().largo) {
		return false;
	}
	int i = 0;
	while(i < _grilla.parcelas.size()) {
		int j = 0;
		while(j < _grilla.parcelas[i].size()) {
			Posicion pos;
			pos.x = i;
			pos.y = j;
			if(_grilla.parcelas[i][j] != otroCampo.contenido(pos)) {
				return false;
			}
			++j;
		}
		++i;
	}
	return true;
}

std::ostream & operator<<(std::ostream & os, const Campo & c)
{
	c.mostrar(os);
	return os;
}

std::ostream & operator<<(std::ostream & os, const Parcela & p)
{
	std::string pstring;
	if(p == Casa) pstring = "Casa";
	if(p == Granero) pstring = "Granero";
	if(p == Cultivo) pstring = "Cultivo";
	os << pstring;
	return os;
}

std::ostream & operator<<(std::ostream & os, const Producto & p)
{
	std::string pstring;
	if(p == Fertilizante) pstring = "Fertilizante";
	if(p == Plaguicida) pstring = "Plaguicida";
	if(p == PlaguicidaBajoConsumo) pstring = "PlaguicidaBajoConsumo";
	if(p == Herbicida) pstring = "Herbicida";
	if(p == HerbicidaLargoAlcance) pstring = "HerbicidaLargoAlcance";
	os << pstring;
	return os;
}

std::ostream & operator<<(std::ostream & os, const EstadoCultivo & e)
{
	std::string estring;
	if(e == RecienSembrado) estring = "RecienSembrado";
	if(e == EnCrecimiento) estring = "EnCrecimiento";
	if(e == ListoParaCosechar) estring = "ListoParaCosechar";
	if(e == ConMaleza) estring = "ConMaleza";
	if(e == ConPlaga) estring = "ConPlaga";
	if(e == NoSensado) estring = "NoSensado";
	os << estring;
	return os;
}
