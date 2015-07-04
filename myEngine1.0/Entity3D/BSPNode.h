#include "../myEngine_API.h"
#include <vector>
#include <string>
#include <d3dx9.h>

namespace DoMaRe{
	class Node;
	class Renderer;
	class BSPNode{
		public:

			//referencias a nodos
			BSPNode* m_pFrontNode;
			BSPNode* m_pBackNode;

			//plano y pos
			D3DXPLANE m_Plane;
			D3DXVECTOR3 m_PlanePoint;

			std::vector<Node*> m_vBackObjects;
			std::vector<Node*> m_vFrontObjects;

			//pos respecto
			enum Position
			{
				BACK, FRONT, INSIDE
			};
			//funciones que me devuelves mi ubic respecto
			Position GetPosition(D3DXVECTOR3 BoundingBox[]);
			Position GetPosition(D3DXVECTOR3 Position);

			//nodo, añadir nodo, hijos, y draw
			~BSPNode();
			BSPNode(D3DXPLANE plane, D3DXVECTOR3 point);


			friend class Node;
			void AddNode(BSPNode* pNode);
			void Draw(Renderer* pRenderer, D3DXVECTOR3 CameraPos);
			void AddChild(Node* nodo);
			std::string Name;
	};
}