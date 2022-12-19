#include "Koopas.h"
#include "Utils.h"
#include "Constant.h"
CKoopas::CKoopas()
{
	nx = -1;
	SetState(KOOPAS_STATE_WALKING);
	//SetState(KOOPAS_STATE_IN_SHELL);
	//SetState(KOOPAS_STATE_SHELL_UP);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;
	if (state == KOOPAS_STATE_IN_SHELL || state == KOOPAS_STATE_SPINNING || state == KOOPAS_STATE_SHELL_UP)
	{
		bottom = y + KOOPAS_BBOX_SHELL_HEIGHT;
	}
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}
int CKoopas::CalRevivable()
{
	CGame* game = CGame::GetInstance();
	float camX, camY;

	camX = game->GetCamX();
	camY = game->GetCamY();

	bool IsStartInViewPort = (start_x > camX - GetWidth() - VIEWPORT_PUSHBACK
		&& start_x < camX + game->GetScreenWidth() + VIEWPORT_PUSHBACK
		&& start_y > camY - (SCREEN_HEIGHT - game->GetScreenHeight())
		&& start_y < camY + SCREEN_HEIGHT);
	return IsStartInViewPort;
}
bool CKoopas::CalKillable(vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
		{
			float mLeft, mTop, mRight, mBottom;
			coObjects->at(i)->GetBoundingBox(mLeft, mTop, mRight, mBottom);
			
		}
	return false;
}
bool CKoopas::CalTurnable(LPGAMEOBJECT object, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsInViewPort())
		return false;
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
			if (abs(coObjects->at(i)->y == object->y))
			{
				if (nx > 0)
					if (coObjects->at(i)->x > object->x && coObjects->at(i)->x - BRICK_BBOX_WIDTH < object->x + BRICK_BBOX_WIDTH)
						return false;
				if (nx < 0)
					if (coObjects->at(i)->x + BRICK_BBOX_WIDTH > object->x - BRICK_BBOX_WIDTH && coObjects->at(i)->x < object->x)
						return false;
			}
	return true;
}
void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - dying_start >= KOOPAS_DIYING_TIME && dying_start != 0)
		
	CGameObject::Update(dt);
	CMario* mario = {};
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
void CKoopas::Render()
{
	int ani = -1;
	if (state == KOOPAS_STATE_SHELL_UP || state == KOOPAS_STATE_DEATH)
		ani = KOOPAS_ANI_SHELL_UP;
	else if (state == KOOPAS_STATE_IN_SHELL)
		ani = KOOPAS_ANI_SHELL;
	else if (state == KOOPAS_STATE_SPINNING)
	{
		if (vx < 0)
			ani = KOOPAS_ANI_SPIN_LEFT;
		else
			ani = KOOPAS_ANI_SPIN_RIGHT;
	}
	else
	{
		if (nx < 0)
			ani = KOOPAS_ANI_WALKING_LEFT;
		else
			ani = KOOPAS_ANI_WALKING_RIGHT;
	}
	if (tag == KOOPAS_GREEN_PARA || tag == KOOPAS_RED_PARA)
		if (nx < 0)
			ani = KOOPAS_ANI_PARA_LEFT;
		else
			ani = KOOPAS_ANI_PARA_RIGHT;
	if (reviving_start != 0)
	{
		if (state == KOOPAS_STATE_IN_SHELL)
			ani = KOOPAS_ANI_SHAKE;
		if (state == KOOPAS_STATE_SHELL_UP)
			ani = KOOPAS_ANI_SHAKE_UP;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	RenderBoundingBox();
}
void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_SHELL_UP:
	{
		CMario* mario = {};
		vy = -KOOPAS_SHELL_DEFLECT_SPEED;
		if (x <= mario->x)
			nx = -1;
		else
			nx = 1;
		vx = nx * KOOPAS_WALKING_SPEED;
		StartShell();
		break;
	}
	case KOOPAS_STATE_WALKING:
		if (tag == KOOPAS_GREEN_PARA)
			vx = nx * KOOPAS_PARA_WALKING_SPEED;
		if (tag == KOOPAS_RED_PARA)
		{
			vx = 0;
			vy = KOOPAS_RED_SPEED;
		}
		if (tag == KOOPAS_RED || tag == KOOPAS_GREEN)
			vx = nx * KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SPINNING:
		if (nx > 0)
			vx = KOOPAS_WALKING_SPEED * 5;
		else
			vx = -KOOPAS_WALKING_SPEED * 5;
		break;
	case KOOPAS_STATE_IN_SHELL:
		vx = 0;
		StartShell();
		break;
	case KOOPAS_STATE_DEATH:
		vy = -KOOPAS_DIE_DEFLECT_SPEED;
		vx = 0;
		StartDying();
		break;
	}

}
void CKoopas::Reset()
{
	x = start_x;
	y = start_y;
	nx = -1;
	SetState(KOOPAS_STATE_WALKING);
}