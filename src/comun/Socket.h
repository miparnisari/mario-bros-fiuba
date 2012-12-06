#ifndef SOCKET_H
#define	SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include "Definiciones.h"
#include "Utilitario.h"
#include "../excepciones/Excepciones.h"
#include "../other/Logger.h"

class Mensaje;

class Socket {
	public:
	 	explicit Socket(Puerto puerto);
		virtual ~Socket();
		void conectar(const std::string& huesped);
	  	void enlazar();
	  	Socket* escucharConexion();
		bool enviar(VectorChar v);//std::string mens);//const Mensaje& mensaje);
		void desconectar();
		bool conectado();
		bool recibirDatos(VectorChar& datos);//std::string& datos);
		void setTimeout(unsigned int segs, unsigned int microsegs);
		bool timeoutCumplido();

	private:
		static const string TAG;
		struct timeval _timeout;
		int _fd;
		struct sockaddr_in _direccion;
		Puerto _puerto;
		bool _conectado;
		bool _enlazado;
		
		explicit Socket(int fd);
		Socket(const Socket& orig) {}
		//void operator=(const Socket& orig) {}
};

#endif	/* SOCKET_H */

