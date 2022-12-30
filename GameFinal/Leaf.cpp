#include "Leaf.h"
#include "debug.h"

Leaf::Leaf(float x, float y) :Item(x, y, 0)
{
	item = ItemType::leaf;
	SetState(LEAF_STATE_APPEAR);
	ay = LEAF_GRAVITY;
	first_y = y;
	ax = 0;
}



void Leaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state != LEAF_STATE_APPEAR)
	{
		if (vx >= 0)
		{
			animations->Get(ID_ANI_LEAF_FALL_RIGHT)->Render(x, y);
		}
		else
			animations->Get(ID_ANI_LEAF_FALL_LEFT)->Render(x, y);
	}
	RenderBoundingBox();
}

void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	OnNoCollision(dt);
	if (state == LEAF_STATE_NORMAL)
	{
		if (first_y - y > 100)
		{
			SetState(LEAF_STATE_FALLING);
		}
	}

	if (state == LEAF_STATE_FALLING)
	{
		
		if (GetTickCount64() - timeFalling >= 700)
		{
			vx = -vx;
			timeFalling = GetTickCount64();
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Leaf::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void Leaf::SetState(int state) {

	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_NORMAL:
		vy = -0.1f;
		ax = 0;
		break;
	case LEAF_STATE_FALLING:
		vx = 0.01f;
		vy = 0.01f;
		timeFalling = GetTickCount64();
		break;
	default:
		break;
	}
}
void Leaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void Leaf::setDirectItem(int nx)
{
	this->nx = nx;
	SetState(LEAF_STATE_NORMAL);
}