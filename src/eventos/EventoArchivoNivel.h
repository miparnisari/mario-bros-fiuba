#ifndef EVENTOARCHIVONIVEL_H
#define EVENTOARCHIVONIVEL_H

#include <iostream>
#include <fstream>
#include "../other/Logger.h"
#include "EventoArchivo.h"

class EventoArchivoNivel: public EventoArchivo
{
	public:
		EventoArchivoNivel(VectorChar v);
		EventoArchivoNivel(ID unID, std::string archivo);
		VectorChar serializar();
		
};

#endif /* EVENTOARCHIVONivel_H */ 
