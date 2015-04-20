#pragma once
#include "../myEngine_API.h"
#include <d3dx9.h>

namespace DoMaRe{
	class Renderer;
	class MYENGINE_API Light{
	friend class Renderer;
	public:
		enum LightType{
			POINT_LIGHT =		1,
			SPOT_LIGHT =		2,
			DIRECTIONAL_LIGHT = 3
		};

		struct LightRGBA{
			float R, G, B, A;
		};

		struct PKVector3{
			float X, Y, Z;
		};

		Light(Renderer*);
		~Light();

		LightRGBA getDiffuse();
		LightRGBA getAmbient();
		LightRGBA getSpecular();

		void setDiffuse(float, float, float, float);
		void setAmbient(float, float, float, float);
		void setSpecular(float, float, float, float);

		PKVector3 getPosition();
		void setPosition(float, float, float);
		
		PKVector3 getDirection();
		void setDirection(float, float, float);

		float getRange();
		void setRange(float);

		float getFalloff();
		void setFalloff(float);

		float getTheta();
		void setTheta(float);

		float getPi();
		void setPi(float);

		LightType getLightType();
		void setLightType(LightType);

		unsigned long getLightIndex();
		void setLightIndex(unsigned long);

		bool isEnabled();
		void enable(bool);

		float getAttenuation0();
		void setAttenuation0(float fAttenuation0);
		float getAttenuation1();
		void setAttenuation1(float fAttenuation1);
		float getAttenuation2();
		void setAttenuation2(float fAttenuation2);
	private:

		unsigned long m_ulLightIndex;
		bool m_bEnabled;
		Renderer* m_pkRenderer;

		D3DLIGHT9 m_pkLight;
	};

}