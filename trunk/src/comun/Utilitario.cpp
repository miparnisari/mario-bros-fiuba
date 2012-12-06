#include "Utilitario.h"
#include "Definiciones.h"

using namespace std;

Utilitario::Utilitario() {
	s_anterior.clear();
	_posiciones.clear();
	sep_anterior = 0;
}

Utilitario::~Utilitario() {
}

bool Utilitario::esIPvalida(string ipAddress) {
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
	return result != 0;
}

bool Utilitario::esPuertoValido(string unPuerto) {
	if (! stringTieneSoloNumeros(unPuerto) || unPuerto.empty() )
		return false;
	return true;
}

bool Utilitario::charEsNumero(char c) {
	vector<char> v;
	for (char i = '0'; i <= '9'; i++) {
		v.push_back(i);
	}
	
	for (int i = 0; i < v.size(); i++) {
		if (c == v[i])
			return true;
	}
	return false;
}

bool Utilitario::charEsLetra(char c) {
	if (charEsNumero(c)) return false;
	return true;
}

bool Utilitario::stringTieneSoloNumeros(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (! charEsNumero(s.at(i)))
			return false;
	}
	return true;
}

bool Utilitario::stringTieneSoloLetras (string s) {
	for (int i = 0; i < s.size(); i++) {
		if (! charEsLetra(s.at(i)))
			return false;
	}
	
	return true;
}

string Utilitario::separar(const string& datos, const char separador, const size_t indice) {


	if (s_anterior != datos || sep_anterior != separador) {
		_posiciones.clear();
		s_anterior.clear();
		s_anterior = datos;
		sep_anterior = separador;
		bool hayMasSeparadores = true;
		size_t pos_sep = -1;
		size_t cant_sep = 0;
		while (hayMasSeparadores) {
			pos_sep = datos.find(separador, pos_sep + 1);

			if (pos_sep != std::string::npos) {
				_posiciones.push_back(pos_sep);
				cant_sep++;
			}
			else{
				hayMasSeparadores = false;
			}
		}
	}

	// si no tiene separadores retorna le dato entero para "indice" = 0
	if ((_posiciones.empty()) && (indice == 0)) {
		return datos;
	}

	if ( (not _posiciones.empty()) && _posiciones.size() >= indice) {
		std::string arg;
		if (indice == 0) {
			arg = datos;
			arg.resize(_posiciones[0]);
		}
		else {
			arg = &datos.c_str()[_posiciones[indice - 1] + 1];
		}

		// caso para el ultimo argumento
		if (indice == _posiciones.size())
			arg.resize(datos.size() - _posiciones[indice - 1] - 1);
		else if (indice > 0)
			arg.resize(_posiciones[indice] - _posiciones[indice - 1] - 1);

		return arg;
	}
	else {
		// retorno string nulo si indice > cantArgumentos
		return STR_NULA;
	}
}


std::string Utilitario::convertirAString(const int& numero) const {
	std::stringstream ss;
	std::string res;


	if (numero == 0)
		res = "0";
	else {
		ss << numero;
		ss >> res;
	}

	return res;
}

int Utilitario::convertirAEntero(const std::string& numero) const {
	std::stringstream ss;
	int res;

	ss << numero;
	ss >> res;

	return res;
}

void Utilitario::borrarCaracter(std::string& palabra, const char caracter) {
	std::string aux;
	std::string parte = separar(palabra, caracter, 0);

	int i = 1;
	int cantBorrada = 0;
	do {
		cantBorrada++;
		aux += parte;
		parte = separar(palabra, caracter, i);
		i++;
	} while ((aux.size() + cantBorrada)< palabra.size());

	palabra = aux;
}

std::string Utilitario::ultimosCaracteres(int n, std::string& cadena){
	// Devuelve los ultimos n caracteres de cadena
	int tam = cadena.size();
	int i = 0;
	std::string resultado = "";
	if (n <= 0) return resultado;
	std::string::iterator it;
	it = cadena.begin();
	while (i < tam - n){
		//  Avanzo el iterador hasta tam - n
		++i;
		++it;
	}
	
	while (it < cadena.end()){
		resultado += (*it);
		++it;  
	}
	
	return resultado;
}

std::string Utilitario::convertirVectorAString(VectorChar v){
    std::string resultado = "";    
    for(IterVectorChar it = v.begin(); it != v.end() ; ++it){
        if ((*it) == '\0'){
            resultado += '\0';
        } 
        else resultado += (*it);
    }
    return resultado;  
}

void Utilitario::agregarCaracteres(VectorChar& v, std::string s){
    std::string::iterator it = s.begin();
    while (it != s.end()){
        v.push_back((*it));
        ++it;
    }
}

void Utilitario::agregarCaracteresAlComienzo(VectorChar& v, std::string s){
    VectorChar aux;
    std::string::iterator it = s.begin();
    while (it != s.end()){
        aux.push_back((*it));
        ++it;
    }
    
		
	for (IterVectorChar it = v.begin(); it != v.end() ; ++it)
		aux.push_back(*it);
		
	v = aux;
}

VectorChar Utilitario::getCampo(VectorChar v, char separador, int index){
	int contador = 0;
	int i = 0;
	VectorChar resultado;
	while ( contador < index and i < v.size()) {
		if (v[i] == separador) contador ++;
		i ++;
	}

	bool encontrado = false;
	
	while (i < v.size() and !encontrado){
		if (v[i] == separador) encontrado = true;
		else resultado.push_back(v[i]);
		i++;
	}
	
	return resultado;
}
