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

	

}

void CTail::OnCollisionWithGoomba(LPGAMEOBJECT& e)
{
	CGoomba* gb = dynamic_cast<CGoomba*>(e);
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

void CTail::OnCollisionWithKoopas(LPGAMEOBJECT& e)
{
	CKoopas* kp = dynamic_cast<CKoopas*>(e);
	if (CMario::GetInstance()->isAttacking)
	{
		kp->nx = nx;
		kp->SetState(KOOPAS_STATE_SHELL_UP);
	}

}

void CTail::OnCollisionWithQB(LPGAMEOBJECT& e)
{
	CQuestionBrick* qb = dynamic_cast<CQuestionBrick*>(e);
	qb->SetState(QUESTIONBRICK_STATE_COLISION);
	
	
}

void CTail::OnCollisionWithB(LPGAMEOBJECT& e)
{
	CBrick* qb = dynamic_cast<CBrick*>(e);
	qb->SetState(BRICK_STATE_BROKEN);


}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i)))
		{
			if (dynamic_cast<CGoomba*>(coObjects->at(i)))
				OnCollisionWithGoomba(coObjects->at(i));
			else if (dynamic_cast<CQuestionBrick*>(coObjects->at(i)))
				OnCollisionWithQB(coObjects->at(i));
			else if (dynamic_cast<CKoopas*>(coObjects->at(i)))
				OnCollisionWithKoopas(coObjects->at(i));
			else if (dynamic_cast<CBrick*>(coObjects->at(i)))
				OnCollisionWithB(coObjects->at(i));
		}
	}
	//CGameObject::Update(dt, coObjects);

}

void CTail::Render()
{
	RenderBoundingBox();
}