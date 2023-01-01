#include "Portal.h"


CPortal::CPortal(float l, float t, float r, float b, int scene_id ): CGameObject(x,y)
{
	this->scene_id = scene_id;
	x = l; 
	y = t;
	//width = r - l;
	//height = b - t;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + PORTAL_BBOX_WIDTH / 2;
	b = y +	PORTAL_BBOX_HEIGHT / 2;
}