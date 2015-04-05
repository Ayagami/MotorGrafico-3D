#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RenderTypes.h"
#include "../Physics/Collider.h"
#include "../Physics/Physics.h"
#include "../Renderer/Material.h"
using namespace DoMaRe;

int Mesh::debugedMeshes = 0;

Mesh::Mesh(Renderer & p_Renderer): pk_Renderer(p_Renderer) , s_Texture(NoTexture), pk_Material(Material::Default_Material){
	mk_VertexBuffer3D = pk_Renderer.createVB(sizeof(DoMaRe::MeshVertex), DoMaRe::MeshVertexType);
	mk_IndexBuffer = pk_Renderer.createIB();
}

Mesh::~Mesh(){
	
	m_pkVertex.clear();
	m_pkIndex.clear();

	if(mk_VertexBuffer3D){
		delete mk_VertexBuffer3D;
		mk_VertexBuffer3D = NULL;
	}
	if(mk_IndexBuffer){
		delete mk_IndexBuffer;
		mk_IndexBuffer = NULL;
	}
	if(pk_Material){
		delete pk_Material;
		pk_Material = NULL;
	}
}

void Mesh::setData(const MeshVertex* Tex_Vertex, size_t vertexCount, DoMaRe::Primitive Prim, const unsigned short* pInt, size_t indexCount){
	pkPrimitive = Prim;
	mk_VertexBuffer3D->setVertexData((void *)Tex_Vertex, vertexCount);
	mk_IndexBuffer->setIndexData(pInt,indexCount);


	// Guardo Vertex
	m_pkVertex.resize(vertexCount);
	memcpy( &( m_pkVertex.front() ), Tex_Vertex, vertexCount * sizeof(MeshVertex) );


	// Guardo Index
	m_pkIndex.resize(indexCount);
	memcpy( &( m_pkIndex.front() ), pInt, indexCount * sizeof(unsigned short) );

	// Actualizo el collider en mi RigidBody.

	/*DoMaRe::MeshCollider* newCollider = new DoMaRe::MeshCollider();
	newCollider->build(this);
	rigidBody()->setCollider(newCollider);
	rigidBody()->setHavokMotion(DoMaRe::RigidBody::HavokMotion::Dynamic);
	Physics::getInstance()->addEntity(rigidBody());
	
	*/
	//
}

void Mesh::Draw(){
	mk_VertexBuffer3D->bind();
	mk_IndexBuffer->bind();
	pk_Renderer.setMaterial(pk_Material);
	pk_Renderer.setCurrentTexture(s_Texture);
	pk_Renderer.setMatrix(World, _TrMatrix );
	pk_Renderer.Draw(pkPrimitive);

	debugedMeshes ++ ;
}

void Mesh::setTexture(std::string pkTextureFile, DWORD theColor){
	s_Texture = pk_Renderer.loadTexture(pkTextureFile,theColor);
}

void Mesh::setTexture(Texture& theTexture){
	s_Texture = theTexture;
}

const std::vector<MeshVertex>& Mesh::vertexs() const{
	return m_pkVertex;
}

const std::vector<unsigned short> Mesh::indexs() const{
	return m_pkIndex;
}

const Material& Mesh::getMaterial() const{
	return *pk_Material;
}

void Mesh::setMaterial(Material& m_cMaterial) {
	pk_Material = &m_cMaterial;
}