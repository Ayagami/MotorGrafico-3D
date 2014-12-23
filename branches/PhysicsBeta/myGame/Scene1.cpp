#include "Scene1.h"

#include "Entity3D\Entity3D.h"
#include "Entity3D\Mesh.h"
#include "Entity3D\Node.h"


#include "Physics\Collider.h"
#include "Physics\Physics.h"
#include "Physics\RigidBody.h"

#include <vector>


//#include "Sound\Sound.h"
using namespace MiJuego;
bool ds = true;
float mSpeed = 0.3f;

bool Scene1::Init(DoMaRe::Import& Importer){
	mainCamera = new DoMaRe::Camera();
	mainCamera->Init(&Importer.GetRenderer());
	mainCamera->SetPosition(0,30,-10);

	pkNode = new DoMaRe::Node();
	

	mainLight = new DoMaRe::Light(&Importer.GetRenderer());
	mainLight->setLightType(DoMaRe::Light::POINT_LIGHT);
	mainLight->setPosition(0, 0, 0);
	mainLight->setDirection(1, 1, 1);
	mainLight->setAmbient(0, 0, 0, 0);
	mainLight->setSpecular(0, 0, 0, 0);
	mainLight->setLightIndex(0);
	mainLight->enable(true);

	Importer.importScene("Mesh.obj", *pkNode);
	pkNode->setPos(0,0,0);
	
	//DoMaRe::Node* pkPlaneNode = dynamic_cast<DoMaRe::Node*>( getEntity3D("Plane001", pkNode) ) ;
	//pkPlaneNode->childs()[0]->rigidBody()->setHavokMotion(DoMaRe::RigidBody::Static);

	Importer.GetSound().playSoundFile("sound.mp3",false);
	return true;
}

bool Scene1::Frame(DoMaRe::Renderer& renderer, DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Import& import, DoMaRe::Game& game, DoMaRe::Sound& pkSound){
	UpdateInputs(dInput,timer,pkSound,renderer);
	return true;
}

bool Scene1::deInit(){
	OutputDebugString("Salí Scene1");

	delete mainLight;

	return true;
}

void Scene1::UpdateInputs(DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Sound& pkSound, DoMaRe::Renderer& renderer){
	if(dInput.keyDown(DoMaRe::Input::KEY_1)){
		pkSound.setMasterVolume(pkSound.getMasterVolume() - 0.1f);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_2)){
		pkSound.setMasterVolume(pkSound.getMasterVolume() + 0.1f);
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_F1)){
			renderer.setWireFrameMode(!renderer.getWireFrameMode());	
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_UP)){
		mainCamera->MoveForward(mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_DOWN)){
		mainCamera->MoveForward(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_LEFT)){
		mainCamera->MoveRight(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_RIGHT)){
		mainCamera->MoveRight(mSpeed * timer.timeBetweenFrames());
	}


	if(dInput.keyDown(DoMaRe::Input::KEY_D)){
		mainCamera->RotateRight(mSpeed / 100 * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_A)){
		mainCamera->RotateRight(-mSpeed  / 100 * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_W)){
		mainCamera->RotateDown(-mSpeed  / 100 * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_S)){
		mainCamera->RotateDown(mSpeed  / 100 * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_Q)){
		mainCamera->MoveUp(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_E)){
		mainCamera->MoveUp(mSpeed * timer.timeBetweenFrames());
	}


	if(dInput.keyDown(DoMaRe::Input::KEY_L)){
		pkNode->setPos(pkNode->posX() + (mSpeed * timer.timeBetweenFrames()) , pkNode->posY(), pkNode->posZ());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_K)){
		pkNode->setPos(pkNode->posX() - (mSpeed * timer.timeBetweenFrames()), pkNode->posY(), pkNode->posZ());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_9)){
		pkNode->childs()[0]->setPos(pkNode->childs()[0]->posX() + (mSpeed*timer.timeBetweenFrames()), pkNode->childs()[0]->posY(), pkNode->childs()[0]->posZ() );
	}
}
