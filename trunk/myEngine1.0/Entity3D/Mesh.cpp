#include "Mesh.h"
#include "../Renderer/Renderer.h"
using namespace DoMaRe;

Mesh::Mesh(Renderer * p_Renderer) : pk_Renderer(p_Renderer){
//	pk_Renderer->createVB(mk_VertexBuffer3D,
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

void Mesh::setData(const TexCoordVertex* Tex_Vertex, size_t vertexCount, DoMaRe::Primitive Prim, const unsigned int* pInt, size_t indexCount){
	pkPrimitive = Prim;

	/*if(!mk_VertexBuffer3D)
		pk_Renderer->createVB(mk_VertexBuffer3D, indexCount, pInt);
	if(!mk_IndexBuffer)
		pk_Renderer->createIB(mk_IndexBuffer);*/

	mk_VertexBuffer3D->setVertexData((void *)Tex_Vertex, vertexCount);
	//mk_IndexBuffer->setIndexData(
	//mk_IndexBuffer->setIndexData(,indexCount);
}
