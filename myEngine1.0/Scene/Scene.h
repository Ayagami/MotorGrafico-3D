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
	class Node;

	class Physics;
	//class Camera;
	class MYENGINE_API Scene{
		public:
			Scene();
			/*Scene(std::string pkName);
			Scene(std::string pkName, Game& pkGame);
			Scene(Game& pkGame);*/
			virtual ~Scene();
			std::string Name;
			virtual bool Init(DoMaRe::Import&);
			virtual bool Frame(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&, DoMaRe::Game&, DoMaRe::Sound&);
			virtual bool deInit() = 0;
			bool deinit();
			bool draw(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&);
			bool getEntity(Sprite**, std::string);
			bool getEntity(Quad**, std::string);
			Entity3D* getEntity3D (const std::string& rkName, const DoMaRe::Node* pkParent);
			bool getNode(Node& theNodeDir);
			Camera* getCamera() { return mainCamera; }
			bool addEntity(Entity2D*);
			bool addEntity(Entity3D*);
			Camera* mainCamera;

			Node* pkNode;
		private:
			std::vector<Entity2D*> m_pkEntidades;
			std::vector<Entity3D*> m_pkEntidades3D;

			void ifNeededtoDraw(Entity3D& pkNode);
			//Game& CurrentGame;
	};
}