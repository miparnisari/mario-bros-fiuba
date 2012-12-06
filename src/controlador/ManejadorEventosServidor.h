#ifndef MANEJADOREVENTOSSERVIDOR_H
#define MANEJADOREVENTOSSERVIDOR_H

#define CANT_TECLAS 323
#include "SDL/SDL.h"
#include <map>
#include "../modelo/Juego.h"
#include "../controlador/Timer.h"
#include "../comun/Definiciones.h"
class Juego;

class ManejadorEventosServidor
{
	public:
		ManejadorEventosServidor();
		~ManejadorEventosServidor();
		void manejarEventos(Juego* juego);
			
	private:
		int teclasPresionadas[CANT_TECLAS];
		tipoMovimiento mov;
};

#endif
