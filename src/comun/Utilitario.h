#ifndef UTILITARIO_H_
#define UTILITARIO_H_
#include <string>
#include <vector>
#include "Definiciones.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>

class Utilitario {
	
	public:
		Utilitario();
		virtual ~Utilitario();
		
		bool esIPvalida(std::string ipAddress);
		bool esPuertoValido(std::string unPuerto);
		bool charEsLetra(char c);
		bool charEsNumero(char c);
		bool stringTieneSoloNumeros(std::string s);
		bool stringTieneSoloLetras (std::string s);
		std::string separar(const std::string& datos, const char separador, const size_t indice);
		std::string convertirAString(const int& numero) const;
		int convertirAEntero(const std::string& numero) const;
		void borrarCaracter(std::string& palabra, const char caracter);
		std::string ultimosCaracteres(int n, std::string& cadena);
		std::string convertirVectorAString(VectorChar v);
		void agregarCaracteres(VectorChar& v, std::string s);
		void agregarCaracteresAlComienzo(VectorChar& v, std::string s);
		VectorChar getCampo(VectorChar v, char separador, int index);
		
	private:
		std::vector<size_t> _posiciones;
		std::string s_anterior;
		char sep_anterior;
};

#endif /* UTILITARIO_H_ */
