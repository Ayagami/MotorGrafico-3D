// ----- Collider Class.
#include "Collider.h"
// ----- Mesh Class
#include "../Entity3D/Mesh.h"
// ----- External Librarys
#include "../3DBuffers/pg2_indexbuffer.h"
#include "../3DBuffers/pg2_vertexbuffer.h"
// ----- HAVOK
#include <Common/Base/hkBase.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Base/Types/Geometry/hkStridedVertices.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
//------
using namespace DoMaRe;

//------------------------------------------------------------- COLLIDER
Collider::Collider() : pk_RigidBody(NULL){
}
Collider::~Collider(){
	pk_RigidBody->removeReference();		// DELETE RIGIDBODY!
	pk_RigidBody = NULL;
}
void Collider::setPosition(float x,float y,float z){
	pk_RigidBody->setPosition( hkVector4(x,y,z) );
}
//------------------------------------------------------------- BoxCollider
BoxCollider::BoxCollider()	:	Collider(),	m_pkBox(NULL){
	// FALTA HACER LA BOX!
}
BoxCollider::~BoxCollider(){

}
void BoxCollider::build(const Mesh* pkMesh){
	// DO CALCULATIONS!
}
hkpShape* BoxCollider::shape(){
	return m_pkBox;
}
//------------------------------------------------------------ MeshCollider
MeshCollider::MeshCollider() :	Collider(),	m_pkMeshCollider(NULL){

}

void MeshCollider::build(const Mesh* pkMesh){
	size_t iCount = pkMesh->indexs().size();
	hkArray<hkVector4> aVertexs(iCount);
	for(unsigned int i=0; i < iCount; i++){
		aVertexs[i].set( -pkMesh->vertexs()[pkMesh->indexs()[i]].x,
						  pkMesh->vertexs()[pkMesh->indexs()[i]].y, 
						  pkMesh->vertexs()[pkMesh->indexs()[i]].z);
	}

	hkStridedVertices StridedVertices(aVertexs);
	m_pkMeshCollider = new hkpConvexVerticesShape(StridedVertices);

	hkpRigidBodyCinfo	rbInfo;
	rbInfo.m_shape = m_pkMeshCollider;
	rbInfo.m_position = hkVector4(0.0f,0.0f,0.0f);
	rbInfo.m_motionType = hkpMotion::MOTION_FIXED;

	pk_RigidBody = new hkpRigidBody(rbInfo);
	m_pkMeshCollider->removeReference();
}
hkpShape* MeshCollider::shape(){
	return m_pkMeshCollider;
}