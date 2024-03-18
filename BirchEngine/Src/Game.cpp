#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;

// Rederizador del jeugo
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,1550,1350 };

// 
AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;
int playerHealth = 3;
int energia = 100;

auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& labelVida(manager.addEntity());
auto& labelEnergia(manager.addEntity());
//----------------------------------------------------------------------------------------------
Game::Game()
{}
//----------------------------------------------------------------------------------------------

Game::~Game()
{}
//----------------------------------------------------------------------------------------------

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	assets->AddTexture("terrain", "assets_nosotros/mapa_ss.png");
	assets->AddTexture("player", "assets_nosotros/Pikachu_Spritesheet.png");
	assets->AddTexture("projectile", "assets/proj.png");
	assets->AddTexture("Object", "assets_nosotros/cc01.png");
	assets->AddTexture("enemy", "assets_nosotros/MUK_ch_d.png");

	assets->AddFont("arial", "assets/arial.ttf", 16);

	map = new Map("terrain", 3, 32);
	//ecs implementation

	map->LoadMap("assets_nosotros/mapa.map", 25, 20);

	player.addComponent<TransformComponent>(700.0f, 540.0f, 32, 32, 2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	SDL_Color white = { 255, 255, 255, 255 };

	label.addComponent<UILabel>(10, 10, "Test String", "arial", white);
	labelVida.addComponent<UILabel>(250, 10, "Vida", "Arial", white);
	labelEnergia.addComponent<UILabel>(350, 10, "Energia", "Arial", white);

	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");

	assets->CreateObject(Vector2D(612, 785), "Object");
	assets->CreateEnemy(Vector2D(520, 800), "enemy");

}
//----------------------------------------------------------------------------------------------
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& objects(manager.getGroup(Game::groupObjects));
auto& enemies(manager.getGroup(Game::groupEnemies));
//----------------------------------------------------------------------------------------------
void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------------------------
void Game::update()
{
	// Obtencion de las coordenadas 
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	

	std::stringstream ss, sv;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

	sv << "Player health: " << playerHealth;
	labelVida.getComponent<UILabel>().SetLabelText(sv.str(), "arial");


	manager.refresh();
	manager.update();

	// Colisiones con los objetos
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player!" << std::endl;
			p->destroy();
		}
	}
	
	for (auto& o : objects)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, o->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Objeto Recogido!" << std::endl;
			o->destroy();
		}
	}
	
	for (auto& e : enemies)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, e->getComponent<ColliderComponent>().collider))
		{
			std::cout << "CUIADDO TE HAN LASTIMADO" << std::endl;
			playerHealth -= 1;
			e->destroy();
		}
	}

	// Control de camara
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}
//----------------------------------------------------------------------------------------------
void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}
	for (auto& o : objects)
	{
		o->draw();
	}

	for (auto& e : enemies)
	{
		e->draw();
	}

	label.draw();
	labelVida.draw();

	SDL_RenderPresent(renderer);
}
//----------------------------------------------------------------------------------------------
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
//----------------------------------------------------------------------------------------------