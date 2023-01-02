#pragma once
#include "GameObject.h"
#define ID_ANI_STACKSPEED	15002
#define ID_ANI_P	15003
class StackSpeed: public CGameObject
{
public:
	StackSpeed() {};	
	int id;
	void RenderStack(int x, int y, int s);
	virtual void Render() {  };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		return;
	};

	~StackSpeed();

};