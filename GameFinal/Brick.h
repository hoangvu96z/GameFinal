#pragma once
#include "AssetIDs.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "BrokenEffect.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define TIMEOUT_CHANGE_COIN 6000

#define BRICK_STATE_NORMAL	0
#define BRICK_STATE_BROKEN 100
#define BRICK_STATE_CHANGE_COIN	200
#define BRICK_STATE_COLLISION	300
class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) { SetState(BRICK_STATE_NORMAL); type = OBJECT_TYPE_BRICK; }
	BrokenEffect* b1;
	BrokenEffect* b2;
	BrokenEffect* b3;
	BrokenEffect* b4;
	ULONGLONG timeChange;
	bool isPbuttonPressed = false;
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	int IsBlocking() { return (state != BRICK_STATE_CHANGE_COIN); }
	virtual int IsCollidable() { return 1; };

};