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


#include "../Entity3D/3DAnimation.h"
#include "../Entity3D/BoneInfo.h"
#include "../Entity3D/Bones.h"

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
	//const aiScene* scene = importer.ReadFile( FileName, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	const aiScene* scene = importer.ReadFile(FileName,
		aiPrimitiveType_LINE|aiPrimitiveType_POINT |
		aiProcess_Triangulate |aiProcess_SortByPType
		|aiProcess_MakeLeftHanded);

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
	//const aiScene* AiScene = kImporter.ReadFile(fileName, aiProcess_Triangulate | aiProcess_SortByPType);
	const aiScene* AiScene = kImporter.ReadFile(fileName,
		aiPrimitiveType_LINE|aiPrimitiveType_POINT |
		aiProcess_Triangulate |aiProcess_SortByPType
		|aiProcess_MakeLeftHanded);

	if(AiScene){
		SceneRoot.setName(AiScene->mRootNode->mName.C_Str());
		for(int i=0; i < AiScene->mNumAnimations; i++){
			SceneRoot.AddAnim(CreateAnimation3D(AiScene->mAnimations[i]));
		}
		importNode(AiScene->mRootNode, AiScene, SceneRoot);
		addBonesToNode(&SceneRoot);
		return true;
	}

	return false;
}
void Import::addBonesToNode(Node* fillNode){
	if( m_pBoneMap.count(fillNode->GetName()) ){
		fillNode->m_pBone = m_pBoneMap[fillNode->GetName()];
	}
	for(int i=0; i< fillNode->m_nChilds; i++){
		addBonesToNode(fillNode->m_vChildNodes[i]);
	}
}
Animation3D* Import::CreateAnimation3D(aiAnimation* aiAnim){
	Animation3D* newAnim = new Animation3D(aiAnim->mName.C_Str(), aiAnim->mDuration, aiAnim->mTicksPerSecond);
	for(int i=0; i < aiAnim->mNumChannels; i++){
		aiNodeAnim* currentChanel = aiAnim->mChannels[i];
		Animation3D::KeyFrame * keyFrameAux = new Animation3D::KeyFrame();
		keyFrameAux->name = currentChanel->mNodeName.C_Str();

		keyFrameAux->iPositionKeys = currentChanel->mNumPositionKeys;
		keyFrameAux->iRotationKeys = currentChanel->mNumRotationKeys;
		keyFrameAux->iScalingKeys  = currentChanel->mNumScalingKeys;

		keyFrameAux->positionKey = new aiVectorKey[currentChanel->mNumPositionKeys];
		for(int j=0; j < currentChanel->mNumPositionKeys; j++){
			keyFrameAux->positionKey[j].mTime = currentChanel->mPositionKeys[j].mTime;
			keyFrameAux->positionKey[j].mValue = currentChanel->mPositionKeys[j].mValue;
		}
		keyFrameAux->rotationKey = new aiQuatKey[currentChanel->mNumRotationKeys];
		for(int j=0; j < currentChanel->mNumRotationKeys; j++){
			keyFrameAux->rotationKey[j].mTime  = currentChanel->mRotationKeys[j].mTime;
			keyFrameAux->rotationKey[j].mValue = currentChanel->mRotationKeys[j].mValue;
		}
		keyFrameAux->scalingKey = new aiVectorKey[currentChanel->mNumScalingKeys];
		for(int j=0; j < currentChanel->mNumScalingKeys; j++){
			keyFrameAux->scalingKey[j].mTime = currentChanel->mScalingKeys[j].mTime;
			keyFrameAux->scalingKey[j].mValue = currentChanel->mScalingKeys[j].mValue;
		}

		newAnim->AddFrame(keyFrameAux);
	}

	return newAnim;
}
bool Import::importNode(aiNode* AiNode, const aiScene* AiScene, Node& kNode){

	kNode.setName(AiNode->mName.C_Str());

	aiMatrix4x4 m = AiNode->mTransformation.Transpose();
	kNode.SetFirstTransform(m.a1, m.a2, m.a3, m.a4,
		m.b1, m.b2, m.b3, m.b4,
		m.c1, m.c2, m.c3, m.c4,
		m.d1, m.d2, m.d3, m.d4);

	for(unsigned int i=0; i<AiNode->mNumChildren; i++){
		Node* pkNode = new Node(AiNode->mChildren[i]->mName.C_Str());
		kNode.AddChild(pkNode);

		importNode(AiNode->mChildren[i], AiScene, *pkNode);
	}
	for(unsigned int i=0; i<AiNode->mNumMeshes; i++){
		Mesh* pkMesh = new Mesh(this->GetRenderer());
		kNode.AddMesh(pkMesh);

		aiMesh* pkAiMesh = AiScene->mMeshes[ AiNode->mMeshes[i] ];
		aiMaterial* pkAiMaterial = AiScene->mMaterials[pkAiMesh->mMaterialIndex];

		importMesh(pkAiMesh, pkAiMaterial, *pkMesh);
	}
	return true;
}
bool Import::importMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& kMesh){

	kMesh.setName( pkAiMesh->mName.C_Str() );

	MeshVertex* pVertices = new MeshVertex[pkAiMesh->mNumVertices];
	for(unsigned int i=0; i<pkAiMesh->mNumVertices; i++){
		pVertices[i].x = pkAiMesh->mVertices[i].x;
		pVertices[i].y = pkAiMesh->mVertices[i].y;
		pVertices[i].z = pkAiMesh->mVertices[i].z;
		if( pkAiMesh->mTextureCoords[0] != NULL ) {
			pVertices[i].u = pkAiMesh->mTextureCoords[0][i].x;
			pVertices[i].v = pkAiMesh->mTextureCoords[0][i].y;
		}


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

		/*std::string basePath = getFullPath(kTexturePath);

		std::string texturePath = "";
		texturePath.append(basePath);
		texturePath.append(kTexturePath.c_str());*/

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

	if(pkAiMesh->HasBones()){
		for(int i=0; i < pkAiMesh->mNumBones; i++){
			aiBone* bone = pkAiMesh->mBones[i];
			BoneInfo* bInfo = new BoneInfo();
			for(int j=0; j <  bone->mNumWeights; j++){
				bInfo->addWeight(bone->mWeights[j].mVertexId, bone->mWeights[j].mWeight);
			}
			aiMatrix4x4 m = bone->mOffsetMatrix.Transpose();
			bInfo->setOffsetMatrix(m.a1, m.a2, m.a3, m.a4, m.b1, m.b2, m.b3, m.b4,
				m.c1, m.c2, m.c3, m.c4, m.d1, m.d2, m.d3, m.d4);
			std::string bName = bone->mName.C_Str();
			if(!m_pBoneMap.count(bName)){
				m_pBoneMap[bName] = new Bone();
				bInfo->setBone(m_pBoneMap[bName]);
			}
			else{
				bInfo->setBone(m_pBoneMap[bName]);
			}
			kMesh.AddBoneInfo(bInfo);
		}
	}

	delete[] pVertices;
	pVertices = NULL;

	return true;
}
std::string Import::getFullPath(std::string fName){
	std::string tempName = fName;
	int last = tempName.find_last_of("/\\");
	tempName = tempName.substr(0, last + 1);
	return tempName;
}
