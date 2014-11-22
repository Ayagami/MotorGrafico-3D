#define NOMINMAX
#include "Import.h"
#include "Scene.h"
#include "../Entity2D/Quad.h"
#include "../Entity2D/Sprite.h"
#include "../Entity2D/Animation.h"
#include "../Entity2D/Entity2D.h"
#include "../Renderer/Renderer.h"
#include "../Sound/Sound.h"

#include "../Entity3D/Mesh.h"
#include "../Entity3D/Node.h"
#include "../Entity3D/Entity3D.h"

//----- Assimp
#include "../../ext/assimp/include/Importer.hpp"
#include "../../ext/assimp/include/scene.h"
#include "../../ext/assimp/include/postprocess.h"
#include "../Renderer/RenderTypes.h"

#include <limits>
#include <cstddef>
#include <iostream>

using namespace DoMaRe;

Import* Import::Instance = NULL;
Import::Import(){
	//*pk_renderer = *pkRenderer;
}
Import::~Import(){
	// Fin MAP de Meshes
}

Import* Import::getInstance(){
	if(Instance == NULL){
		Instance = new Import();
	}

	return Instance;
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
			
			theMesh.setData(pVertices,nVertices,DoMaRe::Primitive::TriangleList,pIndices,nIndices);
			theMesh.setName(pAIMesh->mName.C_Str());
			delete pVertices;
			delete pIndices;
		}
	}
	return;
}
bool Import::importScene (const std::string& rkFilename, Node& orkSceneRoot){

	Assimp::Importer kImporter;
	const aiScene* pkAiScene = kImporter.ReadFile(rkFilename, aiProcess_Triangulate | aiProcess_SortByPType);
	importNode(pkAiScene->mRootNode, pkAiScene, orkSceneRoot);
	
	return true;
}
bool Import::importNode (const aiNode* pkAiNode, const aiScene* pkAiScene, Node& orkNode){
	// import transformation
	aiVector3t<float> v3AiScaling;
	aiQuaterniont<float> qAiRotation;
	aiVector3t<float> v3AiPosition;

	pkAiNode->mTransformation.Decompose(v3AiScaling, qAiRotation, v3AiPosition);

	orkNode.setPos(v3AiPosition.x, v3AiPosition.y, v3AiPosition.z); // Seteo POS
	orkNode.setScale(v3AiScaling.x, v3AiScaling.y, v3AiScaling.z); // Seteo Scale
	float fRotX, fRotY, fRotZ;
	MATHF::quaternionToEulerAngles(qAiRotation.x, qAiRotation.y, qAiRotation.z, qAiRotation.w, fRotX, fRotY, fRotZ); // Uso QuaternionToEuler :)
	
	orkNode.setRotation(fRotX, fRotY, fRotZ); // Seteo Rotation

	
	/*
	//INTENTO crear AABB.
	float fMaxX = std::numeric_limits<float>::lowest();
	float fMaxY = std::numeric_limits<float>::lowest();
	float fMaxZ = std::numeric_limits<float>::lowest();

	float fMinX = std::numeric_limits<float>::max();
	float fMinY = std::numeric_limits<float>::max();
	float fMinZ = std::numeric_limits<float>::max();
	
	*/
	// Importo Child Nodes

	for(unsigned int i=0; i<pkAiNode->mNumChildren; i++){
		Node* pkNode = new Node();
		orkNode.addChild(pkNode);

		pkNode->setParent(&orkNode);

		importNode(pkAiNode->mChildren[i], pkAiScene, *pkNode);

		/*

		//Ajusto AABB ?
		float fAabbMaxX = pkNode->posX() + ( pkNode->aabb().offset()->x + ( pkNode->aabb().width() / 2 ) );
		float fAabbMaxY = pkNode->posY() + ( pkNode->aabb().offset()->y + ( pkNode->aabb().height() / 2 ) );
		float fAabbMaxZ = pkNode->posZ() + ( pkNode->aabb().offset()->z + ( pkNode->aabb().depth() / 2 ) );

		float fAabbMinX = pkNode->posX() + ( pkNode->aabb().offset()->x - ( pkNode->aabb().width() / 2 ) );
		float fAabbMinY = pkNode->posY() + ( pkNode->aabb().offset()->y - ( pkNode->aabb().height() / 2 ) );
		float fAabbMinZ = pkNode->posZ() + ( pkNode->aabb().offset()->z - ( pkNode->aabb().depth() / 2 ) );

		if(fMaxX < fAabbMaxX) fMaxX = fAabbMaxX;
		if(fMaxY < fAabbMaxY) fMaxY = fAabbMaxY;
		if(fMaxZ < fAabbMaxZ) fMaxZ = fAabbMaxZ;

		if(fMinX > fAabbMinX) fMinX = fAabbMinX;
		if(fMinY > fAabbMinY) fMinY = fAabbMinY;
		if(fMinZ > fAabbMinZ) fMinZ = fAabbMinZ;

		*/
	}

	// Importo Child Meshes

	for(unsigned int i=0; i<pkAiNode->mNumMeshes; i++){
		Mesh* pkMesh = new Mesh(this->GetRenderer());
		orkNode.addChild(pkMesh);

		pkMesh->setParent(&orkNode);

		aiMesh* pkAiMesh = pkAiScene->mMeshes[ pkAiNode->mMeshes[i] ];
		aiMaterial* pkAiMaterial = pkAiScene->mMaterials[pkAiMesh->mMaterialIndex];
		importMesh(pkAiMesh, pkAiMaterial, *pkMesh);
/*
		//	Actualizo nuevamente los AABB (Pero para meshes!)
		float fAabbMaxX = pkMesh->posX() + ( pkMesh->aabb().offset()->x + ( pkMesh->aabb().width() / 2 ) );
		float fAabbMaxY = pkMesh->posY() + ( pkMesh->aabb().offset()->y + ( pkMesh->aabb().height() / 2 ) );
		float fAabbMaxZ = pkMesh->posZ() + ( pkMesh->aabb().offset()->z + ( pkMesh->aabb().depth() / 2 ) );

		float fAabbMinX = pkMesh->posX() + ( pkMesh->aabb().offset()->x - ( pkMesh->aabb().width() / 2 ) );
		float fAabbMinY = pkMesh->posY() + ( pkMesh->aabb().offset()->y - ( pkMesh->aabb().height() / 2 ) );
		float fAabbMinZ = pkMesh->posZ() + ( pkMesh->aabb().offset()->z - ( pkMesh->aabb().depth() / 2 ) );

		if(fMaxX < fAabbMaxX) fMaxX = fAabbMaxX;
		if(fMaxY < fAabbMaxY) fMaxY = fAabbMaxY;
		if(fMaxZ < fAabbMaxZ) fMaxZ = fAabbMaxZ;

		if(fMinX > fAabbMinX) fMinX = fAabbMinX;
		if(fMinY > fAabbMinY) fMinY = fAabbMinY;
		if(fMinZ > fAabbMinZ) fMinZ = fAabbMinZ;
		*/
	}

		//Deberia cargar aca la data...
	/*	orkNode.aabb().setData( fabs(fMaxX - fMinX), 
								fabs(fMaxY - fMinY), 
								fabs(fMaxZ - fMinZ), 
								
								(fMinX + fMaxX) / 2 - orkNode.posX(), 
								(fMinY + fMaxY) / 2 - orkNode.posY(), 
								(fMinZ + fMaxZ) / 2 - orkNode.posZ());
	
	*/

	return true;
}
bool Import::importMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& orkMesh){
	
			//Tendria que cargar los AABB para cada Mesh, De Forma Recursiva Quizá?
			/*	float fMaxX = std::numeric_limits<float>::lowest();
				float fMaxY = std::numeric_limits<float>::lowest();
				float fMaxZ = std::numeric_limits<float>::lowest();

				float fMinX = std::numeric_limits<float>::max();
				float fMinY = std::numeric_limits<float>::max();
				float fMinZ = std::numeric_limits<float>::max(); */
	
	MeshVertex* pakVertices = new MeshVertex[pkAiMesh->mNumVertices];
	for(unsigned int i=0; i<pkAiMesh->mNumVertices; i++){
		pakVertices[i].x = pkAiMesh->mVertices[i].x;
		pakVertices[i].y = pkAiMesh->mVertices[i].y;
		pakVertices[i].z = pkAiMesh->mVertices[i].z;
		if( pkAiMesh->mTextureCoords[0] != NULL ) {
			pakVertices[i].u = pkAiMesh->mTextureCoords[0][i].x;
			pakVertices[i].v = pkAiMesh->mTextureCoords[0][i].y;
		}
		/*
		
		// Actualizo AABB
			if( fMaxX < pakVertices[i].x ) fMaxX = pakVertices[i].x;
			if( fMaxY < pakVertices[i].y ) fMaxY = pakVertices[i].y;
			if( fMaxZ < pakVertices[i].z ) fMaxZ = pakVertices[i].z;

			if( fMinX > pakVertices[i].x ) fMinX = pakVertices[i].x;
			if( fMinY > pakVertices[i].y ) fMinY = pakVertices[i].y;
			if( fMinZ > pakVertices[i].z ) fMinZ = pakVertices[i].z;
			*/
		
		if(pkAiMesh->HasNormals()){
			pakVertices[i].nx = pkAiMesh->mNormals[i].x;
			pakVertices[i].ny = pkAiMesh->mNormals[i].y;
			pakVertices[i].nz = pkAiMesh->mNormals[i].z;
		}
	}
	size_t uiIndexCount = pkAiMesh->mNumFaces * 3;
	unsigned short* pausIndices = new unsigned short[uiIndexCount];
	for(unsigned int i=0; i<pkAiMesh->mNumFaces; i++){
		assert(pkAiMesh->mFaces[i].mNumIndices == 3);
		pausIndices[i * 3 + 0] = pkAiMesh->mFaces[i].mIndices[0];
		pausIndices[i * 3 + 1] = pkAiMesh->mFaces[i].mIndices[1];
		pausIndices[i * 3 + 2] = pkAiMesh->mFaces[i].mIndices[2];
	}
	orkMesh.setData(pakVertices, pkAiMesh->mNumVertices, DoMaRe::Primitive::TriangleList, pausIndices, uiIndexCount);
	orkMesh.setName(pkAiMesh->mName.C_Str());

	if(pkAiMaterial){
		// diffuse texture
		aiString kAiTexturePath;
		pkAiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &kAiTexturePath);

		std::string kTexturePath( kAiTexturePath.C_Str() );

		// append '.' if texture is inside folder
		if( !kTexturePath.empty() && kTexturePath.at(0) == '/' )
		{
			kTexturePath = "." + kTexturePath;
		}
		Texture TheTexture = pk_renderer->loadTexture(kTexturePath);
		orkMesh.setTexture(TheTexture);
	}
	
	delete[] pakVertices;
	pakVertices = NULL;

		//Cargo Termino de Actualizar los AABB Seteando Data...

	//	orkMesh.aabb().setData( fabs(fMaxX - fMinX), fabs(fMaxY - fMinY), fabs(fMaxZ - fMinZ),(fMinX + fMaxX) / 2, (fMinY + fMaxY) / 2, (fMinZ + fMaxZ) / 2);
	
	
	return true;
}