#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RenderTypes.h"
#include "../Physics/Collider.h"
#include "../Physics/Physics.h"
#include "../Renderer/Material.h"
#include "BoneInfo.h"
#include "Bones.h"
using namespace DoMaRe;

int Mesh::debugedMeshes = 0;

Mesh::Mesh(Renderer & p_Renderer) : Entity3D(),  pk_Renderer(p_Renderer) , s_Texture(NoTexture), pk_Material(Material::Default_Material), m_VtxBones(NULL), VectorDraw(NULL), m_NormBones(NULL), VectorNorm(NULL){
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


	for(int i = 0; i < m_vBoneData.size(); i++)
		delete m_vBoneData[i];
	if(VectorDraw)
		delete VectorDraw;
	if(m_VtxBones)
		delete m_VtxBones;
}

void Mesh::setData(const MeshVertex* Tex_Vertex, size_t vertexCount, DoMaRe::Primitive Prim, const unsigned short* pInt, size_t indexCount){
	pkPrimitive = Prim;
	mk_VertexBuffer3D->setVertexData((void *)Tex_Vertex, vertexCount);
	mk_IndexBuffer->setIndexData(pInt,indexCount);

	m_iVertexCount = vertexCount;
	// Guardo Vertex
	m_pkVertex.resize(vertexCount);
	memcpy( &( m_pkVertex.front() ), Tex_Vertex, vertexCount * sizeof(MeshVertex) );


	// Guardo Index
	m_pkIndex.resize(indexCount);
	memcpy( &( m_pkIndex.front() ), pInt, indexCount * sizeof(unsigned short) );

	m_VtxBones = new D3DXVECTOR3[vertexCount];
	VectorDraw = new D3DXVECTOR3[vertexCount];

	m_NormBones = new D3DXVECTOR3[vertexCount];
	VectorNorm  = new D3DXVECTOR3[vertexCount];

	for(int i=0; i < vertexCount; i++){
		m_VtxBones[i].x = Tex_Vertex[i].x;
		m_VtxBones[i].y = Tex_Vertex[i].y;
		m_VtxBones[i].z = Tex_Vertex[i].z;

		m_NormBones[i].x = Tex_Vertex[i].nx;
		m_NormBones[i].y = Tex_Vertex[i].ny;
		m_NormBones[i].z = Tex_Vertex[i].nz;
	}
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
	if(HaveBones()){
		AnimationMeshDraw();
		return;
	}
	mk_VertexBuffer3D->bind();
	mk_IndexBuffer->bind();
	pk_Renderer.setMaterial(pk_Material);
	pk_Renderer.setCurrentTexture(s_Texture);
	//pk_Renderer.setMatrix(World, _TrMatrix );
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

void Mesh::AnimationMeshDraw(){
	ZeroMemory((void*) VectorDraw, sizeof(D3DXVECTOR3) * m_iVertexCount);
	ZeroMemory((void*) VectorDraw, sizeof(D3DXVECTOR3) * m_iVertexCount);

	for(int i=0; i < m_vBoneData.size(); i++){
		std::map<unsigned int, float>::iterator iterator = m_vBoneData[i]->m_mWeight.begin();
		while(iterator != m_vBoneData[i]->m_mWeight.end()){
			D3DXVECTOR3 vectorAux(0,0,0);
			D3DXMATRIX mat = m_vBoneData[i]->m_pBone->getTransformation();
			D3DXMatrixMultiply(&mat, &m_vBoneData[i]->offsetMatrix, &mat);
			D3DXVec3TransformCoord(&vectorAux,&m_VtxBones[iterator->first],&mat);

			VectorDraw[iterator->first] += vectorAux * iterator->second;
			mat._41 = 0;
			mat._42 = 0;
			mat._43 = 0;

			D3DXVec3TransformCoord(&vectorAux, &m_NormBones[iterator->first], &mat);
			VectorDraw[iterator->first] += vectorAux * iterator->second;

			iterator++;
		}
	}

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);

	pk_Renderer.setTransformMatrix(&identity);
	pk_Renderer.setMaterial(pk_Material);
	//if(s_Texture != NULL){
		for(int i=0; i < m_iVertexCount; i++){
			m_pkVertex[i].x = VectorDraw[i].x;
			m_pkVertex[i].y = VectorDraw[i].y;
			m_pkVertex[i].z = VectorDraw[i].z;

			m_pkVertex[i].nx = VectorNorm[i].x;
			m_pkVertex[i].ny = VectorNorm[i].y;
			m_pkVertex[i].nz = VectorNorm[i].z;
		}
	//}
		mk_VertexBuffer3D->bind();
		mk_IndexBuffer->bind();
		pk_Renderer.setCurrentTexture(s_Texture);
		mk_VertexBuffer3D->setVertexData((void *)&m_pkVertex, m_iVertexCount);
		pk_Renderer.Draw(pkPrimitive);
		// Aca tengo que llenar los buffers para dibujar esta data generada.
		
}
