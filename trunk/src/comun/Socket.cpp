#include "Socket.h"
#include "Definiciones.h"
#include <cstring>       
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

#define tamBuff 1024
#define CONEX_EN_ESPERA 10

const string Socket::TAG = "Socket";

using namespace std;

Socket::Socket(Puerto puerto) {
	/*
	 * 
	 * 		struct timeval _timeout;
		struct sockaddr_in _direccion;
		* 
		* */
	Logger::info(TAG, "Socket constructor");
    this->_enlazado = false;
    this->_conectado = false;
    this->_puerto = puerto;

    this->_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_fd == -1) {
		Logger::error(TAG, "Error al crear el file descriptor de socket.");
		throw ExceptionConex("Error al crear el file descriptor de socket.");
    }

    
}

Socket::Socket(int fd) {
    this->_enlazado = false;
    this->_puerto = 0;
    this->_conectado = true;
    this->_fd = fd;
}

Socket::~Socket() {
	Logger::info(TAG, "Socket destructor.");
    int res = close(this->_fd);
    if (res != 0)
		Logger::info(TAG, "Error al cerrar el socket.");
}

void Socket::enlazar() {
	
	int opt = 1;
	if (setsockopt(_fd , IPPROTO_TCP, TCP_NODELAY, (const char *)&opt, sizeof(int)) < 0)
       Logger::error(TAG, "No se pudo setear NODELAY");
	if (setsockopt(_fd, SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int)) < 0)
		Logger::error(TAG, "No se pudo setear SO_REUSEADDR");
	if(setsockopt(_fd, SOL_SOCKET, SO_KEEPALIVE, (const char *)&opt,sizeof(int)) < 0) {
		Logger::error(TAG, "No se pudo setear SO_KEEPALIVE");
    }

    memset((char *)&_direccion, 0, sizeof(_direccion));
    _direccion.sin_family = AF_INET;
    _direccion.sin_port = htons(_puerto);
    _direccion.sin_addr.s_addr = INADDR_ANY;

    if (bind( _fd,
        (struct sockaddr *)&_direccion,
        (socklen_t)sizeof(struct sockaddr)) >= 0 ) {
        _enlazado = true;
        _conectado = true;
        listen(_fd, CONEX_EN_ESPERA);
    }
    else {
		Logger::error(TAG, "Enlace del socket fallido.");
		Logger::error(TAG, strerror(errno));
		throw ExceptionConex("Enlace del socket fallido.");
    }
}

Socket* Socket::escucharConexion() {
    if (_enlazado == false)
        return NULL;

    Socket *nsocket = NULL;
    int fd = 0;
    struct sockaddr_in nuevaDir;
    unsigned int cli_tam = (socklen_t) sizeof(nuevaDir);

    // Acepto la conexion entrante
    fd = accept(_fd, (struct sockaddr *)&nuevaDir, &cli_tam);

    if (_enlazado) {
        nsocket = new Socket(fd);
        memcpy(&nsocket->_direccion, &nuevaDir, sizeof(nuevaDir));
    }

    return nsocket;
}

void Socket::conectar(const std::string& huesped) {
	Utilitario u;
	if (! u.stringTieneSoloLetras (huesped)) {
		if (! u.esIPvalida(huesped)) {
			Logger::error(TAG, "Error al obtener el Host: " + huesped);
			throw ExceptionConex("Error al obtener el Host: " + huesped);
		}
	}
		
	Logger::info(TAG, "Socket conectar.");
    if (_enlazado == true || _conectado == true)
        return;

    struct hostent *he;

    he = gethostbyname(huesped.c_str());
    if (he == NULL) {
		Logger::error(TAG, "Error al obtener el Host: " + huesped);
        //_conectado = true;
        _conectado = false;
        throw ExceptionConex("Error al obtener el Host: " + huesped);
    }

    _direccion.sin_family = AF_INET;
    _direccion.sin_port = htons(_puerto);
    _direccion.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(_direccion.sin_zero), 8, sizeof(int));


    int resConexion = connect(_fd, (struct sockaddr *)&_direccion,sizeof(struct sockaddr));

    if (resConexion == -1) {
		Logger::error(TAG, "No existe servidor.");
        _conectado = false;
        throw ExceptionConex("No existe servidor.");
    }

    this->_conectado = true;
}

void Socket::desconectar() {
	Logger::info(TAG, "Socket desconectar.");
    this->_conectado = false;
    this->_enlazado = false;

    if (shutdown(_fd, SHUT_RDWR) == -1) {
		if (errno != ENOTCONN){
			Logger::error(TAG, "Error al cerrar conexion de Socket. ");
			throw ExceptionConex("Error al cerrar conexion de Socket. ");
		}
    }
}

bool Socket::enviar(VectorChar v){//const Mensaje& mensaje) {

	Utilitario u;
	size_t tam_datos = v.size();
	size_t cant_enviada = 0;

    int envActual = 0;
    std::string tam = u.convertirAString(tam_datos);
    tam += SEP_TAM;
    u.agregarCaracteresAlComienzo(v, tam);

    size_t tam_vectorAEnviar = v.size();

	while (cant_enviada < tam_vectorAEnviar && _conectado) {
		//envActual = send(_fd, datos + cant_enviada, (tam_datos - cant_enviada), 0);
		//envActual = send(_fd, &v[cant_enviada], tam_datos - cant_enviada, 0);
    		envActual = send(_fd, &v[cant_enviada], sizeof(char)*(tam_vectorAEnviar-cant_enviada), 0);
		
    		if (envActual <= 0) {
				printf ("enviar es false\n");
    			_conectado = false;
    			throw ExceptionConex("Error al enviar");
		} else cant_enviada += envActual;
    	}

    return _conectado;
}

bool Socket::recibirDatos(VectorChar& v){//std::string& datos){

	Utilitario u;
	int recibidos = 0;
	int i = 0;
	bool finDeMensaje = false;
	char charBuff;
//	char buffer[tamBuff];
	std::string tamanio = "";

	v.clear();

	while (finDeMensaje == false && _conectado) {
		//recibidos = recv(_fd, buff,sizeof(char)*TAM_BUFFER, 0);
		recibidos = recv(_fd, &charBuff,sizeof(char), 0);
		if (recibidos < 0) {
			perror("Error al recibir. ");
			printf("Error: %s\n", strerror(errno));
			Logger::error(TAG, "Error de socket, recibir < 0.");
			_conectado = false;
			throw ExceptionConex("Error de conexion");
		} else if (recibidos == 0) {
			Logger::error(TAG, "Error de socket, recibir == 0.");
			_conectado = false;
			throw ExceptionConex("Error de conexion");
		} else if (recibidos > 0) {
			finDeMensaje = (charBuff == SEP_TAM);
			if (!finDeMensaje) tamanio += charBuff;
		}
	}
	
	int tamNumerico = u.convertirAEntero(tamanio);

	while (i < tamNumerico && _conectado) {
		//recibidos = read(_fd, &buff, sizeof(char));
		//recibidos = recv(_fd, &buff,sizeof(char)*tamBuff, 0);
		recibidos = recv(_fd, &charBuff,sizeof(char), 0);
		if (recibidos < 0) {
			perror("Error al recibir. ");
			printf("Error: %s\n", strerror(errno));
			_conectado = false;
			Logger::error(TAG, "Error de conexion en el Socket. ");
			throw ExceptionConex("Error de conexion");
		} else if (recibidos == 0) {
			_conectado = false;
			Logger::error(TAG, "Error de conexion en el Socket. ");
			throw ExceptionConex("Error de conexion");
		} else if (recibidos > 0) {
			i += recibidos;
			v.push_back(charBuff);
		}
	}

	return _conectado;
}

bool Socket::conectado() {
    return this->_conectado;
}

void Socket::setTimeout(unsigned int segs, unsigned int microsegs){
	this->_timeout.tv_sec = segs;
	this->_timeout.tv_usec = microsegs;
}

bool Socket::timeoutCumplido(){
	int res = select(0,NULL,NULL,NULL,&_timeout);
	if (res) return false;
	else return true;
}


//    else {
//    	this->_timeout.tv_sec = 100;
//    	this->_timeout.tv_usec = 0;
//
//    	if (setsockopt(_fd, SOL_SOCKET, SO_SNDTIMEO, (void*) &_timeout, sizeof(_timeout)) == -1) {
//    		desconectar();
//    		return;
//    	}
//   }
