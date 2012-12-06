#ifndef FACTORYBONUS_H
#define FACTORYBONUS_H
#include "FactoryPlumas.h"
#include "FactoryArmadura.h"
#include "FactoryVidaExtra.h"

class ControladorApp;
class ControladorJugador;
class Nivel;

class FactoryBonus
{
	public:
		FactoryBonus();
		~FactoryBonus();
		//void vivir();
		Bonus* crear(Point* pos, Nivel* unNivel);
		Bonus* crearObligatorio(Point* pos, Nivel* unNivel);
		static FactoryBonus* getInstance();
		static void destroyInstance();

			
	private:
		static FactoryBonus* instance;
		FactoryPlumas* factPlumas;
		FactoryArmadura* factArmadura;
		FactoryVidaExtra* factVidaExtra;
};

#endif /* FACTORYBONUS_H */ 
