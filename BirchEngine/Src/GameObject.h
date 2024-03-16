#pragma once
#include "Game.h"

class GameObject
{

public:
	GameObject(const char* texturesheet ,int x, int y );
	~GameObject();

	void Update();
	void Render();

	int getX();
	int getY();

	void setX(int x);
	void setY(int y);

private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect; 


};