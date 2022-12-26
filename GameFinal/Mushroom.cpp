#include "Mushroom.h"
#include "Platform.h"
#include "Pipe.h"
#include "debug.h"
CMushroom::CMushroom(float x, float y) : CGameObject(x, y)
{
	firstY = y;
	ax = 0;
	ay = MUSHROOM_GRAVITY;
	SetState(MUSHROOM_STATE_COLLISION);
}
void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state != MUSHROOM_STATE_COLLISION)
	{
		animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
	}
	RenderBoundingBox();
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	if (state == MUSHROOM_STATE_APPEAR) {
		y -= MUSHROOM_DEFLECT * dt ;
		if (y < firstY - INGROWTH) {
			SetState(MUSHROOM_STATE_MOVING);
		}

	}
	if (state == MUSHROOM_STATE_MOVING)
	{
		vy += ay * dt;
		vx += ax * dt;
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}

	if (e->ny != 0) {
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
void CMushroom::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_APPEAR:
		vy = 0;
		break;
	case MUSHROOM_STATE_MOVING:
		vx = MUSHROOM_WALKING_SPEED * nx;	
		break;
	default:
		break;
	}
}
void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}