#include "Scene1.h"
using namespace MiJuego;
bool ds = true;
float mSpeed = 1.0f;

bool Scene1::Init(DoMaRe::Import& Importer){
//	getEntity(&_Cubo1,"floor");
//	getEntity(&_Sprite2,"player1");
	mainCamera = new DoMaRe::Camera();
	mainCamera->Init(Importer.GetRenderer());
	
	return true;
}

bool Scene1::Frame(DoMaRe::Renderer& renderer, DoMaRe::DirectInput& dInput, DoMaRe::Timer& timer, DoMaRe::Import& import, DoMaRe::Game& game){
	if(dInput.keyDown(DoMaRe::Input::KEY_P)){
		//game.setScene("main2",import,"Archivo.xml");
		return true;
	}

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

	/*
	static float fSp = 3.0f;
	static float initGravity = _Sprite2->getGravity();
	static float jumpSpeed = 7;
	static bool isJumping = false;

	if(_Sprite2->checkCollision(*_Cubo1) == DoMaRe::Entity2D::CollisionHorizontal ){
		isJumping = true;

		_Sprite2->UseGravity(true);
		_Sprite2->SetGravity( _Sprite2->getGravity()  +  fSp / 10 );				
		_Sprite2->returnToPos( _Sprite2->previousPosX(), _Sprite2->posY() );
	}else if(_Sprite2->checkCollision(*_Cubo1) == DoMaRe::Entity2D::CollisionVertical){
		isJumping = false;
		_Sprite2->UseGravity(false);
		_Sprite2->SetGravity(initGravity);
		_Sprite2->returnToPos( _Sprite2->posX() , _Sprite2->previousPosY() );
	}else{
		isJumping = true;

		_Sprite2->UseGravity(true);
		_Sprite2->SetGravity( _Sprite2->getGravity()  +  fSp / 10  );
	}
	if(dInput.keyDown(DoMaRe::Input::KEY_SUBTRACT)){
		_Cubo1->setPos(_Cubo1->posX(), _Cubo1->posY(), _Cubo1->posZ() - 10.0f);
		
	}
	if(dInput.keyDown(DoMaRe::Input::KEY_ADD)){
		_Cubo1->setPos(_Cubo1->posX(), _Cubo1->posY(), _Cubo1->posZ() + 10.0f);
		
	}
	if(dInput.keyDown(DoMaRe::Input::KEY_LEFT)){

		if(dInput.keyDown(DoMaRe::Input::KEY_UP) && isJumping == false){
		_Sprite2->setAnimation("Jump");
		_Sprite2->setPos(_Sprite2->posX(), _Sprite2->posY() + 0.5f);
		_Sprite2->SetGravity(-jumpSpeed);
		_Sprite2->UseGravity(true);
		isJumping = true;
		}

		_Sprite2->setPos(_Sprite2->posX() - fSp, _Sprite2->posY());
		if(!isJumping) _Sprite2->setAnimation("Run");
		ds=false;
		if(!isJumping) _Sprite2->setScale( -90.0f, 160.0f);
	}
	else if(dInput.keyDown(DoMaRe::Input::KEY_RIGHT)){

		if(dInput.keyDown(DoMaRe::Input::KEY_UP) && isJumping == false){
		_Sprite2->setAnimation("Jump");
		_Sprite2->setPos(_Sprite2->posX(), _Sprite2->posY() + 0.5f);
		_Sprite2->SetGravity(-jumpSpeed);
		_Sprite2->UseGravity(true);
		isJumping = true;
		}
		_Sprite2->setPos(_Sprite2->posX() + fSp, _Sprite2->posY());
		if(!isJumping) _Sprite2->setAnimation("Run");
		ds=true;
		if(!isJumping)_Sprite2->setScale( 90.0f, 160.0f);
	}else if(dInput.keyDown(DoMaRe::Input::KEY_UP) && isJumping == false){
		_Sprite2->setPos(_Sprite2->posX(), _Sprite2->posY() + 0.5f);
		_Sprite2->setAnimation("Jump");
		_Sprite2->SetGravity(-jumpSpeed);
		_Sprite2->UseGravity(true);
	}else{
		if(!isJumping)_Sprite2->setAnimation("Idle");
		if(ds)
		_Sprite2->setScale(60.0f, 160.0f);
		else
		_Sprite2->setScale(-60.0f, 160.0f);
	}
	*/
	return true;
}
