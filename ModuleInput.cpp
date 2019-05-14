#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "p2Qeue.h"
#include <iostream>
#include "SDL/include/SDL_gamecontroller.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"
#include "ModuleEnemy2.h"

ModuleInput::ModuleInput() : Module()
{
	//Starting Keyboard inputs
	for (uint i = 0; i < MAX_KEYS; ++i) {
		keyboard[i] = KEY_IDLE;
	}
	
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	
	bool ret = true;
	SDL_Init(0);
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	//Joystick
	if (SDL_NumJoysticks() < 1) {

		LOG("No Joysticks connected!\n");

	}

	else {
		//Load Joystick

		gGameController = SDL_JoystickOpen(0);
		gGameController = SDL_JoystickOpen(1);
		if (gGameController == NULL) {

			LOG("Couldn't Open Controller! SDL Error: %s\n", SDL_GetError());
		}
	}

	return ret;
}

bool ModuleInput::external_input()
{

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
				//PLAYER 1
			case SDLK_s:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				inputs.Push(IN_LEFT_UP);

				left = false;
				break;
			case SDLK_d:
				inputs.Push(IN_RIGHT_UP);

				right = false;
				break;
				//PLAYER 2
			case SDLK_k:
				inputs2.Push(IN_CROUCH_UP2);
				down2 = false;
				break;
			case SDLK_i:
				up2 = false;
				break;
			case SDLK_j:
				inputs2.Push(IN_LEFT_UP2);
				left2 = false;
				break;
			case SDLK_l:
				inputs2.Push(IN_RIGHT_UP2);
				right2 = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
				//PLAYER 1
			case SDLK_r:
				inputs.Push(IN_R);
				if (App->player2->colcreated == true)
				{
					App->player2->playerkick = App->collision->AddCollider({ 10, 30, 75, 10 }, COLLIDER_PLAYER_SHOT, this);
					App->player2->playerpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
					App->player2->colcreated = false;
				}
				break;
			case SDLK_t:
				inputs.Push(IN_T);
				if (App->player2->colcreated == true)
				{
					App->player2->playerpunch = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					App->player2->playerkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
					App->player2->colcreated = false;
				}
				break;
			case SDLK_f:
				inputs.Push(IN_F);
				break;
			case SDLK_w:
				up = true;
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_d:
				right = true;
				break;

				//PLAYER 2

			case SDLK_u:
				inputs2.Push(IN_U);
				if (App->enemy2->colcreated == true)
				{
					App->enemy2->playerkick = App->collision->AddCollider({ 10, 30, 75, 10 }, COLLIDER_ENEMY_SHOT, this);
					App->enemy2->playerpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
					App->enemy2->colcreated = false;
				}
				break;
			case SDLK_y:
				inputs2.Push(IN_Y);
				if (App->enemy2->colcreated == true)
				{
					App->enemy2->playerpunch = App->collision->AddCollider({ 10, 30, 55, 10 }, COLLIDER_ENEMY_SHOT, this);
					App->enemy2->playerkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_ENEMY_SHOT, 0);
					App->enemy2->colcreated = false;
				}
				break;
			case SDLK_h:
				inputs2.Push(IN_H);
				break;
			case SDLK_i:
				up2 = true;
				break;
			case SDLK_k:
				down2 = true;
				break;
			case SDLK_j:
				left2 = true;
				break;
			case SDLK_l:
				right2 = true;
				break;
			}
		}
		if (event.type == SDL_JOYAXISMOTION) {
			if (event.jaxis.which == 0) { //En el gamepad 0
				if (event.jaxis.axis == 0)
				{
					//Left of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						left = true;
						right = false;
					}
					//Right of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						right = true;
						left = false;
					}
					else
					{
						left = false;
						right = false;
					}
				}
				else if (event.jaxis.axis == 1)
				{
					//Below of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						down = false;
						up = true;
					}
					//Above of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						up = false;
						down = true;
					}
					else
					{
						down = false;
						up = false;
					}
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (event.jaxis.which == 1) { //En el gamepad 2
				if (event.jaxis.axis == 0)
				{
					//Left of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						left2 = true;
						right2 = false;
					}
					//Right of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						right2 = true;
						left2 = false;
					}
					else
					{
						left2 = false;
						right2 = false;
					}
				}
				else if (event.jaxis.axis == 1)
				{
					//Below of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						down2 = false;
						up2 = true;
					}
					//Above of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						up2 = false;
						down2 = true;
					}
					else
					{
						down2 = false;
						up2 = false;
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////

		}


		//PLAYER 1
		if (left && right)
			inputs.Push(IN_LEFT_AND_RIGHT);
		{
			if (left)
				inputs.Push(IN_LEFT_DOWN);
			if (right)
				inputs.Push(IN_RIGHT_DOWN);
		}

		if (!left)
			inputs.Push(IN_LEFT_UP);
		if (!right)
			inputs.Push(IN_RIGHT_UP);
		if (!down)
			inputs.Push(IN_CROUCH_UP);

		if (up && down)
			inputs.Push(IN_JUMP_AND_CROUCH);
		else
		{
			if (down)
				inputs.Push(IN_CROUCH_DOWN);
			if (up)
				inputs.Push(IN_JUMP);
		}

		//PLAYER 2
		if (left2 && right2)
			inputs2.Push(IN_LEFT_AND_RIGHT2);
		{
			if (left2)
				inputs2.Push(IN_LEFT_DOWN2);
			if (right2)
				inputs2.Push(IN_RIGHT_DOWN2);
		}
		///////////////////////////////////////
		if (!left2)
			inputs2.Push(IN_LEFT_UP2);
		if (!right2)
			inputs2.Push(IN_RIGHT_UP2);
		if (!down2)
			inputs2.Push(IN_CROUCH_UP2);
		////////////////////////////////////////
		if (up2 && down2)
			inputs2.Push(IN_JUMP_AND_CROUCH2);
		else
		{
			if (down2)
				inputs2.Push(IN_CROUCH_DOWN2);
			if (up2)
				inputs2.Push(IN_JUMP2);
		}
	}
	return true;
}

void ModuleInput::internal_input(p2Qeue<player_inputs>& inputs, p2Qeue<player_inputs>& inputs2)
{
	//PLAYER 1
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			App->player2->colcreated = true;
			App->player2->playerpunch->to_delete = true;
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (punchc_timer > 0)
	{
		if (SDL_GetTicks() - punchc_timer > PUNCHC_TIME)
		{
			inputs.Push(IN_PUNCH_CROUCH_FINISH);
			punchc_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME)
		{
			App->player2->colcreated = true;
			App->player2->playerkick->to_delete = true;
			inputs.Push(IN_KICK_FINISH);
			kick_timer = 0;
		}
	}

	if (kickc_timer > 0)
	{
		if (SDL_GetTicks() - kickc_timer > KICKC_TIME)
		{
			inputs.Push(IN_KICK_CROUCH_FINISH);
			kickc_timer = 0;
		}
	}

	if (sp1_timer > 0)
	{
		if (SDL_GetTicks() - sp1_timer > SP1_TIME)
		{
			inputs.Push(IN_SM1_FINISH);
			sp1_timer = 0;


		}
		if (SDL_GetTicks() - sp1_timer > SP1_TIME + 500)
		{
			App->player2->Activesm1 = true;
			App->enemy2->Activesm1 = true;

		}
		if (SDL_GetTicks() - sp1_timer > SP1_TIME + 2000)
		{
			App->particles->cont = 0;
		}
	}

	//PLAYER 2
	if (jump_timer2 > 0)
	{
		if (SDL_GetTicks() - jump_timer2 > JUMP_TIME)
		{
			inputs2.Push(IN_JUMP_FINISH2);
			jump_timer2 = 0;
		}
	}

	if (punch_timer2 > 0)
	{
		if (SDL_GetTicks() - punch_timer2 > PUNCH_TIME)
		{
			inputs2.Push(IN_PUNCH_FINISH2);
			punch_timer2 = 0;
		}
	}

	if (punchc_timer2 > 0)
	{
		if (SDL_GetTicks() - punchc_timer2 > PUNCHC_TIME)
		{
			inputs2.Push(IN_PUNCH_CROUCH_FINISH2);
			punchc_timer2 = 0;
		}
	}

	if (kick_timer2 > 0)
	{
		if (SDL_GetTicks() - kick_timer2 > KICK_TIME)
		{
			inputs2.Push(IN_KICK_FINISH2);
			kick_timer2 = 0;
		}
	}

	if (kickc_timer2 > 0)
	{
		if (SDL_GetTicks() - kickc_timer2 > KICKC_TIME)
		{
			inputs2.Push(IN_KICK_CROUCH_FINISH2);
			kickc_timer2 = 0;
		}
	}

	if (sp1_timer2 > 0)
	{
		if (SDL_GetTicks() - sp1_timer2 > SP1_TIME)
		{
			inputs2.Push(IN_SM1_FINISH2);
			sp1_timer2 = 0;
		}
	}

}
// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	//Put inputs to states
	if (external_input() == false) { return update_status::UPDATE_STOP; }
	else {
		internal_input(inputs, inputs2);
	}

	return update_status::UPDATE_CONTINUE;

	SDL_PumpEvents();

}

update_status ModuleInput::PostUpdate() {
	
	key = -1;
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	
	
	//Joystick
	SDL_JoystickClose(gGameController);
	gGameController = NULL;
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	
	return true;

}