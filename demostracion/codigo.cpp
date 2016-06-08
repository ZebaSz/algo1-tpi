if(_trayectoria.size() > 2) {
	int dirx = _trayectoria[0].x - _trayectoria[2].x;
	int diry = _trayectoria[0].y - _trayectoria[2].y;

	if(dirx == 0 || diry == 0) {
		escalerado = false;
	}
	int i = 0;

	// $ P_c $
	// vale $ escalerado == dirx \in [-1, 1] \land diry \in [-1, 1] $
	// implica $ escalerado == (\exists \ x, y \leftarrow [-1, 1]) $
	// $ (\prm{vueloRealizado(this)_0} - \prm{vueloRealizado(this)_2} == x $
	// $ \land \ \sgd{vueloRealizado(this)_0} - \sgd{vueloRealizado(this)_2} == y) $

	// I: $ 0 \leq i \leq \longitud{vueloRealizado(this)} -2 \land (\exists \ x, y \leftarrow [-1, 1]) (\forall j \leftarrow [0..i -1)) $
	// $ (\prm{vueloRealizado(this)_0} - \prm{vueloRealizado(this)_2} == x $
	// $ \land \ \sgd{vueloRealizado(this)_0} - \sgd{vueloRealizado(this)_2} == y) $

	// $ v = \longitud{vueloRealizado(this)} - i - 2 $
	// $ cota = 0 $

	while(escalerado && i < _trayectoria.size() - 2) {
		// E0
		// vale $ escalerado \land i < \longitud{vueloRealizado(this)} - 2) $
		// implica I
		escalerado = _trayectoria[i].x - _trayectoria[i + 2].x == dirx
					 && _trayectoria[i].y - _trayectoria[i + 2].y == diry;
		// E1
		// vale $ escalerado ==  $
		++i;
		// E2
		// vale $ escalerado == escalerado@E1 $
	}
	// $ Q_c $
	// vale $ escalerado == enVuelo(this) \land (\exists \ x, y \leftarrow [-1, 1]) (\forall i \leftarrow [0..\longitud{vueloRealizado(this)} - 2)) $
	// $ (\prm{vueloRealizado(this)_i} - \prm{vueloRealizado(this)_{i+2}} == x $
	// $ \land \ \sgd{vueloRealizado(this)_i} - \sgd{vueloRealizado(this)_{i+2}} == y) $
}