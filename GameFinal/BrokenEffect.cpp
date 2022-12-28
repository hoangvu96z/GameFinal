#include "BrokenEffect.h"
#include "debug.h"
void BrokenEffect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BROKEN_BBOX_WIDTH / 2;
	top = y - BROKEN_BBOX_HEIGHT / 2;
	right = left + BROKEN_BBOX_WIDTH;
	bottom = top + BROKEN_BBOX_HEIGHT;
}

void BrokenEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state != BROKEN_EFFECT_STATE_HIDDEN)
	{
		animations->Get(ID_ANI_BROKEN_EFFECT)->Render(x, y);
	}
	RenderBoundingBox();
}

void BrokenEffect::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void BrokenEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//vy += ay * dt;

	DebugOut(L"state: %d\n", state);
	if (state == BROKEN_EFFECT_STATE_APPEAR)
	{
		
		if (first_y - y > 30)
		{
			vx = 0.1f * nx;
			if (first_y - y > 70)
			{
				vy += ay * dt;
				if (GetTickCount64() - timeEffect > TIME_BROKEN_EFFECT)
				{
					//isDeleted = true;
				}
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void BrokenEffect::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BROKEN_EFFECT_STATE_HIDDEN:
		break;
	case BROKEN_EFFECT_STATE_APPEAR:
		DebugOut(L"HHELLO");
		vy = -0.2f;
		break;
	case BROKEN_EFFECT_STATE_DELETE:
		timeEffect = GetTickCount64();
		break;
	default:
		break;
	}
}