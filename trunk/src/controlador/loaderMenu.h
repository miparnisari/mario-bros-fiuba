#ifndef LOADERMENU_H
#define LOADERMENU_H

#include "Loader.h"

#define PRIOR_NIVEL 0

class LoaderMenu : public Loader{
	
	public:
		LoaderMenu(std::string archConfig);
		~LoaderMenu();
		
		list<st_PersMenu*>  cargarVistas();
		vector<string> cargarRutaArchivos();
		list<st_MusicSound*>  cargarMusica();
	
	 private:
		static const string TAG;
	
		vector<st_Animacion*>* cargarAnimaciones(list<LoadAnimacion*> animaciones);
};


#endif /* LOADERMENU_H */ 
