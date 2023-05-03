#ifndef C_HISCORES
#define C_HISCORES
#pragma once

#include<hge.h>
#include<hgevector.h>
#include<hgefont.h>
#include<hgegui.h>
#include"c_player.h"

struct Plscore
{
	char*name;
	int hiscore;
};

class c_hiscores: public hgeGUIObject, public hgeVector 
{
	static HGE*					hge;
	int length;
	Plscore* list;
	int numb;
	int status;
	float movespeed;
	hgeFont*	Font;
	
public:
	c_hiscores(int _length);

	virtual void	Render();
	virtual void	Update(float dt);

	virtual void	Enter();
	virtual void	Leave();
	virtual bool	IsDone();
	virtual void	Focus(bool bFocused);
	virtual void	MouseOver(bool bOver);

	virtual bool	MouseLButton(bool bDown);
	virtual bool	KeyClick(int key, int chr);


	int Addscore(c_player* Player);
	
	~c_hiscores();
	int GetStatus(){return status;}
};
#endif
