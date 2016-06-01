#include "tipos.h"

std::ostream & operator<<(std::ostream & os, const Parcela & p)
{
    std::string pstring = TipoParcela[p];
    os << pstring;
    return os;
}

std::ostream & operator<<(std::ostream & os, const Producto & p)
{
    std::string pstring = TipoProducto[p];
    os << pstring;
    return os;
}

std::ostream & operator<<(std::ostream & os, const EstadoCultivo & e)
{
    std::string estring = TipoEstado[e];
    os << estring;
    return os;
}

const bool operator==(const Posicion &p1, const Posicion &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

const bool operator==(const InfoVueloCruzado &a, const InfoVueloCruzado &b) {
    return a.posicion == b.posicion && a.cantidadCruces == b.cantidadCruces;
}