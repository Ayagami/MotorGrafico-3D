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
	for (int i = 0; i < 8; i++){
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
void BSPNode::addChild(Node* node){
		
}
//-----------------------------------------------------
void BSPNode::addBSPNode(BSPNode* node){

}
//-----------------------------------------------------
void BSPNode::Draw(Renderer*, D3DXVECTOR3){

}
//-----------------------------------------------------
