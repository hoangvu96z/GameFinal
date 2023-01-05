#pragma once
#include "GameObject.h"
#include "FireBullet.h"
//---------------------------FIRE PLANT
#define ID_ANI_FirePlant_LEFT 10001
#define ID_ANI_FirePlant_RIGHT	10002
#define ID_ANI_FirePlant_UP_LEFT	10003
#define ID_ANI_FirePlant_UP_RIGHT	10004

//---------------------------FIRE GREEN PLANT
#define ID_ANI_Fire_GreenPlant_LEFT 10005
#define ID_ANI_Fire_GreenPlant_RIGHT	10006
#define ID_ANI_Fire_GreenPlant_UP_LEFT	10007
#define ID_ANI_Fire_GreenPlant_UP_RIGHT	10008

//----------------------------GREEN PLANT
#define ID_ANI_GreenPlant_MOUTH 10009

#define FirePlant_BBOX_WIDTH 16
#define FirePlant_BBOX_HEIGHT 32

#define GreenPlant_BBOX_WIDTH 16
#define GreenPlant_BBOX_HEIGHT 26

#define ATTACK_ZONE 150

#define CONST_X 6
#define CONST_Y 8


#define FirePlant_STATE_APPEAR	100
#define FirePlant_STATE_INPIPE	200
#define FirePlant_STATE_STOP_INPIPE	300
#define FirePlant_STATE_STOP_ONPIPE	400
#define FirePlant_STATE_FIRE	500

#define FirePlant_TIME 1000
#define FirePlant_TIME_APPEAR 3000
#define FirePlant_TIME_INPIPE	2000

#define Fire_GreenPlant_TIME_APPEAR 5000
#define Fire_GreenPlant_TIME_INPIPE	2000

#define	GreenPlant_TIME_APPEAR 3500
#define GreenPlant_TIME_INPIPE	2500

#define FirePlant_HEIGHT_OFFSET	46

#define Fire_GreenPlant_HEIGHT_OFFSET	30
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
	int typePlant;
	ULONGLONG timeWarp;
	ULONGLONG timeWarpAppear;
	ULONGLONG timeAttack;
	bool isPlantAttack = false;
	bool isAttack = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void AttackZone()
	{
		if (abs(x - Mario_x <= ATTACK_ZONE))
		{
			calAttack();
		}
	}

	void CreateBullet()
	{
		float BulletX, BulletY;
		if (!fb->isFire)
		{
			if (nx > 0)
			{
				fb->SetPosition(x + FirePlant_BBOX_WIDTH / 2 + CONST_X, y - CONST_Y);
			}
			else
				fb->SetPosition(x - FirePlant_BBOX_WIDTH / 2 - CONST_X, y - CONST_Y);
		}
	}

	void calAttack()
	{
		float vxBullet = 0, vyBullet = 0;

		CreateBullet();

		if (Mario_y < y)
			vyBullet = -VYBULLET;
		else
			vyBullet = VYBULLET;

		if (Mario_x > x)
		{
			vxBullet = VXBULLET;
			nx = 1;
		}
		else
		{
			vxBullet = -VXBULLET;
			nx = -1;
		}

		if (!fb->isFire)
		{
			fb->isFire = true;
			fb->SetSpeed(vxBullet, vyBullet);
			fb->SetState(BULLET_STATE_OUT_RANGE);
		}
	}
public:
	FireBullet* fb;
	CFirePlant(float x, float y, int typeF);
	virtual void SetState(int state);
};