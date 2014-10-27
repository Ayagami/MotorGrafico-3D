#include "Physics.h"
#include <iostream>

//**************************************************************
// Havok Library LINK!
#pragma comment (lib, "hkBase.lib")
#pragma comment (lib, "hkVisualize.lib")
#pragma comment (lib, "hkInternal.lib")
#pragma comment (lib, "hkSerialize.lib")
#pragma comment (lib, "hkGeometryUtilities.lib")
#pragma comment (lib, "hkcdInternal.lib")
#pragma comment (lib, "hkcdCollide.lib")
#pragma comment (lib, "hkpCollide.lib")
#pragma comment (lib, "hkpConstraint.lib")
#pragma comment (lib, "hkpConstraintSolver.lib")
#pragma comment (lib, "hkpDynamics.lib")
#pragma comment (lib, "hkpInternal.lib")
#pragma comment (lib, "hkpUtilities.lib")
// Havok headers
#include <xmmintrin.h>
#include <Common/Base/hkBase.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>

// Cositas de prueba
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
//**************************************************************
using namespace DoMaRe;


//*************************************************************
//Inicializadores que necesita Havok =/
hkVisualDebugger* Physics::s_VDebugger = NULL;
hkpPhysicsContext* Physics::s_HvkContext = NULL;

hkpWorld* Physics::s_HvkWorld = NULL;

bool Physics::s_HavokIsStarted = false;
//*************************************************************
// Cositas para la escena de prueba
hkpRigidBody* Physics::s_RigidBody1 = NULL;
hkpRigidBody* Physics::s_RigidBody2 = NULL;
//**************************************************************
Physics::Physics ()
{
	if(!s_HavokIsStarted) {
		
		#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && (HK_CONFIG_SIMD ==  HK_CONFIG_SIMD_ENABLED)
			_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
		#endif

		// Arrancamos Havok con Memory Leak Detector. Leer documentación para saber mas :)
		hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initChecking( hkMallocAllocator::m_defaultMallocAllocator,  hkMemorySystem::FrameInfo(1024 * 1024));
		hkBaseSystem::init(memoryRouter, HavokFailure);

		//*********************************** COMIENZO A CONFIGURAR WORLD ****************************
		// Configuro la Fisica del World

		hkpWorldCinfo HavokWorldInfo;
		HavokWorldInfo.m_gravity = hkVector4(0.0f, -9.8f, 0.0f); // Ajusto Gravedad YAY!
		HavokWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_CONTINUOUS;

		// ¿Seteo el Frustum? y el Size del World.
		HavokWorldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_REMOVE_ENTITY;
		HavokWorldInfo.setBroadPhaseWorldSize(1000.0f);

		s_HvkWorld = new hkpWorld(HavokWorldInfo);
		s_HvkWorld->m_wantDeactivation = false;

		// Bloqueo el World para poder modificarlo :D!
		s_HvkWorld->markForWrite();

		// Detecto colisiones a travez de Havok Agents.
		hkpAgentRegisterUtil::registerAllAgents( s_HvkWorld->getCollisionDispatcher() );

		//*********************************** TERMINO DE CONFIGURAR WORLD *****************************
		//*********************************** CONFIGURO EL VISUAL DEBUGER *****************************
		// Inicio Visual Debugger
	
		s_HvkContext = new hkpPhysicsContext();
		hkpPhysicsContext::registerAllPhysicsProcesses();
		s_HvkContext->addWorld(s_HvkWorld);

		// Desbloqueo el World para que el resto lo use (AL SER MULTITHREADING ES NECESARIO ESTO)
		s_HvkWorld->unmarkForWrite();

		hkArray<hkProcessContext*> havokContexts;
		havokContexts.pushBack(s_HvkContext);

		s_VDebugger = new hkVisualDebugger(havokContexts);
		s_VDebugger->serve();

		//*********************************** TERMINO EL VISUAL DEBUGER *******************************

		//****************************************** LLAMO A TEST SCENE *******************************
		StartTestScene();
		//****************************** TERMINO DE LLAMAR A TEST SCENE *******************************

		s_HavokIsStarted = true;				// Seteo mi trigger a True para no poder inicializar todo de nuevo :D!
	}
}

void Physics::StartTestScene(){
		//*********************************** COMIENZO LA TEST SCENE  *********************************
				//******************************* CAJA 1 ****************************************
		// Creo la Caja
		hkpBoxShape* m_Box1 = new hkpBoxShape( hkVector4(0.5f, 0.5f, 0.5f) );

		// Seteo el Rigidbody :)
		hkpRigidBodyCinfo HavokRBodyInfo1;
		HavokRBodyInfo1.m_shape = m_Box1;
		HavokRBodyInfo1.m_position = hkVector4(0, 15, 0);
		HavokRBodyInfo1.m_motionType = hkpMotion::MOTION_DYNAMIC;
		HavokRBodyInfo1.m_restitution = 1.9f;
		m_Box1->setRadius(0.001f);
 
		// Configuro la Masa del rigidbody :)
		const hkReal fBoxMass(10.0f);
		hkMassProperties kMassProperties;
 
		// Le digo a havok que calcule los datos del Shape en cuestion.
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(m_Box1, fBoxMass, kMassProperties);
		HavokRBodyInfo1.setMassProperties(kMassProperties);

		// Creo el rigidbory con la data que le cargué antes, y agrego la entity a mi World.
		s_RigidBody1 = new hkpRigidBody(HavokRBodyInfo1);
		s_HvkWorld->addEntity(s_RigidBody1);
	
		// Elimino la referencia a mi Box, ya que puedo acceder a ella a travez de mi Rigidbody Estatico.
		m_Box1->removeReference();
				//*************************** TERMINO CAJA 1 ************************************
				//******************************* CAJA 2 ****************************************
		hkpBoxShape* m_Box2 = new hkpBoxShape( hkVector4(5.0f, 1.0f, 5.0f) );

		hkpRigidBodyCinfo HavokRBodyInfo2;
		HavokRBodyInfo2.m_shape = m_Box2;
		HavokRBodyInfo2.m_position = hkVector4(0.0f, 0.0f, 0.0f);
		HavokRBodyInfo2.m_motionType = hkpMotion::MOTION_FIXED;  // Fixed a Dinamica... Se sobre entiende esto no?
		m_Box2->setRadius(0.0f);

		s_RigidBody2 = new hkpRigidBody(HavokRBodyInfo2);
		s_HvkWorld->addEntity(s_RigidBody2);
	
		m_Box2->removeReference();
				//*************************** TERMINO CAJA 2 ************************************
		//*********************************** TERMINO LA TEST SCENE  ***********************************
}

Physics::~Physics (){
	// Escena de Prueba!
	s_RigidBody1->removeReference();
	s_RigidBody1 = NULL;

	s_RigidBody2->removeReference();
	s_RigidBody2 = NULL;

	// Borro el VDebugger y el vector de Context
	s_VDebugger->shutdown();
	s_VDebugger->removeReference();
	s_HvkContext->removeReference();

	// Elimino el World!
	s_HvkWorld->removeReference();

	// Cierro Havok Base System y el MemoryLeak System.
	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();
}

void Physics::update (float fk_DeltaTime){
	s_VDebugger->step();

	float fHavokStep = (fk_DeltaTime / 1000.0f);
	if(fHavokStep < 0.00001f) {
		return;
	}

	if(fHavokStep > 4.0f) {
		fHavokStep = 3.9f;
	}

	s_HvkWorld->stepDeltaTime(fHavokStep);
}

void Physics::HavokFailure (const char* msg, void* userAgent){
	OutputDebugString(msg);
}

#include <Common\Base\KeyCode.cxx>
//**************************************************************
// Saco Cositas que no me interesan (Al menos por ahora)
#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_BEHAVIOUR
#undef HK_FEATURE_PRODUCT_MILSIM
#undef HK_FEATURE_PRODUCT_PHYSICS

#define HK_EXCLUDE_LIBRARY_hkpVehicle
#define HK_EXCLUDE_LIBRARY_hkCompat
#define HK_EXCLUDE_LIBRARY_hkSceneData
#define HK_EXCLUDE_LIBRARY_hkcdCollide

#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
#define HK_EXCLUDE_FEATURE_hkpHeightField
#define HK_EXCLUDE_FEATURE_hkpAccurateInertiaTensorComputer
#define HK_EXCLUDE_FEATURE_hkpUtilities
#define HK_EXCLUDE_FEATURE_hkpVehicle
#define HK_EXCLUDE_FEATURE_hkpCompressedMeshShape
#define HK_EXCLUDE_FEATURE_hkpConvexPieceMeshShape
#define HK_EXCLUDE_FEATURE_hkpExtendedMeshShape
#define HK_EXCLUDE_FEATURE_hkpMeshShape
#define HK_EXCLUDE_FEATURE_hkpSimpleMeshShape
#define HK_EXCLUDE_FEATURE_hkpPoweredChainData
#define HK_EXCLUDE_FEATURE_hkMonitorStream
//Fin Cositas que no me interesan :)
#include <Common/Base/Config/hkProductFeatures.cxx>