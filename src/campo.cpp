#include "campo.h"

Campo::Campo()
{
}

Campo::Campo(const Posicion &posG, const Posicion &posC)
		: _dimension(std::max(posG.x, posC.x) + 1, std::max(posG.y, posC.y) + 1), _grilla(_dimension)
{
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
	size_t i = 0;
	while(i < _grilla.parcelas.size()) {
		size_t j = 0;
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
	size_t i = 0;
	while(i < _grilla.parcelas.size()) {
		os << "[";
		size_t j = 0;
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
	std::string dimen;
	std::getline(is, dimen, '[');
	std::getline(is, dimen, ',');
	_dimension.ancho = atoi(dimen.c_str());
	std::getline(is, dimen, ']');
	_dimension.largo = atoi(dimen.c_str());

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
			if(parcelastr == "Cultivo") parcela = Cultivo;
			if(parcelastr == "Casa") parcela = Casa;
			if(parcelastr == "Granero") parcela = Granero;

			_grilla.parcelas[i][j] = parcela;
			++j;
		}
		++i;
	}
}

bool Campo::operator==(const Campo & otroCampo) const
{
	bool iguales  = true;
	if(_dimension.ancho != otroCampo.dimensiones().ancho
	   || _dimension.largo != otroCampo.dimensiones().largo) {
		iguales = false;
	} else {
		int i = 0;
		while(i < _grilla.parcelas.size()) {
			int j = 0;
			while(j < _grilla.parcelas[i].size()) {
				Posicion pos;
				pos.x = i;
				pos.y = j;
				if(_grilla.parcelas[i][j] != otroCampo.contenido(pos)) {
					iguales = false;
				}
				++j;
			}
			++i;
		}
	}
	return iguales;
}

std::ostream & operator<<(std::ostream & os, const Campo & c)
{
	c.mostrar(os);
	return os;
}

// TODO preguntar sobre estos operadores
// Algunos no corresponden a campo, deberían estar en otro lado
// Preguntar a De Cristóforis

static const char* TipoParcela[] = {"Cultivo", "Granero", "Casa"};
std::ostream & operator<<(std::ostream & os, const Parcela & p)
{
	std::string pstring = TipoParcela[p];
	os << pstring;
	return os;
}
