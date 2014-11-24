#pragma once
#include <iostream>
#include <string>
#include "../Renderer/EMath.h"
#include "../Renderer/AABB.h"
#include "../Renderer/RenderTypes.h"

#include "../Physics/RigidBody.h"
#include "../../ext/irrKlang/include/irrKlang.h"

namespace DoMaRe{
	class Renderer;
	class Timer;
	class Node;
	class AABB;
	class RigidBody;
	class Physics;
	class MYENGINE_API Entity3D{

		friend class Node;

	public:
		Entity3D();
		virtual ~Entity3D();

	public:

		const RigidBody* rigidbody() const { return m_pkRigidBody; };
		RigidBody* rigidBody(){ return m_pkRigidBody; };

		void setPos(float fPosX, float fPosY);
		void setPos(float fPosX,float fPosY, float fPosZ);
		void setRotation(float fRotationX, float fRotationY, float fRotationZ);
		void setScale(float fScaleX, float fScaleY, float fScaleZ);
		void setName(std::string _name);

		//irrklang::ISound&	getSound()const{ return *_theSound; }
		//void				setSound(irrklang::ISound& theSound){	_theSound = &theSound; }
		std::string getName() const;


		virtual void Draw() = 0;

		void UseGravity(bool _T);
		void SetGravity(float _G);
		
		float posX() const;
		float posY() const;
		float posZ() const;

		float rotationX() const { return m_pkRigidBody->rotationX();}
		float rotationY() const { return m_pkRigidBody->rotationY();}
		float rotationZ() const { return m_pkRigidBody->rotationZ();}

		float scale() const;
		float scaleX() const;
		float scaleY() const;
		float scaleZ() const;
/*
		float previousPosX() const;
		float previousPosY() const;
		float previousPosZ() const;
		*/
		//float getGravity() const;
		//bool isUsingGravity() const;

		enum CollisionResult{
			CollisionVertical,
			CollisionHorizontal,
			NoCollision
		};

		//CollisionResult checkCollision(Entity2D& rkEntity2D) const;
		//void drawAABB (Renderer& rkRenderer) const;

		void drawAABB(Renderer& pkRenderer) const;
		//void UpdateGravityPos();
		
		virtual void updateTransformation();

		void updateLocalTransformation();
		//void returnToPos(float fPosX, float fPosY, float fPosZ);
		const Matrix& transformationMatrix() const;

		void setParent (Node* pkParent);

		const AABB& aabb() const;
		AABB& aabb();
	private:

		AABB* m_kAABB;


		float _PosX, _PosY, _PosZ;
		float _RotX, _RotY, _RotZ;
		float _ScaleX,_ScaleY, _ScaleZ;
		//float _PreviousPosX, _PreviousPosY, _PreviousPosZ;
		//float _Gravity;
		//bool _UseGravity;
		std::string _Name;

		Node* m_pkParent;

		RigidBody* m_pkRigidBody;

	protected:

		Matrix _TrMatrix;
		Matrix _TrLocalMatrix;

	//	irrklang::ISound * _theSound;
	};
}