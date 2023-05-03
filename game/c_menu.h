#ifndef C_MENU_H
#define C_MENU_H
#pragma once

#include <hge.h>
#include <hgegui.h>
#include "c_menu_item.h"
#include "c_hiscores.h"

class c_menu
{
private:
	
	static HGE*				hge;
	HEFFECT					Sound;
	HTEXTURE				t_BackGr;
	HTEXTURE				t_Mouse;
	hgeGUI*					gui;
	hgeGUI*					guiHelp;
	hgeGUI*					guiAbout;
	hgeGUI*					guiHiscores;
	hgeSprite*				s_Backgr;
	hgeSprite*				s_Mouse;
	HTEXTURE				t_MenuItems[5];
	HTEXTURE				t_Slider;
	HTEXTURE				t_Help;
	HTEXTURE				t_About;
	
	int						status;
	c_player*				Player;
	c_hiscores*				Hiscores;
	
	hgeFont*	Font;


public:
	c_menu(c_player* Player,c_hiscores* _List);
	~c_menu(void);
	bool Frame();
	bool Render();
	int GetStatus(){return status;}

};
#endif
