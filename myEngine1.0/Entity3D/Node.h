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
			class MYENGINE_API DoMaReQuat{
				private:
					float x, y, z, w;
				public:
					void setQuaternion(float a, float b, float c, float d){
						x = a;
						y = b;
						z = c;
						w = d;
					}
					DoMaReQuat(){
						x = y = z = w = 0;
					}
				friend class Entity3D;
			};
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

			void setBaseRotation(float a, float b, float c, float d){ 
				baseRot->setQuaternion(a, b, c, d);
			}

		private:
			std::vector<Entity3D*> m_pkChilds;
			DoMaReQuat* baseRot;
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