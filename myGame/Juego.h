#pragma once
#include "Game.h"
#include "Entity2D\Quad.h"
#include "Entity2D\Sprite.h"
#include "Renderer\RenderTypes.h"
#include "Renderer\Renderer.h"
#include "Entity2D\animation.h"
#include "timer\pg1_timer.h"
#include "input\pg1_directinput.h"
#include "Scene\Import.h"
#include "Scene1.h"
#include "Scene2.h"
namespace MiJuego{
	class Game : public DoMaRe::Game{
	public:
		bool Init(DoMaRe::Renderer&, DoMaRe::Import&);
		void Frame(DoMaRe::Renderer&, DoMaRe::DirectInput&, DoMaRe::Timer&, DoMaRe::Import&);
		void DeInit();
	private:
		Scene1* Escena1;
		Scene2* Escena2;
	};
}