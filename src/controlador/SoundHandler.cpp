#include "SoundHandler.h"
#include "../excepciones/Excepciones.h"
using namespace std;

const string SoundHandler::TAG = "SoundHandler";

SoundHandler::SoundHandler() {
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
		Logger::error(TAG, "Error al construir la clase.");
		throw ExceptionSoundHandler();
	}
}

SoundHandler::~SoundHandler() {
	Mix_HaltMusic();
	map<string,Mix_Chunk*>::iterator itS;
	 for ( itS = sonidos.begin() ; itS != sonidos.end(); ++itS )
		 Mix_FreeChunk( (itS->second) );
		 
	map<string,Mix_Music*>::iterator itM;
	for ( itM = musicas.begin() ; itM != musicas.end(); ++itM )
		 Mix_FreeMusic( (itM->second) );
		 
	Logger::info(TAG, "Sonidos y musicas destruidos correctamente.");
}

bool SoundHandler::cargarMusica(string nombre, string tag) {
//	std::cout << "SH CARGARMUSICA; TAG:" << tag << " NOMBRE:" << nombre << "\n";
	Mix_Music* sound = Mix_LoadMUS( nombre.c_str() );
	if ( !sound ){ 
		Logger::error(TAG, "No se pudo cargar el sonido " + nombre);
		throw ExceptionCargaMusica(nombre);
	}
		
	musicas[tag] = sound;
//	std::cout << "SH CARGO " << tag << "\n";
	return true;
}

bool SoundHandler::cargarSonido(string nombre, string tag) {
//	std::cout << "SH CARGARSONIDO; TAG:" << tag << " NOMBRE:" << nombre << "\n";
	Mix_Chunk* sound = Mix_LoadWAV( nombre.c_str() );
	if ( !sound ){
		Logger::error(TAG, "No se pudo cargar el sonido " + nombre);
		throw ExceptionCargaSonido(nombre);
	}
	sonidos[tag] = sound;
//	std::cout << "SH CARGO " << tag << "\n";
	return sound ;
}


bool SoundHandler::reproducirSonido(string tag) {
	if (sonidos.find(tag) == sonidos.end()){
		Logger::error(TAG, "El sonido " + tag + " no se encuentra cargado en el handler.");
		return false;
	}
	
	if ( !Mix_PlayChannel( -1, sonidos[tag], 0 )) {
		Logger::error(TAG, "No se pudo reproducir " + tag);
		return false;
	}
	
	return true;
}

bool SoundHandler::reproducirMusica(string tag) {
	if (musicas.find(tag) == musicas.end()){
		Logger::error(TAG, "La musica " + tag + " no se encuentra cargada en el handler.");
		return false;
	}
	
	if (Mix_PlayMusic( musicas[tag], -1 ) == -1 ){
		// -1 de parametro para que suene en un loop
		Logger::error(TAG, "No se pudo reproducir " + tag);
		return false;
	}
//	std::cout << "SH REPRODUCIR" << tag << "\n";
	return true;
}

void SoundHandler::pausarMusica() {
	Mix_PausedMusic();
}

void SoundHandler::detenerMusica() {
	Mix_HaltMusic();
}

void SoundHandler::continuarMusica() {
	if( Mix_PausedMusic() == 1 ) {
		Mix_ResumeMusic();
	}
}
