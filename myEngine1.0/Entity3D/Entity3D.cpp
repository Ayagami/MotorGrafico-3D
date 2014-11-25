#pragma once
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include "Entity3D.h"
#include "..\Renderer\Renderer.h"
#include "..\Physics\RigidBody.h"
#include "Mesh.h"
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
_ScaleZ(1.0f),/*
_PreviousPosX(0.0f),
_PreviousPosY(0.0f),
_PreviousPosZ(0.0f),
_UseGravity(false),
_Gravity(1.5f),*/
//_theSound(NULL),
_TrMatrix( new D3DXMATRIX() ),
_TrLocalMatrix (new D3DXMATRIX() ),
m_kAABB(new AABB()),
m_pkParent(NULL),
pk_RigidBody( new RigidBody() )
{
	D3DXMatrixIdentity(_TrMatrix);
	updateLocalTransformation();
}
Entity3D::~Entity3D(){
	delete _TrMatrix;
	_TrMatrix = NULL;

	delete _TrLocalMatrix;
	_TrLocalMatrix = NULL;

	delete pk_RigidBody;
	pk_RigidBody = NULL;

	delete m_kAABB;
	m_kAABB = NULL;
}


void Entity3D::setPos(float fPosX, float fPosY){

	pk_RigidBody->setPosition(fPosX,fPosY,pk_RigidBody->posZ());

}

void Entity3D::setPos(float fPosX, float fPosY, float fPosZ){


	pk_RigidBody->setPosition(fPosX,fPosY, fPosZ);
}


void Entity3D::setRotation(float fRotationX, float fRotationY, float fRotationZ){

	pk_RigidBody->setRotation(fRotationX,fRotationY,fRotationZ);
}

void Entity3D::setScale(float fScaleX, float fScaleY, float fScaleZ){
	_ScaleX = fScaleX;
	_ScaleY = fScaleY;
	_ScaleZ = fScaleZ;

}

void Entity3D::updateLocalTransformation(){

 D3DXMATRIX translateMatrix;
 D3DXMatrixTranslation(&translateMatrix, pk_RigidBody->posX(), pk_RigidBody->posY(), pk_RigidBody->posZ());

 D3DXMATRIX rotationMatrixZ, rotationMatrixX, rotationMatrixY;

 D3DXMatrixRotationZ(&rotationMatrixZ, pk_RigidBody->rotationZ());
 D3DXMatrixRotationY(&rotationMatrixY, pk_RigidBody->rotationY());
 D3DXMatrixRotationX(&rotationMatrixX, pk_RigidBody->rotationX());

 D3DXMATRIX scaleMatrix;
 D3DXMatrixScaling(&scaleMatrix, _ScaleX, _ScaleY, _ScaleZ);

 D3DXMatrixIdentity(_TrLocalMatrix);

 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&translateMatrix);
 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&rotationMatrixZ);
 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&rotationMatrixY);
 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&rotationMatrixX);
 D3DXMatrixMultiply(_TrLocalMatrix,_TrLocalMatrix,&scaleMatrix);

	// FALTA ACTUALIZAR Y DEVOLVER MATRIZ DE RIGIDBODY
}

const Matrix& Entity3D::transformationMatrix() const{
	return _TrMatrix;
}

float Entity3D::posX() const{
	return pk_RigidBody->posX();
}

float Entity3D::posY() const{
	return pk_RigidBody->posY();
}

float Entity3D::posZ() const{
	return pk_RigidBody->posZ();
}

void Entity3D::setName(std::string _name){
	_Name = _name;
}

std::string Entity3D::getName() const{
	return _Name;
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

void Entity3D::drawAABB(Renderer& pkRenderer) const{
/*	static Mesh* s_AKAABBMesh;
	static bool s_bIsInitialized = false;
	if(!s_bIsInitialized){
		s_bIsInitialized = true;
		s_AKAABBMesh = new Mesh(pkRenderer);
		DoMaRe::MeshVertex * pakVertices = new DoMaRe::MeshVertex[8];
		unsigned short* pausIndices = new unsigned short[24];

		pakVertices[0].x = +0.5f;       pakVertices[0].y = +0.5f;       pakVertices[0].z = +0.5f;
        pakVertices[1].x = +0.5f;       pakVertices[1].y = +0.5f;       pakVertices[1].z = -0.5f;
        pakVertices[2].x = +0.5f;       pakVertices[2].y = -0.5f;       pakVertices[2].z = +0.5f;
        pakVertices[3].x = +0.5f;       pakVertices[3].y = -0.5f;       pakVertices[3].z = -0.5f;
        pakVertices[4].x = -0.5f;       pakVertices[4].y = +0.5f;       pakVertices[4].z = +0.5f;
        pakVertices[5].x = -0.5f;       pakVertices[5].y = +0.5f;       pakVertices[5].z = -0.5f;
        pakVertices[6].x = -0.5f;       pakVertices[6].y = -0.5f;       pakVertices[6].z = +0.5f;
        pakVertices[7].x = -0.5f;       pakVertices[7].y = -0.5f;       pakVertices[7].z = -0.5f;

        pausIndices[0] =	0;			pausIndices[1] =	1;			pausIndices[2] =	1;		pausIndices[3] = 3;
        pausIndices[4] =	3;			pausIndices[5] =	2;			pausIndices[6] =	2;		pausIndices[7] = 0;
        pausIndices[8] =	4;			pausIndices[9] =	5;			pausIndices[10] =	5;		pausIndices[11] = 7;
        pausIndices[12] =	7;			pausIndices[13] =	6;			pausIndices[14] =	6;		pausIndices[15] = 4;
        pausIndices[16] =	0;			pausIndices[17] =	4;			pausIndices[18] =	1;		pausIndices[19] = 5;
        pausIndices[20] =	3;			pausIndices[21] =	7;			pausIndices[22] =	2;		pausIndices[23] = 6;

		s_AKAABBMesh->setData(pakVertices,8,DoMaRe::LineStrip,pausIndices,24);

		delete[] pakVertices;
		delete[] pausIndices;
	}
	/*const Entity3D* t = this;
	const Node* pk = dynamic_cast<const Node*>(t) ;
	if(pk){
		s_AKAABBMesh->setParent((Node*) this);
	}*/
	
	
	//s_AKAABBMesh->setParent((Node*)this);
/*	s_AKAABBMesh->setPos( (_TrMatrix->_41 + _TrLocalMatrix->_41) / aabb().width() + aabb().offset()->x / aabb().width()  ,
						  (_TrMatrix->_42 + _TrLocalMatrix->_42) / aabb().width() + aabb().offset()->y / aabb().height() , 
						  (_TrMatrix->_43 + _TrLocalMatrix->_43) / aabb().width() + aabb().offset()->z / aabb().depth()  );
						  
	//s_AKAABBMesh->setPos(aabb().offset()->x - _TrMatrix->_41, aabb().offset()->y - _TrMatrix->_42 ,aabb().offset()->z - _TrMatrix->_43);
	//s_AKAABBMesh->setPos(0,0,0);
	
	//s_AKAABBMesh->setPos(aabb().offset()->x + posX() , aabb().offset()->y + posY() , aabb().offset()->z + posZ() );
	
	s_AKAABBMesh->setScale(aabb().width()  ,aabb().height() ,aabb().depth() );
	s_AKAABBMesh->updateTransformation();
	s_AKAABBMesh->Draw();*/

}

void Entity3D::updateTransformation(){
	
	updateLocalTransformation();

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