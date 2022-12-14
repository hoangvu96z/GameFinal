#include <algorithm>
#include "debug.h"
#include "AssetIDs.h"
#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "ColorBox.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
#include "Koopas.h"
#include "KoopasFly.h"
#include "GoombaRed.h"
#include "Pipe.h"
#include "FirePlant.h"
#include "Brick.h"
#include "Pbutton.h"
#include "Leaf.h"
#include "HUD.h"




#include "Collision.h"

CMario* CMario::__instance = NULL;
CKoopas* koopas;




CMario* CMario::GetInstance()
{
	if (__instance == NULL) __instance = new CMario(0, 0);
	return __instance;
}
void CMario::SetInstance(CMario* p)
{
	__instance = p;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (abs(ax) == MARIO_ACCEL_RUN_X)
	{ 
		IncreasePower();
	}
	else
	{
		if (powerStack > 0)
		{
			if (!isFlying)
			{
				DecreasePower();
			}
		}

	}

	if (isFalling)
	{
		if (GetTickCount64() - timeFalling > 200)
		{
			isFalling = false;
			SetState(MARIO_STATE_RELEASE_JUMP);
		}
	}
	//DebugOut(L"state: %d\n", state);
	/*if (isChangingScene == true)
	{
		DebugOut(L"true\n");
	}
	else
		DebugOut(L"false\n");*/
	HUD::GetInstance()->stack = powerStack;

	if (isFlying)
	{
		if (GetTickCount64() - timeFlying > MARIO_TIME_SHOWING_FLYING)
		{
			isFlying = false;
			ay = MARIO_GRAVITY;

		}
	}

	if (isKicking)
	{
		if (GetTickCount64() - timeKick > MARIO_TIMEOUT_KICK)
		{
			isKicking = false;
		}
	}

	if (isHoldKoopas)
	{
		if (nx >= 0)
		{
			koopas->SetPosition(x + MARIO_RACOON_BBOX_WIDTH /2 + KOOPAS_BBOX_WIDTH/2 + RANGE_BETWEEN_OBJECT , y);
		}
		else
			koopas->SetPosition(x - MARIO_RACOON_BBOX_WIDTH /2 - KOOPAS_BBOX_WIDTH/2 - RANGE_BETWEEN_OBJECT, y);
		
		if (koopas->GetState() == KOOPAS_STATE_WALKING)
		{
			SetState(MARIO_STATE_RELEASE_HOLDING_A);
		}
		

	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	isOnPlatform = false;
	/*tail->SetPosition((nx < 0) ?(x + MARIO_BIG_BBOX_WIDTH / 2 + TAIL_BBOX_WIDTH / 2) - 2 : (x - MARIO_BIG_BBOX_WIDTH / 2 - TAIL_BBOX_WIDTH / 2) + 2, y + 6);
	tail->Update(dt, coObjects);*/

	if (isAttacking)
	{
		tail->SetPosition((nx < 0) ? (x - MARIO_BIG_BBOX_WIDTH / 2 - TAIL_BBOX_WIDTH / 2) : (x + MARIO_BIG_BBOX_WIDTH / 2 + TAIL_BBOX_WIDTH / 2) , y + 6);
		tail->SetDirect(nx);
		if (GetTickCount64() - timeAttacking > MARIO_TIME_ATTACKING)
		{
			isAttacking = false;
		}
	}

	if (isPressed)
	{
		isPressed = false;
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type == OBJECT_TYPE_BRICK)
			{
				CBrick* cb = dynamic_cast<CBrick*>(coObjects->at(i));
				cb->SetState(BRICK_STATE_CHANGE_COIN);
			}
		}
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0)
		{
			isOnPlatform = true;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		
		if (abs(ax) == MARIO_ACCEL_RUN_X) { // when mario run if mario collision block, mario can't reach max power stack
			SetPower();
			if (nx > 0)
			{
				SetState(MARIO_STATE_WALKING_RIGHT);
			}
			else
				SetState(MARIO_STATE_WALKING_LEFT);
		}

	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CPipe*>(e->obj))
		OnCollisionWithPipe(e);
	else if (dynamic_cast<ColorBox*>(e->obj))
		OnCollisionWithColorBox(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQB(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CKoopasFly*>(e->obj))
		OnCollisionWithKoopasFly(e);
	else if (dynamic_cast<CGoombaRed*>(e->obj))
		OnCollisionWithRedGoomba(e);
	else if (dynamic_cast<CFirePlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithB(e);
	else if (dynamic_cast<Pbutton*>(e->obj))
		OnCollisionWithPbutton(e);
	else if (dynamic_cast<Leaf*>(e->obj))
		OnCollisionWithLeaf(e);
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	Leaf* leaf = dynamic_cast<Leaf*>(e->obj);

	if (e->nx != 0 || e->ny > 0)
	{
		if (leaf->GetState() == LEAF_STATE_FALLING)
		{
			leaf->SetState(LEAF_STATE_COLLISION);
			if (level < MARIO_LEVEL_RACOON)
			{
				level++;
			}
		}
	}
}


void CMario::OnCollisionWithPbutton(LPCOLLISIONEVENT e)
{
	Pbutton* pb = dynamic_cast<Pbutton*>(e->obj);

	if (e->ny < 0)
	{
		if (pb->GetState() == PBUTTON_STATE_NORMAL)
		{	
			isPressed = true;
			pb->SetState(PBUTTON_STATE_COLLISION);
		}
	}
}


void CMario::OnCollisionWithB(LPCOLLISIONEVENT e)
{
	CBrick* cb = dynamic_cast<CBrick*>(e->obj);
	if (e->ny > 0)
	{
		if (cb->GetState() != BRICK_STATE_BROKEN && cb->GetState() != BRICK_STATE_CHANGE_COIN)
		{
			cb->SetState(BRICK_STATE_BROKEN);
		}
	}
	else if (isAttacking && e->nx != 0)
	{
		if (cb->GetState() != BRICK_STATE_BROKEN)
		{
			cb->SetState(BRICK_STATE_BROKEN);
		}
	}
	
	
	if (cb->GetState() == BRICK_STATE_CHANGE_COIN)
	{
		e->obj->Delete();
		cb->SetState(BRICK_STATE_COLLISION);
		coin++;
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e )
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState()!= GOOMBA_STATE_DIE_BY_ATTACKING)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL && isHoldKoopas)
				{
					level--;
					StartUntouchable();
					SetState(MARIO_STATE_DROP_KOOPAS_SHELL);

				}
				else if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithColorBox(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		vy = 0;
		isOnPlatform = true;
	}
}

void CMario::OnCollisionWithQB(LPCOLLISIONEVENT e) {
	CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny > 0) {

		if (brick->GetState() != QUESTIONBRICK_STATE_EMP)
		{
			brick->SetState(QUESTIONBRICK_STATE_COLISION);
		}
		
	}
	else if (isAttacking)
	{
		if (brick->GetState() != QUESTIONBRICK_STATE_EMP)
		{
			brick->SetState(QUESTIONBRICK_STATE_COLISION);
		}
	}
}


void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* coins = dynamic_cast<CCoin*>(e->obj);
		//coins->SetState(COIN_STATE_APPEAR);
	if (coins->insideQB != 1)
	{
		coin++;
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->nextX = p->next_x;
	CGame::GetInstance()->nextY = p->next_y;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e)
{
	CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
	if (pipe->typePipe != 0)
	{
		float x_pipe, y_pipe;
		pipe->GetPosition(x_pipe, y_pipe);
		float x_max = x_pipe + 16; // x pipe max
		float x_min = x_pipe + 6;// x pipe min
		if (x >= x_min && x <= x_max) // if mario's standing in range between x_min and x_max, mario can switch scene
		{
			if (e->ny < 0 && isSitting)
			{
				isChangingScene = true;
				SetState(MARIO_STATE_FALLDOWN_PIPE);
				pipe->isSwitchScene = true;
			}
			else if (e->ny > 0)
			{
				isChangingScene = true;
				SetState(MARIO_STATE_JUMPING_PIPE);
				pipe->isSwitchScene = true;
			}
		}
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e) {
	CMushroom* mr = dynamic_cast<CMushroom*>(e->obj);
	if (mr->GetState() == MUSHROOM_STATE_MOVING)
	{
		e->obj->Delete();
		if (level < MARIO_LEVEL_RACOON)
		{
			SetLevel(level);
			level++;
			
		}

	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e) {
	CKoopas* kp = dynamic_cast<CKoopas*>(e->obj);
	if (e->ny < 0) {
		if (kp->GetState() != KOOPAS_STATE_SHELL && kp->GetState()!= KOOPAS_STATE_SHELL_UP)
		{
			kp->SetState(KOOPAS_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			
		}
		else if (kp->GetState() == KOOPAS_STATE_SHELL_MOVING)
		{
			kp->SetState(KOOPAS_STATE_SHELL);
		}
		else if (kp->GetState() == KOOPAS_STATE_SHELL_UP_MOVING)
		{
			kp->SetState(KOOPAS_STATE_SHELL_UP);
		}
		else
		{
			kp->nx = nx;
			if (kp->GetState() == KOOPAS_STATE_SHELL)
			{
				kp->SetState(KOOPAS_STATE_SHELL_MOVING);
			}
			else if (kp->GetState() == KOOPAS_STATE_SHELL_UP)
			{
				kp->SetState(KOOPAS_STATE_SHELL_UP_MOVING);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by 
	{
		if (untouchable == 0)
		{
			if (!isHoldKoopas)
			{
				if (kp->GetState() != KOOPAS_STATE_SHELL && kp->GetState() != KOOPAS_STATE_SHELL_UP)
				{

					if (level > MARIO_LEVEL_SMALL)
					{
						level--;
						StartUntouchable();

					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}

	if (e->nx != 0)
	{
		if (abs(ax) == MARIO_ACCEL_WALK_X && !isHoldKoopas)
		{
			switch (kp->GetState())
			{
			case KOOPAS_STATE_SHELL:
				SetState(MARIO_STATE_KICK);
				kp->nx = nx;
				kp->SetState(KOOPAS_STATE_SHELL_MOVING);
				break;
			case KOOPAS_STATE_SHELL_UP:
				SetState(MARIO_STATE_KICK);
				kp->nx = nx;
				kp->SetState(KOOPAS_STATE_SHELL_UP_MOVING);
				break;
			default:
				break;
			}
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			switch (kp->GetState())
			{
			case KOOPAS_STATE_SHELL: 
			{
				koopas = dynamic_cast<CKoopas*>(e->obj);
				SetState(MARIO_STATE_HOLDING);
			}
				break;
			case KOOPAS_STATE_SHELL_UP:
			{
				koopas = dynamic_cast<CKoopas*>(e->obj);
				SetState(MARIO_STATE_HOLDING);
			}
			break;
			
			}
		}
	}


}

void CMario::OnCollisionWithKoopasFly(LPCOLLISIONEVENT e) {
	CKoopasFly* kpF = dynamic_cast<CKoopasFly*>(e->obj);
	if (e->ny < 0) {
		if (kpF->GetState() == KOOPASFLY_STATE_JUMPFLY)
		{
			if (kpF->GetState() != KOOPASFLY_STATE_SHELL)
			{
				kpF->SetState(KOOPASFLY_STATE_WALKING);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else if (kpF->GetState() == KOOPASFLY_STATE_WALKING)
		{
			if (kpF->GetState() != KOOPASFLY_STATE_SHELL)
			{
				kpF->SetState(KOOPASFLY_STATE_SHELL);
				vy = -MARIO_JUMP_DEFLECT_SPEED;

			}
		}
		else {
			kpF->SetState(KOOPASFLY_STATE_SHELL_MOVING);
			kpF->SetSpeed(KOOPASFLY_SHELL_SPEED * nx, 0);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (kpF->GetState() != KOOPASFLY_STATE_SHELL)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}

	if (e->nx != 0)
	{
		if(kpF->GetState() == KOOPASFLY_STATE_SHELL){
			kpF->SetState(KOOPASFLY_STATE_SHELL_MOVING);
			if (vx != 0)
			{
				kpF->SetSpeed(KOOPASFLY_SHELL_SPEED * nx, 0);
			}


		}
	}
}

void CMario::OnCollisionWithRedGoomba(LPCOLLISIONEVENT e) {
	CGoombaRed* rgb = dynamic_cast<CGoombaRed*>(e->obj);

	if (e->ny < 0)
	{
		if (rgb->GetState() != REDGOOMBA_STATE_DIE)
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			if (rgb->GetState() == REDGOOMBA_DEFLECT_SPEED_FLY || rgb->GetState() == REDGOOMBA_STATE_WING_JUMPFLY || rgb->GetState() == REDGOOMBA_STATE_WING_WALKING)
			{
				rgb->SetState(REDGOOMBA_STATE_WALKING);
			}
			else if (rgb->GetState() == REDGOOMBA_STATE_WALKING)
			{
				rgb->SetState(REDGOOMBA_STATE_DIE);
			}
			
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (rgb->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL && isHoldKoopas)
				{
					level--;
					StartUntouchable();
					SetState(MARIO_STATE_DROP_KOOPAS_SHELL);

				}
				else if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CFirePlant* plant = dynamic_cast<CFirePlant*>(e->obj);
	if (untouchable == 0)
	{
			if (level > MARIO_LEVEL_SMALL)
			{
				level--;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
	}
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;

			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isChangingScene)
	{
		if (!isOnPlatform)
		{
			if (!isHoldKoopas)
			{
				if (abs(ax) == MARIO_ACCEL_RUN_X)
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
					else
						aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
				}
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
				}
			}
			else
			{
				if (nx >= 0)
				{
					aniId = ID_ANI_MARIO_JUMPING_HOLD_KOOPAS_RIGHT;
				}
				else
					aniId = ID_ANI_MARIO_JUPMING_HOLD_KOOPAS_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (!isHoldKoopas)
				{
					if (vx == 0)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_IDLE_LEFT;
					}
					else if (vx > 0)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_RUNNING_RIGHT;
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_WALKING_RIGHT;
						else if (isKicking == true)
							aniId = ID_ANI_MARIO_KICK_RIGHT;
					}
					else // vx < 0
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_RUNNING_LEFT;
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_WALKING_LEFT;
						else if (isKicking == true)
							aniId = ID_ANI_MARIO_KICK_LEFT;
					}
				}
				else
				{
					if (vx == 0)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_HOLD_RIGHT;
						else aniId = ID_ANI_MARIO_HOLD_LEFT;
					}
					else
					{
						if (nx > 0) aniId = ID_ANI_MARIO_HOLD_KOOPAS_RIGHT;
						else aniId = ID_ANI_MARIO_HOLD_KOOPAS_LEFT;
					}
				}

		if (isKicking)
		{
			if (nx > 0)
			{
				aniId = ID_ANI_MARIO_KICK_RIGHT;
			}
			else
				aniId = ID_ANI_MARIO_KICK_LEFT;
		}
		if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;
	}
	else
		aniId = ID_ANI_MARIO_PIPE;

	return aniId;
}
//
// Get animation ID for Racoon mario
//


int CMario::GetAniIDRacoon() {
	int aniId = -1;
	if (!isChangingScene)
	{
		if (!isOnPlatform)
		{
			if (!isHoldKoopas)
			{
				if (isFlying)
				{
					if (nx >= 0)
					{
						aniId = ID_ANI_MARIO_RACOON_FLYING_RIGHT;
					}
					else
						aniId = ID_ANI_MARIO_RACOON_FLYING_LEFT;
				}
				else
				{
					if (abs(ax) == MARIO_ACCEL_RUN_X)
					{
						if (vy >= 0)
						{
							if (nx >= 0)
								aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_FALLING_RIGHT;
							else
								aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_FALLING_LEFT;
						}
						else
						{
							if (nx >= 0)
								aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT;
							else
								aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT;
						}
					}
					else if (vy >= 0)
					{
						if (isFalling == true) {
							if (nx >= 0)
								aniId = ID_ANI_MARIO_RACOON_FALLING_SLOWDOWN_RIGHT;
							else
								aniId = ID_ANI_MARIO_RACOON_FALLING_SLOWDOWN_LEFT;
						}
						else {
							if (nx >= 0)
								aniId = ID_ANI_MARIO_RACOON_FALLING_RIGHT;
							else
								aniId = ID_ANI_MARIO_RACOON_FALLING_LEFT;
						}
					}
					else
					{
						if (nx >= 0)
							aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT;
						else
							aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT;
					}
				}
			}
			else
			{
				if (nx >= 0)
				{
					aniId = ID_ANI_MARIO_RACOON_HOLDING_JUMP_RIGHT;
				}
				else
					aniId = ID_ANI_MARIO_RACOON_HOLDING_JUMP_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_RACOON_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_SIT_LEFT;
			}
			else
				if (!isHoldKoopas)
				{
					if (vx == 0)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
					}
					else if (vx > 0)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X)
						{
							if (powerStack == MARIO_MAX_POWER)
							{
								aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
							}
							else
								aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
						}
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
						else if (isKicking == true)
							aniId = ID_ANI_MARIO_KICK_RIGHT;
					}
					else // vx < 0
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X)
						{
							if (powerStack == MARIO_MAX_POWER)
							{
								aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
							}
							else
								aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
						}
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
						else if (isKicking == true)
							aniId = ID_ANI_MARIO_KICK_LEFT;
					}
				}
				else
				{
					if (vx == 0)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_RACOON_HOLDING_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_RACOON_HOLDING_IDLE_LEFT;
					}
					else
					{
						if (nx > 0) aniId = ID_ANI_MARIO_RACOON_HOLDING_WALKING_RIGHT;
						else aniId = ID_ANI_MARIO_RACOON_HOLDING_WALKING_LEFT;
					}
				}
		if (isAttacking) {
			if (nx > 0)
			{
				aniId = ID_ANI_MARIO_RACOON_ATTACKING_RIGHT;
			}
			else
				aniId = ID_ANI_MARIO_RACOON_ATTACKING_LEFT;

		}

		if (isKicking)
		{
			if (nx > 0)
			{
				aniId = ID_ANI_MARIO_RACOON_KICK_RIGHT;
			}
			else
				aniId = ID_ANI_MARIO_RACOON_KICK_LEFT;
		}
		if (aniId == -1) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
	}
	else
		aniId = ID_ANI_MARIO_RACOON_FALLING_PIPE;
	
	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIDRacoon();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);
	if (level == MARIO_LEVEL_RACOON)
	{
		//tail->Render();
	}
	//RenderBoundingBox();



	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
			if (vy < 0) vy = 0;
			ay = MARIO_GRAVITY;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			ax = 0;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_KICK:
		ax = 0;
		vx = 0;
		isKicking = true;
		timeKick = GetTickCount64();
		break;
	case MARIO_STATE_FALLING_SLOWDOWN:
		if (level == MARIO_LEVEL_RACOON)
		{
			ay = 0;
			vy = MARIO_FALLING_SLOWDOWN_SPEED;
			isFalling = true;
			timeFalling = GetTickCount64();
		}
		break;
	case MARIO_STATE_FLYING:
		if (level == MARIO_LEVEL_RACOON) {
			ay = 0;
			vy = -MARIO_FLYING_SPEED;
			if (!isFlying)
			{
				timeFlying = GetTickCount64();
				isFlying = true;
			}
		}
		break;
	case MARIO_STATE_ATTACK:
		if (level == MARIO_LEVEL_RACOON && !isSitting)
		{
			vx = 0;
			isAttacking = true;
			timeAttacking = GetTickCount64();
		}
		break;
	case MARIO_STATE_HOLDING:
		if (!isSitting)
		{
			isHoldKoopas = true;
			koopas->SetSpeed(0, 0);
			koopas->ay = 0;
			koopas->isHold = true;
		}
		break;
	case MARIO_STATE_RELEASE_HOLDING:
	{
		isHoldKoopas = false;
		SetState(MARIO_STATE_KICK);
		koopas->nx = nx;
		koopas->ay = KOOPAS_GRAVITY;
		koopas->isHold = false;
		switch (koopas->GetState())
		{
		case KOOPAS_STATE_SHELL: case KOOPAS_STATE_REBORN:
		{
			koopas->SetState(KOOPAS_STATE_SHELL_MOVING);
		}
		break;
		case KOOPAS_STATE_SHELL_UP: case KOOPAS_STATE_REBORN_UP:
		{
			koopas->SetState(KOOPAS_STATE_SHELL_UP_MOVING);
		}
		break;
		default:
			break;
		}
	}
		break;
	case MARIO_STATE_RELEASE_HOLDING_A:
	{
		isHoldKoopas = false;
		koopas->nx = nx;
		koopas->ay = KOOPAS_GRAVITY;
		koopas->isHold = false;
		koopas->SetPosition(x + KOOPAS_BBOX_WIDTH / 2, y - RANGE_BETWEEN_OBJECT);
		level--;
		StartUntouchable();
		koopas->SetState(KOOPAS_STATE_WALKING);
	}
		break;
	case MARIO_STATE_FALLDOWN_PIPE:
		ay = 0;
		isOnPlatform = true;
		vy = MARIO_SPEED_SWITCH_SCENE;
		vx = 0.0f;
		ax = 0.0f;
		break;
	case MARIO_STATE_JUMPING_PIPE:
		ay = 0;
		isOnPlatform = true;
		vy = -MARIO_SPEED_SWITCH_SCENE;
		vx = 0.0f;
		ax = 0.0f;
		break;
	case MARIO_STATE_DROP_KOOPAS_SHELL:
		isHoldKoopas = false;
		koopas->nx = nx;
		koopas->SetState(KOOPAS_STATE_DIE);
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - MARIO_RACOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - (MARIO_RACOON_BBOX_WIDTH / 2);
			top = y - MARIO_RACOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH ;
			bottom = top + MARIO_RACOON_BBOX_HEIGHT;
		

		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{

	// Adjust position to avoid falling off platform
	if (level == MARIO_LEVEL_SMALL)
	{
		if (nx == 1)
		{
			x -= MARIO_WIDTH_COLLISION;
		}
		else
			x += MARIO_WIDTH_COLLISION;
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::IncreasePower() {
	if (powerStack < MARIO_MAX_POWER)
	{
		if (timeStack == 0)
			timeStack = GetTickCount64();
		else if (GetTickCount64() - timeStack > MARIO_POWER_TIME_STACK)
		{
			timeStack = 0;
			powerStack++;
		}
	}
}

void CMario::DecreasePower() {
	if (timeStack == 0)
		timeStack = GetTickCount64();
	else if (GetTickCount64() - timeStack > MARIO_POWER_TIME_STACK)
	{
		timeStack = 0;
		powerStack--;
	}
}

void CMario::SetPower()
{
	if (powerStack > 0)
	{
		powerStack = 0;
	}
}

void CMario::SetKoopas()
{
	
}