#pragma once
#include "GameObject.h"

enum ItemType 
{
	Undefined = -1,
	Coin,
	Mushroom,
	pbutton,
};

class Item : public CGameObject
{
public:
	ItemType item = ItemType::Undefined;
	float ay;
	float first_y;
public:
	Item(float x, float y, int type) : CGameObject(x, y) { first_y = y; ay = 0; item = (ItemType)type; };
	~Item() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void SetState(int state) {};
	ItemType GetItemType() { return item; };
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };
	virtual void setDirectItem(int nx) {};


};