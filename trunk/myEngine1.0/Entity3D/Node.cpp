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

	for(std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); ++it){
		(*it)->updateTransformation();
	}

}

void Node::Draw(){
	for(std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); ++it) {
		(*it)->Draw();
	}
}