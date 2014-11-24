#pragma once
#include "../myEngine_API.h"


//#include "RigidBody.h"

//#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>

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
	class RigidBody;
	class MYENGINE_API Physics{
		friend class Engine;
	public:
		void update(float fk_DeltaTime);

		static Physics* getInstance();

		static void addEntity(RigidBody* pkR);
	protected:
		Physics();
		~Physics();
	private:  // IDK WHAT IM DOING!-
		static Physics* Instance;
		static void HavokFailure(const char* msg, void* userAgent);
		static void StartTestScene();
		static hkVisualDebugger* s_VDebugger;
		static hkpPhysicsContext* s_HvkContext;

		static hkpWorld* s_HvkWorld;

		static bool s_HavokIsStarted;
	};
}