//hge interfeus
#include <hge.h>

//my class
#include "c_menu.h"
#include "c_game.h"
#include "c_hiscores.h"

//initial
static HGE*				hge;
c_menu*					Menu;
c_game*					Game;
c_player*				Player;
c_hiscores*				Listscores;
enum					s_state{ST_MENU=0,ST_NAME,ST_GAME} status;

bool Frame()
{
	float delta = hge->Timer_GetDelta();
	switch(status)
	{
	case ST_MENU:
		if(Menu->Frame())status=ST_NAME;
		if(Menu->GetStatus()==5)return true;
		break;
	case ST_NAME:
		if(Player->UpdateName(delta))status=ST_GAME;
		break;
	case ST_GAME:
		if(Game->Frame()){
			
			if(Game->GetStatusGame()==0)
			{
				status=ST_MENU;
				delete Menu;
				Menu		= new c_menu(Player,Listscores);
				delete Game;
				Game		= new c_game(Player,Listscores);
			}
			else if(Game->GetStatusGame()==2){
				Player->SetRound();
				delete Game;
				Game		= new c_game(Player,Listscores);
				Game->LoadState(Player->GetRound());
			}
		}

		break;
	}
	return false;

}

bool Render()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);//очистка сцены
	
	switch(status)
	{
	case ST_MENU:
		Menu->Render();
		break;
	case ST_NAME:
		Player->RenderName();
		break;
	case ST_GAME:
		Game->Render();
		break;
	}
	hge->Gfx_EndScene();
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//init window HGE
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_LOGFILE, "game.log");
	hge->System_SetState(HGE_FRAMEFUNC, Frame);
	hge->System_SetState(HGE_RENDERFUNC, Render);
	hge->System_SetState(HGE_TITLE, "Victory tank");
	hge->System_SetState(HGE_FPS, 100);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 900);
	hge->System_SetState(HGE_SCREENHEIGHT, 800);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_USESOUND,true);


	if(hge->System_Initiate()) 
	{
		Listscores	= new c_hiscores(8);
		Player		= new c_player(hgeVector(252, 703),0);
		Menu		= new c_menu(Player,Listscores);
		Game		= new c_game(Player,Listscores);
		
		status		= ST_MENU;
		hge->System_Start();

		delete Player;
		delete Menu;
		delete Game;
	}
	
	hge->System_Shutdown();
	hge->Release();
	return 0;
}