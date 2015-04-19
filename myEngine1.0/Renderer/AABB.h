#pragma once
#include "../myEngine_API.h"
struct D3DXVECTOR3;
struct D3DXMATRIX;
struct D3DXPLANE;
namespace DoMaRe{
	typedef D3DXMATRIX* Matrix;
	//typedef D3DXVECTOR3* Vector3;
	typedef D3DXPLANE* Plane;

	class AABB{
	public:
		AABB();
		~AABB();

		void setData(float fWidth, float fHeight, float fDepth, float fOffsetX, float fOffsetY, float fOffsetZ);
		const Vector3& offset () const;
		const Vector3* corners() const;

		float width()	const;
		float height()	const;
		float depth()	const;
	private:
		Vector3	m_pkOffset;
		Vector3	m_pkCorners[8];

		float m_fWidth;
		float m_fHeight;
		float m_fDepth;
	};
}