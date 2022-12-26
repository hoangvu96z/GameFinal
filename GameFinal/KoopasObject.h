#include "GameObject.h"
#define KOOPAS_OBJECT_GRAVITY 0.002f
#define KOOPAS_OBJECT_WALKING_SPEED 0.05f


#define KOOPAS_OBJECT_BBOX_WIDTH 16
#define KOOPAS_OBJECT_BBOX_HEIGHT 28
class KoopasObject : public CGameObject
{
public:
	KoopasObject(float x, float y);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };

	virtual int IsBlocking() { return 0; };

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	
};