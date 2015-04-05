#pragma once
#include "myEngine_API.h"
#include <Windows.h>
#include <string>
#include <io.h>         //_open_osfhandle
#include <fcntl.h>      //_O_TEXT
namespace DoMaRe{
class Window;
class Renderer;
class Game;
class Camera;
class DirectInput;
class Timer;
class Import;
class Sound;
//class Physics;
	class MYENGINE_API Engine{
		public:
			static const WORD MAX_CONSOLE_LINES = 1000;
			static void Log(std::string pk);
			Engine(HINSTANCE hInst ,int nCmdS, std::string t, int w, int h);
			~Engine();
			bool init();
			void run();
			HWND hWnd;
			Game* G;
			Import* Importer;
		private:

			void RedirectIOToConsole();

			Renderer* Rendr;
			HINSTANCE hInstance;
			Window* WndC;
			DirectInput* dInput;
			Timer* m_pkTimer;
			Sound* pk_Sound;
			//Physics* m_pkPhysics;

			int nCmdShow;
			std::string _t;
			int _w;
			int _h;
	};
}