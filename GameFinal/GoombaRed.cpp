#include "GoombaRed.h"
#include "Koopas.h"
#include "Mario.h"
CGoombaRed::CGoombaRed(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = REDGOOMBA_GRAVITY;
	die_start = -1;
	timeJump = 0;
	timeWalking = 0;
	timeFly = 0;
	SetState(REDGOOMBA_STATE_WING_WALKING);
}

void CGoombaRed::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == REDGOOMBA_STATE_DIE)
	{
		left = x - REDGOOMBA_BBOX_WIDTH / 2;
		top = y - REDGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + REDGOOMBA_BBOX_WIDTH;
		bottom = top + REDGOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == REDGOOMBA_STATE_WING_WALKING)
	{
		left = x - REDGOOMBA_WING_BBOX_WIDTH / 2;
		top = y - REDGOOMBA_WING_BBOX_HEIGHT / 2;
		right = left + REDGOOMBA_WING_BBOX_WIDTH;
		bottom = top + REDGOOMBA_WING_BBOX_HEIGHT;
	}
	else if (state == REDGOOMBA_STATE_WING_FLY || state == REDGOOMBA_STATE_WING_JUMPFLY) {
		left = x - REDGOOMBA_WING_BBOX_WIDTH / 2;
		top = y - REDGOOMBA_FLY_BBOX_HEIGHT / 2;
		right = left + REDGOOMBA_WING_BBOX_WIDTH;
		bottom = top + REDGOOMBA_FLY_BBOX_HEIGHT;
	}
	else
	{
		left = x - REDGOOMBA_BBOX_WIDTH / 2;
		top = y - REDGOOMBA_BBOX_HEIGHT / 2;
		right = left + REDGOOMBA_BBOX_WIDTH;
		bottom = top + REDGOOMBA_BBOX_HEIGHT;
	}
}

void CGoombaRed::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoombaRed::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoombaRed*>(e->obj)) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (state == REDGOOMBA_STATE_WING_JUMPFLY)
	{
		if (e->ny < 0) {
			vy -= REDGOOMBA_DEFLECT_SPEED_JUMP;
		}
	}
	else if (state == REDGOOMBA_STATE_WING_FLY)
	{
		if (e->ny < 0) {
			vy -= REDGOOMBA_DEFLECT_SPEED_FLY;
		}
	}
}

void CGoombaRed::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	float Mario_X = CMario::GetInstance()->GetPositionX();
	if (x > Mario_X) {
		nx = -1;
	}
	else
		nx = 1;


	if (state != REDGOOMBA_STATE_WALKING)
	{
		if (state == REDGOOMBA_STATE_WING_WALKING && (GetTickCount64() - timeWalking > TIMEWALKING))
		{
			SetState(REDGOOMBA_STATE_WING_JUMPFLY);
		}
		else if (state == REDGOOMBA_STATE_WING_JUMPFLY && (GetTickCount64() - timeJump > TIMEJUMP))
		{
			SetState(REDGOOMBA_STATE_WING_FLY);
		}
		else if (state == REDGOOMBA_STATE_WING_FLY && (GetTickCount64() - timeFly > TIMEFLY))
		{
			SetState(REDGOOMBA_STATE_WING_WALKING);
		}
	}

	if ((state == REDGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > REDGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if ((state == REDGOOMBA_STATE_DIE_T) && (GetTickCount64() - die_start > REDGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoombaRed::Render()
{
	int aniId = ID_ANI_RED_GOOMBA_WING_WALKING;
	if (state == REDGOOMBA_STATE_WING_WALKING) {
		aniId = ID_ANI_RED_GOOMBA_WING_WALKING;
	}
	else if (state == REDGOOMBA_STATE_WING_JUMPFLY || state == REDGOOMBA_STATE_WING_FLY)
	{
		aniId = ID_ANI_RED_GOOMBA_WING_JUMPFLY;
	}
	else if (state == REDGOOMBA_STATE_WALKING) {
		aniId = ID_ANI_RED_GOOMBA_WALKING;
	}
	else if(state == REDGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_RED_GOOMBA_DIE;
	}
	else {
		aniId = ID_ANI_RED_GOOMBA_DIE_T;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoombaRed::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case REDGOOMBA_STATE_WING_WALKING:
		timeWalking = GetTickCount64();
		vx = REDGOOMBA_WALKING_SPEED * nx;
		break;
	case REDGOOMBA_STATE_WING_JUMPFLY:
		timeJump = GetTickCount64();	
		break;
	case REDGOOMBA_STATE_WING_FLY:
		timeFly = GetTickCount64();
		break;
	case REDGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (REDGOOMBA_BBOX_HEIGHT - REDGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case REDGOOMBA_STATE_WALKING:
		vx = REDGOOMBA_WALKING_SPEED * nx;
		break;
	}
}