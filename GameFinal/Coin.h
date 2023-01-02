#pragma once

#include "Animation.h"
#include "Animations.h"
#include "Item.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_COLLISION 0
#define COIN_STATE_APPEAR 100
#define COIN_STATE_DISAPPEAR 200

#define TIME_COIN_APPEAR 1000
#define COIN_BOUNCING	0.02
#define MAX_Y	45
class CCoin : public Item {
public:
	int insideQB;
	ULONGLONG timeAppear = GetTickCount64();
	CCoin(float x, float y, int type) : Item(x, y, 0) { item = ItemType::Coin; first_y = y; SetState(COIN_STATE_COLLISION); insideQB = type; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual void SetState(int state);
	void setDirectItem(int nx) { SetState(COIN_STATE_APPEAR); };
};