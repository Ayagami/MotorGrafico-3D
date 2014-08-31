#pragma once
#include "../myEngine_API.h"
#include "Entity3D.h"
#include "../Renderer/RenderTypes.h"
#include "../3DBuffers/pg2_vertexbuffer.h"
#include "../3DBuffers/pg2_indexbuffer.h"

namespace DoMaRe{
	class Renderer;
	class MYENGINE_API Mesh : public Entity3D{
	public:
		Mesh(Renderer&);
		~Mesh();
		void setData(const ColorVertex*, size_t vertexCount, DoMaRe::Primitive, const unsigned short*, size_t indexCount);
		void Draw(Renderer& r) const;
	private:
		IndexBuffer* mk_IndexBuffer;
		VertexBuffer3D* mk_VertexBuffer3D;
		Primitive pkPrimitive;
		Renderer& pk_Renderer;
	};

}