#include "KoopasFly.h"
#include "Goomba.h"
#include "debug.h"
#include "Collision.h"

CKoopasFly::CKoopasFly(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPASFLY_GRAVITY;
	SetState(KOOPASFLY_STATE_JUMPFLY);
	isCollision = false;
}

void CKoopasFly::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPASFLY_STATE_SHELL || state == KOOPASFLY_STATE_SHELL_MOVING)
	{
		left = x - KOOPASFLY_BBOX_WIDTH / 2;
		top = y - KOOPASFLY_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPASFLY_BBOX_WIDTH;
		bottom = top + KOOPASFLY_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPASFLY_BBOX_WIDTH / 2;
		top = y - KOOPASFLY_BBOX_HEIGHT / 2;
		right = left + KOOPASFLY_BBOX_WIDTH;
		bottom = top + KOOPASFLY_BBOX_HEIGHT;
	}
}

void CKoopasFly::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopasFly::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopasFly*>(e->obj)) return;


	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;

	}
	//
	/*if (state == KOOPASFLY_STATE_JUMPFLY)
	{
		if (e->ny < 0) {
			vy -= KOOPASFLY_DEFLECT_JUMP_SPEED;
		}
	}*/


	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);


}

void CKoopasFly::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	CGoomba* gb = dynamic_cast<CGoomba*>(e->obj);
	if (state == KOOPASFLY_STATE_SHELL_MOVING)
	{
		DebugOut(L"state: %d\n", state);
		if (e->nx != 0)
		{
			if (gb->GetState() != GOOMBA_STATE_DIE)
			{
				gb->SetState(GOOMBA_STATE_DIE);
			}
		}
	}
}

void CKoopasFly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	

	if ((state == KOOPASFLY_STATE_SHELL) && GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT)
	{
		SetState(KOOPASFLY_STATE_JUMPFLY);
		ReturnLife();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopasFly::Render()
{
	int aniId = ID_ANI_KOOPASFLY_JUMPFLY_RIGHT;
	if (vx > 0) {
		aniId = ID_ANI_KOOPASFLY_JUMPFLY_RIGHT;
	}
	else
		aniId = ID_ANI_KOOPASFLY_JUMPFLY_LEFT;

	if (state == KOOPASFLY_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPASFLY_SHELL;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopasFly::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPASFLY_STATE_SHELL:
		y += (KOOPASFLY_BBOX_HEIGHT - KOOPASFLY_BBOX_HEIGHT_SHELL) / 2;
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		break;
	case KOOPASFLY_STATE_JUMPFLY:
		vx = KOOPASFLY_WALKING_SPEED * nx;
		break;
	case KOOPASFLY_STATE_SHELL_MOVING:
		//vx = KOOPASFLY_SHELL_SPEED;
		break;

	}
}

void CKoopasFly::ReturnLife()
{
	die_start = 0;
	if (state == KOOPASFLY_STATE_WALKING_RIGHT || state == KOOPASFLY_STATE_WALKING_LEFT)
	{
		y -= (KOOPASFLY_BBOX_HEIGHT - KOOPASFLY_BBOX_HEIGHT_SHELL) / 2;
	}

}