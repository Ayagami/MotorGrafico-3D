#pragma once
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include "Entity3D.h"
#include "..\Renderer\Renderer.h"
#include "Node.h"
#include <string>
#include <d3dx9.h>
using namespace DoMaRe;
Entity3D::Entity3D() :
_PosX(0.0f),
_PosY(0.0f),
_PosZ(0.0f),
_RotX(0.0f),
_RotY(0.0f),
_RotZ(0.0f),
_ScaleX(1.0f),
_ScaleY(1.0f),
_ScaleZ(1.0f),
_PreviousPosX(0.0f),
_PreviousPosY(0.0f),
_PreviousPosZ(0.0f),
_UseGravity(false),
_Gravity(1.5f),
//_theSound(NULL),
_TrMatrix( new D3DXMATRIX() ),
_TrLocalMatrix (new D3DXMATRIX() ),
m_kAABB(new AABB()),
m_pkParent(NULL)
{
	D3DXMatrixIdentity(_TrMatrix);
	updateLocalTransformation();
}
Entity3D::~Entity3D(){
	delete _TrMatrix;
	_TrMatrix = NULL;

	delete _TrLocalMatrix;
	_TrLocalMatrix = NULL;

	delete m_kAABB;
	m_kAABB = NULL;
}


void Entity3D::setPos(float fPosX, float fPosY){
	_PreviousPosX = _PosX;
	_PreviousPosY = _PosY;

	_PosX = fPosX;
	_PosY = fPosY;

	updateLocalTransformation();
}

void Entity3D::setPos(float fPosX, float fPosY, float fPosZ){
	_PreviousPosX = _PosX;
	_PreviousPosY = _PosY;
	_PreviousPosZ = _PosZ;

	_PosX = fPosX;
	_PosY = fPosY;
	_PosZ = fPosZ;

	updateLocalTransformation();
}


float Entity3D::getGravity() const{
	return _Gravity;
}

bool Entity3D::isUsingGravity() const{
	return _UseGravity;
}

void Entity3D::setRotation(float fRotationX, float fRotationY, float fRotationZ){
	_RotX = fRotationX;
	_RotY = fRotationY;
	_RotZ = fRotationZ;
	updateLocalTransformation();
}

void Entity3D::setScale(float fScaleX, float fScaleY, float fScaleZ){
	_ScaleX = fScaleX;
	_ScaleY = fScaleY;
	_ScaleZ = fScaleZ;
	updateLocalTransformation();
}

void Entity3D::SetGravity(float _G){
	_Gravity = _G;
}

void Entity3D::UseGravity(bool _T){
	_UseGravity = _T;
}

void Entity3D::updateLocalTransformation(){

 D3DXMATRIX translateMatrix;
 D3DXMatrixTranslation(&translateMatrix, _PosX, _PosY, _PosZ);

 D3DXMATRIX rotationMatrixZ, rotationMatrixX, rotationMatrixY;

 D3DXMatrixRotationZ(&rotationMatrixZ, _RotZ);
 D3DXMatrixRotationY(&rotationMatrixY, _RotY);
 D3DXMatrixRotationX(&rotationMatrixX, _RotX);

 D3DXMATRIX scaleMatrix;
 D3DXMatrixScaling(&scaleMatrix, _ScaleX, _ScaleY, _ScaleZ);

 D3DXMatrixIdentity(_TrLocalMatrix);

 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&translateMatrix);
 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&rotationMatrixZ);
 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&rotationMatrixY);
 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&rotationMatrixX);
 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&scaleMatrix);

}

const Matrix& Entity3D::transformationMatrix() const{
	return _TrMatrix;
}

float Entity3D::posX() const{
	return _PosX;
}

float Entity3D::posY() const{
	return _PosY;
}

float Entity3D::posZ() const{
	return _PosZ;
}

float Entity3D::previousPosX() const{
	return _PreviousPosX;
}

float Entity3D::previousPosY() const{
	return _PreviousPosY;
}

float Entity3D::previousPosZ() const{
	return _PreviousPosZ;
}

void Entity3D::setName(std::string _name){
	_Name = _name;
}

std::string Entity3D::getName() const{
	return _Name;
}

void Entity3D::returnToPos(float fPosX, float fPosY, float fPosZ){
	_PosX = fPosX;
	_PosY = fPosY;
	_PosZ = fPosZ;

	updateLocalTransformation();
}

float Entity3D::scaleX() const{
	return _ScaleX;
}

float Entity3D::scaleY() const{
	return _ScaleY;
}

float Entity3D::scaleZ() const{
	return _ScaleZ;
}

/*Entity3D::CollisionResult Entity3D::checkCollision(Entity3D& rkEntity3D) const{
	float fOverlapX = std::max( 0.0f, 
								std::min( posX() + fabs( scaleX() ) / 2.0f,rkEntity3D.posX() + fabs( rkEntity3D.scaleX() ) / 2.0f) -  
								std::max( posX() - fabs( scaleX() ) / 2.0f,rkEntity3D.posX() - fabs( rkEntity3D.scaleX() ) / 2.0f)
	);
	float fOverlapY = std::max( 0.0f, 
								std::min( posY() + fabs( scaleY() ) / 2.0f,  rkEntity3D.posY() + fabs( rkEntity3D.scaleY() ) / 2.0f) -  
								std::max( posY() - fabs( scaleY() ) / 2.0f, rkEntity3D.posY() - fabs( rkEntity3D.scaleY() ) / 2.0f)
	);

	if(fOverlapX != 0.0f && fOverlapY != 0.0f){
		if(fOverlapX > fOverlapY){
			return CollisionVertical;
		}else{
			return CollisionHorizontal;
		}
	}

	return NoCollision;
}*/

/*void Entity3D::drawAABB(Renderer& rkRenderer) const{
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
*/
void Entity3D::UpdateGravityPos(){
	if(isUsingGravity()){
		setPos(posX(), posY() - getGravity());
		updateLocalTransformation();
	}
}

void Entity3D::updateTransformation(){
	if(m_pkParent){
		D3DXMatrixIdentity(_TrMatrix);
		D3DXMatrixMultiply(_TrMatrix, m_pkParent->_TrMatrix, _TrLocalMatrix);
	}else{
		(*_TrMatrix) = (*_TrLocalMatrix);
	}
}

void Entity3D::setParent (Node* pkParent){
	m_pkParent = pkParent;
}

const AABB&	Entity3D::aabb() const{	return *m_kAABB; }
AABB&		Entity3D::aabb()	  {	return *m_kAABB; }