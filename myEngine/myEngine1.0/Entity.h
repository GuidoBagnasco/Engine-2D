#pragma once
#include "EMath.h"
#include <string>
#include "RenderTypes.h"
#include "myEngine_API.h"


namespace engine{
	class Renderer;
	class Timer;
	class MYENGINE_API Entity{
	public:
		Entity();
		~Entity();

	public:
		void setPos(float fPosX, float fPosY);
		void setRotation(float fRotation);
		void setScale(float fScale, float fScaleY);
		float posX() const;
		float posY() const;
		float rotation() const;
		float scaleX() const;
		float scaleY() const;

		void returnToPreviousPos();

		virtual void draw(Renderer&) const = 0;
		virtual void update(Timer&) { }

		enum CollisionResult{
			CollisionVertical,
			CollisionHorizontal,
			NoCollision
		};

		CollisionResult checkCollision(Entity& rkEntity2D) const;
		void Entity::drawAABB(Renderer& rkRenderer) const;
		const std::string& getCollisionGroup() const { return m_sColGroup; }
		void setCollisionGroup(std::string ColGroup) { m_sColGroup = ColGroup; }

		void setName(std::string n) { m_sName = n; }
		std::string getName() { return m_sName;  }

	private:
		float _PosX, _PosY;
		float _Rot;
		float _ScaleX;
		float _ScaleY;

		float m_fPrevPosX, m_fPrevPosY;
		std::string m_sColGroup;
		std::string m_sName;
		void updateLocalTransformation();

	protected:
		Matrix _TrMatrix;
	};
}