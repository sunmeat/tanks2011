#pragma once
#ifndef C_ENEMY_H
#define C_ENEMY_H
#pragma once
 
#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include "c_labir.h"
#include <list>
#include "c_player.h"
#include <time.h>
using namespace std;

class c_enemy
{
private:
	static HGE*		hge;
	hgeVector		Position;
	hgeAnimation*	Sprite;
	hgeRect			BoundingBox;

	hgeSprite*		PSprite;
	HTEXTURE		Ptexture;
   	hgeParticleSystem*	par;

	float           Speed;
	int				vector;
	int				number;
	float			Health;
	bool			WantShoot;
	int				Score;
	float			Damage;
	int				TimerShoot;
	int				Level;
	
public:
	 c_enemy(hgeVector Position,int vector,int number,int score,HTEXTURE Texture,int _Damage,int _Level);
	 ~c_enemy();

	 bool Update(float delta,c_labir*labirint,list<c_enemy*> Enemies,c_player* Player1);// метод логики врага
     void Render();

	 void        SetPosition(hgeVector position) { Position = position; };
     hgeRect     GetBoundingBox() { return BoundingBox; };
     hgeVector   GetPosition() { return Position; };
	 void		 CheckMove(c_labir* Labirint);
	 int		 GetNumber(){return number;}
	 int         GetHealth(){return Health;}
	 void		 SetHealth(int health){Health=health;}
	 bool		 GetWantShoot(){return WantShoot;}
	 int		 GetVector(){return vector;}
	 int		 GetScore(){return Score;}
	 int		 GetDamage(){return Damage;}
};



#endif