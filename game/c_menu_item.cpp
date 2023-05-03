#include "c_menu_item.h"

HGE* c_menu_item::hge=0;

c_menu_item::c_menu_item(int _id,HTEXTURE Tex,HEFFECT Snd, HTEXTURE Sld, float _x, float _y)
{
	hge = hgeCreate(HGE_VERSION); //Get interface to hge
	id=_id;
	x=_x;
	y=_y;
	
	bStatic=false;
	bVisible=true;
	bEnabled=true;
	Vis_Slider=0;
	Sound=Snd;
	Exit=0;
	speed=5;
	move=0;
	stposx=-200;
	endposx=_x;

	It_Sprite=new hgeSprite(Tex,0,0,200,80);
	It_Sprite->SetHotSpot(100,40);

	PTexture= hge->Texture_Load("image/particles.png");
	PSprite=new hgeSprite(PTexture, 0, 0, 32, 32);
	PSprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	PSprite->SetHotSpot(16,16);
	par=new hgeParticleSystem("image/menu/particle1.psi",PSprite);
	par->Fire();

	rect.Set(x-100,y-40,x+100,y+40);
}
c_menu_item::c_menu_item(int _id,HTEXTURE Tex,HEFFECT Snd, HTEXTURE Sld, float _x, float _y, float wx,float wy)
{
	hge = hgeCreate(HGE_VERSION); //Get interface to hge
	id=_id;
	x=_x;
	y=_y;
	bStatic=false;
	bVisible=true;
	bEnabled=true;
	Vis_Slider=0;
	Sound=Snd;
	Exit=0;
	speed=5;
	move=0;
	stposx=-wx;
	endposx=0;
	It_Sprite=new hgeSprite(Tex,0,0,wx,wy);
	It_Sprite->SetHotSpot(0,0);
	PTexture= hge->Texture_Load("image/particles.png");
	PSprite=new hgeSprite(PTexture, 0, 0, 32, 32);
	PSprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	PSprite->SetHotSpot(16,16);
	par=new hgeParticleSystem("image/menu/particle1.psi",PSprite);
	par->Fire();
	rect.Set(x,y,wx,wy);
}
void c_menu_item::Render()
{
	
	It_Sprite->Render(x,y);
	par->Render();

}

c_menu_item::~c_menu_item(void)
{

	hge->Release();
}


void c_menu_item::Update(float dt)
{
	static float tepmx=0;
	static float tepmy=0;
	static float step=1;
	if((tepmx+x)<x-100){step=1;tepmy=20;}
	if((tepmx+x)>x+100){step=-1;tepmy=-20;}
	tepmx+=step*dt*40;
	if(move==speed)
	{
		if(x<endposx)x+=move;
		else{ x=endposx;move=0;}
	}
	else if(move==-speed)
	{
	if(x>stposx)x+=move;
	else{ x=stposx; move=0;}
	}
	if(Vis_Slider==1)par->info.nEmission=(int)(500);
	else par->info.nEmission=0;
	par->MoveTo(tepmx+x,y+tepmy);
	par->Update(dt);
}


void c_menu_item::Enter()
{
	x=stposx;move=speed;
}

void c_menu_item::Leave()
{
	move=-speed;
}
bool c_menu_item::IsDone()
{
	if(move==0) return true;
	else return false;
}



// This method is called when the control
// receives or loses keyboard input focus
void c_menu_item::Focus(bool bFocused)
{
	if(bFocused)
	{
		hge->Effect_Play(Sound);
		Vis_Slider=1;
	}
	else
	{
		Vis_Slider=0;
	}

}

// This method is called to notify the control
// that the mouse cursor has entered or left it's area
void c_menu_item::MouseOver(bool bOver)
{
	if(bOver) gui->SetFocus(id);
}


// This method is called to notify the control
// that the left mouse button state has changed.
// If it returns true - the caller will receive
// the control's ID
bool c_menu_item::MouseLButton(bool bDown)
{
	if(!bDown)
	{
		Vis_Slider=0;
		return true;
	}
	else 
	{
		hge->Effect_Play(Sound);
		Vis_Slider=1;
		return false;
	}
}

// This method is called to notify the
// control that a key has been clicked.
// If it returns true - the caller will
// receive the control's ID
bool c_menu_item::KeyClick(int key, int chr)
{
	if(key==HGEK_ENTER || key==HGEK_SPACE)
	{
		MouseLButton(true);
		return MouseLButton(false);
	}

	return false;
}
