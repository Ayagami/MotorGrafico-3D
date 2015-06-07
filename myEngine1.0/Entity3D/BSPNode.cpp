#include "BSPNode.h"
#include "../Renderer/Renderer.h"
#include "Node.h"
using namespace DoMaRe;

//-----------------------------------------------------
BSPNode::BSPNode(D3DXPLANE plane, D3DXVECTOR3 point){
	m_dPlane = plane;
	m_dPoint = point;
	frontBSP = NULL;
	backBSP  = NULL;
}
//-----------------------------------------------------
BSPNode::~BSPNode(){
	if (frontBSP)
		delete frontBSP;
	if (backBSP)
		delete backBSP;
}
//-----------------------------------------------------
BSPNode::BSPposition BSPNode::getPosition(D3DXVECTOR3 BoundingBox[]){
	BSPposition aux = getPosition(BoundingBox[0]);
	for (int i = 1; i < 8; i++){
		if (aux != getPosition(BoundingBox[i]))
			return INSIDE;
	}
	aux;
}
//-----------------------------------------------------
BSPNode::BSPposition BSPNode::getPosition(D3DXVECTOR3 Position){
	float distance = D3DXPlaneDotCoord(&m_dPlane, &Position);
	if (distance > 0){
		return FRONT;
	}
	else if (distance == 0){
		return INSIDE;
	}
	else{
		return BACK;
	}
}
//-----------------------------------------------------
void BSPNode::AddChild(Node* node){
	if (node == NULL) return;

	BSPposition pos = getPosition(node->m_vBB);
	
	if (pos == BACK){

		if (backBSP == NULL)
			backNodes.push_back(node);
		else
			backBSP->AddChild(node);

	}

	else if (pos == FRONT){

		if (frontBSP == NULL)
			frontNodes.push_back(node);
		else
			frontBSP->AddChild(node);

	}

	else if (pos == INSIDE){

		if (frontBSP == NULL)
			frontNodes.push_back(node);
		else
			frontBSP->AddChild(node);

		if (backBSP == NULL)
			backNodes.push_back(node);
		else
			backBSP->AddChild(node);

	}

}
//-----------------------------------------------------
void BSPNode::AddNode(BSPNode* node){
	if (node == NULL) return; // Go away Bitch!
	BSPposition pos = getPosition(node->m_dPoint);	// Obtengo el Nodo con respecto a su punto.
	if (pos == BACK){
		if (backBSP == NULL)
			backBSP = node;
		else
			backBSP->AddNode(node);
	}
	else{
		if (frontBSP == NULL)
			frontBSP = node;
		else
			frontBSP->AddNode(node);
	}
}
//-----------------------------------------------------
void BSPNode::Draw(Renderer* renderer, D3DXVECTOR3 vCameraPos){
	BSPposition pos = getPosition(vCameraPos);
	if (pos == BACK){
		if (backBSP == NULL){
			for (int i = 0; i < backNodes.size(); i++) {
				backNodes[i]->DrawMeshes(renderer);
			}
		}
		else
			backBSP->Draw(renderer, vCameraPos);
	}
	else if (pos == FRONT){
		if (frontBSP == NULL){
			for (int i = 0; i < frontNodes.size(); i++){
				frontNodes[i]->DrawMeshes(renderer);
			}
		}
		else
			frontBSP->Draw(renderer, vCameraPos);
	}
}
//-----------------------------------------------------
