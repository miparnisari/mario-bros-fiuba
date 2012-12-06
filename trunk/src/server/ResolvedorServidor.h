#ifndef RESOLVEDORSERVIDOR_H
#define RESOLVEDORSERVIDOR_H
#include "../comun/Definiciones.h"
#include "../comun/Resolvedor.h"

#include "../eventos/EventoJugadorDesconectado.h"
#include "../eventos/EventoPersonajeSelect.h"
#include "../eventos/EventoMoverVista.h"
#include "../eventos/EventoVistasLoop.h"

class ControladorJugador;
class ControladorApp;
class Jugador;
class JugadorRemoto;

class ResolvedorServidor: public Resolvedor
{
	public:
		ResolvedorServidor(Conexiones* unaLista, ListaEstados* otraLista, Mutex* unMutex);
		~ResolvedorServidor();
		Evento* actualizarEstado(ID cliente,int tecla, bool teclaPresionada);
		Evento* desconectarJugador(ID cliente);
		Evento* personajeSelect(ID unID, std::string personaje);
		Evento* keepAlive(ID unID);
		void OKServidor(ID unID);
	
	private:
		static const string TAG;
		ListaEstados* listaE;
        Conexiones* listaC;
		Mutex* m;
};

#endif /* RESOLVEDORSERVIDOR_H */ 
