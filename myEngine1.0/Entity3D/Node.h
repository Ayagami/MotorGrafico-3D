#pragma once
//-----------------------
#include "../myEngine_API.h"
#include "Entity3D.h"
//-----------------------
#include <string>
#include <vector>
#include <iostream>
#include <map>
namespace DoMaRe{
	class Animation3D;
	class Bone;
	class Mesh;
	class Vector3;
	class MYENGINE_API Node : public Entity3D{
	public:

		Node(std::string name);
		~Node();
		void AddMesh(Mesh* pMeshAux);
		void AddChild(Node* hijo);
		Mesh* GetMesh() {return m_vMeshes[0];}
		Node* GetChild(unsigned int index);
		Node* FindChildByName(std::string sName);
		void SetFirstTransform(float a1,float a2,float a3, float a4, 

			float b1, float b2,float b3, float b4,

			float c1,float c2,float c3,float c4,

			float d1,float d2, float d3, float d4);
		unsigned int GetHijoCount();
		unsigned int GetMeshCount();
		void PlayAnim(std::string sName);
		void AddAnim(Animation3D* pAnimation);
		Animation3D* GetAnim(std::string sName);
		void SetAnim(std::string sName);
		virtual void Update(const double& dDeltaTime);
		bool IsPlaying();
		int drawCalls;

	private:

		std::vector<Node*> m_vChildNodes;
		std::vector<Mesh*> m_vMeshes;
		D3DXMATRIX m_mGlobalTransform;
		D3DXMATRIX m_mOriginalTransform;
		unsigned int m_nChilds;
		unsigned int m_nMeshes;
		virtual void Draw(Renderer * pRenderer);
		void PreDraw(D3DXMATRIX transformation, Renderer * pRenderer);
		void NodeDraw(Renderer * pRenderer);
		void CalculateBB();
		void GetBoundings(Vector3* pOutMin, Vector3* pOutMax);
		std::map<std::string, Animation3D*> m_mAnimations;
		Animation3D* m_pCurrentAnim;
		Bone* m_pBone;       
		void SetAnim(Animation3D* pAnimation);
		int KeyFrameIndex;
		
		D3DXVECTOR3* m_vBB;

		Vector3 v_MinBound;
		Vector3 v_MaxBound;

		friend class Import;
		friend class Scene;
		friend class Frustrum;
	};
}