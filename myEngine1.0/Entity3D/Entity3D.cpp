#include "Entity3D.h"
#include "../Renderer/Renderer.h"
#include <sstream>
#include <string>
using namespace DoMaRe;
//---------------------------------------------------------------
Entity3D::Entity3D(float posX, float posY, std::string name):
m_vPos(posX,posY,0),
m_vScale(1,1,1),
m_vRot(0,0,0),
m_bVisible(true),
m_Name(name),
m_sCollisionGroupName(""),
m_bCollisionEnabled(false){
 
}
//---------------------------------------------------------------
Entity3D::Entity3D():
m_vPos(0,0,0),
m_vScale(1,1,1),
m_vRot(0,0,0),
m_bVisible(true),
m_Name("default"), 
m_sCollisionGroupName(""),
m_bCollisionEnabled(false){
 
}
//---------------------------------------------------------------
void Entity3D::SetPos(const Vector3& vPosition){
        m_vPos = vPosition;
}
//---------------------------------------------------------------
void Entity3D::SetPos(const float &x,const float &y, const float &z){
        m_vPos.x = x;
 
        m_vPos.y = y;
 
        m_vPos.z = z;
 
}
//---------------------------------------------------------------
void Entity3D::SetPos(const float &x,const float &y){
 
        m_vPos.x = x;
 
        m_vPos.y = y;
 
}
//---------------------------------------------------------------
void Entity3D::SetScale(const float &x,const float &y){
 
        m_vScale.x = x;
 
        m_vScale.y = y;
 
}
//--------------------------------------------------------------------------------
void Entity3D::SetScale(const float &x,const float &y, const float&z){
 
        m_vScale.x = x;
 
        m_vScale.y = y;
 
        m_vScale.z = z;
 
} 
//---------------------------------------------------------------
void Entity3D::SetScale(const Vector3& vScaling){
 
        m_vScale = vScaling;
 
}
//--------------------------------------------------------------- 
void Entity3D::SetScaleX(const float &x){
 
        m_vScale.x = x;
 
}
//---------------------------------------------------------------
void Entity3D::SetScaleY(const float &y){
 
        m_vScale.y = y;
 
}
//--------------------------------------------------------------- 
void Entity3D::Rotate(const Vector3& vRotation){
 
        m_vRot = vRotation;
 
}
//---------------------------------------------------------------
void Entity3D::Rotate(const float &degree){
 
        m_vRot.z = degree;
 
}
//--------------------------------------------------------------- 
void Entity3D::Draw(Renderer * pRenderer){
 
		/*
        pRenderer->SetMode(WORLD);
 
        pRenderer->LoadIdentity();
 
        pRenderer->Translate(m_vPos.x , m_vPos.y,  m_vPos.z);
 

 
        Vector3 vRotationInRadians = m_vRot *  0.0175;
 

 
        pRenderer->RotateX(vRotationInRadians.x);
 
        pRenderer->RotateY(vRotationInRadians.y);
 
        pRenderer->RotateZ(vRotationInRadians.z);
 

 
        if (m_bVisible)
 
        {
 
                pRenderer->Scale(m_vScale.x , m_vScale.y, m_vScale.z);
 
        }
 
        else
 
        {
 
                pRenderer->Scale(0,0,0);
 
        }
		*/
}
//---------------------------------------------------------------
std::string Entity3D::GetName(){
        return m_Name;
}
//---------------------------------------------------------------
std::string Entity3D::GetCollisionGroup(){
 
        return m_sCollisionGroupName;
 
}
//--------------------------------------------------------------- 
void Entity3D::SetCollisionGroup(std::string sGroup){
 
        m_sCollisionGroupName = sGroup;
 
}
//--------------------------------------------------------------- 
void Entity3D::FlipH(bool bFlip){
 
        if (bFlip)
 
        {
 
                m_vRot.y = 180;
 
        }
 
        else
 
        {
 
                m_vRot.y = 0;
 
        }
 
}
//--------------------------------------------------------------- 
void Entity3D::FlipV(bool bFlip){
 
        if (bFlip)
 
        {
 
                m_vRot.x = 180;
 
        }
 
        else
 
        {
 
                m_vRot.x = 0;
 
        }
 
} 
//---------------------------------------------------------------
float Entity3D::GetRotationX(){
 
        return m_vRot.x;
 
}
//---------------------------------------------------------------
float Entity3D::GetRotationY(){
 
        return m_vRot.y;
 
}
//---------------------------------------------------------------
float Entity3D::GetRotationZ(){
 
        return m_vRot.z;
 
}
//---------------------------------------------------------------
void Entity3D::Update(const double& dDeltaTime){
 
        OnUpdate(dDeltaTime);
 
}
//---------------------------------------------------------------
void Entity3D::OnUpdate(const double& dDeltaTime){
 
} 
//---------------------------------------------------------------
void Entity3D::OnCollide(Entity3D* pkEntity, float px, float py){
 
}
//--------------------------------------------------------------- 
std::string Entity3D::GiveName(){
 
        return "";
 
}
//--------------------------------------------------------------- 
