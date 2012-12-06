#include "loaderMenu.h"
#include "../vista/Imagen.h"
#include "../modelo/Elemento.h"

#include <iostream>
#define MAXPANT 2000
#define MINPANT 200
#define INVALIDO -1

const string LoaderMenu::TAG = "loaderMenu";


LoaderMenu::LoaderMenu(std::string archConfig) : Loader(archConfig){

}

LoaderMenu::~LoaderMenu() {
	//delete(parser);
}

list<st_MusicSound*> LoaderMenu::cargarMusica() {
	
	list<st_MusicSound*> lista;	

	this->parser->cargarMusica(&lista);
	this->parser->cargarSonido(&lista);

	return lista;
}


vector<st_Animacion*>* LoaderMenu::cargarAnimaciones(list<LoadAnimacion*> animaciones){
	
	vector<st_Animacion*>* vectorAnim = new vector<st_Animacion*>;;
	
	for (list<LoadAnimacion*>::iterator it = animaciones.begin(); it != animaciones.end(); ++it) {
		
		st_Animacion* a = new st_Animacion();
		a->offset = validar((*it)->getOffset());
		a->cantidad = validar((*it)->getCantidad());
		a->periodo = validar((*it)->getPeriodo());
		a->ejecucion= (*it)->getNombre();

		vectorAnim->push_back(a);
	}
	
	return vectorAnim;
}

list<st_PersMenu*> LoaderMenu::cargarVistas(){
			
	st_Nivel nivel;
	this->parser->cargarNivel(nivel);

	list<st_PersMenu*> listaAnimados;
	for(IterPersonajes it = nivel.listaProtagonistas.begin(); it != nivel.listaProtagonistas.end() ; ++it){ 
		st_PersMenu* pers = new st_PersMenu;
		pers->animaciones = cargarAnimaciones((*it)->animaciones);
		pers->ancho = validar((*it)->getAncho());
		pers->alto = validar((*it)->getAlto());
		pers->nombreImagen = "tmp/" + (*it)->getImagen();
		pers->nombrePers = (*it)->getNombre();
		pers->velocidad = validar((*it)->getVelocidad());
		pers->potenciaSalto = validar((*it)->getPotenciaSalto());
		listaAnimados.push_back(pers);
	}
	
	
	return listaAnimados;
}

vector<string> LoaderMenu::cargarRutaArchivos(){
	
	st_Nivel nivel;
	this->parser->cargarNivel(nivel);
	vector<string> listaRutas;
	
	listaRutas.push_back(nivel.fondo);
	listaRutas.push_back("images/boton.png");
	for(IterPersonajes it = nivel.listaProtagonistas.begin(); it != nivel.listaProtagonistas.end() ; ++it){ 
		listaRutas.push_back((*it)->getImagen());
	}
	for(IterPersonajes it = nivel.listaPersonajes.begin(); it != nivel.listaPersonajes.end() ; ++it){ 
		listaRutas.push_back((*it)->getImagen());
	}
	for(IterPersonajes it = nivel.listaEnemigos.begin(); it != nivel.listaEnemigos.end() ; ++it){ 
		listaRutas.push_back((*it)->getImagen());
	}
	vector<LoadTextura*>* datos = this->parser->cargarTexturas();
	for (vector<LoadTextura*>::iterator it = datos->begin() ; it != datos->end(); ++it ){
		 listaRutas.push_back((*it)->getFile());
	}
	listaRutas.push_back(nivel.vida->getImagen());
	listaRutas.push_back(this->parser->getNombreArchivo());
	return listaRutas;
}
