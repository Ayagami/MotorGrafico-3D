#pragma once
#include "../myEngine_API.h"
#include <d3dx9math.h>
#include <string>
#include <vector>

namespace DoMaRe{
	class MYENGINE_API Bone{
		public:
			Bone()										{ D3DXMatrixIdentity(&m_Matrix); }
			D3DXMATRIX getTransformation()				{ return m_Matrix; }
			void	   setTransformation(D3DXMATRIX tr) { m_Matrix = tr; }	
		private:
			D3DXMATRIX m_Matrix;
	};
}