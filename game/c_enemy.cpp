#include "c_enemy.h"

HGE* c_enemy::hge = 0;

c_enemy::c_enemy(hgeVector position, int vector, int number, int score,HTEXTURE Texture,int _Damage,int _Level) : Position(position)
{
	Level=_Level;
	switch(Level)
	{
	case 0:
		Speed       = 2;
		break;
	case 1:
		Speed       = 2.5;
		break;
	case 2:
		Speed       = 2.1;
		break;
	case 3:
		Speed       = 2.2;
		break;
	case 4:
		Speed       = 2.5;
		break;
	}
	Damage=_Damage;
    hge = hgeCreate(HGE_VERSION); //Get interface to hge
	this->number=number;
    Sprite  = new hgeAnimation(Texture,6,18*Speed,0,0,57,57);
    Sprite->SetHotSpot(28,28);
    Sprite->Play();
	Health=Level*50;
	TimerShoot=150;
	Score		= score;
	WantShoot=0;
	Ptexture= hge->Texture_Load("image/particles.png");
	PSprite=new hgeSprite(Ptexture, 32, 96, 32, 32);
	PSprite->SetBlendMode( BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	PSprite->SetHotSpot(16,16);
	par=new hgeParticleSystem("image/trail.psi",PSprite);
	vector=2;
	par->Fire();
	par->SetScale(0.5);
	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
}


c_enemy::~c_enemy(void)
{
	hge->Texture_Free(Ptexture);

	delete Sprite;
	delete PSprite;
	 
    hge->Release();
}

bool c_enemy::Update(float delta,c_labir* Labirint,list<c_enemy*> Enemies,c_player*Player)
{
	WantShoot=0;
	TimerShoot--;
	int Speed=(this->Speed)*delta*100;
	if((rand()%100)>98)vector=rand()%4;
	if((rand()%10)>8)
	{
		WantShoot=1;
	}
	if(Position.x==Player->GetPosition().x||Position.y==Player->GetPosition().y){
		WantShoot=1;
		if(Position.x<Player->GetPosition().x){vector=1;}
		if(Position.x>Player->GetPosition().x){vector=3;}
		if(Position.y<Player->GetPosition().y){vector=2;}
		if(Position.y>Player->GetPosition().y){vector=0;}
	}
	if(vector==3) { Position.x-=Speed; CheckMove(Labirint);}
	else if(vector==1) {Position.x+=Speed; CheckMove(Labirint);}
	else if(vector==0) {Position.y-=Speed; CheckMove(Labirint);} 
	else if(vector==2) {vector=2;Position.y+=Speed; CheckMove(Labirint);}
	for(auto i = Enemies.begin(); i != Enemies.end(); /**/) //присвоить i начальный индекс итератора или масива врагов
    {
		if ((*i)->GetNumber()!=number){
			if(BoundingBox.Intersect(&(*i)->GetBoundingBox()))
			{
				switch(vector){
				case 1:
					vector=3;Position.x-=Speed;
					break;
				case 2:
					vector=0;Position.y-=Speed;
					break;
				case 3:
					vector=1;Position.x+=Speed;
					break;
				case 0:
					vector=2;Position.y+=Speed;
				}
			}
		}
            i++;
    }
	if(BoundingBox.Intersect(&Player->GetBoundingBox()))
			{
				switch(vector){
				case 1:
					vector=3;Position.x-=Speed;
					break;
				case 2:
					vector=0;Position.y-=Speed;
					break;
				case 3:
					vector=1;Position.x+=Speed;
					break;
				case 0:
					vector=2;Position.y+=Speed;
				}
			}
	
	

	if(WantShoot=1&& TimerShoot<1)
	{
		TimerShoot=80;
	}
	else{WantShoot=0;}
	

	Sprite->Update(delta);
	par->info.nEmission=(int)(500-Health/(Level*50/(float)500));
	par->MoveTo(Position.x/0.5,Position.y/0.5);
	par->Update(delta);
   
    Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	return false;
}

void c_enemy::CheckMove(c_labir* Labirint){
	int x,y;
	int lr,ll;
	switch(vector)
	{
	case 1:
		x=int(Position.x/19);
		y=int(Position.y/19);
		if((int(Position.y)%19)<1){ll=-2;lr=1;}
		else if((int(Position.y)%17)>17){ll=-1;lr=2;}
		else {ll=-1;lr=1; Position.y=y*19+8;}
		
		Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
		for(int i=ll;i<=lr;i++){
			if(Labirint->Labir[y+i][x+2].GetVisible()&&BoundingBox.Intersect(&Labirint->Labir[y+i][x+2].GetBoundingBox())){
				Position.x--;CheckMove(Labirint);if((rand()%100)>98)vector=rand()%4;return;
			}
			
		}
		break;
	case 2:
		x=int(Position.x/19);
		y=int(Position.y/19);
		if((int(Position.x)%19)<1){ll=-2;lr=1;}
		else if((int(Position.x)%17)>15){ll=-1;lr=2;}
		else {ll=-1;lr=1; Position.x=x*19+8;}
		Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
		for(int i=ll;i<=lr;i++){
			if(Labirint->Labir[y+2][x+i].GetVisible()&&BoundingBox.Intersect(&Labirint->Labir[y+2][x+i].GetBoundingBox())){
				Position.y--;CheckMove(Labirint);if((rand()%100)>98)vector=rand()%4;return;
			}
			
		}
		break;
	case 3:
		x=int(Position.x/19);
		y=int(Position.y/19);
		if((int(Position.y)%19)<1){ll=-1;lr=2;}
		else if((int(Position.y)%19)>17){ll=-2;lr=1;}
		else {ll=-1;lr=1; Position.y=y*19+8;}
		Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
		for(int i=ll;i<=lr;i++){
			if(Labirint->Labir[y-i][x-2].GetVisible()&&BoundingBox.Intersect(&Labirint->Labir[y-i][x-2].GetBoundingBox())){
				Position.x++;CheckMove(Labirint);if((rand()%100)>98)vector=rand()%4;return;
			}
			
		}
		break;
	case 0:
		x=int(Position.x/19);
		y=int(Position.y/19);
		if((int(Position.x)%19)<1){ll=-1;lr=2;}
		else if((int(Position.x)%19)>17){ll=-2;lr=1;}
		else {ll=-1;lr=1; Position.x=x*19+8;}
		Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
		for(int i=ll;i<=lr;i++){
			if(Labirint->Labir[y-2][x-i].GetVisible()&&BoundingBox.Intersect(&Labirint->Labir[y-2][x-i].GetBoundingBox())){
				Position.y++;CheckMove(Labirint);if((rand()%100)>98)vector=rand()%4;return;
			}
			
		}
		break;
	}

}

void c_enemy::Render()
{
	
	switch(vector){
	case 3:
		Sprite->RenderEx(Position.x, Position.y,4.71f,1.0f,1.0f);
		break;
	case 0:
		Sprite->RenderEx(Position.x, Position.y,0.0f,1.0f,1.0f);
		break;
	case 1:
		Sprite->RenderEx(Position.x, Position.y,1.57f,1.0f,1.0f);
		break;
	case 2:
		Sprite->RenderEx(Position.x, Position.y,3.14f,1.0f,1.0f);
		break;
	}
    par->Render();

}
