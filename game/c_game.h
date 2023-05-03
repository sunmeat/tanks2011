#pragma once
#ifndef C_GAME
#define C_GAME

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgeparticle.h>
#include <time.h>
#include <list>
#include <hgefont.h>
// подключение моих классов
#include "c_player.h"
#include "c_labir.h"
#include "c_enemy.h"
#include "c_bonus.h"
#include "c_bullet.h"
#include "c_bonus.h"
#include "c_base.h"
#include "c_hiscores.h"
#include "c_menu_item.h"

struct explosion
{
    hgeAnimation*   Animation;
    hgeVector       Position;
};


class c_game
{
	static HGE*		hge;
	
	HTEXTURE    g_tBackground;
 	hgeSprite*  g_sBackground;
	hgeSprite*  g_sGameover;
	hgeSprite*  g_sMouse;
	hgeGUI*		gui;
 	hgeVector   g_vBGPosition;
	HTEXTURE    g_tExplosion;
	HTEXTURE    g_tExplosionSm;
	HTEXTURE	g_tGameover;
	HTEXTURE    g_tBonus;
	HTEXTURE	g_tBase;
	HTEXTURE	EnTexture[5];
	HTEXTURE	BuTexture[5];
	HTEXTURE	t_Exite;
	HTEXTURE	t_Exite2;
	HEFFECT     g_eExplosion;
	HEFFECT     g_eBullets;
	HEFFECT     BackMusic;
	HEFFECT		BonusSound;
	HEFFECT		MSound;
	hgeFont*	Font;
	c_player*   Player;
	c_labir*	Labirint;
	c_enemy*	Enemy;
	c_bullet*   MyBullet; 
	c_bullet*	EnBullet;
	c_bonus*    Bonus;
	c_base*		Base;

	c_hiscores* ListHiscores;
	
	std::list<c_bullet*> My_Bullets;
	std::list<c_enemy*> Enemies;
	std::list<c_bullet*> En_Bullets;
	std::list<explosion> Explosions;
	std::list<c_bonus*> Bonuses;
	std::list<explosion> ExplosionsSm;

	int				Status_Game;
	int				TimerGameOver;
	int				HowManyEnemies;
	float				GameTime;

public:
	c_game(c_player* _Player,c_hiscores* _List);
	~c_game(void);
	void			CreateExplosion(hgeVector Position);
	void			CreateExplosionSm(hgeVector Position);
	void			Erase();
	bool			LoadState(int stage);
	void			Bang();
	bool			Frame();
	bool			Render();
	int				GetStatusGame(){return Status_Game;}
	int				numbOFenemy;
};
#endif
