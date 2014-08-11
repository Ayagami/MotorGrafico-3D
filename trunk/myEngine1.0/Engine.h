#pragma once
#include "myEngine_API.h"
#include <Windows.h>
#include <string>
namespace DoMaRe{
class Window;
class Renderer;
class Game;
class DirectInput;
class Timer;
class Import;
	class MYENGINE_API Engine{
		public:
			Engine(HINSTANCE hInst ,int nCmdS, std::string t, int w, int h);
			~Engine();
			bool init();
			void run();
			HWND hWnd;
			Game* G;
			Import* Importer;
		private:
			
			Renderer* Rendr;
			HINSTANCE hInstance;
			Window* WndC;
			DirectInput* dInput;
			Timer* m_pkTimer;
			int nCmdShow;
			std::string _t;
			int _w;
			int _h;
	};
}