#pragma once
#include "Bones.h"
#include <map>

namespace DoMaRe{
	class MYENGINE_API BoneInfo{
		public:		// Tiene que ser todo publico, ya que es solo una estructura con data!

			D3DXMATRIX offsetMatrix;
			std::map<unsigned int, float> m_mWeight;
			BoneInfo();
			Bone* m_pBone;
			void setOffsetMatrix(float, float, float, float,
								 float, float, float, float,
								 float, float, float, float,
								 float, float, float, float);

			void addWeight(unsigned int index, float weight)  { m_mWeight[index] = weight; }
			void setBone(Bone* pBone)						  { m_pBone = pBone; }
	};
}