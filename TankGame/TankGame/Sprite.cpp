#include "StdAfx.h"
#include "Sprite.h"

CSprite::CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h)
{
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());

	if (image == NULL)
	{
		std::cout << "Couldn't Load " << FilePath.c_str() << std::endl;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	
	crop.x = 0;
	crop.y - 0;
	crop.w = 0;
	crop.h - 0;

	X_pos = x;
	Y_pos = y;

	Orgin_X = 0;
	Orgin_Y = 0;
}


CSprite::~CSprite(void)
{
	SDL_DestroyTexture(image);
}

void CSprite::Draw()
{
	SDL_RenderCopy(renderer, image, NULL, &rect);
}

void CSprite::SetX(float X)
{
	X_pos = X;

	rect.x = int(X_pos - Orgin_X);
}

void CSprite::SetY(float Y)
{
	Y_pos = Y;

	rect.y = int(Y_pos - Orgin_Y);
}

void CSprite::SetPosition(float X, float Y)
{
	X_pos = X;
	Y_pos = Y;

	rect.x = int(X_pos - Orgin_X);
	rect.y = int(Y_pos - Orgin_Y);
}

float CSprite::GetX()
{
	return X_pos;
}

float CSprite::GetY()
{
	return Y_pos;
}

void CSprite::SetOrgin(float X, float Y)
{
	Orgin_X = X;
	Orgin_Y = Y;

	SetPosition(GetX(), GetY());

}

void CSprite::SetWidth(int W)
{
	rect.w = W;
}

void CSprite::SetHeight(int H)
{
	rect.h = H;
}

int CSprite::GetWidth()
{
	return rect.w;
}

int CSprite::GetHeight()
{
	return rect.h;
}