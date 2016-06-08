bool Drone::vueloEscalerado() const
{
	// E0
	bool escalerado = _enVuelo;
	// $ P_{if} $
	// vale $ escalerado = enVuelo(this) $
	if(_trayectoria.size() > 2) {
		int dirx = _trayectoria[0].x - _trayectoria[2].x;
		int diry = _trayectoria[0].y - _trayectoria[2].y;
		if(dirx == 0 || diry == 0) {
			escalerado = false;
		}
		int i = 0;
		while(escalerado && i < _trayectoria.size() - 2) {
			if(_trayectoria[i].x - _trayectoria[i + 2].x != dirx)
				escalerado = false;
			if(_trayectoria[i].y - _trayectoria[i + 2].y != diry)
				escalerado = false;
			++i;
		}
	}
	// Q_if
	// vale $ escalerado == enVuelo(this) \land (\exists \ x, y \leftarrow [1, -1]) (\forall i \leftarrow [0..\longitud{vueloRealizado(this)} - 2)) $
	// $ (\prm{vueloRealizado(this)_i} - \prm{vueloRealizado(this)_{i+2}} == x $
	// $ \wedge \ \sgd{vueloRealizado(this)_i} - \sgd{vueloRealizado(this)_{i+2}} == y) $
	return escalerado;
	// EF
	// vale $ res == escalerado $
	// implica $ res == enVuelo(this) \land (\exists \ x, y \leftarrow [1, -1]) (\forall i \leftarrow [0..\longitud{vueloRealizado(this)} - 2)) $
	// $ (\prm{vueloRealizado(this)_i} - \prm{vueloRealizado(this)_{i+2}} == x $
	// $ \wedge \ \sgd{vueloRealizado(this)_i} - \sgd{vueloRealizado(this)_{i+2}} == y) $
}