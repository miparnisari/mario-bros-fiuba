#include "EstadoJugador.h"
//#include "../app/ControladorApp.h"
//#include "../jugador/ControladorJugador.h"

EstadoJugador::EstadoJugador(ID unID)
{
	for (int i = 0; i < CANT_TECLAS ; i++)
		teclasPresionadas[i] = 0 ;
	myID = unID;
	// TODO: random segun el ancho del nivel
	posicion = new Point(500, 500);
	ultimaPosicion = new Point(500, 500);
	modificado = false;
	ultimoMov = quietoder;
	teclaJustReleased = true;
	estaSaltando = false;
}

EstadoJugador::~EstadoJugador(){
	delete(posicion);
	delete(ultimaPosicion);
}

Point* EstadoJugador::getPos(){
	return posicion;
}

void EstadoJugador::teclaPresionada(int tecla){
	if (!teclaValida(tecla)) return;
	teclasPresionadas[tecla] = true;
}

void EstadoJugador::teclaSoltada(int tecla){
	if (!teclaValida(tecla)) return;
	teclasPresionadas[tecla] = false;
}

bool EstadoJugador::estadoTecla(int tecla){
	if (!teclaValida(tecla)) return false;
	return teclasPresionadas[tecla];
}

bool EstadoJugador::teclaValida(int tecla){
	if ((tecla < 0) or (tecla > CANT_TECLAS)) return false;
	return true;
}

ID EstadoJugador::getID(){
    return myID;
}

bool EstadoJugador::getModificado(){
	return this->modificado;
}

void EstadoJugador::setModificado(bool unEstado){
	this->modificado = unEstado;
}

void EstadoJugador::setSaltando(bool unEstado) {
	this->estaSaltando = unEstado;
}

void EstadoJugador::setTeclaJustReleased(bool unEstado){
	this->teclaJustReleased = unEstado;
}

std::string EstadoJugador::ultimoMovToString() {
	if (ultimoMov == arriba)  return "arriba";
	if (ultimoMov == abajo)   return "abajo";
	if (ultimoMov == derecha) return "derecha";
	if (ultimoMov == izquierda) return "izquierda";
	if (ultimoMov == quietoizq) return "quietoizq";
	if (ultimoMov == quietoder) return "quietoder";
	if (ultimoMov == cayendoizq) return "cayendoizq";
	if (ultimoMov == cayendoder) return "cayendoder";
	if (ultimoMov == saltandoizq) return "saltandoizq";
	if (ultimoMov == saltandoder) return "saltandoder";
}

// Recibe la posicion del jugador e informa si hubo cambios
bool EstadoJugador::actualizarPosicion(MovimientoPersonaje* mov, std::string& tipoMov){
	
	// Valor por default
	tipoMov = ultimoMovToString();
	
	if (teclaJustReleased) {
		// Si se solto una tecla, paramos al personaje
		if (ultimoMov == derecha) {
			ultimoMov = quietoder;
		}
		else if (ultimoMov == izquierda) {
			ultimoMov = quietoizq;
		}
		teclaJustReleased = false;
		tipoMov = ultimoMovToString();
		return true;
	}
	
	// Si se movio a la derecha
	if (this->estadoTecla(SDLK_RIGHT)) {
		mov->aplicarFuerza(3);
		ultimoMov = derecha;
	}
	
	// Si se movio a la izquierda
	if (this->estadoTecla(SDLK_LEFT)) {
		mov->aplicarFuerza(-3);
		//printf("desp de aplicar fuerza %f\n", mov->getVelocidadX());
		ultimoMov = izquierda;
	}
	
	// Si salto
	if (this->estadoTecla(SDLK_SPACE)){
		
		mov->setPresionada(true);
		if (mov->estaSaltando() == false){
		
			//	EventoSonido evSalto("S","Salto");
				//std::cout << "EVSalto" << std::endl;
			//	ControladorApp::getInstance()->getServidor()->enviarEventoJugador(&evSalto, myID);
				//std::cout << "DSP EVSalto" << std::endl;
			
			mov->saltar();
		}
		
	//	printf("esta siendo presionada\n");
	} else mov->setPresionada(false);
	
	// Si apreto arriba
	if (this->estadoTecla(SDLK_UP)) {
		ultimoMov = quietoder;
		if ( ! mov->getQuiereSubir() ){
			mov->setQuiereSubir(true);
		}
	} else if (mov->getQuiereSubir()){
			mov->setQuiereSubir(false);
	}
	
	// Si esta saltando
	if (mov->estaSaltando()) {
		if (ultimoMov == quietoder || ultimoMov == derecha || ultimoMov == saltandoder) {
			ultimoMov = saltandoder;
		} else {
			ultimoMov = saltandoizq;
		}
	}
	
	// Si apreto abajo
	if (this->estadoTecla(SDLK_DOWN)) {
		if ( ! mov->getQuiereBajar() ){
			mov->setQuiereBajar(true);
		}
		//mov->caer();
		if (ultimoMov == saltandoder) {
			ultimoMov = cayendoder;
		} else {
			ultimoMov = cayendoizq;
		}
	} else if (mov->getQuiereBajar()){
		mov->setQuiereBajar(false);
	}
	
	// Si esta cayendo
	if (mov->estaCayendo()) {
		if (ultimoMov == cayendoizq) {
			ultimoMov = cayendoizq;
		} else {
			ultimoMov = cayendoder;
		}
	}
	
	//printf("velocidad en X %f\n",mov->getVelocidadX());
	Point* p = mov->getPos();

	// Seteo en negativo
	mov->setPuedeSaltar(false);

	// Las colisiones apropiadas se encargan de setearlo en true si corresponde
	int detener = ControladorApp::getInstance()->getServidor()->getJuego()->detectarColision(myID, *posicion);

	if(detener && mov->estaSaltando()){
		mov->caidaSinSalto = false;
		//mov->detenerCaida();
	}


	bool pudoMover = true;
	if( !(ControladorApp::getInstance()->getServidor()->getJuego()->puedeMoverEnX(myID, mov->getPos())) or !(ControladorApp::getInstance()->getServidor()->getJuego()->puedeMoverEnY(myID, mov->getPos())) ) {
		if(!(ControladorApp::getInstance()->getServidor()->getJuego()->puedeMoverEnX(myID, mov->getPos()))){
			mov->getPos()->x = posicion->x;
			pudoMover = false;
			mov->detenerEnX();
			mov->cayendo = false;
		}
		if(!(ControladorApp::getInstance()->getServidor()->getJuego()->puedeMoverEnY(myID, mov->getPos()))){
			mov->getPos()->y = posicion->y;
			pudoMover = false;
			mov->detenerEnY();
		}
		
		if (mov->estaSaltando()){
			mov->caer();
			if (ultimoMov == saltandoder) {
				ultimoMov = cayendoder;
			} else {
				ultimoMov = cayendoizq;
			}	
		}
		
		if (mov->estaCayendo() and !pudoMover){
			if (ultimoMov == cayendoder) {
				ultimoMov = quietoder;
				tipoMov = "quietoder";
			} else {
				ultimoMov = quietoizq;
				tipoMov = "quietoizq";
			}
		}

	}

	if (!detener) 
		mov->setRozamiento(0);
	
	
	tipoMov = ultimoMovToString();
	posicion->x = p->x;
	posicion->y = p->y;	
	
	if ((p->distanceFrom(*ultimaPosicion) > 2)){
		ultimaPosicion->x = p->x;
		ultimaPosicion->y = p->y;
		return true;
	}

	return false;
}

void EstadoJugador::cambiarPosicion(float x, float y){
	posicion->x = x;
	posicion->y = y;
	ultimaPosicion->x = x;
	ultimaPosicion->y = y;
}
