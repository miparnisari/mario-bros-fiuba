#include "Evento.h"

Evento::Evento(VectorChar v)
{
	myID = ID_INVALIDO;
}

Evento::Evento()
{
	myID = ID_INVALIDO;
}

Evento::~Evento() 
{}

// Devuelve numero de cliente que genero el evento
int Evento::getID()
{
	return myID;
}

VectorChar serializar() {}
void Evento::hidratar(VectorChar v) {}
void Evento::actuar(ResolvedorJugador* res) {}
Evento* Evento::actuar(ResolvedorServidor* res) {}
