#include "TestGame.h"
#include "Timer.h"

TestGame::TestGame(HINSTANCE hInstance) : Game(hInstance){
	
}




bool TestGame::OnStartUp(){
	//t = new Triangle(SetVertex(-50, 0, 0, 152, 20, 71), SetVertex(50, 0, 0, 152, 20, 71), SetVertex(0, 50, 0, 152, 20, 71), 2, 4);

	//b = new Box(SetVertex(-50, -150, 0, 23, 17, 71), SetVertex(0, -150, 0, 23, 17, 71), SetVertex(-10, -50, 0, 23, 17, 71), SetVertex(40, -50, 0, 23, 17, 71), 1, 2);

	//c = new Circle(90, 0, 0, 255, 0, 0);

	importer = new Importer(m_renderer);

	CreateScene("MainScene");
	Engine::Scene* mainScene = GetScene("MainScene");
	importer->Load("Asuna.xml", *mainScene);

	s =  ((Engine::Sprite*)mainScene->GetEntity("character"));
	s2 = ((Engine::Sprite*)mainScene->GetEntity("character2"));

	mainScene->GetTileMap("Map")->SetMapScale(850,850);
	mainScene->GetTileMap("Map")->SetMapPosition(-350,350);
	return true;
}


static float fspeed = 0.20f;

bool TestGame::OnLoop(){
	//t->Draw(m_renderer);
	//b->Draw(m_renderer);
	//c->Draw(m_renderer);
	
	s2->SetAnimation("Idle");

	if(dInput->keyDown(Engine::Input::KEY_DOWN)){
		s2->SetPosition(s2->GetPositionX(), s2->GetPositionY() -  fspeed * timer.GetDT());
		s2->SetAnimation("WalkingSouth");
	}
	else if(dInput->keyDown(Engine::Input::KEY_UP)){
		s2->SetPosition(s2->GetPositionX(), s2->GetPositionY() +  fspeed * timer.GetDT());
		s2->SetAnimation("WalkingNorth");
	}
	else if(dInput->keyDown(Engine::Input::KEY_RIGHT)){
		s2->SetPosition(s2->GetPositionX()  +  fspeed * timer.GetDT(), s2->GetPositionY());
		s2->SetAnimation("WalkingEast");
	}
	else if(dInput->keyDown(Engine::Input::KEY_LEFT)){
		s2->SetPosition(s2->GetPositionX() -  fspeed * timer.GetDT(), s2->GetPositionY());
		s2->SetAnimation("WalkingWest");
	}
	/*
	if(s2->CheckCollision(*s) == Entity2D::CollisionResult::HorizontalCollision){
		s2->SetPosition(s2->GetPreviousX(), s2->GetPositionY());
	}
	else if(s2->CheckCollision(*s) == Entity2D::CollisionResult::VerticalCollision){
		s2->SetPosition(s2->GetPositionX(), s2->GetPreviousY());
	}


	if(s != NULL)
		s->SetAnimation("WalkingSouth-west");
	*/
	s->SetPosition(s->GetPositionX() + dInput->mouseRelPosX(), s->GetPositionY() - dInput->mouseRelPosY());
	/*
	if(s->CheckCollision(*s2) == Entity2D::CollisionResult::HorizontalCollision){
		s->SetPosition(s->GetPreviousX(), s->GetPositionY());
	}
	else if(s->CheckCollision(*s2) == Entity2D::CollisionResult::VerticalCollision){
		s->SetPosition(s->GetPositionX(), s->GetPreviousY());
	}
	
	for(unsigned int i = 0; i < m_pkEntities.size(); i++){
		m_pkEntities[i]->Update(timer);
		m_pkEntities[i]->Draw(m_renderer);
	}
	*/

	return true;
}




bool TestGame::OnShutDown(){
	return true;
}