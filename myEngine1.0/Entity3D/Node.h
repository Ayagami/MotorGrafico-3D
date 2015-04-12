#pragma once
//-----------------------
#include "../myEngine_API.h"
#include "Entity3D.h"
//-----------------------
#include <string>
#include <vector>
#include <map>
namespace DoMaRe{
	class Animation3D;
	class Bone;
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

			// Animaciones!
			void playAnimation(std::string);
			void AddAnimation(Animation3D*);
			Animation3D* getAnimation();
			void setAnimation(std::string);
			void Update(const double&);
			bool isPlaying();

		private:
			std::vector<Entity3D*> m_pkChilds;

			// Animaciones!
			std::map<std::string, Animation3D*> m_Animations;
			Animation3D* m_pCurrentAnimation;
			Bone*		 m_pBone;
			void setAnimation(Animation3D*);
			int  FrameIndex;

			friend class Import;
			friend class Entity3D;
	};
}