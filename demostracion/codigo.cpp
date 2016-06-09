bool Drone::vueloEscalerado() const
{
	bool escalerado = _enVuelo;
	if(_trayectoria.size() > 2) {
	int dirx = _trayectoria[0].x - _trayectoria[2].x;
	int diry = _trayectoria[0].y - _trayectoria[2].y;

		if(dirx == 0 || diry == 0) {
			escalerado = false;
		}
		int i = 0;

// vale $ P_c $: $ escalerado == dirx \in [-1, 1] \land diry \in [-1, 1]$

		while(escalerado && i < _trayectoria.size() - 2) {
		
// invariante I: $ 0 \leq i \leq \longitud{vueloRealizado(this)} -2 \land (\exists \ x, y \leftarrow [-1, 1]) (\forall j \leftarrow [0..i -1) $ $ (\prm{vueloRealizado(this)_0} - \prm{vueloRealizado(this)_2} == x $ $ \land \ \sgd{vueloRealizado(this)_0} - \sgd{vueloRealizado(this)_2} == y) $

// variante v: $ \longitud{vueloRealizado(this)} - i - 2 $

// $ cota = 0 $

			escalerado = _trayectoria[i].x - _trayectoria[i + 2].x == dirx
					 && _trayectoria[i].y - _trayectoria[i + 2].y == diry;
			++i;
		}

// vale $ Q_c $: $ escalerado == (enVuelo(this) \land (\exists \ x, y \leftarrow [-1, 1]) (\forall i \leftarrow [0..\longitud{vueloRealizado(this)} - 2)) $ $ (\prm{vueloRealizado(this)_i} - \prm{vueloRealizado(this)_{i+2}} == x $ $ \land \ \sgd{vueloRealizado(this)_i} - \sgd{vueloRealizado(this)_{i+2}} == y)) $
	
	}
	return escalerado;
}

bool Sistema::listoParaCosechar() const
{
	int cantCosechables = 0;
	int cantCultivos = (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2;
	int x = 0;

// vale $ Pc_1 $: $ x == 0$

	while (_campo.dimensiones().ancho > x) {
		int y = 0;

// invariante $ I_1 $: $ 0 \leq x \leq prm(dimensiones(campo(this))) \land $ $ \longitud{[1| x \leftarrow [0..x), y \leftarrow [0..sgd(dimensiones(campo(this)))), pos \leftarrow (x,y), estadoDelCultivo(pos, this) == ListoParaCosechar]} $ $ == cantCosechables $

// variante $ v_1 $: $ prm(dimensiones(campo(this)) - x $

// $ cota1 = 0 $

// vale $ Pc_2 $: $ y = 0 $

		while(_campo.dimensiones().largo > y) {

// invariante $ I_2 $: $ 0 \leq y \leq sgd(dimensiones(campo(this))) \land $ $ \longitud{[1| x \leftarrow [0..x], y \leftarrow [0..y), pos \leftarrow (x,y), estadoDelCultivo(pos, this) == ListoParaCosechar]} $ $ == cantCosechables $

// variante $ v_2 $: $ sgd(dimensiones(campo(this))) - y $

// $ cota2 = 0 $

			if(_estado.parcelas[x][y] == ListoParaCosechar) {
				++cantCosechables;
			}
			++y;
		}

// vale $ Qc_2 $: $ \longitud{[1| x \leftarrow [0..x], y \leftarrow [0..sgd(dimensiones(campo(this)))), pos \leftarrow (x,y), estadoDelCultivo(pos, this) == ListoParaCosechar]} $ $ == cantCosechables $

		++x;
	}

// vale $ Qc_1 $: $ \longitud{[1| pos \leftarrow parcelasCultivo(campo(this)), estadoDelCultivo(pos, this) == ListoParaCosechar]} $ $ == cantCosechables $

	return (cantCosechables /(double) cantCultivos >= 0.9);
}
