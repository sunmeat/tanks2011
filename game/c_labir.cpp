#include "c_labir.h"

HGE* c_block::hge = 0;

c_block::c_block() : Position()
{
	hge = hgeCreate(HGE_VERSION); 
	Sprite  = new hgeSprite(0,0,0,19,19);
	//Get interface to hge
}

void c_block:: SetBlock(hgeVector position, int armor,HTEXTURE Texture)
{
	Position=position;
	Sprite->SetTexture(Texture);
    Sprite->SetHotSpot(0,0);
	Armor=armor;
	Sprite->GetBoundingBox(Position.x,Position.y,&BoundingBox);
}

c_block::~c_block()
{
    delete Sprite;
 
    hge->Release();
}

void c_block::Render()
{
    Sprite->Render(Position.x, Position.y);
}

hgeRect c_block:: GetBoundingBox()
{
	return BoundingBox;
}   

HGE* c_labir::hge = 0;

c_labir::c_labir()
{
	hge = hgeCreate(HGE_VERSION);
	Texture[0]=hge->Texture_Load("image/blockINV.png");
	Texture[1]=hge->Texture_Load("image/blockVIS.png");
	Texture[2]=hge->Texture_Load("image/blockIMR.png");
}
void c_labir::SetLabir(int **labir)
{
	for(int i=0;i<42;i++){
		for(int j=0;j<42;j++){
			Labir[i][j].SetBlock(hgeVector(j*19,i*19),labir[i/3][j/3],Texture[labir[i/3][j/3]]);
		}
	}
}

c_labir::~c_labir(void)
{
	for(int i=0;i<3;i++){
		hge->Texture_Free(Texture[i]);
	}
    hge->Release();
}
void c_labir::SetShield()
{
	for(int i=39;i>32;i--)
	{
		for(int j=15;j<24;j++)
		{
			if(i<40&&i>35&&j>17&&j<21);
			else Labir[i][j].SetBlock(hgeVector(j*19,i*19),2,Texture[2]);
		}
	}
}

void c_labir::Render(){
	for(int i=0;i<42;i++)
	{
		for(int j=0;j<42;j++)
		{
			if((Labir[i][j].GetVisible())>0) Labir[i][j].Render();
		}

	}
}
