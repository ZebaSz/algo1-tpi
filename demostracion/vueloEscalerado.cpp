bool Drone::vueloEscalerado() const
{
	bool escalerado = _enVuelo;
	if(_trayectoria.size() > 2) {
	int dirx = _trayectoria[0].x - _trayectoria[2].x;
	int diry = _trayectoria[0].y - _trayectoria[2].y;

		if(dirx == 0 || diry == 0) {
			escalerado = false;
		}
		int i = 1;
// estado E1
// vale $ dirx == \prm{vueloRealizado(this)_0} - \prm{vueloRealizado(this)_2} $
// vale $ diry == \sgd{vueloRealizado(this)_0} - \sgd{vueloRealizado(this)_2} $
// vale $ P_c $: $ i = 1 \land \longitud{vueloRealizado(this)} > 2 \land escalerado == (abs(dirx) == abs(diry)) $

		while(escalerado && i < _trayectoria.size() - 2) {
		
// invariante $ I: 1 \leq i \leq \longitud{vueloRealizado(this)} -2 \land escalerado == (abs(dirx) == abs(diry) \land (\forall j \leftarrow [0..i) $ $ (\prm{vueloRealizado(this)_j} - \prm{vueloRealizado(this)_{j+2}} == dirx $ $ \land \ \sgd{vueloRealizado(this)_j} - \sgd{vueloRealizado(this)_{j+2}} == diry) $
// variante $ f_v: \longitud{vueloRealizado(this)} - i - 2 $
// cota = 0

			escalerado = _trayectoria[i].x - _trayectoria[i + 2].x == dirx 
			&& _trayectoria[i].y - _trayectoria[i + 2].y == diry;
			++i;
		}

// vale $ Q_c $: $ escalerado == (abs(dirx) == abs(diry) \ \land \ (\forall j \leftarrow [0..\longitud{vueloRealizado(this)} - 2)) $ $ (\prm{vueloRealizado(this)_j} - \prm{vueloRealizado(this)_{j+2}} == dirx  \land \ $ $ \sgd{vueloRealizado(this)_j} - \sgd{vueloRealizado(this)_{j+2}} == diry) $

	}
	return escalerado;
}