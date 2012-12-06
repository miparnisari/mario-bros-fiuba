#include "Imagen.h"
#include "../excepciones/Excepciones.h"


// IMPORTANTE: IMAGEN NO LIBERA AL POSICIONABLE, ESO LO HACE EL NIVEL
// LIBERANDO LA LISTA DE PERSONAJES, SE PUEDE DEBATIR IGUAL.

const string Imagen::TAG = "Imagen";

Imagen::Imagen(std::string nombreArchivo, Posicionable* elemento, int prior,int alto,int ancho, ID unID, std::string nombre) {
	this->nombreImagen = nombreArchivo;
	this->posicionable = elemento;
	this->prioridad = prior;
	this->alto = alto;
	this->ancho = ancho;
	this->myID = unID;
	this->nombre = nombre;
	this->activo = true;
	this->img = cargarImagen(nombreArchivo);
	if(this->img == NULL){
		Logger::error(TAG,  "No se pudo crear la imagen: " + nombreArchivo);
		throw ExceptionCargaImagen(nombreArchivo);
	}
}

Imagen::~Imagen() {
}

void Imagen::resizearImg(double factX, double factY){
	SDL_Surface* imgAux = NULL;
	imgAux = zoomSurface (this->img, factX, factY, 1);
	if (imgAux != NULL){
		SDL_FreeSurface(this->img);
		this->img = imgAux;
	}
}

void Imagen::rotarImg(int angulo){
	SDL_Surface* imgAux = NULL;
	imgAux = rotozoomSurface (this->img, angulo, 1, 1);
	if (imgAux != NULL){
		SDL_FreeSurface(this->img);
		this->img = imgAux;
	}
}

/** IMG_Load() puede levantar BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA y PNG. **/
SDL_Surface* Imagen::cargarImagen( std::string nombre ) {
    SDL_Surface* loadedImage = NULL;
    
    SDL_Surface* optimizedImage = NULL;
    
    loadedImage = IMG_Load( nombre.c_str() );
    
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        
        SDL_FreeSurface( loadedImage );

	}
	
    return optimizedImage;
}

double Imagen::setFactorXResize(int tam_nivel){
	return ((double)tam_nivel / (double)this->img->w);
}

double Imagen::setFactorYResize(int tam_nivel){
	return ((double)tam_nivel / (double)this->img->h);
}

void Imagen::setPos(Point* pos){
	this->posicionable->setPos(pos);
}

void Imagen::setActivo(bool valor){
	activo = valor;
}

void Imagen::setID(ID unID){
	myID = unID;
}

void Imagen::set_dimension(int ancho,int alto){
	this->alto = alto;
	this->ancho = ancho;
}

const int Imagen::getAlto(){
	return this->alto;
}

const int Imagen::getAncho(){
	return this->ancho;
}

const std::string Imagen::getNombre(){
	return this->nombreImagen;
}

std::string Imagen::getNombrePers(){
	return this->nombre;
}

SDL_Rect* Imagen::getCuadro(){
	// Este metodo se redefine en "Animacion.cpp"
	return NULL;
}

SDL_Surface* Imagen::getImg(){
	return this->img;
}

Point* Imagen::getPos(){
	return this->posicionable->getPos();
}

const ID Imagen::getID(){
	return this->myID;
}

const int Imagen::getPrioridad(){
	return this->prioridad;
}

const bool Imagen::getActivo(){
	return activo;
}
