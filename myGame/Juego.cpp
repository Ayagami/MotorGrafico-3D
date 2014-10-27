#include "Juego.h"
#include "Renderer\RenderTypes.h"

DoMaRe::ColorVertex g_8Vertices[] = {
{-0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 0 
{0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 1 
{ 0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB( 40, 0, 120 )}, // 2 
{ -0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 3

{ -0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 4
{  0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB( 40, 0, 120 )}, // 5
{  0.5f, -0.5f,-0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 6
{ -0.5f, -0.5f,-0.5f, D3DCOLOR_XRGB( 0, 255, 0 )} // 7
};

USHORT g_indices[] = { 0, 1, 2, 0, 2, 3,
					   4, 5, 6, 4, 6, 7,
					   3, 2, 5, 3, 5, 4,
					   2, 1, 6, 2, 6, 5,
					   1, 7, 6, 1, 0, 7,
					   0, 3, 4, 0, 4, 7};

//bool d = true;
using namespace MiJuego;
bool Game::Init(DoMaRe::Renderer& r, DoMaRe::Import& Importer){

	Escena1 = new Scene1();
	Escena1->Name = "main";
	addScene(Escena1);
	//Importer.importScene(*Escena1, "Archivo.xml");

	Escena2 = new Scene2();
	Escena2->Name = "main2";
	addScene(Escena2);
	
	_currentScene = Escena1;
	
	return true;
}
void Game::Frame(DoMaRe::Renderer& r, DoMaRe::DirectInput& eInput, DoMaRe::Timer& t, DoMaRe::Import& Importer){
	if(eInput.keyDown(DoMaRe::Input::KEY_ESCAPE)){
		this->setGame(false);
	}
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
