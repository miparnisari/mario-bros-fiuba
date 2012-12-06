#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H
#include "../other/Logger.h"
#include <ctime>

class Temporizador
{
	public:
		Temporizador();
		bool puedeRealizarAccion();
		void setTiempoInicial();
		void setIntervalo(double inter);
		bool contando;
		
	private:
		static const std::string TAG;
		time_t start,end;
		double intervalo;		
		
};

#endif /* TEMPORIZADOR_H */ 
