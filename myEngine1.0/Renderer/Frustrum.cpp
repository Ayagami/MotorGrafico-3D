#include "Frustrum.h"
#include "../Entity3D/Node.h"
using namespace DoMaRe;
//---------------------------------------------------------------
Frustrum::Frustrum(){
}
//---------------------------------------------------------------
Frustrum::~Frustrum(){
}
//---------------------------------------------------------------
void Frustrum::Calculate(D3DXMATRIX * pMatrizVista,D3DXMATRIX * pMatrizProy){
	D3DXMATRIX mat;
	// Combino las matrices
	D3DXMatrixMultiply(&mat, pMatrizVista, pMatrizProy);
	// Extraigo plano left
	m_Planes[0].a = mat._14 + mat._11;
	m_Planes[0].b = mat._24 + mat._21;
	m_Planes[0].c = mat._34 + mat._31;
	m_Planes[0].d = mat._44 + mat._41;

	// Extraigo plano right
	m_Planes[1].a = mat._14 - mat._11;
	m_Planes[1].b = mat._24 - mat._21;
	m_Planes[1].c = mat._34 - mat._31;
	m_Planes[1].d = mat._44 - mat._41;

	// Extraigo plano bottom
	m_Planes[2].a = mat._14 + mat._12;
	m_Planes[2].b = mat._24 + mat._22;
	m_Planes[2].c = mat._34 + mat._32;
	m_Planes[2].d = mat._44 + mat._42;

	// Extraigo plano top
	m_Planes[3].a = mat._14 - mat._12;
	m_Planes[3].b = mat._24 - mat._22;
	m_Planes[3].c = mat._34 - mat._32;
	m_Planes[3].d = mat._44 - mat._42;

	// Extraigo plano near
	m_Planes[4].a = mat._13;
	m_Planes[4].b = mat._23;
	m_Planes[4].c = mat._33;
	m_Planes[4].d = mat._43;

	// Extraigo plano far
	m_Planes[5].a = mat._14 - mat._13;
	m_Planes[5].b = mat._24 - mat._23;
	m_Planes[5].c = mat._34 - mat._33;
	m_Planes[5].d = mat._44 - mat._43;

	// normalize planes
	for (unsigned int i=0; i<6; i++){
		D3DXPlaneNormalize(&m_Planes[i], &m_Planes[i]);
	}
}
//---------------------------------------------------------------
bool Frustrum::isIn(D3DXVECTOR3* pVertices){
	for (int i = 0; i < 6; i++){
		if (D3DXPlaneDotCoord(&m_Planes[i], &pVertices[0]) >= 0.0f){
			continue;
		}
		if (D3DXPlaneDotCoord(&m_Planes[i], &pVertices[1]) >= 0.0f){
			continue;
		}
		if (D3DXPlaneDotCoord(&m_Planes[i], &pVertices[2]) >= 0.0f){
			continue;
		}
		if (D3DXPlaneDotCoord(&m_Planes[i], &pVertices[3]) >= 0.0f){
			continue;
		}
		if (D3DXPlaneDotCoord(&m_Planes[i], &pVertices[4]) >= 0.0f){
			continue;
		}
		if (D3DXPlaneDotCoord(&m_Planes[i], &pVertices[5]) >= 0.0f){
			continue;
		}
		if (D3DXPlaneDotCoord(&m_Planes[i], &pVertices[6]) >= 0.0f){
			continue;
		}
		if (D3DXPlaneDotCoord(&m_Planes[i], &pVertices[7]) >= 0.0f){
			continue;
		}
		return false;
	}
	return true;
}
//---------------------------------------------------------------