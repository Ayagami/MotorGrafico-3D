#include "Light.h"
#include "Renderer.h"

using namespace DoMaRe;

Light::Light(Renderer * pkRenderer) : m_bEnabled(true), m_ulLightIndex(0), m_pkRenderer(pkRenderer){
	ZeroMemory(&m_pkLight, sizeof(m_pkLight));

	m_pkLight.Type = D3DLIGHT_DIRECTIONAL;
	m_pkLight.Diffuse.r		= 1.0f;
	m_pkLight.Diffuse.g		= 1.0f;
	m_pkLight.Diffuse.b		= 1.0f;
	m_pkLight.Direction.z	= 1.0f;
}

Light::~Light(){

}

void Light::setLightIndex(unsigned long lIndex){
	m_ulLightIndex = lIndex;
	m_pkRenderer->setLight(&m_pkLight, lIndex);
}

void Light::enable(bool bLightEnabled){
	m_bEnabled = bLightEnabled;
	m_pkRenderer->enableLight(bLightEnabled, m_ulLightIndex);
}

DoMaRe::Light::LightRGBA Light::getDiffuse(){
	LightRGBA pkRGBA;
	pkRGBA.R = m_pkLight.Diffuse.r;
	pkRGBA.G = m_pkLight.Diffuse.g;
	pkRGBA.B = m_pkLight.Diffuse.b;
	pkRGBA.A = m_pkLight.Diffuse.a;

	return pkRGBA;
}

DoMaRe::Light::LightRGBA Light::getAmbient(){
	LightRGBA pkRGBA;
	pkRGBA.R = m_pkLight.Ambient.r;
	pkRGBA.G = m_pkLight.Ambient.g;
	pkRGBA.B = m_pkLight.Ambient.b;
	pkRGBA.A = m_pkLight.Ambient.a;

	return pkRGBA;
}

DoMaRe::Light::LightRGBA Light::getSpecular(){
	LightRGBA pkRGBA;
	pkRGBA.R = m_pkLight.Specular.r;
	pkRGBA.G = m_pkLight.Specular.g;
	pkRGBA.B = m_pkLight.Specular.b;
	pkRGBA.A = m_pkLight.Specular.a;

	return pkRGBA;
}

void Light::setDiffuse(float fR, float fG, float fB, float fA){
	m_pkLight.Diffuse.r = fR;
	m_pkLight.Diffuse.g = fG;
	m_pkLight.Diffuse.b = fB;
	m_pkLight.Diffuse.a = fA;
}

void Light::setAmbient(float fR, float fG, float fB, float fA){
	m_pkLight.Ambient.r = fR;
	m_pkLight.Ambient.g = fG;
	m_pkLight.Ambient.b = fB;
	m_pkLight.Ambient.a = fA;
}

void Light::setSpecular(float fR, float fG, float fB, float fA){
	m_pkLight.Specular.r = fR;
	m_pkLight.Specular.g = fG;
	m_pkLight.Specular.b = fB;
	m_pkLight.Specular.a = fA;
}

float Light::getRange(){
	return m_pkLight.Range;
}

void Light::setRange(float pkRange){
	m_pkLight.Range = pkRange;
}
float Light::getFalloff(){
	return m_pkLight.Falloff;
}

void Light::setFalloff(float fFalloff){
	m_pkLight.Falloff = fFalloff;
}

float Light::getAttenuation0(){
	return m_pkLight.Attenuation0;
}

void Light::setAttenuation0(float fAttenuation0){
	m_pkLight.Attenuation0 = fAttenuation0;
}

float Light::getAttenuation1(){
	return m_pkLight.Attenuation1;
}

void Light::setAttenuation1(float fAttenuation1){
	m_pkLight.Attenuation1 = fAttenuation1;
}

float Light::getAttenuation2(){
	return m_pkLight.Attenuation2;
}

void Light::setAttenuation2(float fAttenuation2){
	m_pkLight.Attenuation2 = fAttenuation2;
}

float Light::getTheta(){
	return m_pkLight.Theta;
}

void Light::setTheta(float fTheta){
	m_pkLight.Theta = fTheta;
}

float Light::getPi(){
	return m_pkLight.Phi;
}

void Light::setPi(float fPhi){
	m_pkLight.Phi = fPhi;
}

Light::PKVector3 Light::getPosition(){
	PKVector3 Vector;
	
	Vector.X =  m_pkLight.Position.x;
	Vector.Y = m_pkLight.Position.y;
	Vector.Z = m_pkLight.Position.z;

	return Vector;
}

void Light::setPosition(float fX, float fY, float fZ){
	m_pkLight.Position.x = fX;
	m_pkLight.Position.y = fY;
	m_pkLight.Position.z = fZ;
}

Light::PKVector3 Light::getDirection(){
	PKVector3 Vector;

	Vector.X = m_pkLight.Direction.x;
	Vector.Y = m_pkLight.Direction.y;
	Vector.Z = m_pkLight.Direction.z;
	return Vector;
}

void Light::setDirection(float fX, float fY, float fZ){
	m_pkLight.Direction.x = fX;
	m_pkLight.Direction.y = fY;
	m_pkLight.Direction.z = fZ;
}

Light::LightType Light::getLightType(){
	switch (m_pkLight.Type)
	{
	case D3DLIGHT_POINT:
		return POINT_LIGHT;
	case D3DLIGHT_SPOT:
		return SPOT_LIGHT;
	case D3DLIGHT_DIRECTIONAL:
		return DIRECTIONAL_LIGHT;
	}

	return DIRECTIONAL_LIGHT;
}

void Light::setLightType(LightType eLightType){
	switch (eLightType)
	{
	case POINT_LIGHT:
		m_pkLight.Type = D3DLIGHT_POINT;
	case SPOT_LIGHT:
		m_pkLight.Type = D3DLIGHT_SPOT;
	case DIRECTIONAL_LIGHT:
		m_pkLight.Type = D3DLIGHT_DIRECTIONAL;
	}
}

unsigned long Light::getLightIndex(){
	return m_ulLightIndex;
}

bool Light::isEnabled(){
	return m_bEnabled;
}