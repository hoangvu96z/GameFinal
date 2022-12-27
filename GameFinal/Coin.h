#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_APPEAR 100
#define COIN_STATE_DISAPPEAR 200

#define TIME_COIN_APPEAR 1000
#define COIN_BOUNCING	0.1
#define MAX_Y	35
class CCoin : public CGameObject {
public:
	int firstY;
	ULONGLONG timeAppear = GetTickCount64();
	CCoin(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual void SetState(int state);
};