#include "EventoArchivo.h"
#include "../jugador/ControladorJugador.h"
#include "../app/ControladorApp.h"

const string EventoArchivo::TAG = "EventoArchivo";

EventoArchivo::EventoArchivo(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoArchivo::EventoArchivo(ID unID, std::string unArchivo): Evento() {
	myID = unID;
	archivo = unArchivo;
}

VectorChar EventoArchivo::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_ARCHIVO;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	mensaje += SEP;
	mensaje += archivo; // Mando el nombre del archivo
	mensaje += SEP;
	utilitario.agregarCaracteres(v, mensaje);
	// Hasta aca el vector tiene EVA;ID;NOMBRE_ARCH;
	// Leo el archivo y lo guardo en un string

	FILE* input = fopen(archivo.c_str(),"rb");
	
	if (input == NULL) return v;

	std::string m = "Enviando: " + archivo;
	ControladorApp::getInstance()->setEstado(m);
	Logger::info (TAG, m);
	
	unsigned char buffer;

	while (!feof(input) && !ferror(input) && fread(&buffer,sizeof(char),1,input) > 0){
		v.push_back(buffer);
	}
	
	fclose(input);
	return v;
}

void EventoArchivo::hidratar(VectorChar v) {
	Utilitario utilitario;
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	// consigue campo -> lo pasa a string -> lo pasa a entero.
	myID = utilitario.convertirAEntero(utilitario.convertirVectorAString(utilitario.getCampo(v, SEP, 1)));
/*	archivo = "[JUGADOR-";
	archivo += utilitario.convertirAString(myID);
	archivo += "]";*/
	archivo = DIR;
	archivo += "/"; // Agrego ruta de la carpeta donde voy a guardar los archivos
	
	archivo += utilitario.convertirVectorAString(utilitario.getCampo(v, SEP, 2));
	FILE* output = fopen(archivo.c_str(),"wb");

	int contador = 0;
	int i = 0;
	unsigned char buffer;
	
	std::string m = "Recibiendo: " + archivo;
	ControladorApp::getInstance()->setEstado(m);
	Logger::info (TAG, m);

	// Avanzo el indice hasta donde comienza el archivo y leo hasta el final
	while ( contador < 3 and i < v.size()) {
		if (v[i] == SEP) contador ++;
		i ++;
	}

	for(i ; i < v.size() ; i++){
		buffer = v[i];
		fwrite(&buffer, sizeof(char), 1, output);
	}
	
	fclose(output);
}

void EventoArchivo::actuar(ResolvedorJugador* res){

}
