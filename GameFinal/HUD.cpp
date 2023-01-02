#include "HUD.h"

#include "Mario.h"
CMario* mario = CMario::GetInstance();
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
	stackspeed->RenderStack(CGame::GetInstance()->GetCamX() + 66 , y + 7, stack);
}

void HUD::Update(DWORD dt)
{

	//if (Range < abs(mario->GetAX()) < Range1)
	//{
	//	stack = 1;
	//}
	//else if (Range1 < abs(mario->GetAX()) < Range2)
	//{
	//	stack = 2;
	//}
}