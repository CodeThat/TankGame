#include "StdAfx.h"
#include "Main.h"


CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

	grass = new CSprite(csdl_setup->GetRenderer(), "data/grass.bmp", 0, 0, ScreenWidth, ScreenHeight);

	bob = new CSprite(csdl_setup->GetRenderer(), "data/tom.png", 300, 250, 100, 120);
	bob->SetUpAnimation(4, 4);
	bob->SetOrgin(bob->GetWidth() / 2.0f, bob->GetHeight());

	timeCheck = SDL_GetTicks();
	MouseX = 0;
	MouseY = 0;
	Follow = false;
	distance = 0;
	stopAnimation = false;
}


CMain::~CMain(void)
{
	delete csdl_setup;
	delete grass;
	delete bob;
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
		bob->Draw();

		float angle = atan2(Follow_Point_Y - bob->GetY(), Follow_Point_X - bob->GetX());
		angle = (angle * (180 / 3.14)) + 180;

		if (!stopAnimation)
		{
			if (angle > 45 && angle <= 135)
			{
				//up

				if (distance > 15)
					bob->PlayAnimation(0, 3, 3, 200);
				else
					bob->PlayAnimation(1, 1, 3, 200);
			}
			else if (angle > 135 && angle <= 225)
			{
				//right
				if (distance > 15)
					bob->PlayAnimation(0, 3, 2, 200);
				else
					bob->PlayAnimation(1, 1, 2, 200);
			}
			else if (angle > 225 && angle <= 315)
			{
				//down
				if (distance > 15)
					bob->PlayAnimation(0, 3, 0, 200);
				else
					bob->PlayAnimation(1, 1, 0, 200);
			}
			else if ((angle <= 360 && angle > 315) || (angle >= 0 && angle <= 45))
			{
				//left
				if (distance > 20)
					bob->PlayAnimation(0, 3, 1, 200);
				else
					bob->PlayAnimation(1, 1, 1, 200);
			}
		}



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

			distance = GetDistance(bob->GetX(), bob->GetY(), Follow_Point_X, Follow_Point_Y);

			if (distance == 0)
				stopAnimation = true;
			else
				stopAnimation = false;


			if (distance > 15)
			{
				if (bob->GetX() != Follow_Point_X)
				{
					bob->SetX(bob->GetX() - ((bob->GetX() - Follow_Point_X) / distance) * 1.5f);
				}

				if (bob->GetY() != Follow_Point_Y)
				{
					bob->SetY(bob->GetY() - ((bob->GetY() - Follow_Point_Y) / distance) * 1.5f);
				}
			}
			else
				Follow = false;

			timeCheck = SDL_GetTicks();
		}

		csdl_setup->End();
	}
}