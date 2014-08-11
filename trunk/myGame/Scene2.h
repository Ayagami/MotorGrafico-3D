#pragma once
#include "Scene\Scene.h"
#include "Entity2D\Quad.h"
#include "Entity2D\Sprite.h"
#include "Renderer\RenderTypes.h"
#include "Renderer\Renderer.h"
#include "Entity2D\animation.h"
#include "timer\pg1_timer.h"
#include "input\pg1_directinput.h"
#include "Game.h"
#include "Scene\Import.h"
#include <string>
namespace MiJuego{
	class Scene2 : public DoMaRe::Scene{

	public:
		bool Init();
		bool Frame(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&, DoMaRe::Game&);
	private:

		DoMaRe::Quad * _Cubo1;

		DoMaRe::Sprite * _Sprite2;

	};
}