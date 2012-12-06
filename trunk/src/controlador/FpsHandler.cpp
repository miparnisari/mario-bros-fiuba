#include "FpsHandler.h"

const string FpsHandler::TAG = "FpsHandler";

FpsHandler::FpsHandler(int cantidadFps)
{
	if (cantidadFps <= 0) {
		Logger::warn(TAG, "FPS <= 0. Se toma FPS por default: " + DEFAULT_FPS);
		cantidadFps = DEFAULT_FPS;
	}
	
	fps = cantidadFps;
}

void FpsHandler::setStart()
{
	start = SDL_GetTicks();
}

Uint32 FpsHandler::getTicks()
{
	 return SDL_GetTicks();
}

void FpsHandler::regularFps()
{
	if ( 1000 / fps > SDL_GetTicks() - start )
		SDL_Delay(1000 / fps - (SDL_GetTicks() - start));
}
