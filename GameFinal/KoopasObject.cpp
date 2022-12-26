#include "KoopasObject.h"

KoopasObject::KoopasObject(float x, float y) : CGameObject(x, y) {

}
void KoopasObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - KOOPAS_OBJECT_BBOX_WIDTH / 2;
		top = y - KOOPAS_OBJECT_BBOX_HEIGHT / 2;
		right = left + KOOPAS_OBJECT_BBOX_WIDTH;
		bottom = top + KOOPAS_OBJECT_BBOX_HEIGHT;
}

void KoopasObject::Render() {
	RenderBoundingBox();
}

void KoopasObject::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void KoopasObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += KOOPAS_OBJECT_GRAVITY * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void KoopasObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (e->ny < 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
}