#ifndef HILO_H
#define	HILO_H

#include <pthread.h>
#include <iostream>

// Clase Abstracta utilizada para manipular un Hilo.

class Hilo {
	
	public:

		Hilo();
		virtual ~Hilo();
		virtual void iniciar();
		virtual void parar();    
		virtual void correr() = 0;
		virtual void sincronizar();
		bool corriendo();
		bool sincronizado();

	private:
		Hilo(const Hilo& orig) {}
		static void* llamarHilo(void* hilo);
		
		pthread_t hilo;
		bool _correr;
		bool _sincronizado;
};

#endif	/* HILO_H */

