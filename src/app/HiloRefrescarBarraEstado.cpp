/*#include "HiloRefrescarBarraEstado.h"
#include "../app/ControladorApp.h"

HiloRefrescarBarraEstado::HiloRefrescarBarraEstado(SDL_Surface* surf, BarraDeEstado* unaB, Mutex* unMut):Hilo() {
	this->mutex = unMut;
	this->barra = unaB;
	this->surface = surf;
}

HiloRefrescarBarraEstado::~HiloRefrescarBarraEstado()
{
	
}

void HiloRefrescarBarraEstado::correr() {
	while (corriendo()) {
		int res = SDL_LockSurface(this->surface);
		if (res == 0) {
			//std::cout << "entro al while" << std::endl;
			mutex->lock();
			//std::cout << "luego del lock" << std::endl;
			this->barra->refrescar(this->surface);
			//std::cout << "luego del refrescar" << std::endl;
			mutex->unlock();
			//std::cout << "fin" << std::endl;
			SDL_UnlockSurface(this->surface);
		}
	}
}
*/
