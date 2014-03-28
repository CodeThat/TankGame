#pragma once

class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h);
	~CSprite(void);

	void Draw();

	void SetX(float X);
	void SetY(float Y);
	void SetPosition(float X, float Y);

	float GetX();
	float GetY();

	void SetWidth(int W);
	void SetHeight(int H);
	int GetWidth();
	int GetHeight();

	void SetOrgin(float X, float Y);

private:
	float Orgin_X;
	float Orgin_Y;

	float X_pos;
	float Y_pos;

	SDL_Texture* image;
	SDL_Rect rect;
	SDL_Rect crop;
	int img_width;
	int img_height;

	SDL_Renderer* renderer;
};