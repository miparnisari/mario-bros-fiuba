#include "HiloEnviarJug.h"


HiloEnviarJug::HiloEnviarJug(Conexiones* conex, ListaEventos* listaEv, Mutex* unMut):Hilo() {
	conexiones = conex;
	m = unMut;
	listaEventos = listaEv;
}

HiloEnviarJug::~HiloEnviarJug() {

}

void HiloEnviarJug::correr() {
	while (corriendo()) {
		m->lock();
		for (IterListaEventos it = listaEventos->begin(); it != listaEventos->end(); ++it){
			for (IterConexiones itConex = conexiones->begin(); itConex != conexiones->end(); ++itConex){
//cout << "envio evento de lista eventos" << std::endl;
				(*itConex)->enviar(*it);
			}
			delete (*it);

		}
		m->unlock();
	}
}

