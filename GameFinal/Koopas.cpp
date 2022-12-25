#include "Koopas.h"
#include "Goomba.h"
#include "GoombaRed.h"
#include "debug.h"
#include "Collision.h"
#include "QuestionBrick.h"

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
	if (state == KOOPAS_STATE_WALKING_RIGHT || state== KOOPAS_STATE_WALKING_LEFT)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_SHELL;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CGoomba* gb = dynamic_cast<CGoomba*>(e->obj);
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
		else if (dynamic_cast<CQuestionBrick*>(e->obj))
			OnCollisionWithQB(e);
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0 && isCollision==false)
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
				isCollision = true;
				TimeCollision = GetTickCount64();
				if (vx != 0) {
					gb->SetSpeed(vx, 0);
				}

			}
		}
		else if (e->ny < 0)
		{
			if (gb->GetState() != GOOMBA_STATE_DIE)
			{
				gb->SetState(GOOMBA_STATE_DIE);
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
				isCollision = true;
				TimeCollision = GetTickCount64();

			}
		}
	}
}

void CKoopas::OnCollisionWithQB(LPCOLLISIONEVENT e) {
	CQuestionBrick* qb = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->nx != 0) {
		qb->SetState(QUESTIONBRICK_STATE_COLISION);
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
	
	if ((state == KOOPAS_STATE_SHELL) && GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT )
	{
		SetState(KOOPAS_STATE_REBORN);
	}
	else if (state == KOOPAS_STATE_REBORN && GetTickCount64() - timeReturn > KOOPAS_RETURN_LIFE)
	{
		ReturnLife();
	}
	else if (state == KOOPAS_STATE_SHELL_MOVING)
	{
		if (GetTickCount64() - shell_start > KOOPAS_DIE_TIMEOUT)
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
		else if (GetTickCount64() - TimeCollision > 100)
		{
			isCollision = false;
		}
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

	if (state == KOOPAS_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPAS_SHELL;
	}
	else if (state == KOOPAS_STATE_SHELL_MOVING)
	{
		aniId = ID_ANI_KOOPAS_SHELL_MOVING;
	}
	else if (state == KOOPAS_STATE_REBORN) {
		aniId = ID_ANI_KOOPAS_SHELL_RETURN;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
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
		shell_start = GetTickCount64();
		break;
	case KOOPAS_STATE_REBORN:
		timeReturn = GetTickCount64();
		break;
	}
}

void CKoopas::ReturnLife()
{
	die_start = 0;
	SetState(KOOPAS_STATE_WALKING_RIGHT);
	if (state == KOOPAS_STATE_WALKING_RIGHT || state == KOOPAS_STATE_WALKING_LEFT)
	{
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL) / 2;
	}
	
}