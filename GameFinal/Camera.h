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
		
	}
	bool IsInCam(float objX, float objY)
	{
	
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