#include "ManejadorEventosServidor.h"


ManejadorEventosServidor::ManejadorEventosServidor()
{
	mov = quietoder;
	for (int i = 0; i < CANT_TECLAS ; i++)
		teclasPresionadas[i] = 0 ;
}

ManejadorEventosServidor::~ManejadorEventosServidor() {}

void ManejadorEventosServidor::manejarEventos(Juego* juego) {
	if (juego == NULL) return;
	SDL_Event event;
	/*
	if (mov == derecha)
		mov = quietoder;
	if (mov == izquierda) 
		mov = quietoizq;
	*/
	bool salir = false;

	// Mientras haya eventos para manejar
	while( SDL_PollEvent( &event ) )
	{
		if( event.type == SDL_KEYUP ) teclasPresionadas[event.key.keysym.sym] = false;
		if( event.type == SDL_KEYDOWN ) teclasPresionadas[event.key.keysym.sym] = true;
		if( event.type == SDL_QUIT) salir = true;
	}

	if ( teclasPresionadas[SDLK_UP]) mov = arriba;
	if ( teclasPresionadas[SDLK_DOWN]) mov = abajo;
	if ( teclasPresionadas[SDLK_LEFT]) mov = izquierda;
	if ( teclasPresionadas[SDLK_RIGHT]) mov = derecha;

	// Si toco la cruz de salir, cambia el flag
	if( salir ) {
		juego->setActivo(false);
		
	}
	
}
