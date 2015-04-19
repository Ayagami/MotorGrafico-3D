#include "Frustrum.h"
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
 
        D3DXMatrixMultiply(&mat, pMatrizVista, pMatrizProy);
 

 
        m_Planes[4].a = mat._13;
 
        m_Planes[4].b = mat._23;
 
        m_Planes[4].c = mat._33;
 
        m_Planes[4].d = mat._43;
 
        m_Planes[0].a = mat._14 + mat._11;
 
        m_Planes[0].b = mat._24 + mat._21;
 
        m_Planes[0].c = mat._34 + mat._31;
 
        m_Planes[0].d = mat._44 + mat._41;
 
        m_Planes[1].a = mat._14 - mat._11;
 
        m_Planes[1].b = mat._24 - mat._21;
 
        m_Planes[1].c = mat._34 - mat._31;
 
        m_Planes[1].d = mat._44 - mat._41;
 
        m_Planes[2].a = mat._14 + mat._12;
 
        m_Planes[2].b = mat._24 + mat._22;
 
        m_Planes[2].c = mat._34 + mat._32;
 
        m_Planes[2].d = mat._44 + mat._42;
 
        m_Planes[3].a = mat._14 - mat._12;
 
        m_Planes[3].b = mat._24 - mat._22;
 
        m_Planes[3].c = mat._34 - mat._32;
 
        m_Planes[3].d = mat._44 - mat._42;
 

 
        m_Planes[5].a = mat._14 - mat._13;
 
        m_Planes[5].b = mat._24 - mat._23;
 
        m_Planes[5].c = mat._34 - mat._33;
 
        m_Planes[5].d = mat._44 - mat._43;
 

 
        for(int i = 0; i < 6;i++)
 
        {
 
                D3DXPlaneNormalize(&m_Planes[i],&m_Planes[i]);
 
        }
 
}
 
//---------------------------------------------------------------
 
bool Frustrum::isIn(D3DXVECTOR3* pVertices)
 
{
 
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
 
        return true;
 
}
//---------------------------------------------------------------
bool Frustrum::CheckPointIn(D3DXVECTOR3 pPoint){
 
        for(int i = 0; i < 6; i++)
 
        {
 
                if((D3DXPlaneDotCoord(&m_Planes[i], &pPoint) < 0.0f))
 
                {
 
                        return false;
 
                }
 
        }
 
        return true;
 
}
//--------------------------------------------------------------- 