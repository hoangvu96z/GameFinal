#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (state == BRICK_STATE_BROKEN)
	{
		b1->SetState(BROKEN_EFFECT_STATE_APPEAR);
		b2->SetState(BROKEN_EFFECT_STATE_APPEAR);
		b3->SetState(BROKEN_EFFECT_STATE_APPEAR_BOTTOM);
		b4->SetState(BROKEN_EFFECT_STATE_APPEAR_BOTTOM);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_BROKEN:
		isDeleted = true;
		break;
	default:
		break;
	}
}