#ifndef MANEJADOREVENTOS_H
#define MANEJADOREVENTOS_H

class ManejadorEventos
{
	public:
		ManejadorEventos();
		virtual ~ManejadorEventos();
		virtual void manejarEventos() = 0;
};

#endif /* MANEJADOREVENTOS_H */ 
