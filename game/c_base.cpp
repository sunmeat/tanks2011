#include "c_base.h"

HGE* c_base::hge=0;

c_base::c_base(hgeVector Position,HTEXTURE Texture):hgeVector(Position)
{
	hge = hgeCreate(HGE_VERSION);
	Sprite=new hgeAnimation(Texture,71,34,0,0,59,59);
	Sprite->Play();
	g_tParticle = hge->Texture_Load("image/particles.png");

	s_pSprite=new hgeSprite(g_tParticle, 32, 32, 32, 32);
	s_pSprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	s_pSprite->SetHotSpot(16,16);
	Particle=new hgeParticleSystem("image/trail.psi",s_pSprite);
	Sprite->GetBoundingBox(x, y, &BoundingBox);
	Particle->info.nEmission=(int)(0);
	Particle->Fire();
	Particle->MoveTo(x+27,y+27);
}

void c_base::Update(float dt)
{
	Sprite->Update(dt);
	Particle->Update(dt);
}

void c_base::Dead()
{
	Particle->info.nEmission=(int)(500);
}

void c_base:: Render()
{
	Sprite->Render(x,y);
	Particle->Render();
	
}


c_base::~c_base(void)
{
	hge->Texture_Free(g_tParticle);
	delete Sprite;
	delete Particle;
	delete s_pSprite;
}
