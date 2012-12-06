#include "Animacion.h"

Animacion::Animacion(std::string nombre, Posicionable* animado, int prior,int alto, int ancho, vector<st_Animacion*> vectorAnimaciones, ID unId, std::string nombrePers)
					: Imagen(nombre, animado, prior,alto,ancho,unId, nombrePers)
{
	this-> frame = 0;  //Por defecto el frame 0 indica la posicion "quieto"
	this-> animado = animado;
	set_clips(vectorAnimaciones);
}

Animacion::~Animacion(){
	clips.clear();
}

void Animacion::set_clips(vector<st_Animacion*> vectorAnimaciones){
	
	for (int i = 0; i <= (vectorAnimaciones.size() - 1) ; i++ ){ //Recorro el vector de animaciones
		
		this->animaciones[vectorAnimaciones[i]->ejecucion] = (vectorAnimaciones[i]);
		
		for (int j = 0; j <= ((vectorAnimaciones[i]->cantidad) - 1) ; j++ ){ //Por cada animacion, copio las imagenes

			SDL_Rect clip;
			clip.x = (vectorAnimaciones[i]->offset) * ancho + (j * ancho);
			clip.y = 0; //El offset en Y siempre es cero, ya que estan en tira
			clip.w = ancho;
			clip.h = alto;

			(this->clips[vectorAnimaciones[i]->ejecucion]).push_back(clip);
		}
	}

}
