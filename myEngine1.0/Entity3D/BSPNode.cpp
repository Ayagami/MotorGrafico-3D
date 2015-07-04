#include "BSPNode.h"
#include "../Renderer/Renderer.h"
#include "Node.h"
using namespace DoMaRe;

void BSPNode::AddNode(BSPNode* pNode){
	if (pNode == NULL) return;

	BSPNode::Position pos = GetPosition(pNode->m_PlanePoint);

	if (pos == BACK) {
		if (m_pBackNode == NULL) {
			m_pBackNode = pNode;
		}
		else {
			m_pBackNode->AddNode(pNode);
		}
	}
	else {
		if (m_pFrontNode == NULL) {
			m_pFrontNode = pNode;
		}
		else {
			m_pFrontNode->AddNode(pNode);
		}
	}
}
//----------------------------------------------------------------------
void BSPNode::AddChild(Node* node){
	if (node == NULL) return;

	BSPNode::Position pos = GetPosition(node->m_vBB);

	if (pos == BACK){
		if (m_pBackNode == NULL) {
			m_vBackObjects.push_back(node);
		}
		else {
			m_pBackNode->AddChild(node);
		}
	}
	else if (pos == FRONT) {
		if (m_pFrontNode == NULL) {
			m_vFrontObjects.push_back(node);
		}
		else {
			m_pFrontNode->AddChild(node);
		}
	}
	else if (pos == INSIDE) {
		if (m_pFrontNode == NULL) {
			m_vFrontObjects.push_back(node);
		}
		else {
			m_pFrontNode->AddChild(node);
		}
		if (m_pBackNode == NULL) {
			m_vBackObjects.push_back(node);
		}
		else {
			m_pBackNode->AddChild(node);
		}
	}
}
//---------------------------------------------------------------------------------------
void BSPNode::Draw(Renderer* pRenderer, D3DXVECTOR3 vCameraPos)
{
	BSPNode::Position pos = GetPosition(vCameraPos);
	std::cout << pos << std::endl;
	if (pos == BACK) {
		if (m_pBackNode == NULL) {
			for (int i = 0; i < m_vBackObjects.size(); i++) {
				m_vBackObjects[i]->DrawMeshes(pRenderer);
			}
		}
		else {
			m_pBackNode->Draw(pRenderer, vCameraPos);
		}
	}
	else if (pos == FRONT) {
		if (m_pFrontNode == NULL) {
			for (int i = 0; i < m_vFrontObjects.size(); i++) {
				m_vFrontObjects[i]->DrawMeshes(pRenderer);
			}
		}
		else {
			m_pFrontNode->Draw(pRenderer, vCameraPos);
		}
	}
}
//---------------------------------------------------------------------------------------
BSPNode::Position BSPNode::GetPosition(D3DXVECTOR3 pos) {
	float distance = D3DXPlaneDotCoord(&m_Plane, &pos);
	if (distance > 0) {
		return FRONT;
	}
	else if (distance == 0) {
		return INSIDE;
	}
	else {
		return BACK;
	}
}
//---------------------------------------------------------------------------------------
BSPNode::Position BSPNode::GetPosition(D3DXVECTOR3 BoundingBox[]){
	Position aux;
	aux = GetPosition(BoundingBox[0]); 
	for (int i = 1; i < 8; i++) {
		// 2 points en posiciones distintas... Inside!
		if (aux != GetPosition(BoundingBox[i])) {
			return INSIDE;
		}
	}
	return aux;
}
//----------------------------------------------------------------------
BSPNode::BSPNode(D3DXPLANE plane, D3DXVECTOR3 point) {
	m_Plane = plane;
	m_PlanePoint = point;
	m_pBackNode = NULL;
	m_pFrontNode = NULL;
}
//----------------------------------------------------------------------
BSPNode::~BSPNode() {
	if (m_pFrontNode) {
		delete m_pFrontNode;
	}
	if (m_pBackNode) {
		delete m_pBackNode;
	}
}