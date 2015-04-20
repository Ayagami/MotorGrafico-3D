#pragma once
//---------------------------------------------------------------
#include "../myEngine_API.h"
#include <d3dx9.h> 
#include "../Entity3D/Vector3.h"
#include "EMath.h"
//---------------------------------------------------------------
namespace DoMaRe{
	typedef D3DXPLANE* Plane;
	class Node;
	class MYENGINE_API Frustrum{
	public:
			static enum {OUTSIDE, INTERSECT, INSIDE};
			Frustrum();
			~Frustrum();
			void Calculate(D3DXMATRIX * pMatrizVista,D3DXMATRIX * pMatrizProy);
			int isIn(Node& pkNode);
			bool CheckPointIn(D3DXVECTOR3 pPoint);
	private:
			Plane m_FrustumPlane[6];
	};
}
//---------------------------------------------------------------
