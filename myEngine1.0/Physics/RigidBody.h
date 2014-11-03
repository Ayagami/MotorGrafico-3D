#pragma once
#include "../myEngine_API.h"
#include "../Renderer/EMath.h"

class hkpRigidBody;
namespace DoMaRe{
	class Collider;
	class MYENGINE_API RigidBody{
		friend class Physics;

	public:
		RigidBody();
		virtual ~RigidBody();

		// TR Matrix

		void setPosition(float,float,float);
		float posX() const;
		float posY() const;
		float posZ() const;

		void setRotation(float,float,float);
		float rotationX () const;
		float rotationY () const;
		float rotationZ () const;

		const Matrix& transform () const;

		// Collider
	
		void setCollider(Collider*);
		const Collider* collider() const;

		enum HavokMotion{
			Static,
			Dynamic,
			HavokMotionCount
		};

		void setHavokMotion(HavokMotion type);
		HavokMotion havokMotion () const;

	private:
		Matrix m_pTransformation;

		Collider* m_pkCollider;

		HavokMotion m_HMotion;

	protected:

		hkpRigidBody* rigidBody();
		hkpRigidBody* m_pkRigidBody;
	};
}