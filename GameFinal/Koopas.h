#include "GameObject.h"
#include "KoopasObject.h"
#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_SHELL_SPEED 0.2f
#define KOOPAS_DEFLECT_SPEED_Y 0.5f

#define KOOPAS_DIE_SPEED	0.1f

#define KOOPAS_BBOX_WIDTH 14
#define KOOPAS_BBOX_HEIGHT 28
#define KOOPAS_BBOX_HEIGHT_SHELL 14

#define KOOPAS_DIE_TIMEOUT	8000
#define KOOPAS_RETURN_LIFE 2000
#define KOOPAS_TIME_COLLISION 100
#define KOOPAS_TIME_STOP_MOVING	500
#define KOOPAS_TIME_DIE	500


#define KOOPAS_STATE_WALKING 200
#define KOOPAS_STATE_SHELL 300
#define KOOPAS_STATE_SHELL_MOVING 400
#define	KOOPAS_STATE_REBORN	500
#define KOOPAS_STATE_SHELL_UP	600
#define KOOPAS_STATE_SHELL_UP_MOVING 700
#define	KOOPAS_STATE_REBORN_UP	800
#define KOOPAS_STATE_DIE	900




#define ID_ANI_KOOPAS_WALKING_LEFT 7000
#define ID_ANI_KOOPAS_WALKING_RIGHT 7001
#define ID_ANI_KOOPAS_SHELL 7002
#define ID_ANI_KOOPAS_SHELL_MOVING 7003
#define ID_ANI_KOOPAS_SHELL_RETURN	7004
#define ID_ANI_KOOPAS_SHELL_UP	7005
#define ID_ANI_KOOPAS_SHELL_UP_MOVING	7006
#define ID_ANI_KOOPAS_SHELL_UP_RETURN	7007

class CKoopas : public CGameObject
{
protected:
	float ax;
	int Direct;
	ULONGLONG TimeCollision;
	ULONGLONG timeReturn;
	ULONGLONG die_start;
	ULONGLONG timeDie;
	ULONGLONG shell_start;
	ULONGLONG timeMoving;
	float objX;
	float objY;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithRedGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQB(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	virtual int IsCollidable() { return (state != KOOPAS_STATE_DIE); };

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);


	void ReturnLife();
	
		

public:
	KoopasObject* koo;
	CKoopas(float x, float y);
	virtual void SetState(int state);
	void SetDirect(int n) { this->nx = n; }
	bool isCollision;
	int nx;
	float ay;
	bool isHold;
};