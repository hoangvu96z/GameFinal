#include "Pipe.h"
#include "Textures.h"


void CPipe::Render()
{
	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	float cellWidth_div_2 = this->cellWidth / 2;
	float cellHeight_div_2 = this->cellHeight / 2;
	float yy = (cellHeight - Frame) / 2;

	left = x - cellWidth_div_2;
	top = y - cellHeight_div_2 + yy;
	right = left + this->cellWidth * this->length;
	bottom = top + this->cellHeight;
}

void CPipe::RenderBoundingBox() {
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;
	float yy = (this->cellHeight - Frame) / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy + yy, bbox, nullptr, BBOX_ALPHA, rect.right, rect.bottom);
}