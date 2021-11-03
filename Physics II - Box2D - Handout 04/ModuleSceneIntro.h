#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	
	p2List<PhysBody*> hitbox;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* background;
    SDL_Texture* circle;
	
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;


	// Background
	int hitbox1[146] = {
		98, 422,
		38, 388,
		38, 400,
		21, 400,
		22, 327,
		28, 319,
		42, 319,
		45, 312,
		44, 287,
		35, 279,
		27, 263,
		15, 238,
		8, 208,
		10, 177,
		11, 170,
		10, 144,
		10, 123,
		14, 104,
		21, 87,
		37, 63,
		52, 51,
		63, 46,
		80, 40,
		91, 35,
		112, 27,
		127, 25,
		145, 20,
		162, 18,
		186, 18,
		208, 17,
		223, 20,
		235, 26,
		244, 36,
		249, 49,
		250, 64,
		250, 81,
		249, 97,
		248, 409,
		234, 411,
		229, 98,
		226, 77,
		222, 56,
		209, 46,
		190, 40,
		172, 36,
		161, 36,
		148, 38,
		126, 44,
		144, 54,
		152, 66,
		164, 72,
		178, 77,
		194, 87,
		206, 102,
		214, 116,
		221, 141,
		223, 162,
		224, 189,
		226, 208,
		223, 233,
		216, 248,
		206, 269,
		192, 287,
		190, 312,
		193, 316,
		202, 317,
		211, 321,
		213, 328,
		214, 340,
		213, 397,
		198, 400,
		197, 388,
		140, 423
	};
};
