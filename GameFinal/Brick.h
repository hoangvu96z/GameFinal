#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "BrokenEffect.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_NORMAL	0
#define BRICK_STATE_BROKEN 100
class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) { SetState(BRICK_STATE_NORMAL); }
	BrokenEffect* b1;
	BrokenEffect* b2;
	BrokenEffect* b3;
	BrokenEffect* b4;
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};