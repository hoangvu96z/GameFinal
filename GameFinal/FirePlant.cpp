#include "FirePlant.h"
#include "Mario.h"
#include "debug.h"
CFirePlant::CFirePlant(float x, float y, int typeF) :CGameObject(x, y)
{
	first_y = y;
	second_y = y;
	SetState(FirePlant_STATE_APPEAR);
	typePlant = typeF;
}

void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (typePlant < 2)
	{
		left = x - FirePlant_BBOX_WIDTH / 2;
		top = y - FirePlant_BBOX_HEIGHT / 2;
		right = left + FirePlant_BBOX_WIDTH;
		bottom = top + FirePlant_BBOX_HEIGHT;
	}
	else
	{
		left = x - GreenPlant_BBOX_WIDTH / 2;
		top = y - GreenPlant_BBOX_HEIGHT / 2;
		right = left + GreenPlant_BBOX_WIDTH;
		bottom = top + GreenPlant_BBOX_HEIGHT;
	}
}

void CFirePlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFirePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	

}

void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	Mario_x = CMario::GetInstance()->GetPositionX();
	Mario_y = CMario::GetInstance()->GetPositionY();
	if (Mario_x >= this->x) {
		nx = 1;
	}
	else {
		nx = -1;
	}

	if (typePlant == 0)
	{
		if (state == FirePlant_STATE_APPEAR)
		{
			if (y > first_y + FirePlant_HEIGHT_OFFSET) {
				SetState(FirePlant_STATE_STOP_ONPIPE);
			}
		}
		else if (state == FirePlant_STATE_INPIPE)
		{
			if (y < first_y) {
				SetState(FirePlant_STATE_STOP_INPIPE);
			}
		}

		if (state == FirePlant_STATE_STOP_ONPIPE)
		{
			if (GetTickCount64() - timeWarpAppear > FirePlant_TIME_APPEAR)
			{
				SetState(FirePlant_STATE_INPIPE);
			}
		}
		else if (state == FirePlant_STATE_STOP_INPIPE)
		{
			if (GetTickCount64() - timeWarp > FirePlant_TIME_INPIPE)
			{
				SetState(FirePlant_STATE_APPEAR);
			}
		}
	}
	else if(typePlant == 1)
	{
		if (state == FirePlant_STATE_APPEAR)
		{
			if (y > first_y + Fire_GreenPlant_HEIGHT_OFFSET) {
				SetState(FirePlant_STATE_STOP_ONPIPE);
			}
		}
		else if (state == FirePlant_STATE_INPIPE)
		{
			if (y < first_y) {
				SetState(FirePlant_STATE_STOP_INPIPE);
			}
		}

		if (state == FirePlant_STATE_STOP_ONPIPE)
		{
			if (GetTickCount64() - timeWarpAppear > Fire_GreenPlant_TIME_APPEAR)
			{
				SetState(FirePlant_STATE_INPIPE);
			}
		}
		else if (state == FirePlant_STATE_STOP_INPIPE)
		{
			if (GetTickCount64() - timeWarp > Fire_GreenPlant_TIME_INPIPE)
			{
				SetState(FirePlant_STATE_APPEAR);
			}
		}
	}
	else
	{
		if (state == FirePlant_STATE_APPEAR)
		{
			if (y > first_y + Fire_GreenPlant_HEIGHT_OFFSET) {
				SetState(FirePlant_STATE_STOP_ONPIPE);
			}
		}
		else if (state == FirePlant_STATE_INPIPE)
		{
			if (y < first_y) {
				SetState(FirePlant_STATE_STOP_INPIPE);
			}
		}

		if (state == FirePlant_STATE_STOP_ONPIPE)
		{
			if (GetTickCount64() - timeWarpAppear > GreenPlant_TIME_APPEAR)
			{
				SetState(FirePlant_STATE_INPIPE);
			}
		}
		else if (state == FirePlant_STATE_STOP_INPIPE)
		{
			if (GetTickCount64() - timeWarp > GreenPlant_TIME_INPIPE)
			{
				SetState(FirePlant_STATE_APPEAR);
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFirePlant::Render()
{
	int aniId = -1;
	if (typePlant == 0)
	{
		if (nx > 0)
		{
			if (Mario_y < y) {
				aniId = ID_ANI_FirePlant_UP_RIGHT;
			}
			else
				aniId = ID_ANI_FirePlant_RIGHT;
		}
		else
		{
			if (Mario_y < y)
			{
				aniId = ID_ANI_FirePlant_UP_LEFT;
			}
			else
				aniId = ID_ANI_FirePlant_LEFT;
		}
	}
	else if (typePlant == 1)
	{
		if (nx > 0)
		{
			if (Mario_y < y) {
				aniId = ID_ANI_Fire_GreenPlant_UP_RIGHT;
			}
			else
				aniId = ID_ANI_Fire_GreenPlant_RIGHT;
		}
		else
		{
			if (Mario_y < y)
			{
				aniId = ID_ANI_Fire_GreenPlant_UP_LEFT;
			}
			else
				aniId = ID_ANI_Fire_GreenPlant_LEFT;
		}
	}
	else
	{
		aniId = ID_ANI_GreenPlant_MOUTH;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFirePlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FirePlant_STATE_APPEAR:
		vy = FirePlant_MOVING_SPEED_Y;
		break;
	case FirePlant_STATE_INPIPE:
		vy = -FirePlant_MOVING_SPEED_Y;
		break;
	case FirePlant_STATE_STOP_ONPIPE:
		vy = 0;
		timeWarpAppear = GetTickCount64();
	case FirePlant_STATE_STOP_INPIPE:
		vy = 0;
		timeWarp = GetTickCount64();
		break;
	}
}