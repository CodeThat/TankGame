#include "StdAfx.h"
#include "Main.h"

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

	grass = new CSprite(csdl_setup->GetRenderer(), "data/grass.bmp", 0, 0, ScreenWidth, ScreenHeight);
	tank = new CSprite(csdl_setup->GetRenderer(), "data/tank.png", 300, 250, 75, 75);
	tank->SetOrgin(tank->GetWidth() / 2.0f, tank->GetHeight());

	timeCheck = SDL_GetTicks();
	MouseX = 0;
	MouseY = 0;
	Follow = false;
}


CMain::~CMain(void)
{
	delete csdl_setup;
	delete grass;
	delete tank;
}

double CMain::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}

void CMain::GameLoop(void)
{
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->Begin();
		SDL_GetMouseState(&MouseX, &MouseY);

		grass->Draw();
		tank->Draw();

		if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
		{
			if (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
			{
				Follow_Point_X = MouseX;
				Follow_Point_Y = MouseY;
				Follow = true;
			}
		}

		if (timeCheck + 10 < SDL_GetTicks() && Follow)
		{

			float distance = GetDistance(tank->GetX(), tank->GetY(), Follow_Point_X, Follow_Point_Y);

			if (distance > 1.0)
			{
				if (tank->GetX() != Follow_Point_X)
				{
					tank->SetX(tank->GetX() - ((tank->GetX() - Follow_Point_X) / distance) * 1.5f);
				}

				if (tank->GetY() != Follow_Point_Y)
				{
					tank->SetY(tank->GetY() - ((tank->GetY() - Follow_Point_Y) / distance) * 1.5f);
				}
			}
			else
				Follow = false;

			timeCheck = SDL_GetTicks();
		}

		csdl_setup->End();
	}
}