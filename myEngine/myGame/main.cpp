//----------------
#include "Engine.h"
#include "GaMeT.h"
#include <iostream>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow){
	engine::Engine myEngine(hInst, "Graphics 1", 640, 480);
	myEngine.init();
	myEngine.p_game = new MyGame::Game();
	myEngine.run();
}