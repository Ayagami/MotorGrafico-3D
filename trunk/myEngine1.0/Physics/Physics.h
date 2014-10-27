#pragma once
#include "../myEngine_API.h"

class hkVisualDebugger;
class hkpPhysicsContext;
class hkpWorld;
//***************************************   DOCUMENTACIÓN   *****************************************************
// http://dalyup.wordpress.com/2012/02/07/havok-tutorial-01-getting-started/			<- Documentación	   **
// http://mmmovania.blogspot.com.ar/2014/03/havok-physics-engine-tutorial-series.html	<- Mas Documentación   **
// https://software.intel.com/en-us/forums/topic/278673									<- Moar Documentación  **
//*************************************** FIN DOCUMENTACIÓN *****************************************************
// Rigidbody para Escena de prueba :)
class hkpRigidBody;

namespace DoMaRe{
	class Physics{
	public:
		Physics();
		~Physics();

		void update(float fk_DeltaTime);

	private:  // IDK WHAT IM DOING!-
		static void HavokFailure(const char* msg, void* userAgent);
		static void StartTestScene();
		static hkVisualDebugger* s_VDebugger;
		static hkpPhysicsContext* s_HvkContext;

		static hkpWorld* s_HvkWorld;

		static bool s_HavokIsStarted;

		// Escena de Ejemplo!
		static hkpRigidBody* s_RigidBody1;
		static hkpRigidBody* s_RigidBody2;
		static hkpRigidBody* s_RigidBody3;
	};
}