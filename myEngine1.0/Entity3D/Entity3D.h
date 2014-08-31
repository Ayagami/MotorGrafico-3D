#pragma once
#include <iostream>
#include <string>
#include "../Renderer/EMath.h"
#include "../Renderer/RenderTypes.h"
namespace DoMaRe{
	class Renderer;
	class Timer;
	class MYENGINE_API Entity3D{
	public:
		Entity3D();
		virtual ~Entity3D();
	public:
		void setPos(float fPosX, float fPosY);
		void setPos(float fPosX,float fPosY, float fPosZ);

		void setRotation(float fRotationX, float fRotationY, float fRotationZ);

		void setScale(float fScaleX, float fScaleY, float fScaleZ);
		void setName(std::string _name);
		std::string getName() const;
		virtual void Draw(Renderer& r) const = 0;
		void UseGravity(bool _T);
		void SetGravity(float _G);
		float posX() const;
		float posY() const;
		float posZ() const;

		float rotationX() const { return _RotX;}
		float rotationY() const { return _RotY;}
		float rotationZ() const { return _RotZ;}

		float scale() const;
		float scaleX() const;
		float scaleY() const;
		float scaleZ() const;
		float previousPosX() const;
		float previousPosY() const;
		float previousPosZ() const;

		float getGravity() const;
		bool isUsingGravity() const;

		enum CollisionResult{
			CollisionVertical,
			CollisionHorizontal,
			NoCollision
		};

		//CollisionResult checkCollision(Entity2D& rkEntity2D) const;
		//void drawAABB (Renderer& rkRenderer) const;

		void UpdateGravityPos();
		void updateLocalTransformation();
		void returnToPos(float fPosX, float fPosY, float fPosZ);
		const Matrix transformationMatrix();
	private:
		float _PosX, _PosY, _PosZ;
		float _RotX, _RotY, _RotZ;
		float _ScaleX,_ScaleY, _ScaleZ;
		float _PreviousPosX, _PreviousPosY, _PreviousPosZ;
		float _Gravity;
		bool _UseGravity;
		std::string _Name;
	protected:
		Matrix _TrMatrix;
	};
}