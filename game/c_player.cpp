#include "c_player.h"
 
	HGE* c_player::hge = 0;

c_player::c_player(hgeVector position, int vector=0 ) : Position(position)
{

	Speed       = 2;
	Name = new char[20];
	strcpy(Name,"NAME");
	Level = 1;
	Damage = Level*25;
	Health = 50;
	lives = 3;
	Hiscores = 0;
	Round = 0;
	Imtimer=600;

	hge = hgeCreate(HGE_VERSION); //Get interface to hge
		
	Ptexture= hge->Texture_Load("image/particles.png");
    Texture[0] = hge->Texture_Load("image/PTankSheet1.png");
	Texture[1] = hge->Texture_Load("image/PTankSheet2.png");
	Texture[2] = hge->Texture_Load("image/PTankSheet3.png");
	Texture[3] = hge->Texture_Load("image/PTankSheet4.png");
	Texture[4] = hge->Texture_Load("image/PTankSheet5.png");
	tImortal = hge->Texture_Load("image/Imortal.png");
	
    Sprite  = new hgeAnimation(Texture[Level-1],6,18*Speed,0,0,57,57);
	Sprite->SetHotSpot(28,28);
    Sprite->Play();

	ImSprite = new hgeAnimation(tImortal,6,18,0,0,57,57);
	ImSprite->SetHotSpot(28,28);
    ImSprite->Play();
		    
	PSprite=new hgeSprite(Ptexture, 32, 32, 32, 32);
	PSprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	PSprite->SetHotSpot(16,16);
	par=new hgeParticleSystem("image/trail1.psi",PSprite);
	par->Fire();
	par->SetScale(0.5);

	Font = new hgeFont("image/font1.fnt");
}
c_player::~c_player()
{
	hge->Texture_Free(Texture[0]);
   
    delete Sprite;
 
    hge->Release();
}

bool c_player::UpdateName(float delta)
{
	char temp;
	static int tempcount=-1;
    static float tdelta=0;
	tdelta+=delta;
	if(hge->Input_GetKeyState(HGEK_BACKSPACE)&&tdelta>0.10){
		tempcount>-1?tempcount--:tempcount=-1;
		Name[tempcount+1]= '#';
        Name[tempcount+2]= '\0';
		tdelta=0;
		return false;
	}
	if(hge->Input_GetKeyState(HGEK_ENTER)){Name[tempcount+1]= '\0';return true;}
	
	if(hge->Input_GetKey()){
		temp=hge->Input_GetChar();
		if(temp>45&&temp<250){tempcount++;
		if(tempcount==18)tempcount--;
		Name[tempcount]=temp;
		Name[tempcount+1]= '#';
		Name[tempcount+2]= '\0';
		}
	}
	return false;
}

bool c_player::Update(float delta,c_labir* Labirint)
{
	if(Imtimer>0){
		Imtimer-=delta*100;
		Health=Level*50;
	}

	static int start=0;
	int Speed=(this->Speed)*delta*100;
	if(start>5)Sprite->Stop();
	else {start++; Position.y-=Speed;}

	if(hge->Input_GetKeyState(HGEK_A) || hge->Input_GetKeyState(HGEK_LEFT)) {
		vector=3;Sprite->Resume(); Position.x-=Speed; CheckMove(Labirint);
	}
	else if(hge->Input_GetKeyState(HGEK_D) || hge->Input_GetKeyState(HGEK_RIGHT)) {
		vector=1;Sprite->Resume();Position.x+=Speed; CheckMove(Labirint);
	}
	else if(hge->Input_GetKeyState(HGEK_W) || hge->Input_GetKeyState(HGEK_UP)) {
		vector=0;Sprite->Resume();Position.y-=Speed; CheckMove(Labirint);
	} 
	else if(hge->Input_GetKeyState(HGEK_S) || hge->Input_GetKeyState(HGEK_DOWN)) {
		vector=2;Sprite->Resume();Position.y+=Speed; CheckMove(Labirint);
	}
	
	Sprite->Update(delta);
	ImSprite->Update(delta);

	par->info.nEmission=(int)(500-Health/(Level*50/(float)500));
	par->MoveTo(Position.x/0.5,Position.y/0.5);
	par->Update(delta);
    Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	return false;
}

void c_player::CheckMove(c_labir* Labirint){
	int x,y;
	int lr=0,ll=0;
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
				Position.x--;CheckMove(Labirint);return;
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
				Position.y--;CheckMove(Labirint);return;
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
				Position.x++;CheckMove(Labirint);return;
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
				Position.y++;CheckMove(Labirint);return;
			}
			
		}
		break;
	}

}

void c_player::LevelUP()
{
	if(Level<5)Level++;
	Sprite->SetTexture(Texture[Level-1]);
	Damage=Level*25;
	Health=Level*50;
	switch(Level)
	{
	case 0:
		Speed=2;
		break;
	case 1:
		Speed=2.1;
		break;
	case 2:
		Speed=2.2;
		break;
	case 3:
		Speed=2.5;
		break;
	}

	
}

void c_player::Render()
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
	default:
		Sprite->RenderEx(Position.x, Position.y,0.0f,1.0f,1.0f);
		break;
	}
	if(Imtimer>1){ImSprite->Render(Position.x,Position.y);}
	par->Render();
   
}

void c_player::RenderName()
{
	Font->printf(200,200,HGETEXT_LEFT,"PLEASE ENTER YOUR NAME");
	Font->printf(200,240,HGETEXT_LEFT,"%s",Name);
}

void c_player::Dead()
{
	Speed       = 2;
	Level		= 1;
	Damage      = Level*25;
	Health		= 200;
	lives		= 3;
	Hiscores	= 0;
	Round		= 0;

	Sprite->SetTexture(Texture[Level-1]);
}