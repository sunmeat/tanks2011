#ifndef C_PLAYER_H
#define C_PLAYER_H
#pragma once
 
#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include <hgefont.h>
#include <conio.h>
#include "hgeparticle.h"
#include "c_labir.h"
#include <list>


 
class c_player
{
private:
    static HGE*     hge;
    hgeVector       Position;
    HTEXTURE        Texture[4];
	HTEXTURE		Ptexture;
	HTEXTURE		tImortal;
	hgeAnimation*	ImSprite;	
	hgeAnimation*   Sprite;
	hgeSprite*		PSprite;
	hgeFont*		Font;
	
	hgeParticleSystem*	par;

	hgeRect         BoundingBox;
    float           Speed;
	int				vector;
	int				Health;
	int				lives;
	int				Hiscores;
	int				Level;
	int				Damage;
	char*			Name;
	int				Round;
	float			Imtimer;
	
	public:
    c_player(hgeVector Position,int vector);
    ~c_player();
 
    bool Update(float delta,c_labir*labirint);// метод опроса игрока
	bool UpdateName(float delta);
    void Render();
	void RenderName();
 
    void        SetPosition(hgeVector position) { Position = position; };
    int			SetHealth(int health){return Health=health;}
	void		PlusScore(int Score){Hiscores+=Score;}
	hgeRect     GetBoundingBox() { return BoundingBox; };
    hgeVector   GetPosition() { return Position; };
	void		CheckMove(c_labir* Labirint);
	int			GetVector(){return vector;}
	float		GetPosX(){return Position.x;}
	float		GetPosY(){return Position.y;}
	int			GetSpeed(){return Speed;}
	int			GetHealth(){return Health;}
	void		MinusLives(){--lives;Level=1;Sprite->SetTexture(Texture[Level-1]);Imtimer=600;}
	int			GetLIves(){return lives;}
	int			GetHiscore(){return Hiscores;}
	void		LevelUP();
	int			GetLevel(){return Level;}
	char*		GetName(){return Name;}
	void		SetName(char*name){strcpy(Name,name);}
	void		Dead();
	void		SetRound(){Round++;}
	int			GetRound(){return Round;}
	int			GetDamage(){return Damage;}
};
 
#endif