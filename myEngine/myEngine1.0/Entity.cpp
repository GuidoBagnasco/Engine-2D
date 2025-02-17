#define NOMINMAX
#include <algorithm>
#include "Entity.h"
#include "Renderer.h"
#include <d3dx9.h>
using namespace engine;

Entity::Entity() :
_PosX(0.0f),
_PosY(0.0f),
_Rot(0.0f),
_ScaleX(1.0f),
_ScaleY(1.0f),
m_fPrevPosX(0.0f),
m_fPrevPosY(0.0f),
m_sColGroup(""),
m_sName(""),
_TrMatrix(new D3DXMATRIX()){
	updateLocalTransformation();
}

Entity::~Entity(){
	delete _TrMatrix;
	_TrMatrix = NULL;

}

void Entity::setPos(float fPosX, float fPosY){
	m_fPrevPosX = _PosX;
	m_fPrevPosY = _PosY;
	
	_PosX = fPosX;
	_PosY = fPosY;

	updateLocalTransformation();
}

float Entity::posX() const{
	return _PosX;
}

float Entity::posY() const{
	return _PosY;
}

float Entity::scaleX() const {
	return _ScaleX;
}

float Entity::scaleY() const{
	return _ScaleY;
}

float Entity::rotation() const{
	return _Rot;
}

void Entity::setRotation(float fRotation){
	_Rot = fRotation;
	updateLocalTransformation();
}

void Entity::setScale(float fScale, float fScaleY){
	_ScaleX = fScale;
	_ScaleY = fScaleY;
	updateLocalTransformation();
}

void Entity::returnToPreviousPos(){
	_PosX = m_fPrevPosX;
	_PosY = m_fPrevPosY;

	updateLocalTransformation();
}

void Entity::updateLocalTransformation(){
	D3DXMATRIX translateMatrix;
	D3DXMatrixTranslation(&translateMatrix, _PosX, _PosY, 0);

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationZ(&rotationMatrix, _Rot);

	D3DXMATRIX scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, _ScaleX, _ScaleY, 1);

	D3DXMatrixIdentity(_TrMatrix);
	D3DXMatrixMultiply(_TrMatrix, &translateMatrix, _TrMatrix);
	D3DXMatrixMultiply(_TrMatrix, &rotationMatrix, _TrMatrix);
	D3DXMatrixMultiply(_TrMatrix, &scaleMatrix, _TrMatrix);

}

Entity::CollisionResult Entity::checkCollision(Entity& rkEntity2D) const{
	float fOverlapX = std::max(0.0f,
		std::min(posX() + fabs(scaleX()) / 2.0f, rkEntity2D.posX() + fabs(rkEntity2D.scaleX()) / 2.0f) -
		std::max(posX() - fabs(scaleX()) / 2.0f, rkEntity2D.posX() - fabs(rkEntity2D.scaleX()) / 2.0f)
		);
	float fOverlapY = std::max(0.0f,
		std::min(posY() + fabs(scaleY()) / 2.0f, rkEntity2D.posY() + fabs(rkEntity2D.scaleY()) / 2.0f) -
		std::max(posY() - fabs(scaleY()) / 2.0f, rkEntity2D.posY() - fabs(rkEntity2D.scaleY()) / 2.0f)
		);

	if (fOverlapX != 0.0f && fOverlapY != 0.0f){
		if (fOverlapX > fOverlapY){
			return CollisionVertical;
		}
		else{
			return CollisionHorizontal;
		}
	}

	return NoCollision;
}

void Entity::drawAABB(Renderer& rkRenderer) const{
	static ColorVertex s_akAABBVertices[5];
	static bool s_bIsInitialized = false;
	if (!s_bIsInitialized){
		s_bIsInitialized = true;

		s_akAABBVertices[0].x = -0.5;	s_akAABBVertices[0].y = -0.5;	s_akAABBVertices[0].z = 0.0; s_akAABBVertices[0].color = engine_COLOR_RGB(255, 50, 50);
		s_akAABBVertices[1].x = -0.5;	s_akAABBVertices[1].y = 0.5;	s_akAABBVertices[1].z = 0.0; s_akAABBVertices[1].color = engine_COLOR_RGB(255, 70, 70);
		s_akAABBVertices[2].x = 0.5;	s_akAABBVertices[2].y = 0.5;	s_akAABBVertices[2].z = 0.0; s_akAABBVertices[2].color = engine_COLOR_RGB(255, 30, 30);
		s_akAABBVertices[3].x = 0.5;	s_akAABBVertices[3].y = -0.5;	s_akAABBVertices[3].z = 0.0; s_akAABBVertices[3].color = engine_COLOR_RGB(255, 15, 15);
		s_akAABBVertices[4].x = -0.5;	s_akAABBVertices[4].y = -0.5;	s_akAABBVertices[4].z = 0.0; s_akAABBVertices[4].color = engine_COLOR_RGB(255, 95, 90);
	}

	rkRenderer.setCurrentTexture(NoTexture);
	rkRenderer.setMatrix(World, _TrMatrix);
	rkRenderer.Draw(s_akAABBVertices, engine::LineStrip, 5);
}