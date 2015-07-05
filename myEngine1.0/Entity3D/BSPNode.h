#include "../myEngine_API.h"
#include <vector>
#include <string>
#include <d3dx9.h>

namespace DoMaRe{
	class Node;
	class Renderer;
	class BSPNode{
	public:

		BSPNode* m_pFrontNode;
		BSPNode* m_pBackNode;

		D3DXPLANE m_Plane;
		D3DXVECTOR3 m_PlanePoint;

		std::vector<Node*> m_vBackObjects;
		std::vector<Node*> m_vFrontObjects;

		enum Position
		{
			BACK, FRONT, INSIDE
		};
		Position GetPosition(D3DXVECTOR3 BoundingBox[]);
		Position GetPosition(D3DXVECTOR3 Position);

		~BSPNode();
		BSPNode(D3DXPLANE plane, D3DXVECTOR3 point);


		friend class Node;
		void AddNode(BSPNode* pNode);
		void Draw(Renderer* pRenderer, D3DXVECTOR3 CameraPos);
		void AddChild(Node* nodo);
		std::string Name;
	};
}