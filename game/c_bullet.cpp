#include "c_bullet.h"

HGE* c_bullet::hge = 0;

c_bullet::c_bullet(hgeVector position,int vector,HTEXTURE Texture,int _damage): Position(position)
{
	hge = hgeCreate(HGE_VERSION);
	Sprite= new hgeAnimation(Texture,4,32,0,0,19,19);
	Sprite->SetHotSpot(8,8);
	Sprite->Play();
	this->vector=vector;
	switch(vector)
	{
	case 0:
		Position.y-=28;
		break;
	case 1:
		Position.x+=28;
		break;
	case 2:
		Position.y+=28;
		break;
	case 3:
		Position.x-=28;
		break;

	}
	Speed=6;
	damage=_damage;
	
}
c_bullet::~c_bullet()
{
	delete Sprite;
 
    hge->Release();
}

void c_bullet:: Update(float delta)
{
	switch(vector)
	{
	case 0:
		Position.y-=(Speed*delta*80);
		break;
	case 1:
		Position.x+=(Speed*delta*80);
		break;
	case 2:
		Position.y+=(Speed*delta*80);
		break;
	case 3:
		Position.x-=(Speed*delta*80);
		break;
	}
	Sprite->Update(delta);
	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
}

void c_bullet::Render()
{
	switch(vector){
		
		case 0:
			Sprite->RenderEx(Position.x, Position.y,0.0f,1.0f,1.0f);
			break;
		case 1:
			Sprite->RenderEx(Position.x, Position.y,1.57f,1.0f,1.0f);
			break;
		case 2:
			Sprite->RenderEx(Position.x, Position.y,3.14f,1.0f,1.0f);
			break;
		case 3:
			Sprite->RenderEx(Position.x, Position.y,4.71f,1.0f,1.0f);
			break;
	}
}