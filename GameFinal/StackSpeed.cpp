#include "StackSpeed.h"
void StackSpeed::RenderStack(int x, int y, int stack)
{
	CAnimations* animations = CAnimations::GetInstance();
	for (int i = 0; i < stack; i++)
	{
		if (stack > 1) {
			animations->Get(ID_ANI_STACKSPEED)->Render(x + i * RANGE, y);
		}
		else if(stack >= 6)
			animations->Get(ID_ANI_P)->Render(x + i * RANGE, y);
	}
}