#pragma once
#include <iostream>
#include <string>
#include "../Renderer/EMath.h"
#include "../Renderer/RenderTypes.h"
namespace DoMaRe{
	class Renderer;
	class Timer;
	class MYENGINE_API Entity2D{
	public:
		Entity2D();
		virtual ~Entity2D();
	public:
		void setPos(float fPosX,float fPosY);
		void setRotation(float fRotation);
		void setScale(float fScaleX, float fScaleY);
		void setName(std::string _name);
		std::string getName() const;
		virtual void draw(Renderer& r) const = 0;
		virtual void Update(Timer& t) = 0;
		void UseGravity(bool _T);
		void SetGravity(float _G);
		float posX() const;
		float posY() const;
		float rotation() const;
		float scale() const;
		float scaleX() const;
		float scaleY() const;
		float previousPosX() const;
		float previousPosY() const;
		float getGravity() const;
		bool isUsingGravity() const;

		enum CollisionResult{
			CollisionVertical,
			CollisionHorizontal,
			NoCollision
		};

		CollisionResult checkCollision(Entity2D& rkEntity2D) const;
		void drawAABB (Renderer& rkRenderer) const;

		void UpdateGravityPos();
		void updateLocalTransformation();
		void returnToPos(float fPosX, float fPosY);
		const Matrix transformationMatrix();
	private:
		float _PosX, _PosY;
		float _Rot;
		float _ScaleX,_ScaleY;
		float _PreviousPosX, _PreviousPosY;
		float _Gravity;
		bool _UseGravity;
		std::string _Name;
	protected:
		Matrix _TrMatrix;
	};
}