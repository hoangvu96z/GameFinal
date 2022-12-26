#pragma once
#include "GameObject.h"


#define ID_ANI_WARPIPE_LEFT 10000
#define ID_ANI_WARPIPE_RIGHT	10001	

#define WARPIPE_BBOX_WIDTH 16
#define WARPIPE_BBOX_HEIGHT 32

#define WARPIPE_STATE_APPEAR	100
#define WARPIPE_STATE_INPIPE	200
#define WARPIPE_STATE_STOP_INPIPE	300
#define WARPIPE_STATE_STOP_ONPIPE	400

#define WARPIPE_TIME 1000
class CWarpipe : public CGameObject
{
protected:
	float ax;
	float ay;
	float first_y;
	float second_y;
	ULONGLONG timeWarp;
	ULONGLONG timeWarpAppear;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CWarpipe(float x, float y);
	virtual void SetState(int state);
};