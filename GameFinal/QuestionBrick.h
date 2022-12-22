#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QBRICK 100000
#define QBRICK_WIDTH 16
#define QBRICK_BBOX_WIDTH 16
#define QBRICK_BBOX_HEIGHT 16

class CQuestionBrick : public CGameObject {
public:
	CQuestionBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};