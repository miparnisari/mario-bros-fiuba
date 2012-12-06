#include "HiloResolverMovimientos.h"
#include "../modelo/Juego.h"
#include "../app/ControladorApp.h"
#include "../jugador/ControladorJugador.h"

using namespace std;
//port es el Puerto por el cual escuchará conexiones de los clientes.
HiloResolverMovimientos::HiloResolverMovimientos(ListaEstados* listaEs, ListaEventos* listaEv, Mutex* unMut):Hilo() {
    listaEstados = listaEs;
	listaEventos = listaEv;
	m = unMut;
}

HiloResolverMovimientos::~HiloResolverMovimientos() {
}


void HiloResolverMovimientos::correr() {
/*	while (this->corriendo()) {
//cout << "SERVER RESOLVER MOVIMIENTOS" << std::endl;
		m->lock();
		// Recorro la lista de estados y actualizo
//cout << "SIZE ESTADOS = " << listaEstados->size() << std::endl;
		Juego* juego = ControladorJugador::getInstance()->getControladorApp()->getServidor()->getJuego();
		if (!juego){
//cout << "JUEGO = NULL. detengo hiloresolvermovimientos" << listaEstados->size() << std::endl;
			m->unlock();
			this->parar();
			break;
		}
		
		for (IterListaEstados it = listaEstados->begin(); it != listaEstados->end(); it++){
			ID unID = (*it)->getID();
//cout << "Estado (ID- " << unID << ") " << std::endl;
			// Aca debo buscar al personaje dentro del modelo
			
			Protagonista* unProtagonista = juego->getProtagonista(unID);
			tipoMovimiento tipo;
			if (unProtagonista){
//cout << "Hay estado pero prot" << std::endl;
				if ((*it)->actualizarPosicion(unProtagonista->getMovimiento(), &tipo)){
					EventoMoverVista* ev = new EventoMoverVista(unID, (*it)->getPos(), tipo);
					// Agrego el evento a la lista eventos
//cout << "Agrego evento a la lista eventos " << std::endl;
					this->listaEventos->push_back(ev);
				}
//cout << "Hay estado pero prot == NULL" << std::endl;
		}
		
		m->unlock();
	}*/
}

bool HiloResolverMovimientos::activo() {
	return this->corriendo();
}
