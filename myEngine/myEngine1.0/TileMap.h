#pragma once
#include "myEngine_API.h"

#include "Entity.h"
#include <vector>
#include <map>

namespace engine{
	class Renderer;
	class Tile;
	class Scene;

	class MYENGINE_API TileMap {
		private:
			unsigned int m_uiCols;
			unsigned int m_uiRows;
			std::string m_sName;
			float m_fPositionX, m_fPositionY;
			float m_fTileHeight;
			float m_fTileWidth;

		public:
			std::vector<std::vector<Tile*>> m_vLayers;
			std::map<std::string, int> m_mCollisionLayers;

		public:
			//estas 3 funciones las llama el importer solo.
			void SetColRows(unsigned int uiCols, unsigned int uiRows);
			void AddTile(Tile* pkSprite, unsigned int uiLayerNumber);
			void AddLayer();

		public:
			TileMap(std::string sName);
			~TileMap();
			void Draw(Renderer* pkRenderer);
			void ScaleTiles(float Width, float Height);
			void ScaleMap(float width, float height);
			void SetPosition(const float& x, const float& y);
			std::string GetName();
			void AddCollisionLayer(std::string, int);
			Entity::CollisionResult CollidesWith(std::string, Entity*);
	};
}
