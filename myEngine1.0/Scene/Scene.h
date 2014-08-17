#pragma once
#include "..\myEngine_API.h"
#include "Camera.h"
#include "..\Renderer\Renderer.h"
#include <iostream>
#include <vector>
#include <string>
namespace DoMaRe{
	class Entity2D;
	class Sprite;
	class Quad;
	//class Renderer;
	class Timer;
	class Import;
	class DirectInput;
	class Game;
	//class Camera;
	class MYENGINE_API Scene{
		public:
			std::string Name;
			virtual bool Init(DoMaRe::Import&);
			virtual bool Frame(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&, DoMaRe::Game&);
			bool deinit();
			bool draw(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&);
			bool getEntity(Sprite**, std::string);
			bool getEntity(Quad**, std::string);
			Camera* getCamera() { return mainCamera; }
			bool addEntity(Entity2D*);
			Camera* mainCamera;
		private:
			std::vector<Entity2D*> m_pkEntidades;
			
	};
}