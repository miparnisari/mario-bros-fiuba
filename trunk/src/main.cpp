#include "app/ControladorApp.h"

int main(int argc, char** argv)
{
	ControladorApp* controlador = ControladorApp::getInstance();

	controlador->simular();
	
	ControladorApp::destroyInstance();

	return 0;
}
