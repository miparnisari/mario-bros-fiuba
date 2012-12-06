#include "CamaElastica.h"
const string CamaElastica::TAG = "Cama Elastica";

CamaElastica::CamaElastica(Point* unaPos, int ancho, int alto)
	: Plataforma(unaPos, ancho, alto, 1)
{
	Logger::info  (TAG , "Construccion correcta");
}


CamaElastica::~CamaElastica()
{
	
}

int CamaElastica::aplicarColision(Personaje* pers, int res, Point posAnterior){
	pers->colisionarConCamaElastica(this, posAnterior);
	return 1;
}

