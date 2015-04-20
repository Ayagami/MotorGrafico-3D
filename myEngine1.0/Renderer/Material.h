#pragma once
#include "../myEngine_API.h"
#include <d3dx9.h>

namespace DoMaRe{
	class Renderer;
	class MYENGINE_API Material{
		friend class Renderer;

		public:

			static Material* Default_Material;

			struct MatRGBA{
				float R, G, B, A;
			};

			Material();
			~Material();

			MatRGBA getDiffuse();
			MatRGBA getAmbient();
			MatRGBA getSpecular();
			MatRGBA getEmissive();

			void setDiffuse(float,float,float,float);
			void setAmbient(float,float,float,float);
			void setSpecular(float,float,float,float);
			void setEmissive(float,float,float,float);

			float getPower();
			void setPower(float);

		private:
			D3DMATERIAL9 m_pkMaterial;
	};
}