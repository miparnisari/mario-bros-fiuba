#include "FactoryBonus.h"
#include "../modelo/Nivel.h"
#include "../app/ControladorApp.h"
#include "../jugador/ControladorJugador.h"
#define PROBPLUMA 10
#define PROBARMA 3
#define PROBVIDA 5
#define RANDOMMAX 20

/* La probabilidad de un bonus es (PROBi - PROBi-1)/RANDOMMAX */

FactoryBonus* FactoryBonus::instance = NULL;

FactoryBonus::FactoryBonus()
{
	factPlumas = new FactoryPlumas();
	factArmadura = new FactoryArmadura();
	factVidaExtra = new FactoryVidaExtra();
}

FactoryBonus::~FactoryBonus(){
	delete factPlumas;
	delete factArmadura;
	delete factVidaExtra;
}

FactoryBonus* FactoryBonus::getInstance() {
	if (instance == NULL) {
			instance = new FactoryBonus();
	}
	return instance;
}

void FactoryBonus::destroyInstance() {
	if (! instance) return;
	delete instance;
}

Bonus* FactoryBonus::crear(Point* pos, Nivel* unNivel){
	Bonus* bonus = NULL;
	int random = (rand() % RANDOMMAX);

	if (random >= 0 and random <= PROBPLUMA){
		bonus = this->factPlumas->crear(pos, unNivel);
	}
	else if (random >= (PROBPLUMA + 1) and random <= PROBARMA){
		bonus = this->factArmadura->crear(pos, unNivel);
	}
	else if( random >= (PROBARMA + 1) and random <= PROBVIDA){
		bonus= this->factVidaExtra->crear(pos, unNivel);
	}
	else
		bonus = NULL;
	
	return bonus;
}

// Si o si devuelve un bonus -> se usa en la caja de bonus
Bonus* FactoryBonus::crearObligatorio(Point* pos, Nivel* unNivel){
	Bonus* bonus = NULL;
	int random = (rand() % 10);

	if (random >= 0 and random <= 4){
		bonus = this->factArmadura->crear(pos, unNivel);
	}
	else if( random >= 5 and random <= 9){
		bonus= this->factVidaExtra->crear(pos, unNivel);
	}
	else
		bonus = NULL;
	
	return bonus;
}
