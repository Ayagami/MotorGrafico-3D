#pragma once
#include "Scene\Scene.h"
#include "Entity2D\Quad.h"
#include "Entity2D\Sprite.h"
#include "Renderer\RenderTypes.h"
#include "Scene\Camera.h"
#include "Renderer\Renderer.h"
#include "Entity2D\animation.h"
#include "timer\pg1_timer.h"
#include "input\pg1_directinput.h"
#include "Game.h"
#include "Scene\Import.h"
#include "Scene\Camera.h"
#include "Sound\Sound.h"
#include <string>
namespace MiJuego{
	class Camera;
	class Mesh;
	class Sound;
	class Scene1 : public DoMaRe::Scene{

	public:
		bool Init(DoMaRe::Import&);
		bool Frame(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&, DoMaRe::Game&, DoMaRe::Sound&);
		bool deInit();
	private:

		DoMaRe::Quad * _Cubo1;

		DoMaRe::Sprite * _Sprite2;

		DoMaRe::Mesh * _theMesh;
		DoMaRe::Mesh * _theMesh2;
	};
}