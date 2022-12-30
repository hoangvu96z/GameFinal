#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define BROKEN_EFFECT_GRAVITY 0.001f

#define BROKEN_BBOX_WIDTH	8
#define BROKEN_BBOX_HEIGHT	8

#define BROKEN_EFFECT_SPEED_Y 0.2f
#define BROKEN_EFFECT_SPEED_Y_BOTTOM 0.1f
#define BROKEN_EFFECT_SPEED_X 0.06f

#define BROKEN_EFFECT_Y	30

#define BROKEN_EFFECT_MAX_Y	70

#define TIME_BROKEN_EFFECT	3000

#define BROKEN_EFFECT_STATE_HIDDEN	100
#define BROKEN_EFFECT_STATE_APPEAR	200
#define BROKEN_EFFECT_STATE_APPEAR_BOTTOM	250
#define BROKEN_EFFECT_STATE_DELETE	300

#define ID_ANI_BROKEN_EFFECT	200000
class BrokenEffect: public CGameObject
{
public:
	float first_y;
	float ay;
	int nx;
	ULONGLONG timeEffect;
	BrokenEffect(float x, float y, int direct) : CGameObject(x, y) { SetState(BROKEN_EFFECT_STATE_HIDDEN);  first_y = y; nx = direct; ay = BROKEN_EFFECT_GRAVITY; };
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	int IsBlocking() { return 0; }
	~BrokenEffect() {};
};
