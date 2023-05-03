//#include "c_my_bullet.h"
//
//HGE* c_my_bullet::hge = 0;
//
//c_my_bullet::c_my_bullet(hgeVector position, hgeVector velocity,HTEXTURE &Texture, short damage) : Position(position), Velocity(velocity), Damage(damage)
//{
//    hge = hgeCreate(HGE_VERSION);
// 
//    Sprite  = new hgeSprite(Texture,0,0,6,3);
//    Sprite->SetHotSpot(3,1.5);
// 
//    Speed   = 0.15;
// 
//    CenterY             = 0;
//    Radius              = hge->Random_Float(50.0f,80.0f);
//    Angle               = 0.0f;
//    bCenterYSet         = false;
//    bOscillate          = false;
//    bOscillateReverse   = true;
//}
//c_bullet::~c_bullet()
//{
//    delete Sprite;
// 
//    hge->Release();
//}
//void c_bullet::Update()
//{
//    Velocity.x *= BULLET_FRICTION;
//    Velocity.y *= BULLET_FRICTION;
// 
//    Position.x += Velocity.x;
//    if(!bOscillate) Position.y += Velocity.y;
//    else
//    {
//        if(!bCenterYSet)
//        {
//            CenterY = Position.y;
//            bCenterYSet = true;
//        }
// 
//        if(!bOscillateReverse) Position.y = CenterY - sin(Angle) * Radius;
//        else Position.y = CenterY + sin(Angle) * Radius;
//        Angle += 5 * hge->Timer_GetDelta();
//    }
// 
//    Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
//}
//void c_bullet::Render()
//{
//    Sprite->Render(Position.x, Position.y);
//}