#pragma once
#include "../myEngine_API.h"
#include "Entity3D.h"
#include "../Renderer/RenderTypes.h"
#include "../3DBuffers/pg2_vertexbuffer.h"
#include "../3DBuffers/pg2_indexbuffer.h"
#include <string>
#include <vector>

namespace DoMaRe{
	class Renderer;
	class MYENGINE_API Mesh : public Entity3D{
	public:
		Mesh(Renderer&);
		~Mesh();
		void setData(const MeshVertex*, size_t vertexCount, DoMaRe::Primitive, const unsigned short*, size_t indexCount);
		void setTexture(std::string, DWORD theColor);
		void setTexture(Texture& theTexture);
		void Draw();

		const VertexBuffer3D* vertexBuffer() const;
		const IndexBuffer*	  indexBuffer() const;

		const std::vector<MeshVertex>& vertexs() const;
		const std::vector<unsigned short> indexs() const;

	protected:
		IndexBuffer* mk_IndexBuffer;
		Texture s_Texture;
		VertexBuffer3D* mk_VertexBuffer3D;
		Primitive pkPrimitive;
		Renderer& pk_Renderer;

	private:
		std::vector<MeshVertex>& m_pkVertex;
		std::vector<unsigned short> m_pkIndex;
	};

}