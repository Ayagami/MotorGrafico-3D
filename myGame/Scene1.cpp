#include "Scene1.h"

#include "Entity3D\Entity3D.h"
#include "Entity3D\Mesh.h"
#include "Entity3D\Node.h"


#include "Physics\Collider.h"
#include "Physics\Physics.h"
#include "Physics\RigidBody.h"

#include <iostream>
#include <vector>
#include <math.h>

void Test2(DoMaRe::Entity3D* pk1, DoMaRe::Entity3D* pk2);

//#include "Sound\Sound.h"
using namespace MiJuego;
bool ds = false;
int Anim = 0;
float mSpeed = 0.1f;
DoMaRe::Node* cube;
bool Scene1::Init(DoMaRe::Import& Importer){
	mainCamera = new DoMaRe::Camera();
	mainCamera->Init(&Importer.GetRenderer());
	mainCamera->SetPosition(0,30,-10);
 
	pkNode = new DoMaRe::Node();
	

	mainLight = new DoMaRe::Light(&Importer.GetRenderer());
	mainLight->setLightType(DoMaRe::Light::DIRECTIONAL_LIGHT);
	mainLight->setPosition (0, 0, 0);
	mainLight->setDirection(0, 0, 1);
	mainLight->setAmbient (0, 0, 0, 0);
	mainLight->setSpecular(0, 0, 0, 0);
	mainLight->setLightIndex(0);
	mainLight->setRange(0.3f);
	mainLight->enable(true);

	Importer.importScene("tank.x", *pkNode);
	//pkNode->setPos(0,0,0);
	pkNode->setScale(10,10,10);
	pkNode->setCollisionEvent(&Test2);

	Importer.GetSound().playSoundFile("sound.mp3",false);
	return true;
}

bool Scene1::Frame(DoMaRe::Renderer& renderer, DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Import& import, DoMaRe::Game& game, DoMaRe::Sound& pkSound){
	UpdateInputs(dInput,timer,pkSound,renderer);
	
	if(ds){
		switch (Anim){
		case 0:
			pkNode->playAnimation("Attack");
			break;
		case 1:
			pkNode->playAnimation("Impact");
			break;
		case 2:
			pkNode->playAnimation("Move");
			break;

		}
		pkNode->Update(timer.timeBetweenFrames());
	}

	mainLight->setLightIndex(0);
	mainLight->enable(true);
	/*if( pkNode->childs()[0]->collidesWith(*pkNode->childs()[1]) ) {
		pkNode->OnCollision(pkNode->childs()[0],pkNode->childs()[1]);
	}*/
	
	return true;
}

bool Scene1::deInit(){

	delete mainLight;

	return true;
}

void Test2(DoMaRe::Entity3D* pk1, DoMaRe::Entity3D* pk2){
	std::cout << pk1->getName().c_str() << " COLLIDES WITH " << pk2->getName().c_str() << "\n";
}

void Scene1::UpdateInputs(DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Sound& pkSound, DoMaRe::Renderer& renderer){
	if (dInput.keyDown(DoMaRe::Input::KEY_7)){
		Anim = 0;
	}
	if (dInput.keyDown(DoMaRe::Input::KEY_8)){
		Anim = 1;
	}
	if (dInput.keyDown(DoMaRe::Input::KEY_9)){
		Anim = 2;
	}
	if (dInput.keyDown(DoMaRe::Input::KEY_M)){
		ds = !ds;
	}
	if (dInput.keyDown(DoMaRe::Input::KEY_1)){
		pkSound.setMasterVolume(pkSound.getMasterVolume() - 0.1f);
	}

	if (dInput.keyDown(DoMaRe::Input::KEY_2)){
		pkSound.setMasterVolume(pkSound.getMasterVolume() + 0.1f);
	}

	if (dInput.keyDown(DoMaRe::Input::KEY_F1)){
		renderer.setWireFrameMode(!renderer.getWireFrameMode());
	}

	if (dInput.keyDown(DoMaRe::Input::KEY_F2)){
		ds = !ds;
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

	if(dInput.keyDown(DoMaRe::Input::KEY_B)){
		mainLight->enable(!mainLight->isEnabled());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_V)){
		float newDT = timer.deltaTime() == 1.0f ? 0.0f : 1.0f;
		timer.setdeltaTime(newDT);
	}
}
