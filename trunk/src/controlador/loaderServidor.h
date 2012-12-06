#ifndef LOADERSERVIDOR_H
#define LOADERSERVIDOR_H

#include "Loader.h"

#define PRIOR_NIVEL 0

class LoaderServidor : public Loader {
	
	public:
		LoaderServidor(std::string archConfig);
		~LoaderServidor();
		//void cargarMusica();
		list<PersonajeAnimado*> cargarPersonajes();
		Nivel* cargarNivel();
		void cargarElementos();
		void cargarElementosJuego(Nivel* nivel);
		void cargarElementosLista(std::string tipo, TextureHandler& handler, Nivel* nivel );
		int getDimensionEnemigo(std::string tipo, int* ancho, int* alto);
		
	 private:
		static const string TAG;
		list<LoadPersonaje*>* listaEnemigos;
		void cargarTexturas(vector<LoadTextura*>& texturas, TextureHandler& handler);
		Nivel* NivelCrear(int alto, int ancho);
		Protagonista* ProtagonistaCrear(LoadPersonaje* prot, ID cliente, float piso);
		void cargarPersonajes(ListaLoadPersonaje personajes, Nivel* nivel, float piso);
};


#endif /* LOADERSERVIDOR_H */ 

