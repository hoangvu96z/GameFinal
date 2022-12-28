#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Tail.h"
#include "debug.h"


#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_RUNNING_MAXSPEED	0.5f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define  MARIO_FALLING_SLOWDOWN_SPEED 0.02f

#define MARIO_POWER_TIME_STACK 200

#define MARIO_TIME_SHOWING_FLYING 3000

#define MARIO_TIME_ATTACKING 240

#define MARIO_TIMEOUT_KICK 300

#define MARIO_MAX_POWER	6


#define MARIO_WIDTH_COLLISION 2 // define variable to scale range between small and big width

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_KICK	700
#define MARIO_STATE_FALLING_SLOWDOWN 800 
#define MARIO_STATE_FLYING	900
#define MARIO_STATE_ATTACK 1000
#define MARIO_STATE_HOLDING	1100
#define MARIO_STATE_RELEASE_HOLDING	1200
#define MARIO_STATE_RELEASE_HOLDING_A 1300


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICK_RIGHT	1701
#define ID_ANI_MARIO_KICK_LEFT	1700

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601


// RACOON MARIO
#define ID_ANI_MARIO_RACOON_IDLE_RIGHT 1800
#define ID_ANI_MARIO_RACOON_IDLE_LEFT 1801

#define ID_ANI_MARIO_RACOON_WALKING_RIGHT 1802
#define ID_ANI_MARIO_RACOON_WALKING_LEFT 1803

#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT 1804
#define ID_ANI_MARIO_RACOON_RUNNING_LEFT 1805

#define ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT 1806
#define ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT 1807

#define ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT 1808
#define ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT 1809

#define ID_ANI_MARIO_RACOON_SIT_RIGHT 1810
#define ID_ANI_MARIO_RACOON_SIT_LEFT 1811

#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 1812
#define ID_ANI_MARIO_RACOON_BRACE_LEFT 1813

#define ID_ANI_MARIO_RACOON_FALLING_RIGHT 1814
#define ID_ANI_MARIO_RACOON_FALLING_LEFT 1815

#define ID_ANI_MARIO_RACOON_JUMP_RUN_FALLING_RIGHT 1816
#define ID_ANI_MARIO_RACOON_JUMP_RUN_FALLING_LEFT 1817

#define ID_ANI_MARIO_RACOON_FALLING_SLOWDOWN_RIGHT 1818
#define ID_ANI_MARIO_RACOON_FALLING_SLOWDOWN_LEFT 1819

#define ID_ANI_MARIO_RACOON_ATTACKING_RIGHT 1820
#define ID_ANI_MARIO_RACOON_ATTACKING_LEFT 1821

#define ID_ANI_MARIO_RACOON_KICK_RIGHT 1822
#define ID_ANI_MARIO_RACOON_KICK_LEFT 1823

#define ID_ANI_MARIO_RACOON_FLYING_RIGHT 1824
#define ID_ANI_MARIO_RACOON_FLYING_LEFT 1825

#define ID_ANI_MARIO_RACOON_HOLDING_WALKING_RIGHT 1826
#define ID_ANI_MARIO_RACOON_HOLDING_WALKING_LEFT 1827

#define ID_ANI_MARIO_RACOON_HOLDING_IDLE_RIGHT 1828
#define ID_ANI_MARIO_RACOON_HOLDING_IDLE_LEFT 1829

#define ID_ANI_MARIO_RACOON_HOLDING_JUMP_RIGHT 1830
#define ID_ANI_MARIO_RACOON_HOLDING_JUMP_LEFT 1831
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_RACOON_BBOX_WIDTH	14
#define MARIO_RACOON_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  13
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16
#define MARIO_RACOON_SITTING_BBOX_WIDTH  13

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	bool isFalling;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;		// acceleration on y 
	static CMario* __instance;

	int level; 
	int untouchable; 
	bool isKicking;
	ULONGLONG untouchable_start;
	ULONGLONG timeKick;
	ULONGLONG timeStack;
	ULONGLONG timeFalling;
	ULONGLONG timeFlying;
	ULONGLONG timeAttacking;
	
	
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithColorBox(LPCOLLISIONEVENT e);
	void OnCollisionWithQB(LPCOLLISIONEVENT e);
	void OnCollisionWithB(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopasFly(LPCOLLISIONEVENT e);
	void OnCollisionWithRedGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIDRacoon();

public:
	int coin;
	bool isFlying;
	bool isAttacking;
	int powerStack;
	CTail* tail;
	BOOLEAN isOnPlatform;
	bool isHoldKoopas;
	static CMario* GetInstance();
	static void SetInstance(CMario* p);
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isKicking = isAttacking = isFlying = isHoldKoopas = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		level = MARIO_LEVEL_RACOON;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		type = 0;
		timeStack = timeAttacking = timeFlying = timeFalling = powerStack = 0;
		tail = NULL;
		
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	float GetPositionX() { return x; };
	float GetPositionY() { return y; };
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void IncreasePower();

	void DecreasePower();

	void SetPower();

	float GetAX() { return ax; }

	int Direct() { return this->nx; }

	bool CheckIsOnPlatForm() { return isOnPlatform; }

	void SetKoopas();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
};