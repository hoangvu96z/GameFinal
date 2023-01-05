#include "FireBullet.h"
#include "Mario.h"

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

	if (state == BULLET_STATE_OUT_RANGE)
	{
		if (GetTickCount64() - timeDelete > TIME_DELETE_BULLET)
		{
			isFire = false;
		}
	}

	//CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FireBullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (vx < 0)
	{
		animations->Get(ID_ANI_FIRE_BULLET_LEFT)->Render(x, y);
	}
	else
		animations->Get(ID_ANI_FIRE_BULLET_RIGHT)->Render(x, y);

	animations->Get(ID_ANI_FIRE_BULLET_LEFT)->Render(x, y);
	RenderBoundingBox();
}

void FireBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->obj);
	if (e->nx != 0 || e->ny != 0)
	{
		// mario->CollisionMario();
	}
}

void FireBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_OUT_RANGE:
		timeDelete = GetTickCount64();
		break;
	}
}