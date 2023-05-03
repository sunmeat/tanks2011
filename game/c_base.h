#pragma once
#pragma once
#ifndef C_BASE
#define C_BASE

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include <hgeparticle.h>

class c_base:public hgeVector
{
	static HGE*			hge;
	hgeAnimation*		Sprite;
	hgeParticleSystem*	Particle;
	HTEXTURE			g_tParticle;
	hgeSprite*			s_pSprite;	
	hgeRect             BoundingBox;

public:
	c_base(hgeVector Position,HTEXTURE Texture);
	~c_base(void);
	void Render();
	void Update(float dt);
	void Dead();
	hgeRect     GetBoundingBox() { return BoundingBox; };
};

#endif