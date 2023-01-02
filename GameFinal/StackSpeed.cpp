#include "StackSpeed.h"
void StackSpeed::RenderStack(int x, int y, int s)
{
	CAnimations* animations = CAnimations::GetInstance();
	for (int i = 0; i < s; i++)
	{
		if (s > 1) {
			animations->Get(ID_ANI_STACKSPEED)->Render(x + i * 8, y);
		}
		else if (s >= 6)
			animations->Get(ID_ANI_P)->Render(x + i * 8, y);
	}
}