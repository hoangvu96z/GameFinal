#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "Item.h"

#define ID_ANI_QBRICK 100000
#define ID_ANI_EMP	100001
#define QBRICK_BBOX_WIDTH 16
#define QBRICK_BBOX_HEIGHT 16

#define QUESTIONBRICK_STATE_COLISION 100
#define QUESTIONBRICK_STATE_EMP	200

#define MAX_HEIGHT	5
#define BRICK_GODOWN 0.03f
class CQuestionBrick : public CGameObject 
{
public:
	BOOLEAN CheckBrickCollision = false;
	Item* item = NULL;
	float First_y;
	int typeQB;
	CQuestionBrick(float x, float y, int type);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	void setItem(Item* i);
	Item* getItem();
};