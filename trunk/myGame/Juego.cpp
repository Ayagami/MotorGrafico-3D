#include "Juego.h"
#include "Renderer\RenderTypes.h"

DoMaRe::ColorVertex g_8Vertices[] = {
{-1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 0 
{1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 1 
{ 1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB( 0, 0, 255 )}, // 2 
{ -1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 3
{ -1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 4
{ 1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB( 0, 0, 255 )}, // 5
{ 1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 6
{ -1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB( 0, 255, 0 )} // 7
};

DoMaRe::ColorVertex g_4Vertices[] = 
{

{-1.0f, -1.0f, 5.0f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 0 
{-1.0f, 1.0f, 5.0f, D3DCOLOR_XRGB( 255, 255, 0 )}, // 1 
{ 1.0f, -1.0f, 5.0f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 2 
{ 1.0f, 1.0f, 5.0f, D3DCOLOR_XRGB( 0, 0, 255 )} // 3
};

USHORT g_indices2[] = { 0, 1, 2, 1, 3, 2 };

USHORT g_indices[] = { 0, 1, 2, 0, 2, 3,
					   0, 1, 5, 0, 5, 4,
					   1, 2, 6, 1, 6, 5,
					   2, 6, 7, 2, 7, 3,
					   3, 7, 4, 3, 4, 0,
					   5, 4, 7, 5, 7, 6};

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
	daMesh->setData(g_4Vertices, 4, DoMaRe::Primitive::TriangleList, g_indices2, 6);
	daMesh->setPos(100,0,300);
	daMesh->setScale(10,10,10);
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
