#pragma once
#include <Windows.h>
#include "Utils.h"
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 272
class Camera
{
public:
	float Mariovx, Mariovy=0, MarioY;
	float cam_x, cam_y, cam_vx, cam_vy =0;
	int AutoMove = 0;
	bool IsFollowingMario;
public:
	static Camera* __instance;

	static Camera* GetInstance()
	{
		if (__instance == NULL) __instance = new Camera();
		return __instance;
	}
	Camera();

	void SetCamSpeed()

	{
		if (Mariovy < 0 && cam_y >= 0)
			cam_vy = Mariovy;
		else {
			if (cam_y <= 0)
				cam_y = 0;
			cam_vy = Mariovy*0.7;
		}
		if (cam_vy > 0)
		{
			if (cam_y >= 240)
			{
				IsFollowingMario = false;
				cam_vy = 0;
				cam_y = 240;
			}
		}
	}
	bool IsInCam(float objX, float objY)
	{
		if (objX < cam_x || objX - cam_x>SCREEN_WIDTH || objY < cam_y)
			return false;
		else
			return true;
	}
	void SetCamPos(float x, float y) {
		cam_x = x;
		cam_y = y;
	};	
	float GetCamPosX()
	{
		return cam_x;
	}
	float GetCamPosY()
	{
		return cam_y;
	}

	void GetCamPos(float& x, float& y) {
		x = cam_x;
		y = cam_y;
	}
	void Update( DWORD dt);
};