#pragma once
#include "../myEngine_API.h"
namespace DoMaRe{
	class Mesh;
}

	class hkpRigidBody;
	class hkpShape;
	class hkpBoxShape;
	class hkpConvexVerticesShape;

namespace DoMaRe{

	// ------- Virtual Collider
	class MYENGINE_API Collider{
	friend class Physics;
	friend class RigidBody;
	
	public:
		Collider();
		virtual ~Collider();

		virtual void build(const Mesh* pkMesh) = 0;
		void setPosition (float fX, float fY, float fZ);

	protected:
		virtual hkpShape* shape () = 0;
		hkpRigidBody* rigidBody();
		hkpRigidBody* pk_RigidBody;
	};


	// ------------------ Box Collider
	class MYENGINE_API BoxCollider : public Collider{
		public:
			BoxCollider();
			~BoxCollider();
			void build(const Mesh* pkMesh);

		protected:
			hkpShape* shape();

		private:
			hkpBoxShape* m_pkBox;
	};


	// ------------------ Mesh Collider
	class MYENGINE_API MeshCollider : public Collider{
		public:
			MeshCollider();
			void build(const Mesh* pkMesh);
			//~MeshCollider();
		protected:
			hkpShape* shape();
		private:
			hkpConvexVerticesShape* m_pkMeshCollider;
	};

}