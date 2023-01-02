#include "Brick.h"
#include "Coin.h"
#include "debug.h"
#include "AssetIDs.h"
void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (!isPbuttonPressed)
	{
		animations->Get(ID_ANI_BRICK)->Render(x, y);
	}
	else
		animations->Get(ID_ANI_COIN)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isPbuttonPressed)
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		r = l + BRICK_BBOX_WIDTH;
		t = y - BRICK_BBOX_HEIGHT / 2;
		b = t + BRICK_BBOX_HEIGHT;
	}
	else
	{
		l = x - COIN_BBOX_WIDTH / 2;
		r = l + COIN_BBOX_WIDTH;
		t = y - BRICK_BBOX_HEIGHT / 2;
		b = t + BRICK_BBOX_HEIGHT;
	}

}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (state == BRICK_STATE_BROKEN)
	{
		
	}

	if (state == BRICK_STATE_CHANGE_COIN)
	{
		if (GetTickCount64() - timeChange > TIMEOUT_CHANGE_COIN)
		{
			SetState(BRICK_STATE_NORMAL);
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_NORMAL:
		isPbuttonPressed = false;
		break;
	case BRICK_STATE_BROKEN:
		b1->SetState(BROKEN_EFFECT_STATE_APPEAR);
		b2->SetState(BROKEN_EFFECT_STATE_APPEAR);
		b3->SetState(BROKEN_EFFECT_STATE_APPEAR_BOTTOM);
		b4->SetState(BROKEN_EFFECT_STATE_APPEAR_BOTTOM);
		isDeleted = true;
		break;
	case BRICK_STATE_CHANGE_COIN:
		isPbuttonPressed = true;
		timeChange = GetTickCount64();
		break;
	default:
		break;
	}
}