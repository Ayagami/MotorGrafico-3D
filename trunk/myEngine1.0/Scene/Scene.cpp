#include "Scene.h"
#include "..\Entity2D\Entity2D.h"
#include "..\Entity2D\Sprite.h"
#include "..\Entity2D\Quad.h"
#include "..\Game.h"
#include "..\Entity2D\animation.h"
#include "Import.h"
#include "..\timer\pg1_timer.h"


using namespace DoMaRe;



bool Scene::Init(){
	return true;
	// Aca van cosas del importer.
}

bool Scene::Frame(DoMaRe::Renderer& r, DoMaRe::DirectInput& directInput,Timer& timer, Import& Importer, Game& game){
	return true;
}

bool Scene::draw(DoMaRe::Renderer& r, DoMaRe::DirectInput& directInput,Timer& timer, Import& Importer){
	if(m_pkEntidades.empty()) return false;

	std::vector<Entity2D*>::iterator iter;
	for(iter = m_pkEntidades.begin(); iter != m_pkEntidades.end(); iter++){
		(*iter)->Update(timer);
		(*iter)->UpdateGravityPos();
		(*iter)->draw(r);
	}
	return true;
}

bool Scene::deinit(){
	if(m_pkEntidades.empty()) return true;

	for(int i = 0; i < m_pkEntidades.size() ; i++){
		delete m_pkEntidades[i];
		m_pkEntidades[i] = NULL;
	}

	m_pkEntidades.clear();
	return true;
}

bool Scene::addEntity(Entity2D* Entity){
	m_pkEntidades.push_back(Entity);
	return true;
}

bool Scene::getEntity(Sprite** Entity, std::string Name){
	if(m_pkEntidades.empty())
		return true;

	for(int i=0; i < m_pkEntidades.size(); i++){
		if(m_pkEntidades[i]->getName() == Name){
			*Entity = (Sprite*)m_pkEntidades[i];
			return true;
		}
	}
	return false;
}

bool Scene::getEntity(Quad** Entity, std::string Name){
	if(m_pkEntidades.empty())
		return true;

	for(int i=0; i < m_pkEntidades.size(); i++){
		if(m_pkEntidades[i]->getName() == Name){
			*Entity = (Quad*)m_pkEntidades[i];
			return true;
		}
	}
	return false;
}