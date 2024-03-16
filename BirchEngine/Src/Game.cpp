#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
//#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabel : std::size_t 
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};


Game::Game()
{}

Game::~Game()
{}

//---------------------------------------------------------------------------
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

	map = new Map();
	//ecs implementacion
	
	this->camino = Map::LoadMap("assets/map.map", 32, 32);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/pikachu_0.png");
	player.addComponent<KeyBoardController>(this->camino);
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	

	wall.addComponent<TransformComponent>(300.f, 300.0f, 40, 20, 1);
	wall.addComponent<SpriteComponent>("assets/poso_de_Voltorbs.gif");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
}
//---------------------------------------------------------------------------
void Game::handleEvents()
{
	

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------
void Game::update()
{
	manager.update();
	manager.refresh();
	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		
	}

}
//---------------------------------------------------------------------------
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

//---------------------------------------------------------------------------
void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);

}
//---------------------------------------------------------------------------
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::addTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}

//vector<Nodo*> Game::getCamino() {
//	return camino;
//}