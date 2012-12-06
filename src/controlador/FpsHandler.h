#ifndef FPSHANDLER_H
#define FPSHANDLER_H

#include "SDL/SDL.h"
#include <stdlib.h>
#include "../other/Logger.h"
#include "../comun/Definiciones.h"

class FpsHandler 
{
	
	private:
		static const string TAG;
		Uint32 start;
		int fps;
		
	public:
		FpsHandler(int cantidadFps);
		Uint32 getTicks();
		void regularFps();
		void setStart();
};

#endif /* FPSHANDLER_H */ 
