#include "Frustrum.h"
#include "../Entity3D/Node.h"
using namespace DoMaRe;
//---------------------------------------------------------------
Frustrum::Frustrum(){
 for(unsigned int i=0; i < 6; i++)
		m_FrustumPlane[i] = new D3DXPLANE();
}
//---------------------------------------------------------------
Frustrum::~Frustrum(){
 for(unsigned int i=0; i < 6; i++){
		delete m_FrustumPlane[i];
		m_FrustumPlane[i] = NULL;
	}
}
//---------------------------------------------------------------
void Frustrum::Calculate(D3DXMATRIX * pMatrizVista,D3DXMATRIX * pMatrizProy){
 
        D3DXMATRIX FrustumProjectionMatrix;
 
        D3DXMatrixMultiply(&FrustumProjectionMatrix, pMatrizVista, pMatrizProy);
 
 // left plane
	m_FrustumPlane[0]->a = FrustumProjectionMatrix._14 + FrustumProjectionMatrix._11;
	m_FrustumPlane[0]->b = FrustumProjectionMatrix._24 + FrustumProjectionMatrix._21;
	m_FrustumPlane[0]->c = FrustumProjectionMatrix._34 + FrustumProjectionMatrix._31;
	m_FrustumPlane[0]->d = FrustumProjectionMatrix._44 + FrustumProjectionMatrix._41;

	// right plane
	m_FrustumPlane[1]->a = FrustumProjectionMatrix._14 - FrustumProjectionMatrix._11;
	m_FrustumPlane[1]->b = FrustumProjectionMatrix._24 - FrustumProjectionMatrix._21;
	m_FrustumPlane[1]->c = FrustumProjectionMatrix._34 - FrustumProjectionMatrix._31;
	m_FrustumPlane[1]->d = FrustumProjectionMatrix._44 - FrustumProjectionMatrix._41;

	// top plane
	m_FrustumPlane[2]->a = FrustumProjectionMatrix._14 - FrustumProjectionMatrix._12;
	m_FrustumPlane[2]->b = FrustumProjectionMatrix._24 - FrustumProjectionMatrix._22;
	m_FrustumPlane[2]->c = FrustumProjectionMatrix._34 - FrustumProjectionMatrix._32;
	m_FrustumPlane[2]->d = FrustumProjectionMatrix._44 - FrustumProjectionMatrix._42;

	// bottom plane
	m_FrustumPlane[3]->a = FrustumProjectionMatrix._14 + FrustumProjectionMatrix._12;
	m_FrustumPlane[3]->b = FrustumProjectionMatrix._24 + FrustumProjectionMatrix._22;
	m_FrustumPlane[3]->c = FrustumProjectionMatrix._34 + FrustumProjectionMatrix._32;
	m_FrustumPlane[3]->d = FrustumProjectionMatrix._44 + FrustumProjectionMatrix._42;

	// near plane
	m_FrustumPlane[4]->a = FrustumProjectionMatrix._13;
	m_FrustumPlane[4]->b = FrustumProjectionMatrix._23;
	m_FrustumPlane[4]->c = FrustumProjectionMatrix._33;
	m_FrustumPlane[4]->d = FrustumProjectionMatrix._43;

	// far plane    
	m_FrustumPlane[5]->a = FrustumProjectionMatrix._14 - FrustumProjectionMatrix._13;
	m_FrustumPlane[5]->b = FrustumProjectionMatrix._24 - FrustumProjectionMatrix._23;
	m_FrustumPlane[5]->c = FrustumProjectionMatrix._34 - FrustumProjectionMatrix._33;
	m_FrustumPlane[5]->d = FrustumProjectionMatrix._44 - FrustumProjectionMatrix._43;

	// normalize planes
	for (unsigned int i=0; i<6; i++){
		D3DXPlaneNormalize( m_FrustumPlane[i], m_FrustumPlane[i] );
	}
}
//---------------------------------------------------------------
int Frustrum::isIn(Node& pkNode){

	float sizeX = (pkNode.v_MaxBound.x - pkNode.v_MinBound.x) * 0.5f;
	float sizeY = (pkNode.v_MaxBound.y - pkNode.v_MinBound.y) * 0.5f;
	float sizeZ = (pkNode.v_MaxBound.z - pkNode.v_MinBound.z) * 0.5f;

	D3DXVECTOR3 aabbSize = D3DXVECTOR3(sizeX, sizeY , sizeZ);
	D3DXVECTOR3 aabbCenter = D3DXVECTOR3((pkNode.v_MaxBound.x + pkNode.v_MinBound.x) / 2 + pkNode.GetPos().x  , 
										 (pkNode.v_MaxBound.y + pkNode.v_MinBound.y) / 2 + pkNode.GetPos().y  ,
										 (pkNode.v_MaxBound.z + pkNode.v_MinBound.z) / 2 + pkNode.GetPos().z );

	int result = INSIDE;
	for(int i=0; i < 6; i++){
		Plane frustumPlane = m_FrustumPlane[i];
	float d = aabbCenter.x * frustumPlane->a +
	aabbCenter.y * frustumPlane->b +
	aabbCenter.z * frustumPlane->c;

	float r = aabbSize.x * std::abs(frustumPlane->a) +
	aabbSize.y * std::abs(frustumPlane->b) +
	aabbSize.z * std::abs(frustumPlane->c);

	float d_p_r = d + r;
	float d_m_r = d - r;

	if(d_p_r < -frustumPlane->d){
	result = OUTSIDE;
	break;
	}else if(d_m_r < -frustumPlane->d)
	result = INTERSECT;
	}

	return result;
	/*
        for (int i = 0; i < 6; i++)
 
        {
 
                if(D3DXPlaneDotCoord(&m_Planes[i],&pVertices[0]) >= 0.0f)
 
                {
 
                        continue;
 
                }
 
                if(D3DXPlaneDotCoord(&m_Planes[i],&pVertices[1]) >= 0.0f)
 
                {
 
                        continue;
 
                }
 
                if(D3DXPlaneDotCoord(&m_Planes[i],&pVertices[2]) >= 0.0f)
 
                {
 
                        continue;
 
                }
 
                if(D3DXPlaneDotCoord(&m_Planes[i],&pVertices[3]) >= 0.0f)
 
                {
 
                        continue;
 
                }
 
                if(D3DXPlaneDotCoord(&m_Planes[i],&pVertices[4]) >= 0.0f)
 
                {
 
                        continue;
 
                }
 
                if(D3DXPlaneDotCoord(&m_Planes[i],&pVertices[5]) >= 0.0f)
 
                {
 
                        continue;
 
                }
 
                if(D3DXPlaneDotCoord(&m_Planes[i],&pVertices[6]) >= 0.0f)
 
                {
 
                        continue;
 
                }
 
                if(D3DXPlaneDotCoord(&m_Planes[i],&pVertices[7]) >= 0.0f)
 
                {
 
                        continue;
 
                }
 
                return false;
 
        }
 
        return true; */
 
}
//---------------------------------------------------------------
bool Frustrum::CheckPointIn(D3DXVECTOR3 pPoint){
 
        for(int i = 0; i < 6; i++)
 
        {
 
			if((D3DXPlaneDotCoord(m_FrustumPlane[i], &pPoint) < 0.0f))
 
                {
 
                        return false;
 
                }
 
        }
 
        return true;
 
}
//--------------------------------------------------------------- 