#pragma once
#include "../myEngine_API.h"
#include <d3dx9math.h>
#include <string>
#include <vector>
// Incluyo cosas de assimp para facilitarme la vida!
#include "../../ext/assimp/include/Importer.hpp"
#include "../../ext/assimp/include/types.h"
#include "../../ext/assimp/include/scene.h"
#include "../../ext/assimp/include/postprocess.h"

namespace DoMaRe{
	class MYENGINE_API Animation3D{
		public:
			Animation3D(std::string sName, double duration, double tPS);
			// Enums y structs necesarios para la animacion.
			enum State{
				PLAY,
				STOP,
				PAUSE,
			};
			struct KeyFrame{
				std::string name;
				aiVectorKey* positionKey;
				int iPositionKeys;
				aiVectorKey* scalingKey;
				int iScalingKeys;
				aiQuatKey* rotationKey;
				int iRotationKeys;
			};

			D3DMATRIX GetFrameMatrix(unsigned int index) { return GetInterpolation(m_dCTime, m_vKeyFrames[index]); }
			int		  GetFrameIndex (std::string);
			std::string GetName()						 { return m_sName; }
			State GetState()							 { return m_stState; }
			void AddFrame(KeyFrame* frame)				 { m_vKeyFrames.push_back(frame); }
			void Update(const double&);
			void Stop()									 { m_stState = STOP; m_dDuration = 0;}
			void Play()									 { m_stState = PLAY; }
			void Pause()								 { m_stState = PAUSE;}
			void setSpeed(float speed)					 { m_fSpeed  = speed;}
			float getSpeed()						     { return m_fSpeed; }

		private:
			std::string m_sName;	// Nombre de la animación
			std::vector<KeyFrame*> m_vKeyFrames;
			State m_stState;
			double m_dDuration;
			double m_dTPS;
			double m_dCTime;
			float  m_fSpeed;
			D3DXMATRIX GetInterpolation(double&, KeyFrame*);
			D3DXVECTOR3 CalcInterpVec(double&, aiVectorKey*, int);
			D3DXQUATERNION CalcInterpRot(double&, aiQuatKey*, int); 
	};
}