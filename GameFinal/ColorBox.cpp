
#include "ColorBox.h"

ColorBox::ColorBox(float l, float t, float r, float b) {
	x = l;
	y = t;
	width = r;
	height = b;
	type = 6;
}
void ColorBox::Render()
{
	RenderBoundingBox();
}

void ColorBox::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}