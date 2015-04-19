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
		void setData(const MeshVertex*, size_t vertexCount, DoMaRe::Primitive, const unsigned short*, size_t indexCount);
		void setTexture(std::string, DWORD theColor);
		void setTexture(Texture& theTexture);
		void setMaterial(Material& pkMaterial);
		void Draw(Renderer* pRenderer);
		void AnimationMeshDraw(Renderer* pRenderer);
		const VertexBuffer3D* vertexBuffer() const;
		const IndexBuffer*	  indexBuffer() const;

		const std::vector<MeshVertex>& vertexs() const;
		const std::vector<unsigned short> indexs() const;
		const Material& getMaterial() const;

		static int debugedMeshes;

		// ANIMATIONS!
		void AddBoneInfo(BoneInfo* m_pBoneInfo) { m_vBoneData.push_back(m_pBoneInfo); }
		bool HaveBones() { return (m_vBoneData.size()); }
		
		void GetBounding(Vector3* v_MaxBound, Vector3* v_MinBound);     
        void CalculateBB();
        void GetTransformedBox(D3DXMATRIX * pMatrizMundo, D3DXVECTOR3 * pOut); 

	protected:
		IndexBuffer* mk_IndexBuffer;
		Texture s_Texture;
		VertexBuffer3D* mk_VertexBuffer3D;
		Primitive pkPrimitive;
		Renderer& pk_Renderer;
		Material* pk_Material;

		size_t m_iVertexCount;
		size_t m_iIndexCount;

	private:
		std::vector<MeshVertex> m_pkVertex;
		std::vector<unsigned short> m_pkIndex;
		// ------ Anim...
		friend class Node;
		D3DXVECTOR3* m_VtxBones;
		D3DXVECTOR3* m_NormBones;
		D3DXVECTOR3* VectorDraw;
		D3DXVECTOR3* VectorNorm;
		D3DXVECTOR3* m_pvBB;
		std::vector<BoneInfo*> m_vBoneData;
	};

}