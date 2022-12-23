#include "Pipe.h"


CPipe::CPipe(float l, float t, float r, float b) {
	x = l;
	y = t;
	width = r;
	height = b;
	type = 7;
}
void CPipe::Render()
{
	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}