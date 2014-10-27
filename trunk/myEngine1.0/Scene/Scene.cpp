#include "Scene.h"
#include "..\Entity2D\Entity2D.h"
#include "..\Entity2D\Sprite.h"
#include "..\Entity2D\Quad.h"

#include "..\Entity3D\Entity3D.h"
#include "..\Entity3D\Mesh.h"
#include "..\Entity3D\Node.h"

#include "Camera.h"
#include "..\Game.h"
#include "..\Entity2D\animation.h"
#include "Import.h"
#include "..\timer\pg1_timer.h"
#include "../Sound/Sound.h"

using namespace DoMaRe;

Scene::Scene() : pkNode(NULL){

}
Scene::~Scene(){

}
bool Scene::Init(DoMaRe::Import&){
	return true;
}

bool Scene::Frame(DoMaRe::Renderer& r, DoMaRe::DirectInput& directInput,Timer& timer, Import& Importer, Game& game, Sound& sound){
	return true;
}

bool Scene::draw(DoMaRe::Renderer& r, DoMaRe::DirectInput& directInput,Timer& timer, Import& Importer){
	if(m_pkEntidades.empty() && m_pkEntidades3D.empty() && pkNode == NULL) return false;

	std::vector<Entity2D*>::iterator iter;
	for(iter = m_pkEntidades.begin(); iter != m_pkEntidades.end(); iter++){
		(*iter)->Update(timer);
		(*iter)->UpdateGravityPos();
		(*iter)->draw(r);
	}

	for(int i=0; i < m_pkEntidades3D.size(); i++){
		m_pkEntidades3D[i]->Draw();
	}

	if(pkNode != NULL){
		pkNode->updateTransformation();

		//int r = mainCamera->AABBinFrustum(pkNode->aabb());

		/*
		if( r == Camera::OUTSIDE )
			OutputDebugString("OUTSIDE");
		else if(r == Camera::INTERSECT)
			OutputDebugString("INTERSECT");
		else if(r == Camera::INSIDE)
			OutputDebugString("INSIDE");
		*/
		//int R = mainCamera->AABBinFrustum(pkNode->aabb());
	//	if(R != Camera::OUTSIDE/* && R != Camera::INTERSECT */){
		//	pkNode->Draw();
	//	}

		pkNode->Draw();
	}

	return true;
}

bool Scene::deinit(){
	if(m_pkEntidades.empty() && m_pkEntidades3D.empty()) return true;

	for(int i = 0; i < m_pkEntidades.size() ; i++){
		delete m_pkEntidades[i];
		m_pkEntidades[i] = NULL;
	}

	m_pkEntidades.clear();

	for(int i = 0; i < m_pkEntidades3D.size() ; i++){
		if(m_pkEntidades3D[i]){
			delete m_pkEntidades3D[i];
			m_pkEntidades3D[i] = NULL;
		}
	}

	m_pkEntidades3D.clear();

	if(pkNode != NULL){
		delete pkNode;
		pkNode = NULL;
	}

	return true;
}

bool Scene::getNode(Node& theNodeDir){
	theNodeDir = *pkNode;
	return true;
}

bool Scene::addEntity(Entity2D* Entity){
	m_pkEntidades.push_back(Entity);
	return true;
}

bool Scene::addEntity(Entity3D* Entity){
	m_pkEntidades3D.push_back(Entity);
	return true;
}

bool Scene::getEntity(Mesh** Entity, std::string Name){
	if(m_pkEntidades3D.empty()) return false;
	for(int i=0; i < m_pkEntidades3D.size(); i++){
		if(m_pkEntidades3D[i]->getName() == Name){
			*Entity = (Mesh*)m_pkEntidades3D[i];
			return true;
		}
	}
	return false;
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