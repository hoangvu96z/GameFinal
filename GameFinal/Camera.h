#pragma once
#include <Windows.h>
#include "Game.h"
#include "GameObject.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 272
class Camera
{
public:
	static Camera* __instance;
	//static Camera* GetInstance();
	Camera(int mapW, int mapH);
	float Width, Height;
	float Cam_x, Cam_y;
	int mapwidth;
	int mapheight;
	void SetPosition(float& cam_x, float& cam_y);
	void GetPosition(float& x, float& y);
	float GetWidth();
	float GetHeight();
	~Camera() {};


};