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
DoMaRe::Node* bsp;
DoMaRe::Node* bonesALL;
DoMaRe::Node* Tank;
DoMaRe::Mesh* mesh;
bool Scene1::Init(DoMaRe::Import& Importer){

	//pkNode = new DoMaRe::Node("tiny");
	bsp = new DoMaRe::Node("bspBitch");
	Tank = new DoMaRe::Node("TankBItch");

	// Luces 
	mainLight = new DoMaRe::Light(&Importer.GetRenderer());
	mainLight->setLightType(DoMaRe::Light::DIRECTIONAL_LIGHT);
	mainLight->setPosition (0, 0, 0);
	mainLight->setDirection(0, 0, 1);
	mainLight->setAmbient (0, 0, 0, 0);
	mainLight->setSpecular(0, 0, 0, 0);
	mainLight->setLightIndex(0);
	mainLight->setRange(0.3f);
	mainLight->enable(true);
	// fin Luces.

	//Importer.importScene("tiny.x", *pkNode);
	Importer.importScene("bspScene.3ds", *bsp);
	//Importer.importScene("BSP.3DS", *bsp);
	Importer.importScene("tank.x", *Tank);
	
	//pkNode->SetPos(0, 0, 0);
	//pkNode->SetScale(1, 1, 1);

	RegisterInBSPtree(bsp, true);
	RegisterInBSPtree(Tank, true);
	ArrangeBSPTree();

	//RegisterInBSPtree(Tank, false);
	//RegisterInBSPtree(bsp, true);
	//ArrangeBSPTree();

	mainCamera->SetPosition(0, 0, -20);

	Importer.GetSound().playSoundFile("sound.mp3",false);
	return true;
}

bool Scene1::Frame(DoMaRe::Renderer& renderer, DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Import& import, DoMaRe::Game& game, DoMaRe::Sound& pkSound){
	UpdateInputs(dInput,timer,pkSound,renderer);
	
	if(ds){
		/*switch (Anim){
		case 0:
			bonesALL->PlayAnim("Attack");
			break;
		case 1:
			bonesALL->PlayAnim("Impact");
			break;
		case 2:
			bonesALL->PlayAnim("Move");
			break;

		}
		bonesALL->Update(timer.timeBetweenFrames());*/
		pkNode->PlayAnim("");
		pkNode->Update(timer.timeBetweenFrames());
	}
	mainLight->setLightIndex(0);
	mainLight->enable(true);
	/*if( pkNode->childs()[0]->collidesWith(*pkNode->childs()[1]) ) {
		pkNode->OnCollision(pkNode->childs()[0],pkNode->childs()[1]);
	}*/
	
	//mesh->updateTransformation();
	//mesh->Draw();

	RegisterInBSPtree(bsp, true);
	RegisterInBSPtree(Tank, true);
	ArrangeBSPTree();
	return true;
}

bool Scene1::deInit(){

	delete mainLight;

	return true;
}

void Scene1::UpdateInputs(DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Sound& pkSound, DoMaRe::Renderer& renderer){
	
	if (dInput.keyDown(DoMaRe::Input::KEY_J)){
		DoMaRe::Node * c = Tank->FindChildByName("Body");
		c->SetPos(c->GetPos().x - 0.3f * timer.timeBetweenFrames(), c->GetPos().y, c->GetPos().z);
	}
	if (dInput.keyDown(DoMaRe::Input::KEY_K)){
		DoMaRe::Node * c = Tank->FindChildByName("Body");
		c->SetPos(c->GetPos().x + 0.3f * timer.timeBetweenFrames(), c->GetPos().y, c->GetPos().z);
	}
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

	/*if(dInput.keyDown(DoMaRe::Input::KEY_L)){
		pkNode->setPos(pkNode->posX() + (mSpeed * timer.timeBetweenFrames()) , pkNode->posY(), pkNode->posZ());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_K)){
		pkNode->setPos(pkNode->posX() - (mSpeed * timer.timeBetweenFrames()), pkNode->posY(), pkNode->posZ());
	}*/

	if(dInput.keyDown(DoMaRe::Input::KEY_B)){
		mainLight->enable(!mainLight->isEnabled());
	}

	if(dInput.keyDown(DoMaRe::Input::KEY_V)){
		float newDT = timer.deltaTime() == 1.0f ? 0.0f : 1.0f;
		timer.setdeltaTime(newDT);
	}
}
