#include "Temporizador.h"
#include <iostream>
const std::string Temporizador::TAG = "Temporizador";

Temporizador::Temporizador(){
	this->contando = false;	
}

void Temporizador::setTiempoInicial(){
	time (&start);
	this->contando = true;
}

void Temporizador::setIntervalo(double inter){
	if (inter < 0) Logger::warn(TAG, "Intervalo de tiempo menor a 0");
	intervalo = inter;
	
}

bool Temporizador::puedeRealizarAccion(){
	time (&end);
	double dif = difftime (end,start);
	if (dif >= intervalo) return true;
	return false;
}

