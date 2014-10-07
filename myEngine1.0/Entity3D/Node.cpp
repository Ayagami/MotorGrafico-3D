#define NOMINMAX
#include "Node.h"
#include <algorithm>
using namespace DoMaRe;

Node::Node() : Entity3D() {

}

Node::~Node() {
	while ( !m_pkChilds.empty() ){
		Entity3D* pkChild = m_pkChilds.back();
		m_pkChilds.pop_back();

		delete pkChild;
		pkChild = NULL;
	} 
}

void Node::addChild(Entity3D* pkChild){
	m_pkChilds.push_back(pkChild);
}

void Node::removeChild(Entity3D* pkChild){
	m_pkChilds.erase( std::find( m_pkChilds.begin(), m_pkChilds.end(), pkChild ) );
}

void Node::updateTransformation(){
	Entity3D::updateTransformation();

	//--
	float fMaxX = std::numeric_limits<float>::lowest();
	float fMaxY = std::numeric_limits<float>::lowest();
	float fMaxZ = std::numeric_limits<float>::lowest();

	float fMinX = std::numeric_limits<float>::max();
	float fMinY = std::numeric_limits<float>::max();
	float fMinZ = std::numeric_limits<float>::max();
	
	//---

	for(std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); ++it){
		(*it)->updateTransformation();
		//---
		float fAabbMaxX = (*it)->posX() + ( (*it)->aabb().offset()->x + ( (*it)->aabb().width() / 2 ) );
		float fAabbMaxY = (*it)->posY() + ( (*it)->aabb().offset()->y + ( (*it)->aabb().height() / 2 ) );
		float fAabbMaxZ = (*it)->posZ() + ( (*it)->aabb().offset()->z + ( (*it)->aabb().depth() / 2 ) );

		float fAabbMinX = (*it)->posX() + ( (*it)->aabb().offset()->x - ( (*it)->aabb().width() / 2 ) );
		float fAabbMinY = (*it)->posY() + ( (*it)->aabb().offset()->y - ( (*it)->aabb().height() / 2 ) );
		float fAabbMinZ = (*it)->posZ() + ( (*it)->aabb().offset()->z - ( (*it)->aabb().depth() / 2 ) );

		if(fMaxX < fAabbMaxX) fMaxX = fAabbMaxX;
		if(fMaxY < fAabbMaxY) fMaxY = fAabbMaxY;
		if(fMaxZ < fAabbMaxZ) fMaxZ = fAabbMaxZ;

		if(fMinX > fAabbMinX) fMinX = fAabbMinX;
		if(fMinY > fAabbMinY) fMinY = fAabbMinY;
		if(fMinZ > fAabbMinZ) fMinZ = fAabbMinZ;
		//---
	}
	aabb().setData( fabs(fMaxX - fMinX), fabs(fMaxY - fMinY), fabs(fMaxZ - fMinZ), (fMinX + fMaxX) / 2 - this->posX(), (fMinY + fMaxY) / 2 - this->posY(), (fMinZ + fMaxZ) / 2 - this->posZ());	
}

void Node::Draw(){
	for(std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); ++it) {
		(*it)->Draw();
	}
}