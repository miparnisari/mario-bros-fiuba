#ifndef EVENTOTECLADO_H
#define EVENTOTECLADO_H

#include "../server/ResolvedorServidor.h"
#include "Evento.h"

class EventoTeclado: public Evento
{
	public:
		EventoTeclado(VectorChar v);
		EventoTeclado(ID unID, int unaTecla, bool unPres);
		VectorChar serializar();
		void hidratar(VectorChar v);
		Evento* actuar(ResolvedorServidor* res);
	private:
		int teclaPres;
		bool presionada;
};

#endif /* EVENTOTECLADO_H */ 
