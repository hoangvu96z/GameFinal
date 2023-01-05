#include "FireBullet.h"


void FireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_BULLET_WIDTH / 2;
	right = left + FIRE_BULLET_WIDTH;
	top = y - FIRE_BULLET_HEIGHT / 2;
	bottom = top + FIRE_BULLET_HEIGHT;
}


void FireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FireBullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	/*if (vx < 0)
	{
		animations->Get(ID_ANI_FIRE_BULLET_LEFT)->Render(x, y);
	}
	else
		animations->Get(ID_ANI_FIRE_BULLET_RIGHT)->Render(x, y);*/

	animations->Get(ID_ANI_FIRE_BULLET_LEFT)->Render(x, y);
	RenderBoundingBox();
}