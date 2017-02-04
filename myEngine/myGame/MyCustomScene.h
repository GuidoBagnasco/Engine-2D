#include "Scene.h"
#include "timer\Timer.h"
#include <iostream>

namespace MyGame {
	class MyCustomScene : public engine::Scene{
		public:
			MyCustomScene(std::string);
			~MyCustomScene();

			virtual void OnStart();
			virtual void OnUpdate(engine::Timer*);
			virtual void OnShutdown();
	};
}