#include "Koopas.h"
#include "Goomba.h"
#include "GoombaRed.h"
#include "debug.h"
#include "Collision.h"

CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	SetState(KOOPAS_STATE_WALKING_LEFT);
	isCollision = false;
	koo = new KoopasObject(x, y);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_SHELL || state== KOOPAS_STATE_SHELL_MOVING)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (state != KOOPAS_STATE_SHELL_MOVING)
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CKoopas*>(e->obj)) return;
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
	else if (state == KOOPAS_STATE_SHELL_MOVING) {
		if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CGoombaRed*>(e->obj))
			OnCollisionWithRedGoomba(e);
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;

		}
		
	}

	
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	CGoomba* gb = dynamic_cast<CGoomba*>(e->obj);
	if (state == KOOPAS_STATE_SHELL_MOVING)
	{
		if (e->nx != 0)
		{
			if (gb->GetState() != GOOMBA_STATE_DIE_BY_ATTACKING)
			{
				gb->SetState(GOOMBA_STATE_DIE_BY_ATTACKING);
				
			}
		}
	}
}

void CKoopas::OnCollisionWithRedGoomba(LPCOLLISIONEVENT e) {
	CGoombaRed* rgb = dynamic_cast<CGoombaRed*>(e->obj);
	if (state == KOOPAS_STATE_SHELL_MOVING)
	{
		if (e->nx != 0)
		{
			if (rgb->GetState() != REDGOOMBA_STATE_DIE_T)
			{
				rgb->SetState(REDGOOMBA_STATE_DIE_T);

			}
		}
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (state == KOOPAS_STATE_WALKING_RIGHT || state == KOOPAS_STATE_WALKING_LEFT)
	{
		if (vx > 0) {
			koo->SetPosition(x + KOOPAS_BBOX_WIDTH, y);
		}
		else
		{
			koo->SetPosition(x - KOOPAS_BBOX_WIDTH, y);
		}
		koo->Update(dt, coObjects);
		koo->GetPosition(objX, objY);
		if (objY >= y + 1) {
			vx = -vx;
		}
		
	}
	else if (state == KOOPAS_STATE_SHELL_MOVING) {
		
	}

	
	if ((state == KOOPAS_STATE_SHELL) && GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT )
	{
		SetState(KOOPAS_STATE_WALKING_RIGHT);
		ReturnLife();
	}

	if ((state == KOOPAS_STATE_SHELL_MOVING) && GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT)
	{
		if (vx > 0)
		{
			SetState(KOOPAS_STATE_WALKING_RIGHT);
		}
		else {
			SetState(KOOPAS_STATE_WALKING_LEFT);
		}
		ReturnLife();
	}
	CGameObject::Update(dt, coObjects);
	
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	if (vx > 0) {
		aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	}
	else
		aniId = ID_ANI_KOOPAS_WALKING_LEFT;

	if (state == KOOPAS_STATE_SHELL || state== KOOPAS_STATE_SHELL_MOVING)
	{
		aniId = ID_ANI_KOOPAS_SHELL;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//koo->Render();
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL) / 2;
		die_start = GetTickCount64();
		vx = 0;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		nx = 1;
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPAS_STATE_SHELL_MOVING:
		vx = KOOPAS_SHELL_SPEED * nx;
		break;
	}
}

void CKoopas::ReturnLife()
{
	die_start = 0;
	if (state == KOOPAS_STATE_WALKING_RIGHT || state == KOOPAS_STATE_WALKING_LEFT)
	{
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL) / 2;
	}
	
}