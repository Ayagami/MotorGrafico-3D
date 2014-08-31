#pragma once
#include "..\myEngine_API.h"
#include "Camera.h"
#include "..\Renderer\Renderer.h"
#include <iostream>
#include <vector>
#include <string>
namespace DoMaRe{
	class Entity2D;

	class Entity3D;
	class Mesh;
	class Sprite;
	class Quad;
	//class Renderer;
	class Timer;
	class Import;
	class DirectInput;
	class Game;
	class Sound;
	//class Camera;
	class MYENGINE_API Scene{
		public:
			std::string Name;
			virtual bool Init(DoMaRe::Import&);
			virtual bool Frame(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&, DoMaRe::Game&, DoMaRe::Sound&);
			virtual bool deInit() = 0;
			bool deinit();
			bool draw(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&);
			bool getEntity(Sprite**, std::string);
			bool getEntity(Quad**, std::string);
			bool getEntity(Mesh**, std::string);
			Camera* getCamera() { return mainCamera; }
			bool addEntity(Entity2D*);
			bool addEntity(Entity3D*);
			Camera* mainCamera;
		private:
			std::vector<Entity2D*> m_pkEntidades;
			std::vector<Entity3D*> m_pkEntidades3D;
			
	};
}