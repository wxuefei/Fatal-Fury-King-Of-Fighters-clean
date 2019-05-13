#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include <iostream>
#include "SDL/include/SDL_gamecontroller.h"

using namespace std;

ModuleInput::ModuleInput() : Module()
{
	//Starting Keyboard inputs
	for (uint i = 0; i < MAX_KEYS; ++i) {
		keyboard[i] = KEY_IDLE;
	}

	//Starting Gamepad inputs
	for (uint j = 0; j < SDL_NumJoysticks(); j++) {
		if (SDL_IsGameController(j)) {
			controller = SDL_GameControllerOpen(j);
			cout << SDL_GameControllerMapping(controller) << endl;
			break;
		}
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
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	//SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	//Joystick
	/*if (SDL_NumJoysticks() < 1) {

		LOG("No Joysticks connected!\n");

	}

	else {
		//Load Joystick

		gGameController = SDL_JoystickOpen(0);
		if (gGameController == NULL) {

			LOG("Couldn't Open Controller! SDL Error: %s\n", SDL_GetError());
		}
	}*/

	return ret;
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

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	//Joystick
	/*SDL_JoystickClose(gGameController);
	gGameController = NULL;
	LOG("Quitting Input");*/
	return true;
}