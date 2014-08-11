#include "Juego.h"
//bool d = true;
using namespace MiJuego;

bool Game::Init(DoMaRe::Renderer& r, DoMaRe::Import& Importer){

	Escena1 = new Scene1();
	Escena1->Name = "main";
	addScene(Escena1);
	Importer.importScene(*Escena1, "Archivo.xml");

	Escena2 = new Scene2();
	Escena2->Name = "main2";
	addScene(Escena2);

	_currentScene = Escena1;
	return true;
}
void Game::Frame(DoMaRe::Renderer& r, DoMaRe::DirectInput& eInput, DoMaRe::Timer& t, DoMaRe::Import& Importer){

}
void Game::DeInit(){
	if(Escena2){
		delete Escena2;
		Escena2 = NULL;
	}
	if(Escena1){
		delete Escena1;
		Escena1 = NULL;
	}
}
