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

RigidBody::RigidBody() :	m_pTransformation (new D3DXMATRIX()), m_pkRigidBody(NULL), m_HMotion(Dynamic), m_pkCollider(NULL){
        hkpBoxShape* pkBox = new hkpBoxShape( hkVector4(1.0f, 1.0f, 1.0f) );

        hkpRigidBodyCinfo kRigidBodyInfo;
        kRigidBodyInfo.m_shape = pkBox;
        kRigidBodyInfo.m_position = hkVector4(0, 0, 0);
        kRigidBodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;

        m_pkRigidBody = new hkpRigidBody(kRigidBodyInfo);
}

RigidBody::~RigidBody(){
	m_pkRigidBody->removeReference();
	m_pkRigidBody = NULL;

	delete m_pTransformation;
	m_pTransformation = NULL;

	if(m_pkCollider != NULL){
		delete m_pkCollider;
		m_pkCollider = NULL;
	}
}

void RigidBody::setPosition(float x, float y, float z){
	m_pkRigidBody->markForWrite();
	m_pkRigidBody->setPosition( hkVector4(-x, y, z) );
	m_pkRigidBody->unmarkForWrite();
}

float RigidBody::posX() const{
	    m_pkRigidBody->markForRead();
        float fResult = -m_pkRigidBody->getPosition().getComponent(0);
        m_pkRigidBody->unmarkForRead();
        return fResult;
}
const Matrix& RigidBody::transform () const{

	hkTransform rbTransformation = m_pkRigidBody->getTransform();

	D3DXMATRIX physMat( rbTransformation(0,0), rbTransformation(1,0), rbTransformation(2,0), rbTransformation(3,0),
                        rbTransformation(0,1), rbTransformation(1,1), rbTransformation(2,1), rbTransformation(3,1),
                        rbTransformation(0,2), rbTransformation(1,2), rbTransformation(2,2), rbTransformation(3,2),
                        rbTransformation(0,3), rbTransformation(1,3), rbTransformation(2,3), rbTransformation(3,3) );

	return &physMat;
}
float RigidBody::posY() const{
	    m_pkRigidBody->markForRead();
        float fResult = m_pkRigidBody->getPosition().getComponent(1);
        m_pkRigidBody->unmarkForRead();
        return fResult;
}

float RigidBody::posZ() const{
	    m_pkRigidBody->markForRead();
        float fResult = m_pkRigidBody->getPosition().getComponent(2);
        m_pkRigidBody->unmarkForRead();
        return fResult;
}

void RigidBody::setRotation(float px, float py, float pz){
	    m_pkRigidBody->markForWrite();

        float x, y, z, w;
        MATHF::eulerAnglesToQuaternion(px, py, pz, x, y, z, w);
        hkQuaternion kRotation(x, y, z, w);
        m_pkRigidBody->setRotation(kRotation);

        m_pkRigidBody->unmarkForWrite();
}

float RigidBody::rotationX () const{
        m_pkRigidBody->markForRead();

        float fRotX, fRotY, fRotZ;
		MATHF::quaternionToEulerAngles( m_pkRigidBody->getRotation()(0), 
                                        m_pkRigidBody->getRotation()(1), 
                                        m_pkRigidBody->getRotation()(2), 
                                        m_pkRigidBody->getRotation()(3), 
                                        fRotX, fRotY, fRotZ );

        m_pkRigidBody->unmarkForRead();

        return fRotX;
}
float RigidBody::rotationY () const{
        m_pkRigidBody->markForRead();

        float fRotX, fRotY, fRotZ;
		MATHF::quaternionToEulerAngles( m_pkRigidBody->getRotation()(0), 
                                        m_pkRigidBody->getRotation()(1), 
                                        m_pkRigidBody->getRotation()(2), 
                                        m_pkRigidBody->getRotation()(3), 
                                        fRotX, fRotY, fRotZ );

        m_pkRigidBody->unmarkForRead();

        return fRotY;
}
float RigidBody::rotationZ () const{
        m_pkRigidBody->markForRead();

        float fRotX, fRotY, fRotZ;
		MATHF::quaternionToEulerAngles( m_pkRigidBody->getRotation()(0), 
                                        m_pkRigidBody->getRotation()(1), 
                                        m_pkRigidBody->getRotation()(2), 
                                        m_pkRigidBody->getRotation()(3), 
                                        fRotX, fRotY, fRotZ );

        m_pkRigidBody->unmarkForRead();

        return fRotZ;
}
void RigidBody::setCollider(Collider* pkCollider){

	if(m_pkCollider != NULL){
		m_pkRigidBody->markForWrite();

		delete m_pkCollider;
		m_pkCollider = pkCollider;
	
	}else{
	m_pkCollider = pkCollider;
	m_pkRigidBody->markForWrite();
	}
	m_pkRigidBody->setShape( m_pkCollider->shape() );
	m_pkRigidBody->unmarkForWrite();
}

void RigidBody::setHavokMotion(RigidBody::HavokMotion type){
	m_HMotion = type;
	m_pkRigidBody->markForWrite();
	m_pkRigidBody->setMotionType( s_HavokMType[type] );
	m_pkRigidBody->unmarkForWrite();
}