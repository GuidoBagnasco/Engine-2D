#pragma once
#include "Game.h"
#include "Entity.h"
#include "Quad.h"
#include "Sprite.h"
#include "RenderTypes.h"
#include "Renderer.h"
#include "input\DirectInput.h"
#include "timer\Timer.h"

namespace MyGame {
	class Game : public engine::Game{
		public:
			bool Init(engine::Renderer&);
			void Frame(engine::Renderer&, engine::DirectInput&, engine::Timer&);
			void DeInit();

		private:
			engine::Quad _Cube1;
			engine::Quad _Cube2;
			engine::Sprite* asuna;
			engine::Sprite* kris;
			engine::Sprite* elf;
			engine::Sprite* wheel;
			engine::Sprite* cursor;
	};
}