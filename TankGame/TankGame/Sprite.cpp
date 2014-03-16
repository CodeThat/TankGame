#include "StdAfx.h"
#include "Sprite.h"

CSprite::CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h)
{
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());

	if(image == NULL)
	{
		std::cout << "Couldn't load" << FilePath.c_str() << std::endl;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

CSprite::~CSprite(void)
{
	SDL_DestroyTexture(image);
}

void CSprite::Draw()
{
    SDL_RenderCopy(renderer,image, NULL, &rect);
}

void CSprite::SetX(int x)
{
	rect.x = x;
}

void CSprite::SetY(int y)
{
	rect.y = y;
}

void CSprite::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

int CSprite::GetX()
{
	return rect.x;
}

int CSprite::GetY()
{
	return rect.y;
}