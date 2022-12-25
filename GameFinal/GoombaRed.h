#pragma once
#include "GameObject.h"

#define REDGOOMBA_GRAVITY 0.001f
#define REDGOOMBA_WALKING_SPEED 0.05f
#define REDGOOMBA_DEFLECT_SPEED_JUMP 0.1f
#define REDGOOMBA_DEFLECT_SPEED_FLY	0.4f


#define REDGOOMBA_WING_BBOX_WIDTH 20
#define REDGOOMBA_WING_BBOX_HEIGHT 18
#define REDGOOMBA_FLY_BBOX_HEIGHT 18
#define REDGOOMBA_BBOX_WIDTH 16
#define REDGOOMBA_BBOX_HEIGHT 14
#define REDGOOMBA_BBOX_HEIGHT_DIE 7

#define REDGOOMBA_DIE_TIMEOUT 500

#define REDGOOMBA_STATE_WING_WALKING 100
#define REDGOOMBA_STATE_WING_JUMPFLY 200
#define REDGOOMBA_STATE_WING_FLY 300
#define REDGOOMBA_STATE_WALKING 400
#define REDGOOMBA_STATE_DIE 500
#define REDGOOMBA_STATE_DIE_T 600

#define ID_ANI_RED_GOOMBA_WING_WALKING 9000
#define ID_ANI_RED_GOOMBA_WING_JUMPFLY	9001
#define ID_ANI_RED_GOOMBA_WALKING	9002
#define ID_ANI_RED_GOOMBA_DIE	9003
#define ID_ANI_RED_GOOMBA_DIE_T 9004


#define TIMEWALKING 1000
#define TIMEJUMP 500
#define TIMEFLY 500


class CGoombaRed : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG timeJump;
	ULONGLONG timeFly;
	ULONGLONG timeWalking;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoombaRed(float x, float y);
	virtual void SetState(int state);
};