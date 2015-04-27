#include "../myEngine_API.h"
#include <vector>
#include <string>
#include <d3dx9.h>

namespace DoMaRe{
	class Node;
	class Renderer;
	class BSPNode{
		public:

			BSPNode* frontBSP;
			BSPNode* backBSP;

			D3DXPLANE   m_dPlane;
			D3DXVECTOR3 m_dPoint;

			std::vector<Node*>  frontNodes;
			std::vector<Node*>  backNodes;

			BSPNode(D3DXPLANE plane, D3DXVECTOR3 point);
			~BSPNode();

			enum BSPposition{
				INSIDE, FRONT, BACK
			};

			BSPposition getPosition(D3DXVECTOR3 BoundingBox[]);
			BSPposition getPosition(D3DXVECTOR3 Position);

			friend class Node;
			void addBSPNode(BSPNode* bspNode);
			void Draw(Renderer*, D3DXVECTOR3);
			void addChild(Node* node);
			std::string m_sName;
	};
}