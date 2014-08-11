#include "Sprite.h"
#include "Entity2D.h"
#include "..\Renderer\Renderer.h"
#include "..\timer\pg1_timer.h"
#include "animation.h"
#include <d3dx9.h>
using namespace DoMaRe;


Sprite::Sprite() : Entity2D(), s_Texture(NoTexture), s_Vertex( new TexCoordVertex[4] ){
	s_Vertex[0].x = -0.5;	s_Vertex[0].y = 0.5; s_Vertex[0].z = 0.0;
	s_Vertex[1].x =  0.5;	s_Vertex[1].y = 0.5; s_Vertex[1].z = 0.0;
	s_Vertex[2].x = -0.5;	s_Vertex[2].y = -0.5; s_Vertex[2].z = 0.0;
	s_Vertex[3].x = 0.5;	s_Vertex[3].y = -0.5; s_Vertex[3].z = 0.0;

	s_Vertex[0].u = 0.0;	s_Vertex[0].v = 0.0;
	s_Vertex[1].u = 1.0;	s_Vertex[1].v = 0.0;
	s_Vertex[2].u = 0.0;	s_Vertex[2].v = 1.0;
	s_Vertex[3].u = 1.0;	s_Vertex[3].v = 1.0;
}

Sprite::~Sprite(){
	delete[] s_Vertex;
	s_Vertex = NULL;

	m_pkAnimationList.clear();
}

void Sprite::setTextCoords( float U1, float V1,
							float U2, float V2,
							float U3, float V3,
							float U4, float V4){
		s_Vertex[0].u = U1;	s_Vertex[0].v = V1;
		s_Vertex[1].u = U2;	s_Vertex[1].v = V2;
		s_Vertex[2].u = U3;	s_Vertex[2].v = V3;
		s_Vertex[3].u = U4;	s_Vertex[3].v = V4;
}

void Sprite::setTexture(Texture& _Texture){
	s_Texture = _Texture;
}

void Sprite::setAnimation(Animation* pkAnimation){
	m_pkAnimation = pkAnimation;
	m_pkAnimationList.push_back(*pkAnimation);
}

void Sprite::AddAnimation(Animation* pkAnimation){
	m_pkAnimationList.push_back(*pkAnimation);
}

void Sprite::AddAnimation(std::vector<Animation> animation){
	m_pkAnimationList = animation;
	if(!m_pkAnimationList.empty())
		m_pkAnimation = &m_pkAnimationList[0];
}

void Sprite::setAnimation(std::string pk_Name){
	if(m_pkAnimationList.empty()) return;
	std::vector<Animation>::iterator iter;
	for(iter = m_pkAnimationList.begin(); iter != m_pkAnimationList.end(); iter++){
		if(iter->getName() == pk_Name){
			m_pkAnimation = iter._Ptr;
			return;
		}
	}
}

void Sprite::Update(Timer& rkTimer){
	if(!m_pkAnimation){
		return;
	}
	m_pkAnimation->update(rkTimer);
	unsigned int uiCurrentFrame = m_pkAnimation->currentFrame();
	if(uiCurrentFrame != m_uiPreviousFrame){
		const Animation::Frame& rkFrame = m_pkAnimation->frames()[uiCurrentFrame];
		setTextCoords(rkFrame.u1, rkFrame.v1,rkFrame.u2, rkFrame.v2,rkFrame.u3, rkFrame.v3,rkFrame.u4, rkFrame.v4);
	}
}

void Sprite::draw(Renderer& r) const{
	r.setCurrentTexture(s_Texture);
	r.setMatrix( World, _TrMatrix );
	r.Draw(s_Vertex, DoMaRe::TriangleStrip, 4);
}

/*void Sprite::UpdateGravityPos(){
	if(isUsingGravity()){
		setPos(posX(), posY() - getGravity());
		updateLocalTransformation();
	}
}*/