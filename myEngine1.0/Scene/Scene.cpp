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

#include "../Physics/Physics.h"

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
		m_pkEntidades3D[i]->Draw(&r);
	}

	if(pkNode != NULL){
		pkNode->Draw(&r);
	}

	return true;
}
void Scene::ifNeededtoDraw(Entity3D& pkNode){

	/*int Result = getCamera()->AABBinFrustum(pkNode);

	switch(Result){
	
		case Camera::INSIDE :

			pkNode.Draw();
			break;

		case Camera::INTERSECT:
			{
			DoMaRe::Node* pkChild = dynamic_cast<DoMaRe::Node*>(&pkNode);
			if(pkChild){ // its a node...
			
				for( std::vector<Entity3D*>::const_iterator it = pkChild->childs().begin(); it != pkChild->childs().end(); it++){
				
					ifNeededtoDraw( *(*it) );

				}

			}else{
				pkNode.Draw();
			}

			break;
			}

	}*/
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

Entity3D* Scene::getEntity3D (const std::string& rkName, const DoMaRe::Node* pkParent){
     /*   for( std::vector<DoMaRe::Entity3D*>::const_iterator it = pkParent->childs().begin(); it != pkParent->childs().end(); it++){
				if( (*it)->getName() == rkName ){
                        return (*it);
                }
                
                DoMaRe::Node* pkChild = dynamic_cast<DoMaRe::Node*>(*it);

                if(pkChild){
                        for( std::vector<DoMaRe::Entity3D*>::const_iterator it = pkChild->childs().begin(); it != pkChild->childs().end();  it++){
								DoMaRe::Entity3D* pkResult = getEntity3D(rkName, pkChild);
                                if(pkResult){
                                        return pkResult;
                                }
                        }
                }
        }
        */
        return NULL;
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