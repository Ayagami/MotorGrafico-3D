	#include "3DAnimation.h"
#include <assert.h>
using namespace DoMaRe;

Animation3D::Animation3D(std::string pName, double duration, double tPS)
:m_sName(pName), m_dDuration(duration), m_dTPS(tPS), m_dCTime(0), m_stState(PLAY), m_fSpeed(1.0f){
	if(tPS <= 0)
		m_dTPS = 1500;
}

int Animation3D::GetFrameIndex(std::string sNodeName){
	for(int i=0; i < m_vKeyFrames.size(); i++){
		if(m_vKeyFrames[i]->name == sNodeName)
			return i;
	}

	return -1;	// Devuelvo -1 por que no encontré nada.
}

D3DXMATRIX Animation3D::GetInterpolation(double& cTime, KeyFrame* frame){
	D3DXMATRIX returnMatrix;
	D3DXMatrixIdentity(&returnMatrix);
	
	D3DXVECTOR3 pos = CalcInterpVec(cTime, frame->positionKey, frame->iPositionKeys);
	D3DXVECTOR3 scale = CalcInterpVec(cTime, frame->scalingKey, frame->iScalingKeys);
	D3DXQUATERNION rot = CalcInterpRot(cTime, frame->rotationKey, frame->iRotationKeys);

	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, pos.x, pos.y, pos.z);

	D3DXMATRIX scalation;
	D3DXMatrixScaling(&scalation, scale.x, scale.y, scale.z);

	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, &rot);

	D3DXMatrixMultiply(&returnMatrix, &translation, &returnMatrix);
	D3DXMatrixMultiply(&returnMatrix, &rotation, &returnMatrix);
	D3DXMatrixMultiply(&returnMatrix, &scalation, &returnMatrix);

	return returnMatrix;
}

D3DXVECTOR3 Animation3D::CalcInterpVec(double& cTime, aiVectorKey* keys, int cKeys){
	D3DXVECTOR3 finalVector;

	int fIndexAux = -1;
	int lIndexAux = -1;
	float dAux;

	for(int i=0; i < cKeys; i++){
		if(keys[i].mTime == cTime)
			return D3DXVECTOR3(keys[i].mValue.x, keys[i].mValue.y, keys[i].mValue.z);

		if(cTime < keys[i].mTime){
			fIndexAux = i-1;
			lIndexAux = i;
			break;
		}
	}

	dAux = (cTime -  keys[fIndexAux].mTime) / ( keys[lIndexAux].mTime - keys[fIndexAux].mTime );
	assert(dAux >= 0.0f && dAux <= 1.0f);
	D3DXVECTOR3 vec1(keys[fIndexAux].mValue.x, keys[fIndexAux].mValue.y, keys[fIndexAux].mValue.z);
	D3DXVECTOR3 vec2(keys[lIndexAux].mValue.x, keys[lIndexAux].mValue.y, keys[lIndexAux].mValue.z);

	finalVector = vec2 * dAux + vec1 * (1.0f - dAux);
	return finalVector;
}

D3DXQUATERNION Animation3D::CalcInterpRot(double& cTime, aiQuatKey* keys, int cKeys){
	int fIndexAux = -1;
	int lIndexAux = -1;
	float dAux;

	for(int i=0; i < cKeys; i++){
		if(keys[i].mTime == cTime)
			return D3DXQUATERNION(keys[i].mValue.x, keys[i].mValue.y, keys[i].mValue.z, keys[i].mValue.w);

		if(cTime < keys[i].mTime){
			fIndexAux = i-1;
			lIndexAux = i;
			break;
		}
	}

	dAux = (cTime -  keys[fIndexAux].mTime) / ( keys[lIndexAux].mTime - keys[fIndexAux].mTime );
	assert(dAux >= 0.0f && dAux <= 1.0f);
	const aiQuaternion& startRot = keys[fIndexAux].mValue;
	const aiQuaternion& endRot   = keys[lIndexAux].mValue;
	aiQuaternion rotation;
	aiQuaternion::Interpolate(rotation, startRot, endRot, dAux);
	return D3DXQUATERNION (rotation.x, rotation.y, rotation.z, rotation.w);
}

void Animation3D::Update(const double& deltaTime){
	if(m_stState == PLAY){
		m_dCTime += (deltaTime/1000) * m_dTPS;
		while(m_dCTime >= m_dDuration)
			m_dCTime -= m_dDuration;
	}
}
