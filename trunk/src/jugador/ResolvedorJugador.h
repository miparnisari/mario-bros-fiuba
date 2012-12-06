#ifndef RESOLVEDORJUGADOR_H
#define RESOLVEDORJUGADOR_H

#include "../comun/Resolvedor.h"
#include "../modelo/Point.h"
#include "../comun/Definiciones.h"
#include "../controlador/SoundHandler.h"
class JugadorRemoto;
class ControladorJugador;
class ControladorApp;
class ResolvedorJugador: public Resolvedor
{
	public:
		ResolvedorJugador();
		~ResolvedorJugador();
		void iniciarJuego(ID unID);
		void avisarDesconeccionJugador (ID unID);
		void personajeSelect(ID unID, std::string personaje);
		void OKServidor(ID unID);
		void moverVista(ID unID, Point* posicion, std::string tipo);
		void moverVistaEnemigo(std::string tipo,ID myID,Point* miPos, std::string tipoMov);
		void moverVistasLoop(VectorEventoMV* vectorEventos);
		void setNivelActivo(ID unID, std::string nivel);
		void cargarLista(ListaParJugador* unaLista);
		void desocuparVistaPersonaje(ID myID);
		void borrarParJugador(ID unID);
		void keepAlive(ID unID);
		void crearEnemigo(std::string tipo, ID myID, Point* miPos);
		void crearPersonajeAnimado(std::string tipo, ID myID, Point* miPos);
		void reproducirMusica(std::string tag);
		void reproducirSonido(std::string tag);
		void cargarMusica(std::string ruta, std::string tag);
		void cargarSonido(std::string ruta, std::string tag);
		void eliminarVistaEnemigo(std::string unNombre, ID unID);
		void dibujarVidas(int cantVidas);
		void dibujarBonus(std::string elem, bool activo);
		void terminarJuego(std::string estado);
		void detenerMusica();
		void setPosVistaNivel(Point* pos);
	private:
		static const string TAG;
		SoundHandler SH;
};

#endif /* RESOLVEDORJUGADOR_H */ 
