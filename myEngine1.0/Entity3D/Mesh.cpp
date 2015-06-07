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
Mesh::Mesh(Renderer & p_Renderer) : Entity3D(), pk_Renderer(p_Renderer), s_Texture(NoTexture), pk_Material(Material::Default_Material), m_pvBB(new D3DXVECTOR3[8]), m_VtxHuesos(NULL), VectorDraw(NULL), m_pIndices(NULL), m_pTexVtx(NULL){
	mk_VertexBuffer3D = pk_Renderer.createVB(sizeof(DoMaRe::MeshVertex), DoMaRe::MeshVertexType);
	mk_IndexBuffer = pk_Renderer.createIB();
}
//---------------------------------------------------------------
Mesh::~Mesh(){

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
	if(m_pvBB)
		delete m_pvBB;

	if (m_pTexVtx)
		delete m_pTexVtx;
	if (m_pIndices)
		delete m_pIndices;
	if (m_VtxHuesos)
		delete m_VtxHuesos;
	if (VectorDraw)
		delete VectorDraw;

}
//---------------------------------------------------------------
D3DXPLANE Mesh::GetPlane(D3DXMATRIX * transform){
	D3DXVECTOR3 planepoints[3];
	for (int i = 0; i < 3; i++){
		D3DXVECTOR3 pos(m_pTexVtx[i].x, m_pTexVtx[i].y, m_pTexVtx[i].z);
		D3DXVec3TransformCoord(&planepoints[i], &pos, transform);
	}
	D3DXPLANE plane;
	D3DXPlaneFromPoints(&plane, &planepoints[0], &planepoints[1], &planepoints[2]);
	return plane;
}
//---------------------------------------------------------------
void Mesh::setData(MeshVertex* Tex_Vertex, size_t vertexCount, DoMaRe::Primitive Prim, unsigned short* pInt, size_t indexCount){
	pkPrimitive = Prim;
	mk_VertexBuffer3D->setVertexData((void *)Tex_Vertex, vertexCount);
	mk_IndexBuffer->setIndexData(pInt,indexCount);

	m_pIndices = pInt;
	m_pTexVtx = Tex_Vertex;

	m_uiIndxCount = indexCount;
	m_uiVtxCount = vertexCount;

	m_VtxHuesos = new D3DXVECTOR3[m_uiVtxCount];
	VectorDraw = new D3DXVECTOR3[m_uiVtxCount];
	for (int i = 0; i < m_uiVtxCount; i++){
		m_VtxHuesos[i].x = m_pTexVtx[i].x;
		m_VtxHuesos[i].y = m_pTexVtx[i].y;
		m_VtxHuesos[i].z = m_pTexVtx[i].z;
	}

	CalculateBB();
}
//---------------------------------------------------------------
void Mesh::Draw(Renderer* pRenderer){
	mk_VertexBuffer3D->bind();
	mk_IndexBuffer->bind();
	pk_Renderer.setMaterial(pk_Material);
	pk_Renderer.setCurrentTexture(s_Texture);
	pk_Renderer.Draw(pkPrimitive);

	debugedMeshes++;
}
//---------------------------------------------------------------
void Mesh::setTexture(std::string pkTextureFile, DWORD theColor){
	s_Texture = pk_Renderer.loadTexture(pkTextureFile,theColor);
}
//---------------------------------------------------------------
void Mesh::setTexture(Texture& theTexture){
	s_Texture = theTexture;
}
//---------------------------------------------------------------
const Material& Mesh::getMaterial() const{
	return *pk_Material;
}
//---------------------------------------------------------------
void Mesh::setMaterial(Material& m_cMaterial) {
	pk_Material = &m_cMaterial;
}
//---------------------------------------------------------------
void Mesh::GetTransformedBox(D3DXMATRIX * pMatrizMundo, D3DXVECTOR3* pOut){
	for(int i = 0; i < 8;i++){
		D3DXVec3TransformCoord(&pOut[i],&m_pvBB[i],pMatrizMundo);
	}
} 
//---------------------------------------------------------------
void Mesh::CalculateBB(){
	Vector3 v_MaxBound;
	Vector3 v_MinBound;

	v_MaxBound.x = m_pTexVtx[0].x;
	v_MaxBound.y = m_pTexVtx[0].y;
	v_MaxBound.z = m_pTexVtx[0].z;

	v_MinBound.x = m_pTexVtx[0].x;
	v_MinBound.y = m_pTexVtx[0].y;
	v_MinBound.z = m_pTexVtx[0].z;

	for (int i = 1; i < m_uiVtxCount; i++){
		if(m_pTexVtx[i].x > v_MaxBound.x) 
			v_MaxBound.x = m_pTexVtx[i].x;
		else if(m_pTexVtx[i].x < v_MinBound.x)
			v_MinBound.x = m_pTexVtx[i].x;

		if(m_pTexVtx[i].y > v_MaxBound.y) 
			v_MaxBound.y = m_pTexVtx[i].y;
		else if(m_pTexVtx[i].y < v_MinBound.y)
			v_MinBound.y = m_pTexVtx[i].y;

		if(m_pTexVtx[i].z > v_MaxBound.z) 
			v_MaxBound.z = m_pTexVtx[i].z;
		else if(m_pTexVtx[i].z < v_MinBound.z)
			v_MinBound.z = m_pTexVtx[i].z;
	}
	m_pvBB[0].x = v_MaxBound.x;
	m_pvBB[0].y = v_MaxBound.y;
	m_pvBB[0].z = v_MaxBound.z;

	m_pvBB[1].x = v_MaxBound.x;
	m_pvBB[1].y = v_MinBound.y;
	m_pvBB[1].z = v_MaxBound.z;

	m_pvBB[2].x = v_MinBound.x;
	m_pvBB[2].y = v_MinBound.y;
	m_pvBB[2].z = v_MaxBound.z;

	m_pvBB[3].x = v_MinBound.x;
	m_pvBB[3].y = v_MaxBound.y;
	m_pvBB[3].z = v_MaxBound.z;

	m_pvBB[4].x = v_MaxBound.x;
	m_pvBB[4].y = v_MaxBound.y;
	m_pvBB[4].z = v_MinBound.z;

	m_pvBB[5].x = v_MaxBound.x;
	m_pvBB[5].y = v_MinBound.y;
	m_pvBB[5].z = v_MinBound.z;

	m_pvBB[6].x = v_MinBound.x;
	m_pvBB[6].y = v_MinBound.y;
	m_pvBB[6].z = v_MinBound.z;

	m_pvBB[7].x = v_MinBound.x;
	m_pvBB[7].y = v_MaxBound.y;
	m_pvBB[7].z = v_MinBound.z;
}
//---------------------------------------------------------------
void Mesh::AnimationMeshDraw(Renderer* pRenderer){
	ZeroMemory((void*)VectorDraw, sizeof(D3DXVECTOR3) * m_uiVtxCount);
	for (int i = 0; i < m_vBoneData.size(); i++){
		std::map<unsigned int, float>::iterator iterator = m_vBoneData[i]->m_mWeight.begin();
		while (iterator != m_vBoneData[i]->m_mWeight.end())
		{
			D3DXVECTOR3 vectorAux(0, 0, 0);
			D3DXMATRIX mat = m_vBoneData[i]->m_pBone->getTransformation();
			D3DXMatrixMultiply(&mat, &m_vBoneData[i]->offsetMatrix, &mat);
			D3DXVec3TransformCoord(&vectorAux, &m_VtxHuesos[iterator->first], &mat);
			VectorDraw[iterator->first] += vectorAux *iterator->second;
			iterator++;
		}
	}
	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	pRenderer->setMatrix(World, &identity);
	pRenderer->setMaterial(pk_Material);
		for (int i = 0; i < m_uiVtxCount; i++){
			m_pTexVtx[i].x = VectorDraw[i].x;
			m_pTexVtx[i].y = VectorDraw[i].y;
			m_pTexVtx[i].z = VectorDraw[i].z;
		}
	pRenderer->setCurrentTexture(s_Texture);
	mk_VertexBuffer3D->setVertexData((void *)m_pTexVtx, m_uiVtxCount);
	mk_VertexBuffer3D->bind();
	mk_IndexBuffer->bind();
	pRenderer->Draw(pkPrimitive);
}
//---------------------------------------------------------------