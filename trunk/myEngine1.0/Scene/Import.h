#pragma once
#include "../myEngine_API.h"
#include <string>
#include "../TinyXML/tinyxml2.h"
#include <list>
#include <vector>

#pragma comment(lib, "../ext/assimp/lib/assimp.lib") // link with irrKlang.dll
namespace DoMaRe{
	
	class Scene;
	class Quad;
	class Sprite;
	class Animation;
	class Renderer;
	class Sound;
	class Mesh;
	class MYENGINE_API Import{
		public:
			Import();
			bool Init(Renderer* pkRenderer, Sound* pkSound);
			bool importScene(Scene&, std::string);
			void importSprite(Scene&,tinyxml2::XMLElement*);
			void importQuad(Scene&,tinyxml2::XMLElement*);
			void importAnimation(std::vector<Animation> **animations,tinyxml2::XMLElement*);
			void importMesh(Mesh&, std::string);
			Renderer& GetRenderer() const{ return *pk_renderer; }
			Sound&	  GetSound()	const{ return *pk_Sound;	   }
			//Renderer *renderer;
		private:
			Renderer* pk_renderer;
			Sound* pk_Sound;
	};
}
