#ifndef VENTANA_H
#define VENTANA_H

#include <map>
#include <list>
#include "Solapa.h"

class Ventana
{
	public:
		Ventana(std::string nombre);
		virtual ~Ventana();
		
		const string getNombre();
		list<Componente*>& getComponentes();
		bool refrescar(SDL_Surface* destino);
		void manejarEventos(SDL_Event evento);
		void activarSolapa(string nombre);
		void agregarSolapa(Solapa* solapa);
		void agregarComponente(Componente* unComp);
	
	private:
		Solapa*						solapaActiva;
		std::list<Componente*>		componentes;
		std::string 				nombre;
		map<std::string,Solapa*>	solapas;
};

#endif /* VENTANA_H */ 
