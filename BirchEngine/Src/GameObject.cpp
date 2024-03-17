#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* texturesheet, int x, int y)
{
	
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;

}
//---------------------------------------------------------------------------
void GameObject::Update()
{
	
	//xpos++;
	//ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2 ;
	destRect.h = srcRect.h * 2 ;
}
//---------------------------------------------------------------------------
void GameObject::Render()
{
	//SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);

}
//---------------------------------------------------------------------------
int GameObject::getX()
{
	return xpos;
}
//---------------------------------------------------------------------------
int GameObject::getY()
{
	return ypos;
}
//---------------------------------------------------------------------------
void GameObject::setX(int x)
{
	xpos = x;
}
//---------------------------------------------------------------------------
void GameObject::setY(int y)
{
	ypos = y;
}
