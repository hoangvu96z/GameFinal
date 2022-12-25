#include "GameObject.h"
#include "KoopasObject.h"
#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_SHELL_SPEED 0.2f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 28
#define KOOPAS_BBOX_HEIGHT_SHELL 16

#define KOOPAS_DIE_TIMEOUT 10000

#define KOOPAS_STATE_WALKING_LEFT 100
#define KOOPAS_STATE_WALKING_RIGHT 200
#define KOOPAS_STATE_SHELL 300
#define KOOPAS_STATE_SHELL_MOVING 400

#define ID_ANI_KOOPAS_WALKING_LEFT 7000
#define ID_ANI_KOOPAS_WALKING_RIGHT 7001
#define ID_ANI_KOOPAS_SHELL 7002
class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	int Direct;
	bool isCollision;
	ULONGLONG die_start;
	float objX;
	float objY;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithRedGoomba(LPCOLLISIONEVENT e);
	virtual int IsCollidable() { return 1; };

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);


	void ReturnLife();
	
		

public:
	KoopasObject* koo;
	CKoopas(float x, float y);
	virtual void SetState(int state);
};