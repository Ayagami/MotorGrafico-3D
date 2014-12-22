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

#include "../Renderer/Material.h"

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
	Instance = this;
}
Import::~Import(){
	// Fin MAP de Meshes
}

Import* Import::getInstance(){
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
bool Import::importScene (const std::string& fileName, Node& SceneRoot){

	Assimp::Importer kImporter;
	const aiScene* AiScene = kImporter.ReadFile(fileName, aiProcess_Triangulate | aiProcess_SortByPType);
	importNode(AiScene->mRootNode, AiScene, SceneRoot);
	
	return true;
}
bool Import::importNode (const aiNode* AiNode, const aiScene* AiScene, Node& kNode){
	// import transformation
	aiVector3t<float> v3AiScaling;
	aiQuaterniont<float> qAiRotation;
	aiVector3t<float> v3AiPosition;

	AiNode->mTransformation.Decompose(v3AiScaling, qAiRotation, v3AiPosition);

	kNode.setPos(v3AiPosition.x, v3AiPosition.y, v3AiPosition.z); // Seteo POS
	kNode.setScale(v3AiScaling.x, v3AiScaling.y, v3AiScaling.z); // Seteo Scale
	float fRotX, fRotY, fRotZ;
	MATHF::quaternionToEulerAngles(qAiRotation.x, qAiRotation.y, qAiRotation.z, qAiRotation.w, fRotX, fRotY, fRotZ); // Uso QuaternionToEuler :)
	
	kNode.setRotation(fRotX, fRotY, fRotZ); // Seteo Rotation

	
	
	//INTENTO crear AABB.
	float MaxX = std::numeric_limits<float>::lowest();
	float MaxY = std::numeric_limits<float>::lowest();
	float MaxZ = std::numeric_limits<float>::lowest();

	float MinX = std::numeric_limits<float>::max();
	float MinY = std::numeric_limits<float>::max();
	float MinZ = std::numeric_limits<float>::max();
	
	
	// Importo Child Nodes

	for(unsigned int i=0; i<AiNode->mNumChildren; i++){
		Node* pkNode = new Node();
		kNode.addChild(pkNode);

		pkNode->setParent(&kNode);

		importNode(AiNode->mChildren[i], AiScene, *pkNode);

		

		//Ajusto AABB ?
		float AabbMx = pkNode->posX() + ( pkNode->aabb().offset()->x + ( pkNode->aabb().width() / 2 ) );
		float AabbMy = pkNode->posY() + ( pkNode->aabb().offset()->y + ( pkNode->aabb().height() / 2 ) );
		float AabbMz = pkNode->posZ() + ( pkNode->aabb().offset()->z + ( pkNode->aabb().depth() / 2 ) );

		float Aabbmx = pkNode->posX() + ( pkNode->aabb().offset()->x - ( pkNode->aabb().width() / 2 ) );
		float Aabbmy = pkNode->posY() + ( pkNode->aabb().offset()->y - ( pkNode->aabb().height() / 2 ) );
		float Aabbmz = pkNode->posZ() + ( pkNode->aabb().offset()->z - ( pkNode->aabb().depth() / 2 ) );

		if(MaxX < AabbMx) MaxX = AabbMx;
		if(MaxY < AabbMy) MaxY = AabbMy;
		if(MaxZ < AabbMz) MaxZ = AabbMz;

		if(MinX > Aabbmx) MinX = Aabbmx;
		if(MinY > Aabbmy) MinY = Aabbmy;
		if(MinZ > Aabbmz) MinZ = Aabbmz;

		
	}

	// Importo Child Meshes

	for(unsigned int i=0; i<AiNode->mNumMeshes; i++){
		Mesh* pkMesh = new Mesh(this->GetRenderer());
		kNode.addChild(pkMesh);

		pkMesh->setParent(&kNode);

		aiMesh* pkAiMesh = AiScene->mMeshes[ AiNode->mMeshes[i] ];
		aiMaterial* pkAiMaterial = AiScene->mMaterials[pkAiMesh->mMaterialIndex];

		importMesh(pkAiMesh, pkAiMaterial, *pkMesh);

		//	Actualizo nuevamente los AABB (Pero para meshes!)
		float AabbMx = pkMesh->posX() + ( pkMesh->aabb().offset()->x + ( pkMesh->aabb().width() / 2 ) );
		float AabbMy = pkMesh->posY() + ( pkMesh->aabb().offset()->y + ( pkMesh->aabb().height() / 2 ) );
		float AabbMz = pkMesh->posZ() + ( pkMesh->aabb().offset()->z + ( pkMesh->aabb().depth() / 2 ) );

		float Aabbmx = pkMesh->posX() + ( pkMesh->aabb().offset()->x - ( pkMesh->aabb().width() / 2 ) );
		float Aabbmy = pkMesh->posY() + ( pkMesh->aabb().offset()->y - ( pkMesh->aabb().height() / 2 ) );
		float Aabbmz = pkMesh->posZ() + ( pkMesh->aabb().offset()->z - ( pkMesh->aabb().depth() / 2 ) );

		if(MaxX < AabbMx) MaxX = AabbMx;
		if(MaxY < AabbMy) MaxY = AabbMy;
		if(MaxZ < AabbMz) MaxZ = AabbMz;

		if(MinX > Aabbmx) MinX = Aabbmx;
		if(MinY > Aabbmy) MinY = Aabbmy;
		if(MinZ > Aabbmz) MinZ = Aabbmz;
		
	}

		//Deberia cargar aca la data...
		kNode.aabb().setData( fabs(MaxX - MinX), fabs(MaxY - MinY), fabs(MaxZ - MinZ), (MinX + MaxX) / 2 - kNode.posX(), (MinY + MaxY) / 2 - kNode.posY(), (MinZ + MaxZ) / 2 - kNode.posZ());
	
	

	return true;
}
bool Import::importMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& kMesh){

			//Tendria que cargar los AABB para cada Mesh, De Forma Recursiva Quizá?
				float MaxX = std::numeric_limits<float>::lowest();
				float MaxY = std::numeric_limits<float>::lowest();
				float MaxZ = std::numeric_limits<float>::lowest();

				float MinX = std::numeric_limits<float>::max();
				float MinY = std::numeric_limits<float>::max();
				float MinZ = std::numeric_limits<float>::max(); 
	
	MeshVertex* pVertices = new MeshVertex[pkAiMesh->mNumVertices];
	for(unsigned int i=0; i<pkAiMesh->mNumVertices; i++){
		pVertices[i].x = pkAiMesh->mVertices[i].x;
		pVertices[i].y = pkAiMesh->mVertices[i].y;
		pVertices[i].z = pkAiMesh->mVertices[i].z;
		if( pkAiMesh->mTextureCoords[0] != NULL ) {
			pVertices[i].u = pkAiMesh->mTextureCoords[0][i].x;
			pVertices[i].v = pkAiMesh->mTextureCoords[0][i].y;
		}
		
		
		// Actualizo AABB
			if( MaxX < pVertices[i].x ) MaxX = pVertices[i].x;
			if( MaxY < pVertices[i].y ) MaxY = pVertices[i].y;
			if( MaxZ < pVertices[i].z ) MaxZ = pVertices[i].z;

			if( MinX > pVertices[i].x ) MinX = pVertices[i].x;
			if( MinY > pVertices[i].y ) MinY = pVertices[i].y;
			if( MinZ > pVertices[i].z ) MinZ = pVertices[i].z;
			
		
		if(pkAiMesh->HasNormals()){
			pVertices[i].nx = pkAiMesh->mNormals[i].x;
			pVertices[i].ny = pkAiMesh->mNormals[i].y;
			pVertices[i].nz = pkAiMesh->mNormals[i].z;
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
	kMesh.setData(pVertices, pkAiMesh->mNumVertices, DoMaRe::Primitive::TriangleList, pausIndices, uiIndexCount);
	kMesh.setName(pkAiMesh->mName.C_Str());

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
		kMesh.setTexture(TheTexture);

		// Loading Material...
		aiColor4D diffuse;
		aiReturn di = aiGetMaterialColor(pkAiMaterial, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
		
		aiColor4D ambient;
		aiReturn am = aiGetMaterialColor(pkAiMaterial, AI_MATKEY_COLOR_AMBIENT, &ambient);

		aiColor4D specular;
		aiReturn sp = aiGetMaterialColor(pkAiMaterial, AI_MATKEY_COLOR_SPECULAR, &specular);

		aiColor4D emissive;
		aiReturn em = aiGetMaterialColor(pkAiMaterial, AI_MATKEY_COLOR_EMISSIVE, &emissive);

		if(di == aiReturn_SUCCESS && am == aiReturn_SUCCESS && sp == aiReturn_SUCCESS && em == aiReturn_SUCCESS){

			Material* pkMaterial = new Material();
			pkMaterial->setDiffuse(diffuse.r,diffuse.g,diffuse.b,diffuse.a);
			pkMaterial->setAmbient(ambient.r,ambient.g,ambient.b,ambient.a);
			pkMaterial->setSpecular(specular.r,specular.g,specular.b,specular.a);
			pkMaterial->setEmissive(emissive.r,emissive.g,emissive.b,emissive.a);

			kMesh.setMaterial(*pkMaterial);
		}
	}
	
	delete[] pVertices;
	pVertices = NULL;

		//Cargo Termino de Actualizar los AABB Seteando Data...

	kMesh.aabb().setData( fabs(MaxX - MinX), fabs(MaxY - MinY), fabs(MaxZ - MinZ),(MinX + MaxX) / 2, (MinY + MaxY) / 2, (MinZ + MaxZ) / 2);
	
	
	return true;
}