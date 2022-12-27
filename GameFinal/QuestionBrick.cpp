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
			vy -= BRICK_GODOWN;
			break;
		case QUESTIONBRICK_STATE_EMP:
			vy = 0;
			y = First_y;
			CheckBrickCollision = true;		
			if (item->GetItemType() == ItemType::Mushroom) {
				item->setDirectItem(nx);
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
			switch (item->GetItemType())
			{
			case ItemType::Coin:
			{
				item->setDirectItem(0);
				if (y < First_y - MAX_HEIGHT) {
					vy = BRICK_GODOWN;
					SetState(QUESTIONBRICK_STATE_EMP);
				}
				break;
			}
			case ItemType::Mushroom:
			{
				if (y < First_y - MAX_HEIGHT) {
					vy = BRICK_GODOWN;
					SetState(QUESTIONBRICK_STATE_EMP);
				}
				break;
			}
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

void CQuestionBrick::setItem(Item* i)
{
	item = i;
}
Item* CQuestionBrick::getItem()
{
	return item;
}