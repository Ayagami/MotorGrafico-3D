#include "Import.h"
#include "Scene.h"
#include "../Entity2D/Quad.h"
#include "../Entity2D/Sprite.h"
#include "../Entity2D/Animation.h"
#include "../Entity2D/Entity2D.h"
#include "../Renderer/Renderer.h"
#include "../Sound/Sound.h"
#include "../Entity3D/Mesh.h"
//----- Assimp
#include "../../ext/assimp/include/Importer.hpp"
#include "../../ext/assimp/include/scene.h"
#include "../../ext/assimp/include/postprocess.h"
#include "../Renderer/RenderTypes.h"

using namespace DoMaRe;

Import::Import(){
	//*pk_renderer = *pkRenderer;
}
Import::~Import(){
	
	// Destruyo MAP de Meshes.
	for( std::map<std::string, MeshVertex*>::iterator it = m_pkMeshesVertexMap.begin(); it != m_pkMeshesVertexMap.end(); ){ // Vertex
		MeshVertex* pkMesh = it->second;
		m_pkMeshesVertexMap.erase(it++);
		delete pkMesh;
		pkMesh = NULL;
	}

	for( std::map<std::string, unsigned short*>::iterator it = m_pkMeshesIndexMap.begin(); it != m_pkMeshesIndexMap.end(); ){ // Index
		unsigned short* pkMesh = it->second;
		m_pkMeshesIndexMap.erase(it++);
		delete pkMesh;
		pkMesh = NULL;
	}
	// Fin MAP de Meshes
}
bool Import::Init(Renderer* pkRenderer, Sound* pkSound){
	pk_renderer = pkRenderer;
	pk_Sound	= pkSound;
	return true;
}
bool Import::importScene(Scene &scene, std::string fileName)
{
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	if(xmlDoc.Error())
		return false;
	tinyxml2::XMLElement *root = xmlDoc.FirstChildElement("SCENE");
	importQuad(scene,root);
	importSprite(scene,root);
	return true;
}
void Import::importSprite(Scene &scene,tinyxml2::XMLElement* root)
{
	tinyxml2::XMLElement *sprite = root->FirstChildElement("SPRITE");
	tinyxml2::XMLElement *instance = root->FirstChildElement("INSTANCE");

	while(sprite!= NULL)
	{	
		std::string nameSprite = sprite->Attribute("name");
		std::string texturePath = sprite->Attribute("texture");
		int r = sprite->IntAttribute("r");
		int g = sprite->IntAttribute("g");
		int b = sprite->IntAttribute("b");

		DoMaRe::Texture texture = pk_renderer->loadTexture(texturePath,DoMaRe_COLOR_RGB(r,g,b));

		//CREAR LISTA ANIM
		std::vector<Animation> *list_animations = new std::vector<Animation>();

		importAnimation(&list_animations,sprite->FirstChildElement("ANIMATION"));

		instance = root->FirstChildElement("INSTANCE");
		while(instance != NULL)
		{
			//CREAR SPRITE 
			Sprite*  ent_sprite = new Sprite();

			if(instance->Attribute("sprite") == nameSprite)
			{
				std::string name = instance->Attribute("name");
				float posX = instance->FloatAttribute("posX");
				float posY = instance->FloatAttribute("posY");
				float posZ = instance->FloatAttribute("posZ");
				float rotation = instance->FloatAttribute("rotation");
				float scaleX = instance->FloatAttribute("scaleX");
				float scaleY = instance->FloatAttribute("scaleY");
				
				//GRABAMOS SPRITE			
				ent_sprite->setPos(posX,posY,posZ);
				ent_sprite->setName(name);
				ent_sprite->setRotation(rotation);
				ent_sprite->setScale(scaleX,scaleY);
				ent_sprite->setTexture(texture);

			}
			//CARGO ANIMACIONES
			ent_sprite->AddAnimation(*list_animations);

			//PUSH_BACK A LISTA ENTITY2D
			scene.addEntity(ent_sprite);

			instance = instance->NextSiblingElement("INSTANCE");
		}
		sprite = sprite->NextSiblingElement("SPRITE");
	}

}
void Import::importQuad(Scene &scene,tinyxml2::XMLElement* root)
{
	tinyxml2::XMLElement *quad = root->FirstChildElement("QUAD");

	while(quad != NULL)
	{
		//CREO QUAD
		Quad  * ent_quad = new Quad();

		std::string name = quad->Attribute("name");
		float posX = quad->FloatAttribute("posX");
		float posY = quad->FloatAttribute("posY");
		float posZ = quad->FloatAttribute("posZ");
		float rotation = quad->FloatAttribute("rotation");
		float scaleX = quad->FloatAttribute("scaleX");
		float scaleY = quad->FloatAttribute("scaleY");
		int r = quad->IntAttribute("r");
		int g = quad->IntAttribute("g");
		int b = quad->IntAttribute("b");

		ent_quad->setName(name);
		ent_quad->setPos(posX,posY,posZ);
		ent_quad->setRotation(rotation);
		ent_quad->setScale(scaleX,scaleY);
		ent_quad->setColor(DoMaRe_COLOR_RGB(r,g,b));

		//PUSH_BACK A LISTA ENTITY2D
		scene.addEntity(ent_quad);

		quad = quad->NextSiblingElement("QUAD");
	}

}
void Import::importAnimation(std::vector<Animation> ** list_animations,tinyxml2::XMLElement* animations)
{
	while(animations != NULL)
	{
		//CREATE ANIMATION AUX
		Animation *anim = new Animation();

		std::string name = animations->Attribute("name");
		float lenght = animations->FloatAttribute("lenght");
		float t_width = animations->FloatAttribute("width");
		float t_height = animations->FloatAttribute("height");

		anim->setName(name);
		anim->setLength(lenght);

		tinyxml2::XMLElement *frame = animations->FirstChildElement("FRAME");
		while(frame != NULL)
		{
			
			float posX = frame->FloatAttribute("posX");
			float posY = frame->FloatAttribute("posY");
			float width = frame->FloatAttribute("width");
			float height = frame->FloatAttribute("height");

			//ADDFRAME (t_width, t_height, posX, posY, width, height);
			anim->addFrame(t_width, t_height, posX, posY, width, height);

			frame = frame->NextSiblingElement("FRAME");
		}
		// PUSH_BACK ANIMATION
		(*list_animations)->push_back(*anim);

		animations = animations->NextSiblingElement("ANIMATION");
	}
}
void Import::importMesh(Mesh& theMesh, std::string FileName){

	if(m_pkMeshesVertexMap[FileName] != NULL){
		theMesh.setData(m_pkMeshesVertexMap[FileName],m_pkMeshesNVertexMap[FileName],DoMaRe::Primitive::TriangleList,m_pkMeshesIndexMap[FileName],m_pkMeshesNIndexMap[FileName]);
		return;
	}

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( FileName, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	if(!scene) return;
	int nIndices;
	unsigned short *pIndices;
	
	if(scene->mMeshes[0]){
		aiMesh * pAIMesh = scene->mMeshes[0];
		if(pAIMesh->HasFaces()){ // Genero Faces.
			aiFace* pAIFaces;
			pAIFaces = pAIMesh->mFaces;
			nIndices = pAIMesh->mNumFaces *3;
			pIndices = new unsigned short[nIndices];
			for(DWORD i=0; i < pAIMesh->mNumFaces; i++){
				if(pAIFaces[i].mNumIndices != 3){
					delete[] pIndices;
					return;
				}
				for(DWORD j=0; j < 3; j ++){
					pIndices[i * 3 + j ] = pAIFaces[i].mIndices[j];
				}
			}
		}// Termino Faces.
		if(pAIMesh->HasPositions()){
			int nVertices;
			MeshVertex * pVertices;
			nVertices = pAIMesh->mNumVertices;
			pVertices = new MeshVertex[nVertices];

			for(DWORD i=0; i < nVertices; i++){
				pVertices[i].x = pAIMesh->mVertices[i].x;
				pVertices[i].y = pAIMesh->mVertices[i].y;
				pVertices[i].z = pAIMesh->mVertices[i].z;
			}

			if(pAIMesh->HasNormals()){
				for(DWORD i=0; i < nVertices; i++){
					pVertices[i].nx = pAIMesh->mNormals[i].x;
					pVertices[i].ny = pAIMesh->mNormals[i].y;
					pVertices[i].nz = pAIMesh->mNormals[i].z;
				}
			}

			if(pAIMesh->HasTextureCoords(0)){
				for(DWORD i=0; i < nVertices; i++){
					pVertices[i].u = pAIMesh->mTextureCoords[0][i].x;
					pVertices[i].v = pAIMesh->mTextureCoords[0][i].y;
				}
			}
			
			m_pkMeshesVertexMap[FileName] = pVertices;
			m_pkMeshesNVertexMap[FileName] = nVertices;
			m_pkMeshesIndexMap[FileName] = pIndices;
			m_pkMeshesNIndexMap[FileName] = nIndices;

			theMesh.setData(pVertices,nVertices,DoMaRe::Primitive::TriangleList,pIndices,nIndices);
		}
	}
	return;
}