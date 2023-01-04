#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define TAIL_BBOX_WIDTH 8
#define TAIL_BBOX_HEIGHT 8

class CTail : public CGameObject {
public:
	int nx;
	CTail(float x, float y) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPGAMEOBJECT& e);
	void OnCollisionWithGoombaRed(LPGAMEOBJECT& e);
	void OnCollisionWithKoopas(LPGAMEOBJECT& e);
	void OnCollisionWithQB(LPGAMEOBJECT& e);
	void OnCollisionWithB(LPGAMEOBJECT& e);
	void SetDirect(int n) { this->nx = n; }
};