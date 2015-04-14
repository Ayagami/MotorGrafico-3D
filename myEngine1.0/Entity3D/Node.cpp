#define NOMINMAX
#include "Node.h"
#include "BoneInfo.h"
#include "Bones.h"
#include "3DAnimation.h"
#include <algorithm>
using namespace DoMaRe;

Node::Node() : Entity3D(), m_pBone(NULL), m_pCurrentAnimation(NULL), FrameIndex(-1), baseRot( new DoMaReQuat() ){
}

Node::~Node() {
	while ( !m_pkChilds.empty() ){
		Entity3D* pkChild = m_pkChilds.back();
		m_pkChilds.pop_back();

		delete pkChild;
		pkChild = NULL;
	} 

	if(m_pBone != NULL){
		delete m_pBone;
		m_pBone = NULL;
	}

	if (baseRot != NULL){
		delete baseRot;
		baseRot = NULL;
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

	if(m_pBone != NULL){
		m_pBone->setTransformation(*_TrMatrix);
	}
	//--
	float MaxX = std::numeric_limits<float>::lowest();
	float MaxY = std::numeric_limits<float>::lowest();
	float MaxZ = std::numeric_limits<float>::lowest();

	float MinX = std::numeric_limits<float>::max();
	float MinY = std::numeric_limits<float>::max();
	float MinZ = std::numeric_limits<float>::max();
	
	//---

	for(std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); ++it){
		(*it)->updateTransformation();

		//---
		float AabbMx = (*it)->posX() + ( (*it)->aabb().offset()->x + ( (*it)->aabb().width() / 2 ) );
		float AabbMy = (*it)->posY() + ( (*it)->aabb().offset()->y + ( (*it)->aabb().height() / 2 ) );
		float AabbMz = (*it)->posZ() + ( (*it)->aabb().offset()->z + ( (*it)->aabb().depth() / 2 ) );

		
		float Aabbmx = (*it)->posX() + ( (*it)->aabb().offset()->x - ( (*it)->aabb().width() / 2 ) );
		float Aabbmy = (*it)->posY() + ( (*it)->aabb().offset()->y - ( (*it)->aabb().height() / 2 ) );
		float Aabbmz = (*it)->posZ() + ( (*it)->aabb().offset()->z - ( (*it)->aabb().depth() / 2 ) );


		if(MaxX < AabbMx) MaxX = AabbMx;
		if(MaxY < AabbMy) MaxY = AabbMy;
		if(MaxZ < AabbMz) MaxZ = AabbMz;

		if(MinX > Aabbmx) MinX = Aabbmx;
		if(MinY > Aabbmy) MinY = Aabbmy;
		if(MinZ > Aabbmz) MinZ = Aabbmz;
		//---

	}
	aabb().setData( fabs(MaxX - MinX), fabs(MaxY - MinY), fabs(MaxZ - MinZ), (MinX + MaxX) / 2 - this->posX() , (MinY + MaxY) / 2 - this->posY(), (MinZ + MaxZ) / 2 - this->posZ());	
}

void Node::Draw(){
	for(std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); ++it) {
		(*it)->Draw();
	}
}

void Node::playAnimation(std::string animationName){
	if(m_Animations.count(animationName)){
		if(m_pCurrentAnimation != m_Animations[animationName]){
			if(m_pCurrentAnimation != NULL){
				m_pCurrentAnimation->Stop();
			}
			setAnimation(animationName);
		}
		m_pCurrentAnimation->Play();
	}
}

void Node::AddAnimation(Animation3D* anim){
	if(!m_Animations.count(anim->GetName())){
		m_Animations[anim->GetName()] = anim;
	}
}

void Node::Update(const double& dTime){
	if(m_pCurrentAnimation != NULL)
		m_pCurrentAnimation->Update(dTime);
}

void Node::setAnimation(Animation3D* anim){
	m_pCurrentAnimation = anim;
	FrameIndex = m_pCurrentAnimation->GetFrameIndex(getName());
	for(int i=0; i < m_pkChilds.size(); i++){
		DoMaRe::Node* pkChild = dynamic_cast<DoMaRe::Node*>(m_pkChilds[i]);
		if(pkChild){		// Its a node.
			pkChild->setAnimation(anim);
		}
	}
}

bool Node::isPlaying(){
	if(m_pCurrentAnimation != NULL){
		if(m_pCurrentAnimation->GetState() == Animation3D::State::PLAY){
			if(FrameIndex != -1)
				return true;
		}
	}
	return false;
}

void Node::setAnimation(std::string animName){
	if(m_Animations.count(animName)){
		setAnimation(m_Animations[animName]);
	}
}