#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define TAIL_BBOX_WIDTH 8
#define TAIL_BBOX_HEIGHT 8

class CTail : public CGameObject {
public:
	CTail(float x, float y) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithQB(LPCOLLISIONEVENT e);
	void OnCollisionWithB(LPCOLLISIONEVENT e);
	void SetDirect(int n) { this->nx = n; }
};