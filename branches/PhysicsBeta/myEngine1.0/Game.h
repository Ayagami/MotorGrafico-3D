#pragma once
#include "myEngine_API.h"
#include <iostream>
#include <string>
#include <vector>
namespace DoMaRe{
	class Renderer;
	class DirectInput;
	class Timer;
	class Scene;
	class Import;
	class MYENGINE_API Game{
		public:
			Game();
			Game(std::string);
			virtual bool Init(DoMaRe::Renderer&, DoMaRe::Import&) = 0;
			virtual void Frame(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&) = 0;
			virtual void DeInit() = 0;
			bool GameOn;
			void setGame(const bool b){ GameOn = b;}
			bool getGame(){ return GameOn;}
			Scene* currentScene();
			void setScene(std::string,DoMaRe::Import&, std::string fileName);
			void addScene(Scene* pkScene);
		protected:
			Scene * _currentScene;
			std::vector<Scene*> scenesList;
	};
}