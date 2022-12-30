#pragma once
#include"Item.h"
#include "Animation.h"
#include "Animations.h"

#define PBUTTON_BBOX_HEIGHT_BIG	16
#define PBUTTON_BBOX_WIDTH	16
#define PBUTTON_BBOX_HEIGHT_SMALL	7

#define POSITION_Y ((PBUTTON_BBOX_HEIGHT_BIG - PBUTTON_BBOX_HEIGHT_SMALL) / 2) + 3

#define ID_ANI_PBUTTON_NORMAL	13000
#define ID_ANI_PBUTTON_ISPRESSED	13001

#define PBUTTON_STATE_APPEAR	100
#define PBUTTON_STATE_NORMAL	200
#define PBUTTON_STATE_COLLISION	300

class Pbutton : public Item {
public:
	ULONGLONG timeAppear = GetTickCount64();
	Pbutton(float x, float y) : Item(x, y, 0) { item = ItemType::pbutton; first_y = y; SetState(PBUTTON_STATE_APPEAR); }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { 
		if (state != PBUTTON_STATE_COLLISION)
		{
			return 1;
		}
		else
			return 0;
	}
	void SetState(int state);
	void setDirectItem(int nx);
	
};
