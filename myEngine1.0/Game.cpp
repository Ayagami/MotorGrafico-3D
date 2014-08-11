#include "Game.h"
#include "Scene\Scene.h"
#include "Scene\Import.h"
#include "Renderer\Renderer.h"
using namespace DoMaRe;
Game::Game() : GameOn(true){
}

Game::Game(std::string name) : GameOn(true){
	//setScene(name);
}

Scene* Game::currentScene(){
	return _currentScene;
}

void Game::addScene(Scene* pkScene){
	scenesList.push_back(pkScene);
}

void Game::setScene(std::string name, DoMaRe::Import& importer, std::string fileName){
	if(!_currentScene) return;
	if(_currentScene->Name == name) return;
	if(scenesList.empty()) return;

	std::vector<Scene*>::iterator iter;
	for(iter = scenesList.begin(); iter != scenesList.end(); iter++){
		if( (*iter._Ptr)->Name == name){
			_currentScene->deinit();
			_currentScene = *iter._Ptr;
			importer.GetRenderer()->Clear();
			importer.importScene(*_currentScene, fileName);
			_currentScene->Init();
			return;
		}
	}
}