#include "EventoPersonajesUsados.h"
#include "../jugador/ControladorJugador.h"
#include "../app/ControladorApp.h"

EventoPersonajesUsados::EventoPersonajesUsados(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoPersonajesUsados::EventoPersonajesUsados(ListaParJugador* unaLista): Evento() {
	lista = unaLista;
}

EventoPersonajesUsados::~EventoPersonajesUsados() {
	//delete(lista);
}

VectorChar EventoPersonajesUsados::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_PERSONAJES_USADOS;
	mensaje += SEP;
	// Formato de la lista nombre-id|nombre-id|
	for (IterParJugador it = lista->begin() ; it != lista->end() ; ++it){
		mensaje += (*it)->first;
		mensaje += SEP_PAIR;
		mensaje += utilitario.convertirAString((*it)->second);
		mensaje += SEP_LISTA_PAIR;
	}
	
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoPersonajesUsados::hidratar(VectorChar v) {
	Utilitario utilitario;
	lista = new ListaParJugador; // FIXME! se esta sobrescribiendo lo del constructor
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	std::string listaSerializada = utilitario.separar(mensaje, SEP, 1);
	VectorChar aux;
	utilitario.agregarCaracteres(aux, listaSerializada);
	VectorChar campo;
	campo.push_back('a'); // le agrego algo para que entre al while
	int i = 0;
	while (not campo.empty()){
		// getCampo devuelve un vector vacio si no pudo encontrarlo
		campo = utilitario.getCampo(aux, SEP_LISTA_PAIR, i);
		if (not campo.empty()){
			VectorChar personaje = utilitario.getCampo(campo, SEP_PAIR, 0);
			VectorChar idSerializado = utilitario.getCampo(campo, SEP_PAIR, 1);
			ID unID = utilitario.convertirAEntero(utilitario.convertirVectorAString(idSerializado));
			parJugador* par = new parJugador(utilitario.convertirVectorAString(personaje), unID);
			lista->push_back(par);
		}
		i++;
	}
	
}

void EventoPersonajesUsados::actuar(ResolvedorJugador* res){
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	Logger::info("EventoPersonajesUsados", "Recibo EPU");
	// Aviso que llego la respuesta del servidor
	cj->setRespuesta(true);
	bool ok = false;
	ID unID = cj->getID();
	for (IterParJugador it = lista->begin() ; it != lista->end() ; ++it){
		if ((*it)->second == unID) {
			ok = true;
			break;
		}
	}
//	Logger::info("EventoPersonajesUsados", "Dsp de la iterar la lista");
//	if (ok) Logger::info("EventoPersonajesUsados", "Me encontraba en la lista");
	// Si yo estoy en la lista que me mandan, puedo arrancar el juego
	if (ok){
		ControladorApp::getInstance()->setEstado("El personaje estaba disponible.");
		Logger::info("EventoPersonajesUsados", "El personaje estaba disponible.");
		res->cargarLista(lista);
		
	// Sino debo informar y no hacer nada (queda en el menu de seleccion de pers)
	}else{
	//	ControladorJugador::getInstance()->setRespuesta(false);
		ControladorApp::getInstance()->setEstado("El personaje ya se encuentra seleccionado por otro jugador.");
		Logger::info("EventoPersonajesUsados", "El personaje ya se encuentra seleccionado por otro jugador.");
	}
}
