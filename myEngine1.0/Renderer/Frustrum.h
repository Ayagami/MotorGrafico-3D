#pragma once
//---------------------------------------------------------------
#include "../myEngine_API.h"
#include <d3dx9.h> 
#include "../Entity3D/Vector3.h"
//---------------------------------------------------------------
namespace DoMaRe{
	class MYENGINE_API Frustrum{
	public:
			Frustrum();
			~Frustrum();
			void Calculate(D3DXMATRIX * pMatrizVista,D3DXMATRIX * pMatrizProy);
			bool isIn(D3DXVECTOR3* pVertices);
			bool CheckPointIn(D3DXVECTOR3 pPoint);
	private:
			D3DXPLANE m_Planes[6];
	};
}
//---------------------------------------------------------------
