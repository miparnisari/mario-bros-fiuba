#include "Ventana.h"

using namespace std;

Ventana::Ventana(string nombr) 
{
	this->nombre = nombr;
	this->solapaActiva = NULL;
}

const string Ventana::getNombre() {
	return nombre;
}

list<Componente*>& Ventana::getComponentes() {
	if (solapaActiva)
		return (this->solapaActiva->getComponentes());
	else
		return (this->componentes);
}

bool Ventana::refrescar(SDL_Surface* destino) {
	// Refrescamos los componentes
	list<Componente*>::iterator it;
    for ( it=componentes.begin() ; it != componentes.end(); ++it ) {
		(*it)->refrescar(destino);
	}
	
	// Refrescamos los componentes de las solapas
	map<string,Solapa*>::iterator iter;
	for ( iter=solapas.begin() ; iter != solapas.end(); ++iter ) {
		(iter->second)->refrescar(destino);
	}
}

void Ventana::agregarComponente(Componente* unComp) {
	this->componentes.push_front(unComp);
}

void Ventana::manejarEventos(SDL_Event evento) {
	
	// Si hay solapas, activamos la que fue presionada
	map<string,Solapa*>::iterator iter;
	for ( iter=solapas.begin() ; iter != solapas.end(); ++iter) {
		bool sActiva = iter->second->isActive();
		bool bPresionado = iter->second->getBotonAsociado()->fuePresionado(evento);
		if (!sActiva && bPresionado) {
			this->activarSolapa(iter->first);
		}
	}
	if (this->solapaActiva)
		this->solapaActiva->manejarEventos(evento);
	
	list<Componente*>::iterator it;
	for ( it=componentes.begin() ; it != componentes.end(); ++it ) {
		(*it)->manejarEventos(evento);
	}
	

}

void Ventana::activarSolapa(string nombre) {
	map<string,Solapa*>::iterator iter;
	for ( iter=solapas.begin() ; iter != solapas.end(); ++iter ) {
		if ((iter->first) == nombre) {
			this->solapaActiva = iter->second;
			this->solapaActiva->setActive(true);
			
		}
		else {
			(iter->second)->setActive(false);
		}
	}
}

void Ventana::agregarSolapa(Solapa* solapa) {
	if (solapas.empty()) {
		this->solapaActiva = solapa;
		this->solapaActiva->setActive(true);
	}
	
	
	int size = solapas.size();
	
	int x, y, w, h;
	
	if (size == 0) {
		x = MENU_INNER_BORDER;
		y = MENU_INNER_BORDER;
		w = ANCHO_BOTON;
		h = ALTO_BOTON;
		this->solapaActiva = solapa;
	} else {
		x = MENU_INNER_BORDER + 15 + (size*ANCHO_BOTON);
		y = MENU_INNER_BORDER;
		w = ANCHO_BOTON;
		h = ALTO_BOTON;
	}
	
	solapa->setBotonAsociado(x,y,w,h);
	this->solapas.insert(pair<string,Solapa*>(solapa->getNombre(),solapa));
} 


Ventana::~Ventana()
{
	list<Componente*>::iterator it;
    for ( it=componentes.begin() ; it != componentes.end(); ++it ) {
		delete(*it);
		*it = NULL;
	}
	
	map<std::string,Solapa*>::iterator iter;
	for ( iter=solapas.begin() ; iter != solapas.end(); ++iter ) {
		delete (iter->second);
		iter->second = NULL;
	}
	
	this->solapaActiva = NULL;
}

