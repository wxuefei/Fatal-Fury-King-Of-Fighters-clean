#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"
#include "p2Qeue.h"

#define MAX_KEYS 500
#define JUMP_TIME 1000
#define JUMPF_TIME 1000
#define JUMPB_TIME 1000

#define PUNCH_TIME 400
#define PUNCHF_TIME 400
#define PUNCHB_TIME 400
#define PUNCHN_TIME 400
#define PUNCHC_TIME 400

#define SP1_TIME 500

#define KICK_TIME 550
#define KICKF_TIME 150
#define KICKB_TIME 150
#define KICKN_TIME 150
#define KICKC_TIME 300

#define LDAMAGE_TIME 100
#define HDAMAGE_TIME 200
#define HHDAMAGE_TIME 300

enum player_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,

	ST_JUMP_NEUTRAL,
	ST_JUMP_FORWARD,
	ST_JUMP_BACKWARD,

	ST_CROUCH,

	ST_PUNCH_STANDING,
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH,

	ST_KICK_STANDING,
	ST_KICK_NEUTRAL_JUMP,
	ST_KICK_FORWARD_JUMP,
	ST_KICK_BACKWARD_JUMP,
	ST_KICK_CROUCH,

	ST_HIT,
	ST_SM1

};

enum player_inputs
{
	// PLAYER 1
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	IN_LEFT_AND_RIGHT,
	IN_JUMP,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_JUMP_AND_CROUCH,
	IN_V,
	IN_T,
	IN_R,
	IN_F,
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_PUNCH_CROUCH_FINISH,
	IN_KICK_FINISH,
	IN_KICK_CROUCH_FINISH,
	IN_SM1_FINISH,

	// PLAYER 2
	IN_LEFT_DOWN2,
	IN_LEFT_UP2,
	IN_RIGHT_DOWN2,
	IN_RIGHT_UP2,
	IN_LEFT_AND_RIGHT2,
	IN_JUMP2,
	IN_CROUCH_UP2,
	IN_CROUCH_DOWN2,
	IN_JUMP_AND_CROUCH2,
	IN_B,
	IN_Y,
	IN_U,
	IN_H,
	IN_JUMP_FINISH2,
	IN_PUNCH_FINISH2,
	IN_PUNCH_CROUCH_FINISH2,
	IN_KICK_FINISH2,
	IN_KICK_CROUCH_FINISH2,
	IN_SM1_FINISH2

};

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	bool external_input();
	void internal_input(p2Qeue<player_inputs>& inputs, p2Qeue<player_inputs>& inputs2);

public:

	KEY_STATE keyboard[MAX_KEYS];
	int j = 0;
	int y = 0;
	int t = 0;
	int r = 0;
	int o = 0;
	int p = 0;
	int i = 0;
	int u = 0;
	p2Qeue<player_inputs> inputs;
	p2Qeue<player_inputs> inputs2;

	bool left = false;
	bool right = false;
	bool down = false;
	bool up = false;

	bool left2 = false;
	bool right2 = false;
	bool down2 = false;
	bool up2 = false;

	int key = -1;

	Uint32 jump_timer = 0;
	Uint32 jumpf_timer = 0;
	Uint32 jumpb_timer = 0;

	Uint32 punch_timer = 0;
	Uint32 punchc_timer = 0;
	Uint32 punchf_timer = 0;
	Uint32 punchb_timer = 0;
	Uint32 punchn_timer = 0;

	Uint32 sp1_timer = 0;

	Uint32 kick_timer = 0;
	Uint32 kickc_timer = 0;
	Uint32 kickf_timer = 0;
	Uint32 kickb_timer = 0;
	Uint32 kickn_timer = 0;

	Uint32 ldamage_timer = 0;
	Uint32 hdamage_timer = 0;
	Uint32 hhdamage_timer = 0;

	Uint32 jump_timer2 = 0;
	Uint32 jumpf_timer2 = 0;
	Uint32 jumpb_timer2 = 0;

	Uint32 punch_timer2 = 0;
	Uint32 punchc_timer2 = 0;
	Uint32 punchf_timer2 = 0;
	Uint32 punchb_timer2 = 0;
	Uint32 punchn_timer2 = 0;

	Uint32 sp1_timer2 = 0;

	Uint32 kick_timer2 = 0;
	Uint32 kickc_timer2 = 0;
	Uint32 kickf_timer2 = 0;
	Uint32 kickb_timer2 = 0;
	Uint32 kickn_timer2 = 0;

	Uint32 ldamage_timer2 = 0;
	Uint32 hdamage_timer2 = 0;
	Uint32 hhdamage_timer2 = 0;

	const int GAMEPAD_DEAD_ZONE = 8000;

	SDL_GameController* gamepad1 = NULL;
	SDL_GameController* gamepad2 = NULL;

};

#endif // __Module