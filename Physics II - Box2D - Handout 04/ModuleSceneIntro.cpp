#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/Ball_PNG.png"); 
	center = App->textures->Load("pinball/poke_center.png");
	screen = App->textures->Load("pinball/tv_screen.png");
	background = App->textures->Load("pinball/fondo.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	hitbox.add(App->physics->CreateChain(0, 0, hitbox2, 166));
	hitboxa.add(App->physics->CreateChain(0, 0, hitbox3, 38));
	hitboxb.add(App->physics->CreateChain(0, 0, hitbox4, 20));
	hitboxc.add(App->physics->CreateChain(0, 0, hitbox5, 16));
	hitboxd.add(App->physics->CreateChain(0, 0, hitbox6, 70));
	hitboxe.add(App->physics->CreateChain(0, 0, hitbox7, 8));
	hitboxf.add(App->physics->CreateChain(0, 0, hitbox8, 8));
	hitboxg.add(App->physics->CreateChain(0, 0, hitbox9, 32));
	hitboxh.add(App->physics->CreateChain(0, 0, hitbox10, 36));

	rectangles.add(App->physics->CreateRectangle(103, 403, 25, 7));
	flickerA = rectangles.getLast()->data;

	rectangles2.add(App->physics->CreateRectangle(130, 403, 25, 7));
	flickerD = rectangles2.getLast()->data;


	circles.add(App->physics->CreateCircle(242, 350, 8));
	ball = circles.getLast()->data;
	//circles.getLast()->data->listener = this;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Flicker A movement

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		flickerA->body->SetAngularVelocity({ -50 });
		
	} 
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		flickerA->body->SetAngularVelocity({ 0 });

	}

	//Flicker D movement

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		flickerD->body->SetAngularVelocity({ 50 });

	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		flickerD->body->SetAngularVelocity({ 0 });

	}

	//Propeller movement
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ball->body->ApplyForceToCenter({0, -55}, true);

	}

	/*
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	*/

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8));
		circles.getLast()->data->listener = this;
	}
	

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();
	App->renderer->Blit(background, 0, 0, NULL, 1.0f);
	App->renderer->Blit(center, 160, 16, NULL, 1.0f);
	App->renderer->Blit(screen, 20, 110, NULL, 1.0f);

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
