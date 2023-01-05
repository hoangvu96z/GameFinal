#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Animation.h"

#define FIRE_BULLET_WIDTH	8	
#define FIRE_BULLET_HEIGHT	8

#define ID_ANI_FIRE_BULLET_LEFT	16000
#define ID_ANI_FIRE_BULLET_RIGHT	16001

#define VXBULLET 0.1f
#define VYBULLET 0.05f

#define BULLET_STATE_OUT_RANGE	0

#define TIME_DELETE_BULLET	2000
class FireBullet : public CGameObject
{
public:
	bool isFire = false;
	ULONGLONG timeDelete;
	FireBullet(float x, float y) : CGameObject(x, y) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void SetState(int state);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};
