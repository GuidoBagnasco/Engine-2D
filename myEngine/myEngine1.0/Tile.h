#pragma once
//------------------------------------------------
#include "Sprite.h"
#include "animation.h"
#include "myEngine_API.h"
//------------------------------------------------
namespace engine{
	class MYENGINE_API Tile : public Sprite
	{
		public:
			unsigned int width;
			unsigned int height;
			Tile(int id, int w, int h):m_iID(id),width(w),height(h){}
			void Draw(Renderer *m_pkRenderer){ 
				Sprite::draw(*m_pkRenderer);
			}
			int getID() { return m_iID; }
			~Tile() {}

		private:
			int m_iID;
		};
}
//------------------------------------------------