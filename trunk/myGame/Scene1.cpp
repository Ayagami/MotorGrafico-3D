#include "Scene1.h"
#include "Entity3D\Mesh.h"
//#include "Sound\Sound.h"
using namespace MiJuego;
bool ds = true;
float mSpeed = 1.0f;

DoMaRe::ColorVertex g_8Vertices2[] = {
{-0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 0 
{0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 1 
{ 0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB( 40, 0, 120 )}, // 2 
{ -0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 3

{ -0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 4
{  0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB( 40, 0, 120 )}, // 5
{  0.5f, -0.5f,-0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 6
{ -0.5f, -0.5f,-0.5f, D3DCOLOR_XRGB( 0, 255, 0 )} // 7
};

USHORT g_indices2[] = { 0, 1, 2, 0, 2, 3,
					   4, 5, 6, 4, 6, 7,
					   3, 2, 5, 3, 5, 4,
					   2, 1, 6, 2, 6, 5,
					   1, 7, 6, 1, 0, 7,
					   0, 3, 4, 0, 4, 7};

					   


bool Scene1::Init(DoMaRe::Import& Importer){
//	getEntity(&_Cubo1,"floor");
//	getEntity(&_Sprite2,"player1");
	mainCamera = new DoMaRe::Camera();
	mainCamera->Init(&Importer.GetRenderer());

	Importer.GetSound().playSoundFile("sound.mp3",false);

	
	_theMesh = new DoMaRe::Mesh( Importer.GetRenderer() );
	/*_theMesh->setData(g_8Vertices2, 8, DoMaRe::Primitive::LineStrip, g_indices2, 36);
	_theMesh->setPos(0,30,10);
	_theMesh->setScale(10,10,10);*/
	Importer.importMesh(*_theMesh,"box.obj");
	_theMesh->setTexture("assets/text.jpg",DoMaRe_COLOR_RGB(255,255,255));
	_theMesh->setPos(0,30,10);
	_theMesh->setScale(10,10,10);
	addEntity(_theMesh);
	
	return true;
}

bool Scene1::Frame(DoMaRe::Renderer& renderer, DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Import& import, DoMaRe::Game& game, DoMaRe::Sound& pkSound){
	if(dInput.keyDown(DoMaRe::Input::KEY_1)){
		pkSound.setMasterVolume(pkSound.getMasterVolume() - 0.1f);
	}
	if(dInput.keyDown(DoMaRe::Input::KEY_2)){
		pkSound.setMasterVolume(pkSound.getMasterVolume() + 0.1f);
	}
	/*if(dInput.keyDown(DoMaRe::Input::KEY_P)){
		//game.setScene("main2",import,"Archivo.xml");
		return true;
	}*/

	if(dInput.keyDown(DoMaRe::Input::KEY_UP)){
		mainCamera->MoveForward(mSpeed);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_DOWN)){
		mainCamera->MoveForward(-mSpeed);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_LEFT)){
		mainCamera->MoveRight(-mSpeed);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_RIGHT)){
		mainCamera->MoveRight(mSpeed);
	}


	if(dInput.keyDown(DoMaRe::Input::KEY_D)){
		mainCamera->RotateRight(mSpeed / 100);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_A)){
		mainCamera->RotateRight(-mSpeed  / 100);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_W)){
		mainCamera->RotateDown(-mSpeed  / 100);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_S)){
		mainCamera->RotateDown(mSpeed  / 100);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_Q)){
		mainCamera->MoveUp(-mSpeed);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_E)){
		mainCamera->MoveUp(mSpeed);
	}

	return true;
}

bool Scene1::deInit(){
	OutputDebugString("Sal� Scene1");
	return true;
}