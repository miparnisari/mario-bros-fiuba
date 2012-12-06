#include "EventoEnviarArchivos.h"

using namespace std;

const string EventoEnviarArchivos::TAG = "EventoEnviarArchivos";

EventoEnviarArchivos::EventoEnviarArchivos(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoEnviarArchivos::EventoEnviarArchivos(ID unID, string unDir): Evento() {
	myID = unID;
	dir = unDir;
}

void EventoEnviarArchivos::crearDirectorio(string unDirect) {
	int resultado = mkdir((unDirect).c_str() , S_IRWXU);
	
	if (resultado == 0 || errno == EEXIST ) {
		Logger::info(TAG, "Directorio: " + unDirect + " se ha creado exitosamente.");
	}
	else {
		Logger::info(TAG, "Error al crear el directorio: " + unDirect);
	}
}

VectorChar EventoEnviarArchivos::serializar(){
	Utilitario utilitario;
	VectorChar v;
	string mensaje = EVENTO_ENV_ARCHIVOS;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	mensaje += SEP;
	mensaje += dir; // Mando el nombre del archivo
	mensaje += SEP;
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoEnviarArchivos::hidratar(VectorChar v) {
	Utilitario utilitario;
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	// consigue campo -> lo pasa a string -> lo pasa a entero.
	myID = utilitario.convertirAEntero(utilitario.convertirVectorAString(utilitario.getCampo(v, SEP, 1)));
	dir += utilitario.convertirVectorAString(utilitario.getCampo(v, SEP, 2));
}

void EventoEnviarArchivos::actuar(ResolvedorJugador* res){
	
	crearDirectorio(this->dir);
	
	string dirImg = this->dir + "/images";
	string dirSound = this->dir + "/sounds";
	string dirLevel = this->dir + "/niveles";
	
	crearDirectorio(dirImg);
	crearDirectorio(dirSound);
	crearDirectorio(dirLevel);
}
