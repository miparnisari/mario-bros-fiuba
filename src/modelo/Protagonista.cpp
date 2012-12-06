#include "Protagonista.h"
#include "Elemento.h"
#include "../app/ControladorApp.h"
#include "Hongo.h"
#include "../bonus/Armadura.h"
#include "../bonus/VidaExtra.h"
#include "Barril.h"
#include "Princesa.h"
#include "Tortuga.h"
#include "CamaElastica.h"
#include "../eventos/EventoVistaNivel.h"

const string Protagonista::TAG = "Protagonista";
Protagonista::Protagonista(Point* punto, int ancho, int alto,int velocidad, int potenciaSalto, ID cliente, string Nombre, float piso)
	: Personaje(punto, ancho, alto, Nombre, piso)
{
	this->cliente = cliente;
	this->movimiento =  new MovimientoPersonaje(punto, potenciaSalto, velocidad, piso);
	this->vidas = CANT_VIDAS;
	this->armadura = false;
	this->tempVidas = new Temporizador();
	this->tempVidas->setIntervalo(TIEMPO_DESPUES_MORIR);
	this->tempBonus = new Temporizador();
	this->tempBonus->setIntervalo(TIEMPO_VUELO);
	this->vivo = true;
	//std::cout << "Creo el respawn de " << Nombre << " en " << *punto << std::endl;
	this->posRespawn = new Point(punto->x, punto->y);
}

Protagonista::~Protagonista(){
	
	delete this->movimiento;
	//printf("delete this->movimiento;\n");
	delete(tempVidas);
	//printf("delete(tempVidas);\n");
	delete(tempBonus);
	//printf("delete(tempBonus);\n");
	delete posRespawn;
	//delete (this->posicion); se borra en el movimiento
}

void Protagonista::vivir(){
	//ControladorApp::getInstance()->getServidor()->getJuego()->aplicarMovimiento(this);
	this->getMovimiento()->setQuiereVolar(false);
	this->mover(1);
	
	if(this->tempBonus->contando){
		if (!this->tempBonus->puedeRealizarAccion() && this->getMovimiento()->getPresionada()){
	
			this->getMovimiento()->setQuiereVolar(true);
		} else if (this->tempBonus->puedeRealizarAccion()) this->tempBonus->contando = false;
	}	
}

void Protagonista::saltar(){
	this->movimiento->saltar();
}

void Protagonista::caer(){
	this->movimiento->caer();
}

void Protagonista::mover(int result){
	this->movimiento->caerSinSalto();
}

void Protagonista::colisionarConBarril(Barril* barril) {
	// Redefinido en protagonista y en los otros queda igual
	this->perderVidas(1);	
}

void Protagonista::colisionarConFuego(Fuego* unFuego) {
	// Redefinido en protagonista y en los otros queda igual
	this->perderVidas(1);
}

int Protagonista::colisionarConHongo(Hongo* hongo, Point posAnterior){
	//Si la colision se produce con el personaje saltando arriba del hongo
	//entonces el hongo se elimina

	if (hongo->getActivo()){	
		if((posAnterior.y + (this->alto / 2)) <= hongo->getPos()->y){
			this->getPos()->y = posAnterior.y;
			hongo->getMovimiento()->detenerEnX();
			hongo->getMovimiento()->detenerEnY();
			
			this->getMovimiento()->setSaltando(false);
			this->getMovimiento()->cayendo = false;
			this->getMovimiento()->sePuedeSaltar = true;
			this->getMovimiento()->saltar();
			hongo->morir();
			printf("Mato al hongo\n");
		} else{ 
			this->perderVidas(1);
			printf("El hongo me mata\n");
		}
		std::cout << "Pos Anterior: " << posAnterior << "\n";
		std::cout << "Pos Anterior + Alto: " << posAnterior.y + this->alto << "\n";
		std::cout << "Pos Hongo: " << *hongo->getPos() << "\n";
		//Le quita una vida al protagonista
	} 
		
	return true;
}

void Protagonista::colisionarConPrincesa(Princesa* princesa){
//	printf(" Protagonista::colisionarConPrincesa(Princesa* princesa)\n");
	if (princesa->getActivo() and vivo){
		vivo = false;
		EventoSonido evSG("S","ganar");
		EventoSonido evSP("S","perder");
		EventoGameOver evG("ganar");
		EventoGameOver evP("perder");
		
		//Le aviso al ganador que gano
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evSG, myID);
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evG, myID);
		
		// Y a los perdedores que perdieron
		ControladorApp::getInstance()->getServidor()->enviarEventoRestoJugador(&evSP, myID);
		ControladorApp::getInstance()->getServidor()->enviarEventoRestoJugador(&evP, myID);
		princesa->setActivo(false);
	}
}

int Protagonista::colisionarConTortuga(Tortuga* tortuga, Point posAnterior){
	//Si la colision se produce con el personaje saltando arriba de la tortuga
	//entonces la tortuga se transforma en caparazon
	if (tortuga->getActivo()){
		if (! tortuga->esCaparazon){
			
			if((posAnterior.y + (this->alto / 2)) <= tortuga->getPos()->y){
					
					this->getPos()->y = posAnterior.y;
					tortuga->getMovimiento()->detenerEnX();
					tortuga->getMovimiento()->detenerEnY();
					this->getMovimiento()->setSaltando(false);
					this->getMovimiento()->cayendo = false;
					this->getMovimiento()->sePuedeSaltar = true;
					this->getMovimiento()->detenerEnY();
					this->getMovimiento()->saltar();
					tortuga->hacerseCaparazon();
				//Le quita una vida al protagonista

			} else this->perderVidas(1);

		}
				
		else { //La tortuga es caparazon

			if (tortuga->quieto){
				//Es caparazon quieto y salto arriba -> Muere
				if((posAnterior.y + this->alto) <= (tortuga->getPos()->y + (tortuga->getAlto()/2) )){
					this->getPos()->y = posAnterior.y;
					tortuga->getMovimiento()->detenerEnX();
					tortuga->getMovimiento()->detenerEnY();
					this->getMovimiento()->setSaltando(false);
					this->getMovimiento()->cayendo = false;
					this->getMovimiento()->sePuedeSaltar = true;
					this->getMovimiento()->detenerEnY();
					this->getMovimiento()->saltar();
					tortuga->morir();
				}

				//Es caparazon quieto y lo toco de costado -> Se mueve
				else if ((posAnterior.x + this->ancho) >= (tortuga->getPos()->x) and (posAnterior.x < tortuga->getPos()->x) ){
					//Costado izquierdo
					this->getPos()->x = posAnterior.x;
					tortuga->quieto = false;
					tortuga->desplazar(5);
					tortuga->direccion = 1;
				}
				else if ((posAnterior.x) <= (tortuga->getPos()->x + tortuga->getAncho()) and (posAnterior.x > tortuga->getPos()->x)) {
					//Costado derecho
					this->getPos()->x = posAnterior.x;
					tortuga->quieto = false;
					tortuga->desplazar(-5);
					tortuga->direccion = -1;
				}

			}

			else {
				//Es caparazon en movimiento y le salta arriba -> Se queda quieto
				if((posAnterior.y + this->alto) <= (tortuga->getPos()->y + (tortuga->getAlto()/2) )){
					this->getPos()->y = posAnterior.y;
					tortuga->getMovimiento()->detenerEnX();
					tortuga->getMovimiento()->detenerEnY();
					this->getMovimiento()->setSaltando(false);
					this->getMovimiento()->cayendo = false;
					this->getMovimiento()->sePuedeSaltar = true;
					this->getMovimiento()->saltar();
					tortuga->quieto = true;
				} else 	this->perderVidas(1);

			}
		}
	}

	return true;
}

void Protagonista::colisionarConArmadura(Armadura* armadura){
	this->setArmadura(true);
	//TODO: Avisar que se agarro armadura
	if (!armadura->getMorir()){
		EventoSonido ev("S", "Armadura");
		EventoDibujar evDib("iconoArmadura",true);
		
		// Le muestro el icono (y reproduzco el sonido) al jugador que agarro el item
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evDib, myID);	
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&ev, myID);
		armadura->getMovimiento()->detenerEnX();
		armadura->getMovimiento()->detenerEnY();
		armadura->setActivo(false);
		armadura->setMorir(true);
	}
	
}

void Protagonista::colisionarConVidaExtra(VidaExtra* vidaExtra){

	if (!vidaExtra->getMorir()){
		EventoSonido ev("S", "1UP");
		// Le muestro el icono (y reproduzco el sonido) al jugador que agarro el item
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&ev, myID);
		this->ganarVidas(1);
		vidaExtra->getMovimiento()->detenerEnX();
		vidaExtra->getMovimiento()->detenerEnY();
		vidaExtra->setActivo(false);
		vidaExtra->setMorir(true);
	}
	
}

void Protagonista::perderVidas(int cantidad){

	if(this->tempVidas->contando){
		if (!this->tempVidas->puedeRealizarAccion()){
			// Si el temporizador esta contando, y no paso el tiempo
			// soy invencible durante ese ratito despues de morir
			return;
		} else this->tempVidas->contando = false;
	}	

	EventoSonido evS("S","Yah");
	
	if (armadura){
		// Se podria avisar que se perdio la armadura
		armadura = false;
		this->tempVidas->setTiempoInicial();
		EventoDibujar evDib("iconoArmadura",false);
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evDib, myID);
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evS, myID);
		return;
	}

	this->posicion->x = posRespawn->x;
	this->posicion->y = posRespawn->y;
	EventoVistaNivel eVN(new Point(0,0));
	ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&eVN, myID);
	EventoMoverVista eMV(myID, posRespawn, "quietoder");
	ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&eMV);
	this->vidas -= cantidad;
	this->tempVidas->setTiempoInicial();
	
	if(this->vidas >= 0){
		//printf("CANTIDAD DE VIDAS %d\n", this->vidas);
		EventoVidas ev(this->vidas);
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&ev, myID);
		
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evS, myID);
	}
	if ((this->vidas <= 0) and (vivo)){
		vivo = false;
		std::cout << "vidas < 0 \n";
		EventoSonido evSP("S","perder");
		EventoGameOver evP("perder");
		// Aviso que se murio un personaje, adentro chequea si queda uno solo
		ControladorApp::getInstance()->getServidor()->setFinalizo(true);
		//Le aviso al jugador que perdio
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evSP, myID);
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evP, myID);
	}
}

void Protagonista::ganarVidas(int cantidad){
	if ( (this->vidas + cantidad) <= 9 ){ //Maximo de vidas es 9
		this->vidas += cantidad;
		EventoVidas ev(this->vidas);
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&ev, myID);
	}
}


void Protagonista::setArmadura(bool valor){
	this->armadura = valor;
}

void Protagonista::colisionarConBolaDeFuego(BolaDeFuego* bola) {
	// Redefinido en protagonista y en los otros queda igual
	printf("COLISION CON bola de FUEGO\n");
	this->perderVidas(1);	
}

void Protagonista::colisionarConCamaElastica(CamaElastica* cama, Point posAnterior){
//Impulsa al jugador como si estuviera en una cama elástica.

	if(((this->getPos()->y + this->getAlto() > cama->getPos()->y) || (this->getPos()->y < cama->getPos()->y + cama->getAlto())) &&
		((posAnterior.x < cama->getPos()->x +cama->getAncho()) || ((posAnterior.x  + this->getAncho() > cama->getPos()->x ) && (posAnterior.x  + this->getAncho() < cama->getPos()->x +cama->getAncho())))){
		this->getMovimiento()->getPos()->y = posAnterior.y;
	//	this->getMovimiento()->empujarEnY(this->multiplicadorSgetAlto());
//		printf("1\n");
		this->getMovimiento()->detenerCaida();
		this->getMovimiento()->setSaltando(false);
		this->getMovimiento()->cayendo = false;
		this->getMovimiento()->sePuedeSaltar = true;
		this->getMovimiento()->estaSiendoEmpujado = true;
		this->getMovimiento()->rebotando = false;
		this->getMovimiento()->rebotar();
		EventoSonido evS("S","Cama");
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evS, myID);
	}
	
	if(( ((this->getPos()->y > cama->getPos()->y) && (this->getPos()->y + this->getAlto() < cama->getPos()->y +cama->getAlto())) ||
		((this->getPos()->y > cama->getPos()->y) && (this->getPos()->y + this->getAlto() > cama->getPos()->y +cama->getAlto())) ||
		((this->getPos()->y < cama->getPos()->y) && (this->getPos()->y + this->getAlto() > cama->getPos()->y)) ||
		((this->getPos()->y < cama->getPos()->y +cama->getAlto()) && (this->getPos()->y + this->getAlto() > cama->getPos()->y +cama->getAlto()))
		
		)	&& ((this->getPos()->x < cama->getPos()->x +cama->getAncho()) || (this->getPos()->x  + this->getAncho() > cama->getPos()->x ))){
		this->getMovimiento()->getPos()->x = posAnterior.x;
		this->getMovimiento()->getPos()->y = posAnterior.y; //esto lo agregue
		this->getMovimiento()->detenerCaida();
		this->getMovimiento()->detenerDesplazamiento(); //esto lo agregue
	}
	//If el thisonaje esta por debajo de la cama elastica.
	if((cama->getPos()->y >= this->getPos()->y) && (((cama->getPos()->y) - this->getAlto()) <= this->getPos()->y)) {
		this->getMovimiento()->getPos()->x = posAnterior.x;
		this->getMovimiento()->getPos()->y = posAnterior.y; //esto lo agregue
		this->getMovimiento()->detenerDesplazamiento(); //esto lo agregue
		this->getMovimiento()->detenerCaida();
	}
}

void Protagonista::colisionarConPluma(Pluma* pluma, Point posAnterior){
	
	if (!pluma->getMorir()){
		
		EventoSonido ev("S", "Pluma");
		// Le muestro el icono (y reproduzco el sonido) al jugador que agarro el item
		ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&ev, myID);
		this->movimiento->detenerEnY();
		this->movimiento->setQuiereVolar(true);
		this->tempBonus->setTiempoInicial();
		pluma->setActivo(false);
		pluma->setMorir(true);
	}	
}

int Protagonista::getVidas(){ return this->vidas;}
