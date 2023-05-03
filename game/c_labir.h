#ifndef C_LABIR_H
#define C_LABIR_H
#pragma once

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgeanim.h>

class c_block
{
private:
	static HGE*     hge;
    hgeVector       Position;
   	hgeSprite*		Sprite;
	hgeRect         BoundingBox; //Needed for collision detection 
	int				Armor;//1 -visible 0 -invisible 2-imortal
public:
	c_block();
	~c_block();
	void SetBlock(hgeVector position,int armor,HTEXTURE Texture);
	void SetVisible(bool armor){Armor=armor;}
	int GetVisible(){return Armor;}
	void Render();
	hgeRect GetBoundingBox();    
};


class c_labir
{
private:
	static HGE*     hge;
	HTEXTURE		Texture[3];
public:
	c_block 		Labir[42][42];
	c_labir ();
	~c_labir();
	void Render();
	void SetShield();
	void SetLabir(int **labir);
};
#endif
