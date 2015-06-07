#pragma once
#include "../myEngine_API.h"
#include "Entity3D.h"
#include "../Renderer/RenderTypes.h"
#include "../3DBuffers/pg2_vertexbuffer.h"
#include "../3DBuffers/pg2_indexbuffer.h"
#include <string>
#include <vector>

namespace DoMaRe{
	class BoneInfo;
	class Renderer;
	class Material;
	class MYENGINE_API Mesh : public Entity3D{
	public:
		Mesh(Renderer&);
		~Mesh();
		void setData(MeshVertex*, size_t vertexCount, DoMaRe::Primitive,  unsigned short*, size_t indexCount);
		void setTexture(std::string, DWORD theColor);
		void setTexture(Texture& theTexture);
		void setMaterial(Material& pkMaterial);
		void Draw(Renderer* pRenderer);
		void AnimationMeshDraw(Renderer* pRenderer);
		const VertexBuffer3D* vertexBuffer() const;
		const IndexBuffer*	  indexBuffer() const;

		const Material& getMaterial() const;

		static int debugedMeshes;

		// ANIMATIONS!
		void AddBoneInfo(BoneInfo* m_pBoneInfo) { m_vBoneData.push_back(m_pBoneInfo); }
		bool HaveBones() { return (m_vBoneData.size()); }

		//void GetBounding(Vector3* v_MaxBound, Vector3* v_MinBound);     
		void CalculateBB();
		void GetTransformedBox(D3DXMATRIX * pMatrizMundo, D3DXVECTOR3 * pOut); 
		D3DXPLANE GetPlane(D3DXMATRIX*);

	protected:
		IndexBuffer* mk_IndexBuffer;
		Texture s_Texture;
		VertexBuffer3D* mk_VertexBuffer3D;
		Primitive pkPrimitive;
		Renderer& pk_Renderer;
		Material* pk_Material;

		unsigned short* m_pIndices;
		unsigned int m_uiIndxCount;
		MeshVertex* m_pTexVtx;
		unsigned int m_uiVtxCount;

	private:
		// ------ Anim...
		friend class Node;
		D3DXVECTOR3* m_VtxHuesos;
		D3DXVECTOR3* VectorDraw;

		D3DXVECTOR3* m_pvBB;
		std::vector<BoneInfo*> m_vBoneData;
	};

}