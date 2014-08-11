#pragma once
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include "Entity2D.h"
#include "..\Renderer\Renderer.h"
#include <string>
#include <d3dx9.h>
using namespace DoMaRe;
Entity2D::Entity2D() :
_PosX(0.0f),
_PosY(0.0f),
_Rot(0.0f),
_ScaleX(1.0f),
_ScaleY(1.0f),
_UseGravity(false),
_Gravity(1.5f),
_TrMatrix( new D3DXMATRIX() )
{

}
Entity2D::~Entity2D(){
	delete _TrMatrix;
	_TrMatrix = NULL;
}


void Entity2D::setPos(float fPosX, float fPosY){
	_PreviousPosX = _PosX;
	_PreviousPosY = _PosY;

	_PosX = fPosX;
	_PosY = fPosY;

	updateLocalTransformation();
}

float Entity2D::getGravity() const{
	return _Gravity;
}

bool Entity2D::isUsingGravity() const{
	return _UseGravity;
}

void Entity2D::setRotation(float fRotation){
	_Rot = fRotation;
	updateLocalTransformation();
}

void Entity2D::setScale(float fScaleX, float fScaleY){
	_ScaleX = fScaleX;
	_ScaleY = fScaleY;
	updateLocalTransformation();
}

void Entity2D::SetGravity(float _G){
	_Gravity = _G;
}

void Entity2D::UseGravity(bool _T){
	_UseGravity = _T;
}

void Entity2D::updateLocalTransformation(){
 D3DXMATRIX translateMatrix;
 D3DXMatrixTranslation(&translateMatrix, _PosX, _PosY, 0);

 D3DXMATRIX rotationMatrix;
 D3DXMatrixRotationZ(&rotationMatrix, _Rot);

 D3DXMATRIX scaleMatrix;
 D3DXMatrixScaling(&scaleMatrix, _ScaleX, _ScaleY, 1);

 D3DXMatrixIdentity(_TrMatrix);
 D3DXMatrixMultiply(_TrMatrix,&translateMatrix,_TrMatrix);
 D3DXMatrixMultiply(_TrMatrix,&rotationMatrix,_TrMatrix);
 D3DXMatrixMultiply(_TrMatrix,&scaleMatrix,_TrMatrix);
}

const Matrix Entity2D::transformationMatrix(){
	return (_TrMatrix);
}

float Entity2D::posX() const{
	return _PosX;
}

float Entity2D::posY() const{
	return _PosY;
}

float Entity2D::previousPosX() const{
	return _PreviousPosX;
}

float Entity2D::previousPosY() const{
	return _PreviousPosY;
}

void Entity2D::setName(std::string _name){
	_Name = _name;
}

std::string Entity2D::getName() const{
	return _Name;
}

void Entity2D::returnToPos(float fPosX, float fPosY){
	_PosX = fPosX;
	_PosY = fPosY;

	updateLocalTransformation();
}

float Entity2D::scaleX() const{
	return _ScaleX;
}

float Entity2D::scaleY() const{
	return _ScaleY;
}

Entity2D::CollisionResult Entity2D::checkCollision(Entity2D& rkEntity2D) const{
	float fOverlapX = std::max( 0.0f, 
								std::min( posX() + fabs( scaleX() ) / 2.0f,rkEntity2D.posX() + fabs( rkEntity2D.scaleX() ) / 2.0f) -  
								std::max( posX() - fabs( scaleX() ) / 2.0f,rkEntity2D.posX() - fabs( rkEntity2D.scaleX() ) / 2.0f)
	);
	float fOverlapY = std::max( 0.0f, 
								std::min( posY() + fabs( scaleY() ) / 2.0f,  rkEntity2D.posY() + fabs( rkEntity2D.scaleY() ) / 2.0f) -  
								std::max( posY() - fabs( scaleY() ) / 2.0f, rkEntity2D.posY() - fabs( rkEntity2D.scaleY() ) / 2.0f)
	);

	if(fOverlapX != 0.0f && fOverlapY != 0.0f){
		if(fOverlapX > fOverlapY){
			return CollisionVertical;
		}else{
			return CollisionHorizontal;
		}
	}

	return NoCollision;
}

void Entity2D::drawAABB(Renderer& rkRenderer) const{
	static ColorVertex s_akAABBVertices[5];
	static bool s_bIsInitialized = false;
	if(!s_bIsInitialized){
		s_bIsInitialized = true;

		s_akAABBVertices[0].x = -0.5;	s_akAABBVertices[0].y = -0.5;	s_akAABBVertices[0].z = 0.0; s_akAABBVertices[0].color = DoMaRe_COLOR_RGB(255,50,50);
		s_akAABBVertices[1].x = -0.5;	s_akAABBVertices[1].y = 0.5;	s_akAABBVertices[1].z = 0.0; s_akAABBVertices[1].color = DoMaRe_COLOR_RGB(255,70,70);
		s_akAABBVertices[2].x = 0.5;	s_akAABBVertices[2].y = 0.5;	s_akAABBVertices[2].z = 0.0; s_akAABBVertices[2].color = DoMaRe_COLOR_RGB(255,30,30);
		s_akAABBVertices[3].x = 0.5;	s_akAABBVertices[3].y = -0.5;	s_akAABBVertices[3].z = 0.0; s_akAABBVertices[3].color = DoMaRe_COLOR_RGB(255,15,15);
		s_akAABBVertices[4].x = -0.5;	s_akAABBVertices[4].y = -0.5;	s_akAABBVertices[4].z = 0.0; s_akAABBVertices[4].color = DoMaRe_COLOR_RGB(255,95,90);
	}

	rkRenderer.setCurrentTexture(NoTexture);
	rkRenderer.setMatrix(World, _TrMatrix );
	rkRenderer.Draw(s_akAABBVertices, DoMaRe::LineStrip, 5);
}

void Entity2D::UpdateGravityPos(){
	if(isUsingGravity()){
		setPos(posX(), posY() - getGravity());
		updateLocalTransformation();
	}
}