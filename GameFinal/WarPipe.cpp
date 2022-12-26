#include "Warpipe.h"
#include "debug.h"
CWarpipe::CWarpipe(float x, float y) :CGameObject(x, y)
{
	first_y = y;
	second_y = y;
	SetState(WARPIPE_STATE_APPEAR);
}

void CWarpipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - WARPIPE_BBOX_WIDTH / 2;
		top = y - WARPIPE_BBOX_HEIGHT / 2;
		right = left + WARPIPE_BBOX_WIDTH;
		bottom = top + WARPIPE_BBOX_HEIGHT;
}

void CWarpipe::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CWarpipe::OnCollisionWith(LPCOLLISIONEVENT e)
{
	

}

void CWarpipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	
	if (state == WARPIPE_STATE_APPEAR)
	{
		if (y > first_y + 46) {
			SetState(WARPIPE_STATE_STOP_ONPIPE);
		}
	}
	else if (state == WARPIPE_STATE_INPIPE )
	{
		if (y < first_y  ) {
			SetState(WARPIPE_STATE_STOP_INPIPE);
		}
	}

	if (state == WARPIPE_STATE_STOP_ONPIPE)
	{
		if (GetTickCount64() - timeWarpAppear > 3000)
		{
			SetState(WARPIPE_STATE_INPIPE);
		}
	}
	else if (state == WARPIPE_STATE_STOP_INPIPE)
	{
		if (GetTickCount64() - timeWarp > 3000)
		{
			SetState(WARPIPE_STATE_APPEAR);
		}
	}


	DebugOut(L"state: %d\n", state);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CWarpipe::Render()
{


		int aniId = ID_ANI_WARPIPE_LEFT;
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
		RenderBoundingBox();
}

void CWarpipe::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WARPIPE_STATE_APPEAR:
		vy = 0.01;
		break;
	case WARPIPE_STATE_INPIPE:
		vy = -0.01;
		break;
	case WARPIPE_STATE_STOP_ONPIPE:
		vy = 0;
		timeWarpAppear = GetTickCount64();
	case WARPIPE_STATE_STOP_INPIPE:
		vy = 0;
		timeWarp = GetTickCount64();
		break;
	}
}