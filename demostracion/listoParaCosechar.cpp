bool Sistema::listoParaCosechar() const
{
    int cantCosechables = 0;
    int cantCultivos = (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2;
    int i = 0;

// vale $ P_c $: $ cantCosechables == 0 \land i == 0$

    while (_campo.dimensiones().ancho * _campo.dimensiones().largo > i) {

// invariante $ I: 0 \leq i \leq (prm(dimensiones(campo(this))) \times sgd(dimensiones(campo(this))) $ $ \land | [1| x \leftarrow [0..i \div sgd(dimensiones(campo(this)))], $ $ y \leftarrow [0.. min(sgd(dimensiones(campo(this)), i - x * sgd(dimensiones(campo(this)))), $ $estadoDelCultivo((x,y), this) == ListoParaCosechar]| == cantCosechables $
// variante $ v : prm(dimensiones(campo(this)) \times sgd(dimensiones(campo(this))) - i $
// cota: 0

        if(_estado.parcelas[i/_campo.dimensiones().largo][i % _campo.dimensiones().largo] == ListoParaCosechar) {
            ++cantCosechables;
        }
        ++i;
    }

// vale $ Q_c : i == (prm(dimensiones(campo(this)) \times sgd(dimensiones(campo(this)))) \ \land cantCosechables == $$ | [1| x \leftarrow [0..prm(dimensiones(campo(this)))), y \leftarrow [0..sgd(dimensiones(campo(this)))), $$ estadoDelCultivo((x,y), this) == ListoParaCosechar] | $
    return (cantCosechables /(double) cantCultivos >= 0.9);
}