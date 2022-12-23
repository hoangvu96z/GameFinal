#include "QuestionBrick.h"
CQuestionBrick::CQuestionBrick(float x, float y) : CGameObject(x, y)
{
	First_y = y;
}
void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (CheckBrickCollision == false)
	{
		animations->Get(ID_ANI_QBRICK)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_EMP)->Render(x, y);
	}
	RenderBoundingBox();
}

void CQuestionBrick::SetState(int state) {
	CGameObject::SetState(state);
	if (CheckBrickCollision == false)
	{
		switch (state)
		{
		case QUESTIONBRICK_STATE_COLISION:
			vy -= 0.03;
			break;
		case QUESTIONBRICK_STATE_EMP:
			vy = 0;
			y = First_y;
			CheckBrickCollision = true;
			if (mus != NULL)
			{
				mus->SetState(MUSHROOM_STATE_APPEAR);
			}
			else if (coin != NULL) {
				coin->SetState(COIN_STATE_APPEAR);
			}
			break;

		}
	}
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	y += vy * dt;
	if (CheckBrickCollision == false)
	{
		if (state == QUESTIONBRICK_STATE_COLISION) {
			if (y < First_y - MAX_HEIGHT) {
				vy = 0.03;
				SetState(QUESTIONBRICK_STATE_EMP);
			}
		}
	}
	CGameObject::Update(dt, coObjects);
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QBRICK_BBOX_WIDTH / 2;
	t = y - QBRICK_BBOX_HEIGHT / 2;
	r = l + QBRICK_BBOX_WIDTH;
	b = t + QBRICK_BBOX_HEIGHT;
}

void CQuestionBrick::SetItem(CMushroom* mr) {
	mus = mr;
}

void CQuestionBrick::SetItemC(CCoin* co) {
	coin = co;
}