#include "Juego.h"
#include "Renderer\RenderTypes.h"

DoMaRe::ColorVertex g_4Vertices[] = {
{-1.0f, -1.0f, 2.0f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 0 
{-1.0f, 1.0f, 4.0f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 1 
{ 1.0f, -1.0f, 6.0f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 2 
{ 1.0f, 1.0f, 8.0f, D3DCOLOR_XRGB( 255, 0, 0 )} // 3
};

USHORT g_indices[] = { 0, 1, 2, 1, 3, 2 };

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
	
	daMesh = new DoMaRe::Mesh(r);
	daMesh->setData(g_4Vertices, 4, DoMaRe::Primitive::TriangleList, g_indices, 8);
	daMesh->setPos(100,0,300);
	daMesh->setScale(100,100,100);
	daMesh->setRotation(14);
	return true;
}
void Game::Frame(DoMaRe::Renderer& r, DoMaRe::DirectInput& eInput, DoMaRe::Timer& t, DoMaRe::Import& Importer){
	daMesh->Draw(r);
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
	if(daMesh){
		delete daMesh;
		daMesh = NULL;
	}
}
