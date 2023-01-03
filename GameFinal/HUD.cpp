#include "HUD.h"

HUD* HUD::__instance = NULL;
HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}


void HUD::Render()
{
	float x = CGame::GetInstance()->GetCamX() + CGame::GetInstance()->GetBackBufferWidth() / 2  + SCREEN_W_PLUS;
	float y = CGame::GetInstance()->GetCamY() + CGame::GetInstance()->GetBackBufferHeight() - SCREEN_H / 2;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HUD)->Render(x , y + SCREEN_PLUS);
	animations->Get(ID_ANI_ITEM)->Render(x + SCREEN_W , y + SCREEN_PLUS);
	for (int i = 0; i < stack; i++)
	{
		stackspeed->RenderStack(CGame::GetInstance()->GetCamX() + 66, y + 7, stack);
	}
}

void HUD::Update(DWORD dt)
{
	
}