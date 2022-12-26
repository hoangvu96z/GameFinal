#include "Pipe.h"
#include "Textures.h"

#define HEIGHTPIPE 16
#define WIDTHPIPE 16

void CPipe::Render()
{
	if (this->length <= 0) return;
	float xx = x;
	float yy = y;
	int heightPipe = (this->height / HEIGHTPIPE);
	CSprites* s = CSprites::GetInstance();

	s->Get(this->sprites_id_1)->Draw(xx, y);
	s->Get(this->sprites_id_2)->Draw(xx + WIDTHPIPE, y);
	for (int i = 1; i < heightPipe; i++)
	{
		yy += HEIGHTPIPE;
		s->Get(this->sprites_id_3)->Draw(xx, yy);
		s->Get(this->sprites_id_4)->Draw(xx + WIDTHPIPE, yy);
		
	}
	//RenderBoundingBox();
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

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_PIPE);

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