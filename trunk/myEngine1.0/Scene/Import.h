#pragma once
#include "../myEngine_API.h"
#include <string>
#include "../TinyXML/tinyxml2.h"
#include "../Renderer/RenderTypes.h"
#include <list>
#include <vector>
#include <map>

// Estructuras de ayuda de Assimp
struct aiNode;
struct aiMesh;
struct aiMaterial;
struct aiScene;
// - Fin Estructuras de Ayuda de Assimp

#pragma comment(lib, "../ext/assimp/lib/assimp.lib") // link with assimp.dll
namespace DoMaRe{
	
	class Scene;
	class Quad;
	class Sprite;
	class Animation;
	class Renderer;
	class Sound;
	class Mesh;
	class Node;

	class MYENGINE_API Import{
		public:
			Import();
			~Import();
			bool Init(Renderer* pkRenderer, Sound* pkSound);
			// 2D
			bool importScene(Scene&, std::string);
			void importSprite(Scene&,tinyxml2::XMLElement*);
			void importQuad(Scene&,tinyxml2::XMLElement*);
			void importAnimation(std::vector<Animation> **animations,tinyxml2::XMLElement*);
			// - 2D

			// 3D
			void importMesh(Mesh&, std::string);
			bool importScene(const std::string& FileName, Node& theNode);
			// - 3D
			Renderer& GetRenderer() const{ return *pk_renderer; }
			Sound&	  GetSound()	const{ return *pk_Sound;	}
			//Renderer *renderer;
		private:

			bool importNode(const aiNode* pkAiNode, const aiScene* pkAiScene, Node& orkNode);
			bool importMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& orkMesh);

			// HELPER EXTRAIDO DE WIKI-DEV
			void quaternionToEulerAngles (float qX, float qY, float qZ, float qW, 
								  float& orfRotX, float& orfRotY, float& orfRotZ);

			Renderer* pk_renderer;
			Sound* pk_Sound;

	};
}
