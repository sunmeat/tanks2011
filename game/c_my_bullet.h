#ifndef C_MY_BULLET_H
#define C_MY_BULLET_H
#pragma once
 
#include <hge.h>
#include <hgesprite.h>
#include <hgerect.h>
#include <hgevector.h>
#include <list>
#include "c_enemy.h"
#include "c_labir.h"
  
class c_my_bullet
{
private:
    static HGE*     hge;
	HTEXTURE        Texture;
	hgeAnimation    Sprite;
    hgeVector       Position;
    hgeSprite*      Sprite;
    hgeRect         BoundingBox;
    float           Speed;
    short           Damage;
	int             Vector;
	
	public:
    c_my_bullet(hgeVector Position, short Damage);
    ~c_my_bullet();
 
    void Update();
    void Render();
 
    void        SetDamage(short damage) { Damage = damage; };
    short       GetDamage() { return Damage; };
    hgeRect     GetBoundingBox() { return BoundingBox; };
    hgeVector   GetPosition() { return Position; };
};
 
#endif