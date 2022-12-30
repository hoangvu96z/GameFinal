#include "Pbutton.h"
#include "debug.h"
void Pbutton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (state == PBUTTON_STATE_NORMAL)
	{
		animations->Get(ID_ANI_PBUTTON_NORMAL)->Render(x, y);
	}
	else if (state == PBUTTON_STATE_COLLISION)
	{
		animations->Get(ID_ANI_PBUTTON_ISPRESSED)->Render(x, y);
	}


	RenderBoundingBox();
}

void Pbutton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (state == PBUTTON_STATE_NORMAL)
	{
		if (first_y - y >= 13)
		{
			vy = 0;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Pbutton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x -	PBUTTON_BBOX_WIDTH / 2;
	r = l + PBUTTON_BBOX_WIDTH;
	if (state != PBUTTON_STATE_COLLISION)
	{
		t = y - PBUTTON_BBOX_HEIGHT_BIG / 2;
		b = t + PBUTTON_BBOX_HEIGHT_BIG / 2;
	}
	else
		t = y - PBUTTON_BBOX_HEIGHT_SMALL / 2;
		b = t + PBUTTON_BBOX_HEIGHT_SMALL / 2;
}

void Pbutton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PBUTTON_STATE_APPEAR:
		break;
	case PBUTTON_STATE_NORMAL:
		vy -= 0.2f;
		break;
	case PBUTTON_STATE_COLLISION:
		y += POSITION_Y;
		break;
	default:
		break;
	}
}

void Pbutton::setDirectItem(int nx)
{
	SetState(PBUTTON_STATE_NORMAL);
}