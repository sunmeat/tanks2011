#pragma once
#ifndef C_BONUS
#define C_BONUS

#include "c_labir.h"
#include "c_player.h"
#include "c_enemy.h"
#include <list>



class c_bonus: public hgeVector
{
private:
	static HGE*		hge;
	float			timer;
	int				number;
	hgeSprite*		Sprite;
	hgeRect         BoundingBox;
	
public:
	c_bonus(hgeVector Position,HTEXTURE Texture, int _number, HEFFECT Sound);
	void Update(float dt);
	~c_bonus();
	void Render();
	hgeRect     GetBoundingBox() { return BoundingBox; };
	hgeVector   GetPosition() { return hgeVector(x,y); };
	float		GetTimer(){return timer;}
	float		Hilevel(c_labir*labir,c_player* Player,std::list<c_enemy*>Enemies);

};
#endif
