#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RenderTypes.h"
using namespace DoMaRe;

Mesh::Mesh(Renderer & p_Renderer): pk_Renderer(p_Renderer){
	mk_VertexBuffer3D = pk_Renderer.createVB(sizeof(DoMaRe::ColorVertex), DoMaRe::ColorVertexType);
	mk_IndexBuffer = pk_Renderer.createIB();
}

Mesh::~Mesh(){
	if(mk_VertexBuffer3D){
		delete mk_VertexBuffer3D;
		mk_VertexBuffer3D = NULL;
	}
	if(mk_IndexBuffer){
		delete mk_IndexBuffer;
		mk_IndexBuffer = NULL;
	}
}

void Mesh::setData(const ColorVertex* Tex_Vertex, size_t vertexCount, DoMaRe::Primitive Prim, const unsigned short* pInt, size_t indexCount){
	pkPrimitive = Prim;
	mk_VertexBuffer3D->setVertexData((void *)Tex_Vertex, vertexCount);
	mk_IndexBuffer->setIndexData(pInt,indexCount);
}

void Mesh::Draw(Renderer& pkR) const{
	mk_VertexBuffer3D->bind();
	mk_IndexBuffer->bind();
	pk_Renderer.setCurrentTexture(NoTexture);
	pk_Renderer.setMatrix(World, _TrMatrix );
	pk_Renderer.Draw(pkPrimitive,mk_IndexBuffer->indexCount() / 3);
}
