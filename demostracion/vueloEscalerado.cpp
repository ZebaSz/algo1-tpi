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
		// vale $ P_c : i == 1 \land enVuelo(this) \land \longitud{vueloRealizado(this)} > 2 \land $
		//    $ escalerado == (|dirx| == 1 \ \land |diry| == 1) $

		while(escalerado && i < _trayectoria.size() - 2) {

		// I: $ 1 \leq i \leq \longitud{vueloRealizado(this)} -2 \ \land $
		//    $ escalerado == (\forall j \leftarrow [0..i)) (\prm{vueloRealizado(this)_i} - \prm{vueloRealizado(this)_{i+2}} == dirx \ \land $ 
		//    $ \sgd{vueloRealizado(this)_i} - \sgd{vueloRealizado(this)_{i+2}} == diry) $
		// v: $ \longitud{vueloRealizado(this)} - i - 2 $

			escalerado = _trayectoria[i].x - _trayectoria[i + 2].x == dirx 
			&& _trayectoria[i].y - _trayectoria[i + 2].y == diry;
			++i;
		}

		// vale $ Q_c : escalerado == (\forall i \leftarrow [0..\longitud{vueloRealizado(this)} - 2)) (\prm{vueloRealizado(this)_i} - \prm{vueloRealizado(this)_{i+2}} == dirx  \land \ \sgd{vueloRealizado(this)_i} - \sgd{vueloRealizado(this)_{i+2}} == diry) $

	}
	return escalerado;
}