#ifndef EVENTO_H
#define EVENTO_H
#include "../comun/Definiciones.h"
#include "../comun/Mensaje.h"
#include "../comun/Utilitario.h"

class ResolvedorJugador;
class ResolvedorServidor;

class Evento{
	
	public:
		Evento(VectorChar v);//VectorChar v);
		Evento();
		virtual ~Evento();
		virtual VectorChar serializar() = 0;
		virtual void hidratar(VectorChar v) = 0;
		int getID();
		virtual void actuar(ResolvedorJugador* res);
		virtual Evento* actuar(ResolvedorServidor* res);
		
    protected:
        ID myID;
};

#endif /* EVENTO_H */ 
