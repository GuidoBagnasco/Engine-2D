#include "GaMeT.h"
#include "animation.h"
#include "Scene.h"
#include "Importer.h"
#include "TileMap.h"
#include "MyCustomScene.h"
#include <iostream>
//#include "Renderer.h"

using namespace MyGame;

engine::TileMap* tilemap;
static float fspeed = 0.20f;
static float fRot = 0.001f;


bool Game::Init(engine::Renderer& r){
	r.SetBackgroundColor(300, 300, 300);

	CreateScene("Scene1");
	engine::Scene* scene1 = GetScene("Scene1");

	MyCustomScene* mcs = new MyCustomScene("MyCustomSceneYAY");
	AddScene(mcs);

	engine::Importer* importer = engine::Importer::GetInstance();

	importer->importScene(*scene1, "scene1.xml");

	//scene1->GetTileMap("Mapa1")->setScaleTileMap(400, 400);
	//scene1->GetTileMap("Mapa1")->setTileMapPos(-200, 200);

	tilemap = scene1->GetTileMap("TileMap");
	tilemap->ScaleMap(1.5f, 1.5f);
	tilemap->SetPosition(-300, 210);

	asuna = ((engine::Sprite*)scene1->GetEntity("asuna"));
	if (asuna != NULL) {
		asuna->setAnimation("Idle");
		asuna->ScaleSprite(0.5f, 0.5f);
	}

	//_Sprite2 = new engine::Sprite();
	kris = ((engine::Sprite*)scene1->GetEntity("kris"));
	if (kris != NULL) {
		kris->setAnimation("Idle");
		kris->ScaleSprite(0.5f, 0.5f);
	}

	elf = ((engine::Sprite*)scene1->GetEntity("elf"));
	if (elf != NULL) {
		elf->setAnimation("Idle");
		elf->ScaleSprite(0.45f, 0.45f);
	}

	wheel = ((engine::Sprite*)scene1->GetEntity("compass"));
	cursor = ((engine::Sprite*)scene1->GetEntity("cursor"));

	if (cursor != NULL)
		cursor->setAnimation("Idle");

	return true;
}


void Game::Frame(engine::Renderer& r, engine::DirectInput& dInput, engine::Timer& timer){
	if (asuna != NULL){
		float fX = asuna->posX();
		float fY = asuna->posY();

		asuna->setAnimation("Idle");

		if (dInput.keyDown(engine::Input::KEY_W)){
			fY += fspeed * timer.timeBetweenFrames();
			asuna->setAnimation("WalkingN");
		}
		if (dInput.keyDown(engine::Input::KEY_S)){
			fY -= fspeed * timer.timeBetweenFrames();
			asuna->setAnimation("WalkingS");
		}
		if (dInput.keyDown(engine::Input::KEY_A)){
			fX -= fspeed * timer.timeBetweenFrames();
			asuna->setAnimation("WalkingW");
		}
		if (dInput.keyDown(engine::Input::KEY_D)){
			fX += fspeed * timer.timeBetweenFrames();
			asuna->setAnimation("WalkingE");
		}

		asuna->setPos(fX, fY);

		if (asuna->checkCollision(*kris) != engine::Entity::NoCollision) {
			asuna->returnToPreviousPos();
		}
		if (asuna->checkCollision(*elf) != engine::Entity::NoCollision) {
			asuna->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Stuff", asuna) != engine::Entity::NoCollision) {
			asuna->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Trees", asuna) != engine::Entity::NoCollision) {
			asuna->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Buildings", asuna) != engine::Entity::NoCollision) {
			asuna->returnToPreviousPos();
		}
	}

	if (kris != NULL) {
		float fX = kris->posX();
		float fY = kris->posY();

		kris->setAnimation("Idle");

		if (dInput.keyDown(engine::Input::KEY_I)){
			fY += fspeed * timer.timeBetweenFrames();
			kris->setAnimation("WalkingN");
		}
		if (dInput.keyDown(engine::Input::KEY_K)){
			fY -= fspeed * timer.timeBetweenFrames();
			kris->setAnimation("WalkingS");
		}
		if (dInput.keyDown(engine::Input::KEY_J)){
			fX -= fspeed * timer.timeBetweenFrames();
			kris->setAnimation("WalkingW");
		}
		if (dInput.keyDown(engine::Input::KEY_L)){
			fX += fspeed * timer.timeBetweenFrames();
			kris->setAnimation("WalkingE");
		}

		kris->setPos(fX, fY);

		if (kris->checkCollision(*asuna) != engine::Entity::NoCollision) {
			kris->returnToPreviousPos();
		}
		if (kris->checkCollision(*elf) != engine::Entity::NoCollision) {
			kris->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Stuff", kris) != engine::Entity::NoCollision) {
			kris->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Trees", kris) != engine::Entity::NoCollision) {
			kris->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Buildings", kris) != engine::Entity::NoCollision) {
			kris->returnToPreviousPos();
		}
	}

	if (elf != NULL) {
		float fX = elf->posX();
		float fY = elf->posY();

		elf->setAnimation("Idle");

		if (dInput.keyDown(engine::Input::KEY_T)) {
			fY += fspeed * timer.timeBetweenFrames();
			elf->setAnimation("WalkingN");
		}
		if (dInput.keyDown(engine::Input::KEY_G)) {
			fY -= fspeed * timer.timeBetweenFrames();
			elf->setAnimation("WalkingS");
		}
		if (dInput.keyDown(engine::Input::KEY_F)) {
			fX -= fspeed * timer.timeBetweenFrames();
			elf->setAnimation("WalkingW");
		}
		if (dInput.keyDown(engine::Input::KEY_H)) {
			fX += fspeed * timer.timeBetweenFrames();
			elf->setAnimation("WalkingE");
		}

		elf->setPos(fX, fY);

		if (elf->checkCollision(*asuna) != engine::Entity::NoCollision) {
			elf->returnToPreviousPos();
		}
		if (elf->checkCollision(*kris) != engine::Entity::NoCollision) {
			elf->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Stuff", elf) != engine::Entity::NoCollision) {
			elf->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Trees", elf) != engine::Entity::NoCollision) {
			elf->returnToPreviousPos();
		}
		if (tilemap->CollidesWith("Buildings", elf) != engine::Entity::NoCollision) {
			elf->returnToPreviousPos();
		}
	}

	if (cursor != NULL){
		cursor->setPos(cursor->posX() + dInput.mouseRelPosX(), cursor->posY() - dInput.mouseRelPosY());
		cursor->setAnimation("Idle");
	}

	wheel->setRotation(wheel->rotation() - fRot * timer.timeBetweenFrames());
	wheel->setAnimation("Idle");

	if (dInput.keyDown(engine::Input::KEY_ESCAPE))
		setGame(false);
}


void Game::DeInit(){
	if (asuna != NULL) delete asuna;
	if (kris != NULL) delete kris;
	if (wheel != NULL) delete wheel;
	if (cursor != NULL) delete cursor;
}
