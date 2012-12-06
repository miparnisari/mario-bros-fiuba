#include "EventoArchivoNivel.h"


EventoArchivoNivel::EventoArchivoNivel(VectorChar v): EventoArchivo(v) {
}

EventoArchivoNivel::EventoArchivoNivel(ID unID, std::string unArchivo): EventoArchivo(unID, unArchivo) {
}

VectorChar EventoArchivoNivel::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_ARCHIVO;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	mensaje += SEP;
	mensaje += "config.yaml"; // Mando el archivo con el nombre default para la carga de niveles
	mensaje += SEP;
	utilitario.agregarCaracteres(v, mensaje);
	// Hasta aca el vector tiene EVA;ID;NOMBRE_ARCH;
	// Leo el archivo y lo guardo en un string

	FILE* input = fopen(archivo.c_str(),"rb");
	
	if (input == NULL) return v;
	
	unsigned char buffer;

	while (!feof(input) and !ferror(input) and (fread(&buffer,sizeof(char),1,input)) > 0){
		v.push_back(buffer);
	}
	
	fclose(input);
	return v;
}
