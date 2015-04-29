#define NOMINMAX
#include "Node.h"
#include "BoneInfo.h"
#include "Bones.h"
#include "3DAnimation.h"
#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include <algorithm>
using namespace DoMaRe;
Node::Node(std::string name) 
	: Entity3D(0,0,name),
	m_nChilds(0),

	m_nMeshes(0),

	m_vBB(new D3DXVECTOR3[8]),

	m_pBone(NULL),

	m_pCurrentAnim(NULL),

	KeyFrameIndex(-1){

}
//---------------------------------------------------------------
Node::~Node(){

	if (m_vBB) {

		delete m_vBB;

	}

	for(int i = 0; i < m_nChilds;i++) {

		delete m_vChildNodes[i];

	}

	for(int i = 0; i < m_nMeshes;i++) {

		delete m_vMeshes[i];

	}

	if(m_pBone) {

		delete m_pBone;

	}

}
//---------------------------------------------------------------
void Node::AddMesh(Mesh* pMeshAux){

	m_vMeshes.push_back(pMeshAux);

	m_nMeshes++;

}
//---------------------------------------------------------------
void Node::AddChild(Node* child){

	m_vChildNodes.push_back(child);

	m_nChilds++;

}
//---------------------------------------------------------------
void Node::Draw(Renderer * pRenderer){
	D3DXMatrixIdentity(&m_mGlobalTransform);

	pRenderer->setMatrix(World, &m_mGlobalTransform);

	pRenderer->CalculateFrustrum();

	PreDraw(m_mGlobalTransform, pRenderer);

	NodeDraw(pRenderer);
}
//---------------------------------------------------------------
void Node::PreDraw(D3DXMATRIX transformation, Renderer * pRenderer){       

	D3DXMATRIX translation;

	D3DXMATRIX scaling;

	D3DXMATRIX rotx;

	D3DXMATRIX roty;

	D3DXMATRIX rotz;



	D3DXMatrixTranslation(&translation, m_vPos.x,m_vPos.y,m_vPos.z);

	D3DXMatrixScaling(&scaling,m_vScale.x,m_vScale.y,m_vScale.z);

	Vector3 vRotationInRadians = m_vRot *  0.0174532925;



	D3DXMatrixRotationX(&rotx, vRotationInRadians.x);

	D3DXMatrixRotationY(&roty, vRotationInRadians.y);

	D3DXMatrixRotationZ(&rotz,vRotationInRadians.z);

	D3DXMATRIX LocalTransform;

	D3DXMatrixIdentity(&LocalTransform);

	D3DXMatrixMultiply(&LocalTransform , &translation, &LocalTransform);

	D3DXMatrixMultiply(&LocalTransform, &rotx,&LocalTransform);

	D3DXMatrixMultiply(&LocalTransform, &roty, &LocalTransform);

	D3DXMatrixMultiply(&LocalTransform, &rotz, &LocalTransform);

	D3DXMatrixMultiply(&LocalTransform, &scaling, &LocalTransform); 

	if(!IsPlaying()){
		D3DXMatrixMultiply(&LocalTransform, &LocalTransform,&m_mOriginalTransform);
	}
	else{
		D3DXMATRIX frameTransform = m_pCurrentAnim->GetFrameMatrix(KeyFrameIndex);

		D3DXMatrixMultiply(&LocalTransform, &LocalTransform,&frameTransform);
	}

	D3DXMatrixMultiply(&m_mGlobalTransform, &LocalTransform,&transformation);

	if(m_pBone != NULL){

		m_pBone->setTransformation(m_mGlobalTransform);

	}

	if(m_nChilds){

		for(int i = 0; i <m_nChilds; i++){
	
			m_vChildNodes[i]->PreDraw(m_mGlobalTransform,pRenderer);

		}

	}

	CalculateBB();

}
//---------------------------------------------------------------
Node* Node::GetChild(unsigned int index){

	if(index>= m_nChilds){

		return NULL;

	}

	return m_vChildNodes[index];

}
//---------------------------------------------------------------
Node* Node::FindChildByName(std::string sName){

	if(this->m_Name == sName){

		return this;

	}

	Node* hijo = NULL;



	for(int i = 0; i < m_nChilds; i++){

		if (hijo == NULL){

			hijo = m_vChildNodes[i]->FindChildByName(sName);

		}

	}

	return hijo;

}
//--------------------------------------------------------------- 
void Node::NodeDraw(Renderer * pRenderer){       

	drawCalls=0;
	if(m_pBone == NULL) {
		if ( pRenderer->CheckFrustumCulling(m_vBB) ) {
			drawCalls = 1;
			if(m_nMeshes) {
				for (int i = 0; i < m_nMeshes; i++) {
					if (!m_vMeshes[i]->HaveBones()) {
						pRenderer->setMatrix(World, &m_mGlobalTransform);
						m_vMeshes[i]->Draw(pRenderer);
					}
					else {
						m_vMeshes[i]->AnimationMeshDraw(pRenderer);
					}
				}
			}
			if(m_nChilds) {
				for(int i = 0; i < m_nChilds;i++) {
					m_vChildNodes[i]->NodeDraw(pRenderer);
					drawCalls+=m_vChildNodes[i]->drawCalls;
				}
			}
		}
	}
}
//---------------------------------------------------------------
void Node::SetFirstTransform(float a1,float a2,float a3, float a4, float b1, float b2,float b3, float b4, float c1,float c2,float c3,float c4, float d1,float d2, float d3, float d4){

	m_mOriginalTransform._11 = a1;

	m_mOriginalTransform._12 = a2;

	m_mOriginalTransform._13 = a3;

	m_mOriginalTransform._14 = a4;



	m_mOriginalTransform._21 = b1;

	m_mOriginalTransform._22 = b2;

	m_mOriginalTransform._23 = b3;

	m_mOriginalTransform._24 = b4;



	m_mOriginalTransform._31 = c1;

	m_mOriginalTransform._32 = c2;

	m_mOriginalTransform._33 = c3;

	m_mOriginalTransform._34 = c4;



	m_mOriginalTransform._41 = d1;

	m_mOriginalTransform._42 = d2;

	m_mOriginalTransform._43 = d3;

	m_mOriginalTransform._44 = d4;



}
//---------------------------------------------------------------
void Node::PlayAnim(std::string sName){

	if (m_mAnimations.count(sName)) {

		if(m_pCurrentAnim != m_mAnimations[sName]) {

			if (m_pCurrentAnim != NULL) {
				m_pCurrentAnim->Stop();
			}

			SetAnim(sName);

		}

		m_pCurrentAnim->Play();

	}

}
//---------------------------------------------------------------
void Node::CalculateBB() {

	if(m_nMeshes){

		D3DXVECTOR3 vMeshVertices[8];

		m_vMeshes[0]->GetTransformedBox(&m_mGlobalTransform,vMeshVertices);

		v_MaxBound.x = vMeshVertices[0].x;

		v_MaxBound.y = vMeshVertices[0].y;

		v_MaxBound.z = vMeshVertices[0].z;



		v_MinBound.x = vMeshVertices[0].x;

		v_MinBound.y = vMeshVertices[0].y;

		v_MinBound.z = vMeshVertices[0].z;

		for(int i = 1; i<8;i++) {

			if(vMeshVertices[i].x > v_MaxBound.x) 

				v_MaxBound.x = vMeshVertices[i].x;

			else if(vMeshVertices[i].x < v_MinBound.x)

				v_MinBound.x = vMeshVertices[i].x;



			if(vMeshVertices[i].y > v_MaxBound.y) 

				v_MaxBound.y = vMeshVertices[i].y;

			else if(vMeshVertices[i].y < v_MinBound.y)

				v_MinBound.y = vMeshVertices[i].y;



			if(vMeshVertices[i].z > v_MaxBound.z) 

				v_MaxBound.z = vMeshVertices[i].z;

			else if(vMeshVertices[i].z < v_MinBound.z)

				v_MinBound.z = vMeshVertices[i].z;

		}

	}

	else if(m_nChilds) {

		m_vChildNodes[0]->GetBoundings(&v_MinBound,&v_MaxBound);

	}

	for(int i = 0; i < m_nChilds; i++) {

		Vector3 vChildMax; 

		Vector3 vChildMin;

		m_vChildNodes[i]->GetBoundings(&vChildMin,&vChildMax);



		if(vChildMax.x > v_MaxBound.x) {
			v_MaxBound.x = vChildMax.x;
		}

		if(vChildMax.y > v_MaxBound.y) {
			v_MaxBound.y = vChildMax.y;
		}

		if(vChildMax.z > v_MaxBound.z) {
			v_MaxBound.z = vChildMax.z;
		}

		if(vChildMin.x < v_MinBound.x) {
			v_MinBound.x = vChildMin.x;
		}

		if(vChildMin.y < v_MinBound.y) {
			v_MinBound.y = vChildMin.y;
		}

		if(vChildMin.z < v_MinBound.z) {
			v_MinBound.z = vChildMin.z;
		}

	}

	m_vBB[0].x = v_MaxBound.x;

	m_vBB[0].y = v_MaxBound.y;

	m_vBB[0].z = v_MaxBound.z;



	m_vBB[1].x = v_MaxBound.x;

	m_vBB[1].y = v_MinBound.y;

	m_vBB[1].z = v_MaxBound.z;



	m_vBB[2].x = v_MinBound.x;

	m_vBB[2].y = v_MinBound.y;

	m_vBB[2].z = v_MaxBound.z;



	m_vBB[3].x = v_MinBound.x;

	m_vBB[3].y = v_MaxBound.y;

	m_vBB[3].z = v_MaxBound.z;



	m_vBB[4].x = v_MaxBound.x;

	m_vBB[4].y = v_MaxBound.y;

	m_vBB[4].z = v_MinBound.z;



	m_vBB[5].x = v_MaxBound.x;

	m_vBB[5].y = v_MinBound.y;

	m_vBB[5].z = v_MinBound.z;



	m_vBB[6].x = v_MinBound.x;

	m_vBB[6].y = v_MinBound.y;

	m_vBB[6].z = v_MinBound.z;



	m_vBB[7].x = v_MinBound.x;

	m_vBB[7].y = v_MaxBound.y;

	m_vBB[7].z = v_MinBound.z;

}
//---------------------------------------------------------------
void Node::GetBoundings(Vector3* pOutMin, Vector3* pOutMax){

	*pOutMax = v_MaxBound;

	*pOutMin = v_MinBound;

}
//---------------------------------------------------------------
void Node::AddAnim(Animation3D* pAnimation){

	if(!m_mAnimations.count(pAnimation->GetName())) {       
		m_mAnimations[pAnimation->GetName()] = pAnimation;
	}

}
//---------------------------------------------------------------
void Node::Update(const double& dDeltaTime){

	if(m_pCurrentAnim != NULL) {
		m_pCurrentAnim->Update(dDeltaTime);
	}

}
//---------------------------------------------------------------
void Node::SetAnim(std::string sName){

	if (m_mAnimations.count(sName)) {

		Animation3D* pAnimation = m_mAnimations[sName];

		SetAnim(pAnimation);

	}

}
//---------------------------------------------------------------
void Node::SetAnim(Animation3D* pAnimation){

	//le asigna a los hijos, accede al keyframeindex por su nombre

	m_pCurrentAnim = pAnimation;

	KeyFrameIndex = m_pCurrentAnim->GetFrameIndex(m_Name);

	for(int i = 0; i < m_nChilds;i++) {

		m_vChildNodes[i]->SetAnim(pAnimation);

	}

}
//---------------------------------------------------------------
bool Node::IsPlaying(){

	if(m_pCurrentAnim != NULL)

		if(m_pCurrentAnim->GetState() == Animation3D::State::PLAY)

			if(KeyFrameIndex != -1)

				return true;

	return false;

}
//---------------------------------------------------------------
Animation3D* Node::GetAnim(std::string sName){

	if(m_mAnimations.count(sName)) {
		return m_mAnimations[sName];    
	}

	return NULL;

}
//----------------------------------------------------------------