#include "c_bonus.h"

HGE*c_bonus::hge=0;

c_bonus::c_bonus(hgeVector Position,HTEXTURE Texture, int _number, HEFFECT Sound):hgeVector(Position)
{
	hge = hgeCreate(HGE_VERSION);
	timer=50;
	number=_number;
	switch(number)
	{
	case 0:
		Sprite=new hgeSprite(Texture,0,0,57,57);
		break;
	case 1:
		Sprite=new hgeSprite(Texture,0,57,57,57);
		break;
	case 2:
		Sprite=new hgeSprite(Texture,0,114,57,57);
		break;
	case 3:
		Sprite=new hgeSprite(Texture,0,171,57,57);
		break;
	}
	Sprite->SetHotSpot(28,28);
	Sprite->GetBoundingBox(x,y,&BoundingBox);
	hge->Effect_Play(Sound);
	
}

void c_bonus::Update(float dt)
{
	timer-=dt;
}

float c_bonus::Hilevel(c_labir*labir,c_player* Player,std::list<c_enemy*>Enemies)
{
	switch(number)
	{
	case 1:
		labir->SetShield();
		return 20;
		break;
	
	case 3:
		for(auto i=Enemies.begin();i!=Enemies.end();)
		{
			
			(*i)->SetHealth(0);
			i++;
		}
		break;
	case 0:
		Player->LevelUP();
		break;
	case 2:
		Player->SetHealth(Player->GetLevel()*25+200);
		break;
	}
}

void c_bonus::Render()
{
	Sprite->Render(x,y);

}

c_bonus::~c_bonus(void)
{
	delete Sprite;
}
