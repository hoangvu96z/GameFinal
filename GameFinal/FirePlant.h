#pragma once
#include "GameObject.h"


#define ID_ANI_FirePlant_LEFT 10000
#define ID_ANI_FirePlant_RIGHT	10001
#define ID_ANI_FirePlant_UP_LEFT	10002
#define ID_ANI_FirePlant_UP_RIGHT	10003

#define FirePlant_BBOX_WIDTH 16
#define FirePlant_BBOX_HEIGHT 32

#define FirePlant_STATE_APPEAR	100
#define FirePlant_STATE_INPIPE	200
#define FirePlant_STATE_STOP_INPIPE	300
#define FirePlant_STATE_STOP_ONPIPE	400

#define FirePlant_TIME 1000
#define FirePlant_TIME_APPEAR 5000
#define FirePlant_TIME_INPIPE	3000
#define FirePlant_HEIGHT_OFFSET	46
#define FirePlant_MOVING_SPEED_Y	0.01;
class CFirePlant : public CGameObject
{
protected:
	float ax;
	float ay;
	float first_y;
	float second_y;
	float Mario_x;
	float Mario_y;
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
	CFirePlant(float x, float y);
	virtual void SetState(int state);
};