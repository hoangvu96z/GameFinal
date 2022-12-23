#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MUSHROOM 12000


#define MUSHROOM_BBOX_WIDTH 15
#define MUSHROOM_BBOX_HEIGHT 15

#define MUSHROOM_STATE_APPEAR 100
#define MUSHROOM_STATE_COLLISION 0
#define MUSHROOM_STATE_MOVING	200

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f
#define MUSHROOM_DEFLECT 0.007f
class CMushroom : public CGameObject {
public:
	int firstY;
	float ax;
	float ay;

	CMushroom(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsCollidable() { return 1; };// 
	virtual int IsBlocking() { return 0; }
	virtual void SetState(int state);
};