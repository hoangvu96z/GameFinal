#include "Coin.h"
#include "debug.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

		animations->Get(ID_ANI_COIN)->Render(x, y);


	RenderBoundingBox();
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	y += vy * dt;
	if (state == COIN_STATE_APPEAR)
	{
		if (y < first_y - MAX_Y) {
			y = COIN_BOUNCING ;
			
			if (GetTickCount64() - timeAppear >= TIME_COIN_APPEAR)
			{
				SetState(COIN_STATE_DISAPPEAR);
				timeAppear = 0;
			}
			
		}
	}
	CGameObject::Update(dt, coObjects);
}

void CCoin::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_APPEAR:
		vy -= COIN_BOUNCING;
		break;
	case COIN_STATE_DISAPPEAR:
		isDeleted = true;
		break;
	default:
		break;
	}
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}