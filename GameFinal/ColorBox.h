#pragma once
#include "GameObject.h"
#define Frame	16
class ColorBox : public CGameObject
{
protected:
	float width, height;
	float cellWidth;
	float cellHeight;
	int length;
public:
	ColorBox(float x, float y, float w, float h, float cw, float ch, int l) : CGameObject(x, y) {
		width = w;
		height = h;
		cellWidth = cw;
		cellHeight = ch;
		length = l;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void RenderBoundingBox();
	virtual int GetWidth() { return width; };
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	//virtual int IsBlockingOnSide(){ return 0; };
	//virtual int IsBlockingOnTop() { return 1; };
	virtual void DirectBlocking(int& l, int& t, int& r, int& b) { l = 0; t = 1; b = 0; r = 0; }
};