#include "Scene2.h"
using namespace MiJuego;

bool Scene2::Init(){
	getEntity(&_Cubo1,"floor");
	getEntity(&_Sprite2,"player1");
	return true;
}

bool Scene2::Frame(DoMaRe::Renderer& renderer, DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Import& import, DoMaRe::Game& game){
	if(dInput.keyDown(DoMaRe::Input::KEY_P)){
		game.setScene("main",import,"Archivo.xml");
		return true;
	}
	if(dInput.keyDown(DoMaRe::Input::KEY_DOWN)){
		_Cubo1->setPos(_Cubo1->posX(),_Cubo1->posY() - 1);
	}
	return true;
}
