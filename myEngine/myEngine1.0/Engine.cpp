#pragma once
#include "Engine.h"
#include <string>
#include "Window.h"
#include "Renderer.h"
#include "Importer.h"
#include "input\DirectInput.h"
#include "timer\Timer.h"
#include "Game.h"


using namespace engine;
Engine::Engine(HINSTANCE hInst, std::string t, int w, int h):
hInstance(hInst), _t(t), _w(w), _h(h), hWnd(0), WndC(new Window(hInst) ), Rendr(new Renderer), m_diInput(new DirectInput()), m_tTimer(new Timer()), m_iImporter(new Importer()), p_game(NULL){
}


bool Engine::init(){
	if(WndC->CrearVentana(_t,_w,_h) == TRUE && Rendr->Init(WndC->hWnd()) == TRUE && m_iImporter->Init(*Rendr) == TRUE && m_diInput->init( hInstance, WndC->hWnd()) == TRUE)
		return true;
	return false;
}


void Engine::run(){
	MSG Mess;

	#ifdef _DEBUG
		RedirectIOToConsole();
	#endif

	if(!p_game) return;
	if(!p_game->Init(*Rendr)) return;

	p_game->OnSceneInit();	// Starteo scenes...

	m_tTimer->firstMeasure();

	while(p_game->getGame()){
		m_tTimer->measure();

		m_diInput->reacquire();
		Rendr->BeginFrame();

		p_game->Frame(*Rendr, *m_diInput, *m_tTimer);
		p_game->OnSceneUpdate(m_tTimer);
		p_game->DrawScenes(Rendr, m_tTimer);
		Rendr->EndFrame();
		if(PeekMessage(&Mess,NULL,0,0,PM_REMOVE)){
			TranslateMessage(&Mess);
			DispatchMessage(&Mess);
		}
		if(Mess.message == WM_QUIT)
			p_game->setGame(false);
	}
	p_game->OnSceneShutdown();
}


void Engine::RedirectIOToConsole(){
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	FILE *fp;
	AllocConsole();
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
		&conInfo);
	conInfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
		conInfo.dwSize);
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);
	std::ios::sync_with_stdio();
}



Engine::~Engine(){
	if(p_game){
		delete p_game;
		p_game = NULL;
	}
	if (m_tTimer){
		delete m_tTimer;
		m_tTimer = NULL;
	}
	if (m_diInput){
		delete m_diInput;
		m_diInput = NULL;
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