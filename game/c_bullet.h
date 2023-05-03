#pragma once
#ifndef C_BULLET_H
#define C_BULLET_H
#pragma once
 
#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include "c_enemy.h"
#include "c_labir.h"
#include "c_player.h"
#include <list>


class c_bullet
{
private:
	static HGE* hge;
	hgeVector       Position;

	hgeAnimation*   Sprite;
    hgeRect         BoundingBox; //Needed for collision detection 
    float           Speed;
	int				vector;
	int				damage;
public:
	public:
    c_bullet(hgeVector Position,int vector,HTEXTURE Texture,int _damage);
    ~c_bullet();
	void Update(float delta);
	void Render();
	hgeRect     GetBoundingBox() { return BoundingBox; };
	hgeVector		GetPosition(){return Position;}
	float GetPosX(){return Position.x;}
	float GetPosY(){return Position.y;}
	int   GetVector(){return vector;}
	int		GetDamage(){return damage;}
	
};
#endif