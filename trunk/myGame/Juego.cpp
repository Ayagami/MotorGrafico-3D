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
	
	/*daMesh = new DoMaRe::Mesh(r);
	daMesh->setData(g_8Vertices, 8, DoMaRe::Primitive::TriangleList, g_indices, 36);
	daMesh->setPos(0,0,10);
	daMesh->setScale(10,10,10);*/

/*
	daMesh2 = new DoMaRe::Mesh(r);
	daMesh2->setData(g_8Vertices, 8, DoMaRe::Primitive::TriangleList, g_indices, 36);
	daMesh2->setPos(0,10,20);
	daMesh2->setScale(10,10,10);*/
	return true;
}
void Game::Frame(DoMaRe::Renderer& r, DoMaRe::DirectInput& eInput, DoMaRe::Timer& t, DoMaRe::Import& Importer){
	/*static float rot = 0.1f;
	daMesh->setRotation(rot, rot, rot);
	rot+= 0.01f;
	daMesh->Draw(r);*/
	//daMesh2->Draw(r);
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
	/*if(daMesh){
		delete daMesh;
		daMesh = NULL;
	}*/
	/*
	if(daMesh2){
		delete daMesh2;
		daMesh2 = NULL;
	}*/
}
