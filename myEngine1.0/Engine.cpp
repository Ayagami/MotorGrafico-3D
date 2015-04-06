#pragma once
#include <sstream>
#include "Engine.h"
#include <string>
#include "Renderer\Window.h"
#include "Scene\Camera.h"
#include "Renderer\Renderer.h"
#include "Game.h"
#include "timer\pg1_timer.h"
#include "input\pg1_directinput.h"
#include "Scene\Import.h"
#include "Scene\Scene.h"
#include "Sound\Sound.h"
//#include "Physics\Physics.h"

#include "Entity3D\Mesh.h"
using namespace DoMaRe;
Engine::Engine(HINSTANCE hInst, int nCmdS, std::string t, int w, int h):
hInstance(hInst),nCmdShow(nCmdS), _t(t), _w(w), _h(h), hWnd(0), WndC(new Window(hInst) ), Rendr(new Renderer), G(NULL), dInput( new DirectInput() ), m_pkTimer( new Timer() ), Importer (new Import()), pk_Sound(new Sound())/*, m_pkPhysics(new Physics())*/{
	// So... Why so Serious?
}
bool Engine::init(){
	if(WndC->CrearVentana(_t,_w,_h) == TRUE && Rendr->Init(WndC->hWnd()) == TRUE && Importer->Init(Rendr, pk_Sound) == TRUE && dInput->init(hInstance,WndC->hWnd()) == TRUE && pk_Sound->startSoundEngine() == TRUE){
		return true;
	}
	return false;
}
void Engine::Log(std::string pk){
	std::cout << pk;
}
void Engine::RedirectIOToConsole(){
        int hConHandle;
        long lStdHandle;
        CONSOLE_SCREEN_BUFFER_INFO coninfo;
        FILE *fp;
        AllocConsole();
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), 
                &coninfo);
        coninfo.dwSize.Y = MAX_CONSOLE_LINES;
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), 
                coninfo.dwSize);
        lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        fp = _fdopen( hConHandle, "w" );
        *stdout = *fp;
        setvbuf( stdout, NULL, _IONBF, 0 );
        lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        fp = _fdopen( hConHandle, "r" );
        *stdin = *fp;
        setvbuf( stdin, NULL, _IONBF, 0 );
        lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        fp = _fdopen( hConHandle, "w" );
        *stderr = *fp;
        setvbuf( stderr, NULL, _IONBF, 0 );
        std::ios::sync_with_stdio();
}

void Engine::run(){
	//bool grs = true;
	MSG Mess;
	#ifdef _DEBUG
	RedirectIOToConsole();
	#endif
	Log("Starting Engine");
	if(!G) return;
	if(!G->Init(*Rendr, *Importer)) return;
	if(!G->currentScene()->Init(*Importer)) return;
	m_pkTimer->firstMeasure();

	while(G->getGame()){

		m_pkTimer->measure();


		dInput->reacquire();

		//m_pkPhysics->update(m_pkTimer->timeBetweenFrames());


		Mesh::debugedMeshes = 0;
		Rendr->BeginFrame();
		G->currentScene()->getCamera()->Update();
		G->Frame(*Rendr, *dInput, *m_pkTimer, *Importer);
		G->currentScene()->Frame(*Rendr,*dInput, *m_pkTimer, *Importer, *G, *pk_Sound);
		G->currentScene()->draw(*Rendr,*dInput, *m_pkTimer, *Importer);
		Rendr->EndFrame();

		static std::stringstream Title;
		Title.str("");
		Title << WndC->getWindowName()<< " <<DEBUG>> (" << m_pkTimer->fps() << " FPS) Scene: " << G->currentScene()->Name << " Draw Counts : " << Mesh::debugedMeshes  << " <</DEBUG>>";

		WndC->setWindowName(Title.str());


		if(PeekMessage(&Mess,NULL,0,0,PM_REMOVE)){
			TranslateMessage(&Mess);
			DispatchMessage(&Mess);
		}
		if(Mess.message == WM_QUIT)
			G->setGame(false);
	}
	G->currentScene()->deInit();
	G->currentScene()->deinit();
	G->DeInit();
}
Engine::~Engine(){
	/*if(m_pkPhysics){
	delete m_pkPhysics;
	m_pkPhysics = NULL;
	}*/
	if(pk_Sound){
	pk_Sound->stopSoundEngine();
	delete pk_Sound;
	pk_Sound = NULL;
	}
	if(Importer){
	delete Importer;
	Importer = NULL;
	}
	if(m_pkTimer){
	delete m_pkTimer;
	m_pkTimer = NULL;
	}
	if(dInput){
	delete dInput;
	dInput = NULL;
	}
	if(G){
	delete G;
	G = NULL;
	}
	if(Rendr){
	delete Rendr;
	Rendr = NULL;
	}
	if(WndC){
	delete WndC;
	WndC = NULL;
	}
}
