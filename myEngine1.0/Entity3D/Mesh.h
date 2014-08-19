#pragma once
#include "../myEngine_API.h"
#include "Entity3D.h"
#include "../Renderer/RenderTypes.h"
#include "../3DBuffers/pg2_vertexbuffer.h"
#include "../3DBuffers/pg2_indexbuffer.h"

namespace DoMaRe{
	class Renderer;
	class Mesh : public Entity3D{
	public:
		Mesh(Renderer *);
		~Mesh();
		void setData(const TexCoordVertex*, size_t vertexCount, DoMaRe::Primitive, const unsigned int*, size_t indexCount);
	private:

		IndexBuffer* mk_IndexBuffer;
		VertexBuffer3D* mk_VertexBuffer3D;
		DoMaRe::Primitive pkPrimitive;
		Renderer* pk_Renderer;
	};

}