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

	circle = App->textures->Load("pinball/wheel.png"); 
	
	background = App->textures->Load("pinball/fondo.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	kickerD = App->textures->Load("pinball/KickerDer.png");
	kickerI = App->textures->Load("pinball/KickerIzq.png");

	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	hitbox.add(App->physics->CreateChain(0, 0, hitbox2, 166));
	hitboxa.add(App->physics->CreateChain(0, 0, hitbox3, 38));
	hitboxb.add(App->physics->CreateChain(0, 0, hitbox4, 20));
	hitboxc.add(App->physics->CreateChain(0, 0, hitbox5, 16));
	hitboxd.add(App->physics->CreateChain(0, 0, hitbox6, 70));
	hitboxe.add(App->physics->CreateChain(0, 0, hitbox7, 8));
	hitboxf.add(App->physics->CreateChain(0, 0, hitbox8, 8));

	
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
<<<<<<< HEAD
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->physics->motor = true;
		
	} 

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ball->body->ApplyForceToCenter({0, -55}, true);

	}

	/*
=======
	graphics = App->textures->Load("pinball/Ball_PNG.png");
	App->renderer->Blit(background, 0, 0, NULL, 1.0f);

	if (createball == true)
	{
		player = App->physics->CreateCircle(245, 380, 7);
		player->listener = App->scene_intro;
		b2Filter b;
		b.categoryBits = ON;
		b.maskBits = ON | OFF;
		player->body->GetFixtureList()->SetFilterData(b);
		createball = false;
	}
	player->body->SetBullet(true);

	if ((player->body->GetPosition().x > 364) && (player->body->GetPosition().y > 280)) //sets restitution only if ball has departed
	{
		player->body->GetFixtureList()->SetRestitution(0.3);
	}

	int playerPositionX, playerPositionY;
	player->GetPosition(playerPositionX, playerPositionY);
	App->renderer->Blit(graphics, playerPositionX, playerPositionY, NULL, 1.0f, player->GetRotation());
>>>>>>> d27644b5a4b176f133e37aabfe0959df856a0ed5
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
	
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	if (kickerIzq) {
		App->renderer->Blit(kickerI, 78, 377, NULL, 0.25, -30);
	}
	else {
		App->renderer->Blit(kickerI, 78, 394, NULL, 0.25, 12);
	}
	
	if (kickerDer) {
		App->renderer->Blit(kickerD, 120, 377, NULL, 0.25, 30);
	}
	else {
		App->renderer->Blit(kickerD, 120, 394, NULL, 0.25, -12);
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
