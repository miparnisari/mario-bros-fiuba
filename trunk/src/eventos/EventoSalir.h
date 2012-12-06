#ifndef EVENTOSALIR_H
#define EVENTOSALIR_H
#include "../server/ResolvedorServidor.h"
#include "../comun/Utilitario.h"
#include "Evento.h"

class ControladorJugador;
class ControladorApp;

class EventoSalir: public Evento
{
	public:
		EventoSalir(VectorChar v);
		EventoSalir(ID unID);
		VectorChar serializar();
		void hidratar(VectorChar v);
		Evento* actuar(ResolvedorServidor* res);
};

#endif /* EVENTOSSALIR_H */ 
