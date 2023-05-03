#ifndef C_MENU_ITEM
#define C_MENU_ITEM
#pragma once

#include<hge.h>
#include<hgegui.h>
#include<hgevector.h>
#include<hgeanim.h>
#include<hgeparticle.h>

class c_menu_item: public hgeGUIObject, public hgeVector 
{
public:
	c_menu_item(int id,HTEXTURE Tex, HEFFECT Snd,HTEXTURE Sld, float x, float y);
	c_menu_item(int _id,HTEXTURE Tex,HEFFECT Snd, HTEXTURE Sld, float _x, float _y,float wx,float wy);

	virtual void	Render();
	virtual void	Update(float dt);

	virtual void	Enter();
	virtual void	Leave();
	virtual bool	IsDone();
	virtual void	Focus(bool bFocused);
	virtual void	MouseOver(bool bOver);

	virtual bool	MouseLButton(bool bDown);
	virtual bool	KeyClick(int key, int chr);
	
		
	~c_menu_item();
private:
	static HGE*					hge;
	HEFFECT					Sound;

	hgeParticleSystem*	par;
	HTEXTURE				PTexture;
	hgeSprite*				PSprite;
	hgeSprite*				It_Sprite;

	float					delay;
	bool					Vis_Slider;
	bool					Exit;
	int						move;
	int						speed;
	int						stposx;
	int						endposx;
	
	
};

#endif
