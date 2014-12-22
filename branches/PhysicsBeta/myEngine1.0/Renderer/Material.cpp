#include "Material.h"
#include "Renderer.h"

using namespace DoMaRe;
Material*	Material::Default_Material = NULL;

Material::Material(){
	ZeroMemory(&m_pkMaterial, sizeof(m_pkMaterial));
	m_pkMaterial.Diffuse.r	= 1.0f;
	m_pkMaterial.Diffuse.g	= 1.0f;
	m_pkMaterial.Diffuse.b	= 1.0f;
	m_pkMaterial.Diffuse.a	= 1.0f;
	m_pkMaterial.Power		= 1.0f;
}

Material::~Material(){
	// Nothing to do.
}

Material::MatRGBA Material::getDiffuse(){
	MatRGBA out;

	out.R = m_pkMaterial.Diffuse.r;
	out.G = m_pkMaterial.Diffuse.g;
	out.B = m_pkMaterial.Diffuse.b;
	out.A = m_pkMaterial.Diffuse.a;

	return out;
}

Material::MatRGBA Material::getAmbient(){
	MatRGBA out;

	out.R = m_pkMaterial.Ambient.r;
	out.G = m_pkMaterial.Ambient.g;
	out.B = m_pkMaterial.Ambient.b;
	out.A = m_pkMaterial.Ambient.a;

	return out;
}

Material::MatRGBA Material::getSpecular(){
	MatRGBA out;

	out.R = m_pkMaterial.Specular.r;
	out.G = m_pkMaterial.Specular.g;
	out.B = m_pkMaterial.Specular.b;
	out.A = m_pkMaterial.Specular.a;

	return out;
}

Material::MatRGBA Material::getEmissive(){
	MatRGBA out;

	out.R = m_pkMaterial.Emissive.r;
	out.G = m_pkMaterial.Emissive.g;
	out.B = m_pkMaterial.Emissive.b;
	out.A = m_pkMaterial.Emissive.a;

	return out;
}

void Material::setDiffuse(float r, float g, float b, float a){
	m_pkMaterial.Diffuse.r = r;
	m_pkMaterial.Diffuse.g = g;
	m_pkMaterial.Diffuse.b = b;
	m_pkMaterial.Diffuse.a = a;
}

void Material::setAmbient(float r, float g, float b, float a){
	m_pkMaterial.Ambient.r = r;
	m_pkMaterial.Ambient.g = g;
	m_pkMaterial.Ambient.b = b;
	m_pkMaterial.Ambient.a = a;
}

void Material::setSpecular(float r, float g, float b, float a){
	m_pkMaterial.Specular.r = r;
	m_pkMaterial.Specular.g = g;
	m_pkMaterial.Specular.b = b;
	m_pkMaterial.Specular.a = a;
}

void Material::setEmissive(float r, float g, float b, float a){
	m_pkMaterial.Emissive.r = r;
	m_pkMaterial.Emissive.g = g;
	m_pkMaterial.Emissive.b = b;
	m_pkMaterial.Emissive.a = a;
}

float Material::getPower(){
	return m_pkMaterial.Power;
}

void Material::setPower(float power){
	m_pkMaterial.Power = power;
}