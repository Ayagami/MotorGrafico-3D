#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RenderTypes.h"
using namespace DoMaRe;

Mesh::Mesh(Renderer & p_Renderer): pk_Renderer(p_Renderer) , s_Texture(NoTexture){
	mk_VertexBuffer3D = pk_Renderer.createVB(sizeof(DoMaRe::MeshVertex), DoMaRe::MeshVertexType);
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

void Mesh::setData(const MeshVertex* Tex_Vertex, size_t vertexCount, DoMaRe::Primitive Prim, const unsigned short* pInt, size_t indexCount){
	pkPrimitive = Prim;
	mk_VertexBuffer3D->setVertexData((void *)Tex_Vertex, vertexCount);
	mk_IndexBuffer->setIndexData(pInt,indexCount);
}

void Mesh::Draw(){
	mk_VertexBuffer3D->bind();
	mk_IndexBuffer->bind();
	pk_Renderer.setCurrentTexture(s_Texture);
	pk_Renderer.setMatrix(World, _TrLocalMatrix );
	pk_Renderer.Draw(pkPrimitive);
}

void Mesh::setTexture(std::string pkTextureFile, DWORD theColor){
	s_Texture = pk_Renderer.loadTexture(pkTextureFile,theColor);
}

void Mesh::setTexture(Texture& theTexture){
	s_Texture = theTexture;
}