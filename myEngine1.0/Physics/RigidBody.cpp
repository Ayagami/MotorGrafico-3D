#include "RigidBody.h"
#include "../Renderer/EMath.h"
#include "Collider.h"
#include <d3dx9.h>
#include <Common/Base/hkBase.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
using namespace DoMaRe;

hkpMotion::MotionType s_HavokMType [RigidBody::HavokMotionCount] = {
	hkpMotion::MOTION_FIXED,
	hkpMotion::MOTION_DYNAMIC
};

RigidBody::RigidBody() : pk_RigidBody(NULL), m_HMotion(Dynamic), m_pkCollider(NULL){
        hkpBoxShape* pkBox = new hkpBoxShape( hkVector4(1.0f, 1.0f, 1.0f) );

        hkpRigidBodyCinfo RigidBodyInfo;
        RigidBodyInfo.m_shape = pkBox;
        RigidBodyInfo.m_position = hkVector4(0, 0, 0);
        RigidBodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;

        pk_RigidBody = new hkpRigidBody(RigidBodyInfo);
}

RigidBody::~RigidBody(){
	pk_RigidBody->removeReference();
	pk_RigidBody = NULL;

	if(m_pkCollider != NULL){
		delete m_pkCollider;
		m_pkCollider = NULL;
	}
}

void RigidBody::setPosition(float x, float y, float z){
	pk_RigidBody->markForWrite();
	pk_RigidBody->setPosition( hkVector4(-x, y, z) );
	pk_RigidBody->unmarkForWrite();
}

float RigidBody::posX() const{
	    pk_RigidBody->markForRead();
        float posX = -pk_RigidBody->getPosition().getComponent(0);
        pk_RigidBody->unmarkForRead();
        return posX;
}
const Matrix& RigidBody::transform () const{

	hkTransform rbTransformation = pk_RigidBody->getTransform();

	D3DXMATRIX rigidbodyMaterial( rbTransformation(0,0), rbTransformation(1,0), rbTransformation(2,0), rbTransformation(3,0),
								  rbTransformation(0,1), rbTransformation(1,1), rbTransformation(2,1), rbTransformation(3,1),
								  rbTransformation(0,2), rbTransformation(1,2), rbTransformation(2,2), rbTransformation(3,2),
								  rbTransformation(0,3), rbTransformation(1,3), rbTransformation(2,3), rbTransformation(3,3) );

	return &rigidbodyMaterial;
}
float RigidBody::posY() const{
	    pk_RigidBody->markForRead();
        float posY = pk_RigidBody->getPosition().getComponent(1);
        pk_RigidBody->unmarkForRead();
        return posY;
}

float RigidBody::posZ() const{
	    pk_RigidBody->markForRead();
        float posZ = pk_RigidBody->getPosition().getComponent(2);
        pk_RigidBody->unmarkForRead();
        return posZ;
}

void RigidBody::setRotation(float px, float py, float pz){
	    pk_RigidBody->markForWrite();

        float x, y, z, w;
        MATHF::eulerAnglesToQuaternion(px, py, pz, x, y, z, w);
        hkQuaternion kRotation(x, y, z, w);
        pk_RigidBody->setRotation(kRotation);

        pk_RigidBody->unmarkForWrite();
}

float RigidBody::rotationX () const{
        pk_RigidBody->markForRead();

        float rotX, rotY, rotZ;
		MATHF::quaternionToEulerAngles( pk_RigidBody->getRotation()(0),  pk_RigidBody->getRotation()(1),  pk_RigidBody->getRotation()(2),   pk_RigidBody->getRotation()(3),  rotX, rotY, rotZ );

        pk_RigidBody->unmarkForRead();

        return rotX;
}
float RigidBody::rotationY () const{
        pk_RigidBody->markForRead();

        float rotX, rotY, rotZ;
		MATHF::quaternionToEulerAngles( pk_RigidBody->getRotation()(0),  pk_RigidBody->getRotation()(1),  pk_RigidBody->getRotation()(2),  pk_RigidBody->getRotation()(3),  rotX, rotY, rotZ );

        pk_RigidBody->unmarkForRead();

        return rotY;
}
float RigidBody::rotationZ () const{
        pk_RigidBody->markForRead();

        float rotX, rotY, rotZ;
		MATHF::quaternionToEulerAngles( pk_RigidBody->getRotation()(0),   pk_RigidBody->getRotation()(1),   pk_RigidBody->getRotation()(2),   pk_RigidBody->getRotation()(3),   rotX, rotY, rotZ );

        pk_RigidBody->unmarkForRead();

        return rotZ;
}
void RigidBody::setCollider(Collider* pkCollider){

	if(m_pkCollider != NULL){
		pk_RigidBody->markForWrite();

		delete m_pkCollider;
		m_pkCollider = pkCollider;
	
	}else{
	m_pkCollider = pkCollider;
	pk_RigidBody->markForWrite();
	}
	pk_RigidBody->setShape( m_pkCollider->shape() );
	pk_RigidBody->unmarkForWrite();
}

void RigidBody::setHavokMotion(RigidBody::HavokMotion type){
	m_HMotion = type;
	pk_RigidBody->markForWrite();
	pk_RigidBody->setMotionType( s_HavokMType[type] );
	pk_RigidBody->unmarkForWrite();
}