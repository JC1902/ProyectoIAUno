#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
//#include "Nodo.h"
//#include "Grafo.h"
#include <thread>
#include <chrono>

class KeyBoardController : public Component
{
public:
	int casillaNodoX;
	int casillaNodoY;
	int casillaValor;
	int posicionPersonajeX;
	int posicionPersonajeY;
	int difPosX;
	int difPosY;
	TransformComponent* transform;
	KeyBoardController(vector<Nodo*> camino) {
		this->caminoFinal = camino;
	};
	KeyBoardController() = default;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

	}
	void pressKey(SDL_Keycode key) {
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.keysym.sym = key;
		SDL_PushEvent(&event);

	}
	void update() override
	{

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				if (!this->caminoFinal.empty()) {
					vector<Nodo*>camino = this->caminoFinal;

					for (Nodo* nodo : camino) {
						casillaNodoX = nodo->getX();
						casillaNodoY = nodo->getY();
						casillaValor = nodo->getValorCasilla();
						posicionPersonajeX = transform->position.x + 15;


						posicionPersonajeY = transform->position.y + 15;


						if (casillaValor == 1) {
							transform->position.x -= 15;
							transform->position.y -= 15;

						}
						else {
							difPosX = casillaNodoX - posicionPersonajeX;
							difPosY = casillaNodoY - posicionPersonajeY;
							if (difPosX >= 0 && difPosY >= 0) {
								for (int i = 0; i < difPosX; i++)
								{

									//transform->position.x += 1;
									pressKey(SDLK_d);
									//std::this_thread::sleep_for(std::chrono::milliseconds(100));
								}
								for (int j = 0; j < difPosY;j++) {
									//transform->position.y += 1;
									pressKey(SDLK_s);
									//std::this_thread::sleep_for(std::chrono::milliseconds(100));
								}
							}
							if (difPosX < 0 && difPosY < 0) {
								for (int i = 0; i < (difPosX * -1); i++)
								{

									//transform->position.x -= 1;
									pressKey(SDLK_a);
									//std::this_thread::sleep_for(std::chrono::milliseconds(500));
								}
								for (int j = 0; j < (difPosY * -1);j++) {
									pressKey(SDLK_w);
									//transform->position.y -= 1;
									//std::this_thread::sleep_for(std::chrono::milliseconds(500));
								}
							}
							if (difPosX < 0 && difPosY >= 0) {
								for (int i = 0; i < (difPosX * -1); i++)
								{
									//transform->position.x -= 1;
									pressKey(SDLK_a);
									//std::this_thread::sleep_for(std::chrono::milliseconds(500));
								}
								for (int j = 0; j < difPosY;j++) {
									//transform->position.y += 1;
									pressKey(SDLK_s);
									//std::this_thread::sleep_for(std::chrono::milliseconds(500));
								}
							}
							if (difPosX >= 0 && difPosY < 0) {
								for (int i = 0; i < difPosX; i++)
								{
									pressKey(SDLK_d);
									//transform->position.x += 1;
									//std::this_thread::sleep_for(std::chrono::milliseconds(500));
								}
								for (int j = 0; j < (difPosY * -1);j++) {
									//transform->position.y -= 1;
									pressKey(SDLK_w);
									//std::this_thread::sleep_for(std::chrono::milliseconds(500));
								}
							}
						}




						/*if (posicionPersonajeX < casillaX) {
							while (posicionPersonajeX != casillaX) {
								transform->velocity.x = + 1;

							}
						}
						if (posicionPersonajeX > casillaX) {
							while (posicionPersonajeX != casillaX) {
								transform->velocity.x = -1;
							}
						}*/
					}

				}
				break;
			case SDLK_j:
				transform->position.y -= 1;
				break;
			case SDLK_a:
				transform->position.x -= 1;
				break;
			case SDLK_d:
				transform->position.x += 1;
				break;
			case SDLK_s:
				transform->position.y += 1;
				break;
			default:
				break;


			}
		}

		/*if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			default:
				break;


			}
		}*/

	}
private:
	vector<Nodo*> caminoFinal;

};