#include "Tail.h"
#include "Goomba.h"
#include"GoombaRed.h"
#include "QuestionBrick.h"
#include "Koopas.h"
#include "Mario.h"
#include "Brick.h"
#include "debug.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = left + TAIL_BBOX_WIDTH + 2;
	bottom = top + TAIL_BBOX_HEIGHT;
}

void CTail::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}


void CTail::OnCollisionWith(LPCOLLISIONEVENT e) {

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQB(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithB(e);

}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* gb = dynamic_cast<CGoomba*>(e->obj);
	if (CMario::GetInstance()->isAttacking)
	{
		gb->SetState(GOOMBA_STATE_DIE_BY_ATTACKING);
		if (CMario::GetInstance()->Direct() == 1)
		{
			gb->SetSpeed(GOOMBA_REFLECT_BY_ATTACKING_SPEED, 0);
		}
		else
			gb->SetSpeed(-GOOMBA_REFLECT_BY_ATTACKING_SPEED, 0);
	}

}

void CTail::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* kp = dynamic_cast<CKoopas*>(e->obj);
	if (CMario::GetInstance()->isAttacking)
	{
		kp->SetState(KOOPAS_STATE_SHELL_UP);
	}

}

void CTail::OnCollisionWithQB(LPCOLLISIONEVENT e)
{
	CQuestionBrick* qb = dynamic_cast<CQuestionBrick*>(e->obj);
	qb->SetState(QUESTIONBRICK_STATE_COLISION);
	
	
}

void CTail::OnCollisionWithB(LPCOLLISIONEVENT e)
{
	CBrick* qb = dynamic_cast<CBrick*>(e->obj);
	qb->SetState(BRICK_STATE_BROKEN);


}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	
	//CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::Render()
{
	RenderBoundingBox();
}