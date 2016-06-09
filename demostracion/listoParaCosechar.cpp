bool Sistema::listoParaCosechar() const
{
	int cantCosechables = 0;
	int cantCultivos = (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2;
	int x = 0;

// vale $ Pc_1 $: $ x == 0$

	while (_campo.dimensiones().ancho > x) {
		int y = 0;

// invariante $ I_1 $: $ 0 \leq x \leq prm(dimensiones(campo(this))) \land $ $ \longitud{[1| x \leftarrow [0..x), y \leftarrow [0..sgd(dimensiones(campo(this)))), estadoDelCultivo((x,y), this) == ListoParaCosechar]} $ $ == cantCosechables $

// variante $ v_1 $: $ prm(dimensiones(campo(this)) - x $

// $ cota1 = 0 $

// vale $ Pc_2 $: $ y = 0 $

		while(_campo.dimensiones().largo > y) {

// invariante $ I_2 $: $ 0 \leq y \leq sgd(dimensiones(campo(this))) \land $ $ \longitud{[1| x \leftarrow [0..x], y \leftarrow [0..y), estadoDelCultivo(((x,y)), this) == ListoParaCosechar]} $ $ == cantCosechables $

// variante $ v_2 $: $ sgd(dimensiones(campo(this))) - y $

// $ cota2 = 0 $

			if(_estado.parcelas[x][y] == ListoParaCosechar) {
				++cantCosechables;
			}
			++y;
		}

// vale $ Qc_2 $: $ \longitud{[1| x \leftarrow [0..x], y \leftarrow [0..sgd(dimensiones(campo(this)))), estadoDelCultivo((x,y), this) == ListoParaCosechar]} $ $ == cantCosechables $

		++x;
	}

// vale $ Qc_1 $: $ \longitud{[1| pos \leftarrow parcelasCultivo(campo(this)), estadoDelCultivo(pos, this) == ListoParaCosechar]} $ $ == cantCosechables $

	return (cantCosechables /(double) cantCultivos >= 0.9);
}
