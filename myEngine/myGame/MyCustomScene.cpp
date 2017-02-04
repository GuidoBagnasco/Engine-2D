#include "MyCustomScene.h"
using namespace MyGame;


MyCustomScene::MyCustomScene(std::string s) : Scene(s){

}


MyCustomScene::~MyCustomScene() {

}


void MyCustomScene::OnStart(){
	std::cout << "Testing Start" << std::endl;
}


void MyCustomScene::OnUpdate(engine::Timer*) {
	//std::cout << "Testing MyCustomScene Loop" << std::endl;
}


void MyCustomScene::OnShutdown() {
	std::cout << "Testing shutdown" << std::endl;
}