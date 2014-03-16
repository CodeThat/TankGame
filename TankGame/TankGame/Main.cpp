#include "StdAfx.h"
#include "Main.h"

CMain::CMain(int passed_ScreenWidth, int passedScreenHeight)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passedScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

	grass = new CSprite(csdl_setup->GetRenderer(), "data/grass.bmp", 0, 0, ScreenWidth, ScreenHeight);
	
	tank = new CSprite(csdl_setup->GetRenderer(), "data/tank.png", 300, 250, 50, 60);
}

CMain::~CMain(void)
{
	delete csdl_setup;
	delete grass;
	delete tank;
}

void CMain::GameLoop(void)  //draw game
{
	while(!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->Begin();

		grass->Draw();
		tank->Draw();

		switch(csdl_setup->GetMainEvent()->type)
		{
		case SDL_KEYDOWN:

			switch(csdl_setup->GetMainEvent()->key.keysym.sym)
			{
			case SDLK_a:
				tank->SetX(tank->GetX() -1 ); //subtract one from current position, move up
				break;
			case SDLK_s:
				tank->SetY(tank->GetY() +1 ); //add one from current position, move down
				break;
			case SDLK_d:
				tank->SetX(tank->GetX() +1 ); 
				break;
			case SDLK_w:
				tank->SetY(tank->GetY() -1 );
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}		
		csdl_setup->End();
	}
}

