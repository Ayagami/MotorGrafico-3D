#pragma once
//-----------------------
#include "../myEngine_API.h"
#include "Entity3D.h"
//-----------------------
#include <string>
#include <vector>

namespace DoMaRe{
	class MYENGINE_API Node : public Entity3D{
		public:
			Node();
			~Node();
		public:

			const std::vector<Entity3D*>& childs () const{ return m_pkChilds; }
			void addChild (Entity3D* pkChild);
			void removeChild(Entity3D* pkChild);

			void updateTransformation();
			void Draw();

		private:
			std::vector<Entity3D*> m_pkChilds;

	};
}