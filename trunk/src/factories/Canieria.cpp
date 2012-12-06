#include "Canieria.h"
#include "../modelo/Nivel.h"
#include "../app/ControladorApp.h"
#include "../jugador/ControladorJugador.h"

// El asignador de ID se crea en LoaderServidor
Canieria::Canieria(Point* unaPosicion, int ancho, int alto, Nivel* unNivel, IdHandler* idHandler): Elemento(unaPosicion)
{
	nivel = unNivel;
	factHongos = new FactoryHongos(posicion, nivel->getPiso());
	factBolas = new FactoryBolasFuego(posicion, nivel->getPiso());
	factTortugas = new FactoryTortugas(posicion, nivel->getPiso());
	
	// atributos de elemento
	this->ancho = ancho;
	this->alto = alto;
	this->asignadorID = idHandler;
}

Canieria::~Canieria()
{
	delete factHongos;
	delete factBolas;
	delete factTortugas;
	delete (asignadorID); asignadorID = NULL;
}

void Canieria::vivir()
{
	ID unID = asignadorID->asignarID();
	if (unID == ID_INVALIDO) {
		return;
	}
	
	Hongo* hongo = NULL;
	Tortuga* tortuga = NULL;
	
	int random = (rand() % 100);  //random esta en el rango [0,99]

	if (random >= 0 and random <= 49){
		hongo = factHongos->crear(unID);
	} else {
		tortuga = factTortugas->crear(unID);
	}

	if (hongo != NULL){
		nivel->agregarEnemigo(hongo);
		ControladorApp::getInstance()->getServidor()->agregarEnemigo(hongo);
		EventoCrearEnemigo ev(hongo);
		ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);
	}

	if (tortuga != NULL){
		nivel->agregarEnemigo(tortuga);
		ControladorApp::getInstance()->getServidor()->agregarEnemigo(tortuga);
		EventoCrearEnemigo ev3(tortuga);
		ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev3);
	}
}

int Canieria::aplicarColision(Elemento* elem,int resultado, Point posAnterior)
{
	return false;
}

int Canieria::aplicarColision(Personaje* pers,int resultado, Point posAnterior)
{
	if((posAnterior.y + pers->getAlto()) <= this->posicion->y ){
		pers->getMovimiento()->setSaltando(false);
		pers->getMovimiento()->sePuedeSaltar = true;
		pers->getPos()->y = posAnterior.y;
		pers->getMovimiento()->detenerCaida();
		return true;
	}	
	return false;
}
