#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H
#include "../other/Logger.h"
#include "SDL/SDL_mixer.h"
#include "../excepciones/Excepciones.h"
#include <map>
#include <string>
class SoundHandler
{
	public:
		SoundHandler();
		~SoundHandler();
		bool cargarSonido(std::string nombre, std::string tag);
		bool cargarMusica(std::string nombre, std::string tag);
		bool reproducirSonido(std::string tag) ;
		void detenerMusica();
		void pausarMusica() ;
		bool reproducirMusica(string tag);
		void continuarMusica();
	
	private:
		static const string TAG;
		map<std::string,Mix_Chunk*> sonidos;
		map<std::string,Mix_Music*> musicas;
};

#endif /* SOUNDHANDLER_H */ 
