#include "c_game.h"

HGE* c_game::hge = 0;

c_game::c_game(c_player* _Player, c_hiscores* _List)
{
	hge = hgeCreate(HGE_VERSION);
	g_vBGPosition       = hgeVector(0,0);
	Enemy				= NULL;
	MyBullet			= NULL; 
	EnBullet			= NULL;
	g_tBackground   = hge->Texture_Load("image/background.jpg");
	
	g_tExplosion    = hge->Texture_Load("image/Explosion-Sprite-Sheet.png");
	g_tExplosionSm  = hge->Texture_Load("image/Explosion-Sprite-SheetSm.png");
	g_tBase			= hge->Texture_Load("image/base.png");
	g_eExplosion	= hge->Effect_Load("sound/explo.wav");
	g_eBullets		= hge->Effect_Load("sound/bang.wav");
	BackMusic		= hge->Effect_Load("sound/bg.mp3");
	BonusSound		= hge->Effect_Load("sound/bonus.wav");
	MSound			= hge->Effect_Load("sound/Menu.mp3");
	g_tGameover		= hge->Texture_Load("image/Gameover.png");
	g_tBonus		= hge->Texture_Load("image/Bonus.png");
	EnTexture[0]	= hge->Texture_Load("image/TankSheet1.png");
	EnTexture[1]	= hge->Texture_Load("image/TankSheet2.png");
	EnTexture[2]	= hge->Texture_Load("image/TankSheet3.png");
	EnTexture[3]	= hge->Texture_Load("image/TankSheet4.png");
	EnTexture[4]	= hge->Texture_Load("image/TankSheet5.png");
	BuTexture[0]	= hge->Texture_Load("image/BuTexture1.png");
	BuTexture[1]	= hge->Texture_Load("image/BuTexture2.png");
	BuTexture[2]	= hge->Texture_Load("image/BuTexture3.png");
	BuTexture[3]	= hge->Texture_Load("image/BuTexture4.png");
	BuTexture[4]	= hge->Texture_Load("image/BuTexture5.png");
	t_Exite			= hge->Texture_Load("image/Exite.png");
	t_Exite2			= hge->Texture_Load("image/Exite2.png");

	gui=new hgeGUI();
	gui->AddCtrl(new c_menu_item(1,t_Exite,MSound,t_Exite,450,300));
	gui->AddCtrl(new c_menu_item(2,t_Exite2,MSound,t_Exite,450,380));
			
	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	g_sMouse=new hgeSprite(t_Exite,10,10,10,10);
	gui->SetCursor(g_sMouse);
	
	gui->Enter();
	
	hge->Effect_PlayEx(BackMusic,100,0,0);
	//запись текстур в спрайты
    g_sBackground   = new hgeSprite(g_tBackground, 0, 0, 1980, 1080);
	g_sGameover     = new hgeSprite(g_tGameover, 0, 0, 400, 400);
	Font		    = new hgeFont("image/font1.fnt");
	Base			= new c_base(hgeVector(340,685),g_tBase);
	g_sGameover->SetHotSpot(200,200);
	//задание позиции заднего плана
    g_vBGPosition   = hgeVector(0, 0);
	// создание игрока
	Player =_Player;
	Player->SetPosition(hgeVector(252, 703));
	Status_Game=1;
	TimerGameOver=1000;
	GameTime=0;
	srand(time(NULL));
	Labirint = new c_labir();
	LoadState(1);
	numbOFenemy=0;
	ListHiscores=_List;
}

void c_game::Erase()
{
	for(auto i = Explosions.begin(); i != Explosions.end(); /**/)
		{
			  delete (*i).Animation;
			  i = Explosions.erase(i);
		}
	for(auto i = ExplosionsSm.begin(); i != ExplosionsSm.end(); /**/)
		{
			  delete (*i).Animation;
			  i = ExplosionsSm.erase(i);
		}
	for(auto i = Enemies.begin(); i != Enemies.end(); /**/)
		{
			  delete (*i);
			  i = Enemies.erase(i);
		}
	for(auto i = My_Bullets.begin(); i != My_Bullets.end(); /**/)
		{
			  delete (*i);
			  i = My_Bullets.erase(i);
		}
	for(auto i = En_Bullets.begin(); i != En_Bullets.end(); /**/)
		{
			  delete (*i);
			  i = En_Bullets.erase(i);
		}
	for(auto i = Bonuses.begin(); i != Bonuses.end(); /**/)
		{
			  delete (*i);
			  i = Bonuses.erase(i);
		}
	Player->SetPosition(hgeVector(252,703));
}

bool c_game::LoadState(int stage)
{
	int**map=new int*[14];
	for(int i=0;i<14;i++){
		map[i]=new int[14];
	}
	FILE* f;
	char* temp=new char[60];
	sprintf(temp,"../Debug/levels/%d.txt\0",stage);
	if((f=fopen(temp,"r"))==NULL)return false;
	for(int i=0;i<14;i++)
	{
		for (int j=0;j<14;j++)
		{
			map[i][j]=(fgetc(f)-48);
		}
	}
	HowManyEnemies=fgetc(f);

	Labirint->SetLabir(map);

	for(int i=0;i<14;i++){
		delete[]map[i];
	}
	delete[]map;
	delete[]temp;
	fclose(f);
	return true;
}

void c_game::CreateExplosion(hgeVector Position)
{
    explosion exp;
    exp.Animation = new hgeAnimation(g_tExplosion,16,16,0,0,120,120);
    exp.Animation->SetHotSpot(59,59);
    exp.Animation->Play();
    exp.Position = Position;
    Explosions.push_back(exp);
    hge->Effect_PlayEx(g_eExplosion,50,0,0);
}
	void c_game::CreateExplosionSm(hgeVector Position)
{
    explosion exp;
    exp.Animation = new hgeAnimation(g_tExplosionSm,4,8,0,0,59,59);
    exp.Animation->SetHotSpot(28,28);
    exp.Animation->Play();
    exp.Position = Position;
    ExplosionsSm.push_back(exp);
    hge->Effect_PlayEx(g_eExplosion,50,0,0);
}

void c_game::Bang()
{
	hge->Effect_PlayEx(g_eBullets,5,0,0);
}

bool c_game::Frame()
{   
	//записывает в дельта количество секунд прошедших с момента последнего запуска функции frame 
	float delta = hge->Timer_GetDelta();
	
	int id;
	static int lastid=0;

	if(Status_Game==1){gui->Leave();}

	id=gui->Update(delta);
	//обновление меню 
	if (Status_Game==4)
	{
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:
				gui->Leave();
				Status_Game=0;
				return false;
				break;
			case 2:
				gui->Leave();
				Status_Game=1;
				break;
			}
		}
		else if(id) { lastid=id; gui->Leave(); }
		
		return false;
	}
	// проверка на нажатие ескейп
	if (hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		
		if(TimerGameOver==0||Status_Game==0) return true;
		else
		{
			gui->SetFocus(1);
			gui->Enter();Status_Game=4;
		}
	}
	// запуск опроса дейстивий игрока 
	GameTime+=delta*100;
	Player->Update(delta,Labirint);
	Base->Update(delta);
	
	//запуск прощета логики врага 
	for(auto i = Enemies.begin(); i != Enemies.end(); /**/) 
    {
            (*i)->Update(delta,Labirint,Enemies,Player);// запустить логику текущего врага
            i++;// сделать шаг к следующей итерации
    }

	//проверка на совпадение врага и игрока
	for(auto i = Enemies.begin(); i != Enemies.end(); /**/)
    {
		
		if(Player->GetBoundingBox().Intersect(&(*i)->GetBoundingBox()))
			{
				switch(Player->GetVector()){
				case 1:
					Player->SetPosition(hgeVector(Player->GetPosX()-Player->GetSpeed(),Player->GetPosY()));
					break;
				case 2:
					Player->SetPosition(hgeVector(Player->GetPosX(),Player->GetPosY()-Player->GetSpeed()));
					break;
				case 3:
					Player->SetPosition(hgeVector(Player->GetPosX()+Player->GetSpeed(),Player->GetPosY()));
					break;
				case 0:
					Player->SetPosition(hgeVector(Player->GetPosX(),Player->GetPosY()+Player->GetSpeed()));
				}
			}
		
            i++;
    }

	//выстрел игрока
	static int timepl=25;
	timepl--;
	if(hge->Input_KeyDown(HGEK_SPACE)&&Status_Game==1&&timepl<1)// проверка на нажатие пробела обработка выстрела игрока
	{
		Bang();
		c_bullet* MyBullet = new c_bullet(Player->GetPosition(),Player->GetVector(),BuTexture[(Player->GetLevel())-1],Player->GetDamage()); 
 		My_Bullets.push_back(MyBullet);
		timepl=25;
	}


	//выстрел врага
	for(auto i=Enemies.begin();i!=Enemies.end();/**/)
	{
		if((*i)->GetWantShoot()){
			Bang();
			c_bullet*EnBullet = new c_bullet((*i)->GetPosition(),(*i)->GetVector(),BuTexture[((*i)->GetDamage()/25)-1],(*i)->GetDamage());
			En_Bullets.push_back(EnBullet);
		}
		i++;
	}

	//полет пули врага
	for(auto i = En_Bullets.begin(); i != En_Bullets.end(); /**/)
	{
		(*i)->Update(delta);
		 i++;
	}

	//полет пули игрока
	for(auto i = My_Bullets.begin(); i != My_Bullets.end(); /**/)
	{
		 (*i)->Update(delta);
		 i++;
	}

	// проверка на совпадение игрока и пуль
	for(auto i = En_Bullets.begin(); i != En_Bullets.end(); /**/)
    {
        bool bHit = false;// обнуление флага попадания
 
        if(Player->GetBoundingBox().Intersect(&(*i)->GetBoundingBox()))
            {
				Player->SetHealth(Player->GetHealth() - (*i)->GetDamage());
				CreateExplosionSm(Player->GetPosition());
                delete (*i); 
                i    = En_Bullets.erase(i);
                bHit = true;
				break;
            }
		if(Base->GetBoundingBox().Intersect(&(*i)->GetBoundingBox()))
		{
			Base->Dead();
			Status_Game=0;
		}
        
        if(!bHit) i++;//если пуля не попала то сделать шаг вперед
    }

	//если у игрока нет здоровья убрать жизнь и востановить в новом месте
	if(Player->GetHealth()<1){
		 CreateExplosion(Player->GetPosition());
		 Player->SetPosition(hgeVector(252,703));
		 Player->SetHealth(Player->GetLevel()*25+200);
		 Player->MinusLives();
		 if(!Player->GetLIves())Status_Game=0;
	}

	//проверка на попадание пули во врага
	if(!My_Bullets.empty() && !Enemies.empty()) 
	{
		for(auto i = My_Bullets.begin(); i != My_Bullets.end(); /**/)
		 {
		  bool bHit = false;// обнуление флага попадания
	        for(auto x = Enemies.begin(); x != Enemies.end(); x++)// задаются итерации для списка врагов
		 {
            if((*x)->GetBoundingBox().Intersect(&(*i)->GetBoundingBox()))
            {
				(*x)->SetHealth((*x)->GetHealth() - (*i)->GetDamage());
				CreateExplosionSm((*i)->GetPosition());
                delete (*i);
                i    = My_Bullets.erase(i);
                bHit = true;
				Player->PlusScore(10);
                break;
            }
        }
        if(!bHit) i++;//если пуля не попала то сделать шаг вперед
		}
	}

	if(!My_Bullets.empty() && !En_Bullets.empty()) 
	{
		for(auto i = My_Bullets.begin(); i != My_Bullets.end(); /**/)
		{
			bool bHit = false;// обнуление флага попадания
	        for(auto x = En_Bullets.begin(); x != En_Bullets.end(); )// задаются итерации для списка врагов
			{
            if((*x)->GetBoundingBox().Intersect(&(*i)->GetBoundingBox()))
            {
				CreateExplosionSm((*i)->GetPosition());
				delete (*i);
				delete (*x);
                i    = My_Bullets.erase(i);
				x	 = En_Bullets.erase(x);
                bHit = true;
				break;
            }
			if(!bHit) {x++;}
			}
			if(!bHit) {i++;}
		}
	}
	//проверка здоровья врагов
	for(auto i = Enemies.begin(); i != Enemies.end(); /**/)
	{
		if((*i)->GetHealth() <= 0)
		{
			if(rand()%4==1){
				Bonus=new c_bonus((*i)->GetPosition(),g_tBonus,rand()%4,BonusSound);
				Bonuses.push_back(Bonus);
			}
			CreateExplosion((*i)->GetPosition());
			delete (*i);
			i = Enemies.erase(i);
			Player->PlusScore(100);
		}
		else i++;
	}

	for(auto i = Bonuses.begin(); i!=Bonuses.end();)
	{
		(*i)->Update(delta);
		i++;
	}

	for(auto i = Bonuses.begin(); i != Bonuses.end(); /**/)
    {
        bool blevelUP = false;// обнуление флага попадания
 
        if(Player->GetBoundingBox().Intersect(&(*i)->GetBoundingBox()))
            {
				(*i)->Hilevel(Labirint,Player,Enemies);
				delete (*i); 
                i    = Bonuses.erase(i);
                blevelUP = true;
				break;
            }
        
        if(!blevelUP) i++;
    }
	//////////////////////////////////////////////////////////////////////////////////////////
	for(auto i=My_Bullets.begin();i !=My_Bullets.end();/**/)//проверка на попадание в лабиринт
	{
		int x,y;
		x=(*i)->GetPosX()/19;
		y=(*i)->GetPosY()/19;
		if(Labirint->Labir[y][x].GetVisible()>0){
			if(Labirint->Labir[y][x].GetVisible()<2){
				switch((*i)->GetVector()){
				case 0:
					for(int k=-1;k<=1;k++){
					Labirint->Labir[y][x+k].SetVisible(0);
					}
					break;
				case 1:
					for(int k=-1;k<=1;k++){
					Labirint->Labir[y+k][x].SetVisible(0);
					}
					break;
				case 2:
					for(int k=-1;k<=1;k++){
					Labirint->Labir[y][x+k].SetVisible(0);
					}
					break;
				case 3:
					for(int k=-1;k<=1;k++){
					Labirint->Labir[y+k][x].SetVisible(0);
					}
					break;
				}
			}
			CreateExplosionSm((*i)->GetPosition());
			delete (*i); 
			i = My_Bullets.erase(i);
		}else i++;
	
	}

	////////////////////////////////////////////////////
	for(auto i=En_Bullets.begin();i !=En_Bullets.end();/**/)//проверка на попадание в лабиринт
	{
		int x,y;
		x=(*i)->GetPosX()/19;
		y=(*i)->GetPosY()/19;
		if(Labirint->Labir[y][x].GetVisible()>0){
			if(Labirint->Labir[y][x].GetVisible()<2){
				switch((*i)->GetVector()){
				case 0:
					for(int k=-1;k<=1;k++){
					Labirint->Labir[y][x+k].SetVisible(0);
					}
					break;
				case 1:
					for(int k=-1;k<=1;k++){
					Labirint->Labir[y+k][x].SetVisible(0);
					}
					break;
				case 2:
					for(int k=-1;k<=1;k++){
					Labirint->Labir[y][x+k].SetVisible(0);
					}
					break;
				case 3:
					for(int k=-1;k<=1;k++){
					Labirint->Labir[y+k][x].SetVisible(0);
					}
					break;
				}
			}
			CreateExplosionSm((*i)->GetPosition());
			delete (*i); 
			i = En_Bullets.erase(i);
		}else i++;
	
	}
	for(auto i = Explosions.begin(); i != Explosions.end(); /**/)// обработка взрывов
	{
	   if((*i).Animation->GetFrame() == 15)// если текущий кадр анимации взрыва равен 4 тогда удалить взрыв
	   {
	      delete (*i).Animation;
	      i = Explosions.erase(i);
	   }
	  else
	  {
	      (*i).Animation->Update(delta);// иначе передать время после фрейма в функциию обновления взрыва 
	      i++;//переход к следующему шагу
	  }

	}
	for(auto i = ExplosionsSm.begin(); i != ExplosionsSm.end(); /**/)// обработка взрывов
	{
	   if((*i).Animation->GetFrame() == 3)// если текущий кадр анимации взрыва равен 4 тогда удалить взрыв
	   {
	      delete (*i).Animation;
	      i = ExplosionsSm.erase(i);
	   }
	  else
	  {
	      (*i).Animation->Update(delta);// иначе передать время после фрейма в функциию обновления взрыва 
	      i++;//переход к следующему шагу
	  }

	}

	////////////////////////////////////////////////////////
	//Создание врагов
	
	if(Enemies.size() < 5&&numbOFenemy<=HowManyEnemies-3)
	{
			static int x=85;
			int cheker=0;

			c_enemy* Enemy = new c_enemy(hgeVector(x,85),2,numbOFenemy,50,EnTexture[numbOFenemy/6],25*(numbOFenemy/6+1),numbOFenemy/6+1);
			for(auto i=Enemies.begin();i!=Enemies.end();i++){
				if(Enemy->GetBoundingBox().Intersect(&(*i)->GetBoundingBox()))
				{
					delete Enemy;
					if(x<500){x+=170;}else {x=85;}
					cheker=1;
					break;
				}
			}
			if(cheker==0){
				numbOFenemy++;
				Enemies.push_back(Enemy);
			}
	}
	

	if(Enemies.empty())Status_Game=2;
	if(Status_Game==2){
		if (hge->Input_GetKeyState(HGEK_ESCAPE)||TimerGameOver==0)return true;
	}
	return false;
}
 
bool c_game::Render()
{
	Font->SetColor(0xFF333399);
    g_sBackground->Render(g_vBGPosition.x,g_vBGPosition.y);// вывод бекграунда
   	Labirint->Render();
	Player->Render();
	
	for(auto i = Enemies.begin(); i != Enemies.end(); i++)// вывод врагов
	{
		(*i)->Render();
	}
	
	for(auto i = My_Bullets.begin(); i!= My_Bullets.end(); i++)// вывод пуль
	{
		(*i)->Render();
	}
	for(auto i = En_Bullets.begin(); i!= En_Bullets.end(); i++)// вывод пуль
	{
		(*i)->Render();
	}
	for(auto i = Explosions.begin(); i != Explosions.end(); i++)// вывод взрывов
	{
		(*i).Animation->Render((*i).Position.x, (*i).Position.y);
	}
	for(auto i = ExplosionsSm.begin(); i != ExplosionsSm.end(); i++)// вывод взрывов
	{
		(*i).Animation->Render((*i).Position.x, (*i).Position.y);
	}
	for(auto i = Bonuses.begin(); i != Bonuses.end(); i++)// вывод bonuses
	{
		(*i)->Render();
	}
	Base->Render();
	gui->Render();

	if(Status_Game==0){
		g_sGameover->Render(450,400);
		TimerGameOver--;
		static int temp1=1;
		if(TimerGameOver==999){temp1=ListHiscores->Addscore(Player);}
		switch(temp1){
			case 3:
				Font->printf(100,450,HGETEXT_LEFT,"CONGRATULATION!!!NEW HISCORES"); 
				Font->printf(350,490,HGETEXT_LEFT,"%5.5d ",Player->GetHiscore());
				break;
			case 2:
				Font->printf(250,450,HGETEXT_LEFT,"Not so bad You score");
				Font->printf(250,490,HGETEXT_LEFT,"%5.5d ",Player->GetHiscore());
				break;
			case 0:
				Font->printf(250,450,HGETEXT_LEFT,"Very bad You score");
				Font->printf(300,490,HGETEXT_LEFT,"%5.5d ",Player->GetHiscore());
				break;
			default:
				break;
			}
		if(TimerGameOver==1)temp1=1;
	}	
	if(Status_Game==2){
		Font->printf(400,400, HGETEXT_LEFT, "YOU WIN!!!!");
		TimerGameOver--;
		
	}
	if (GameTime<300){Font->printf(350,350,HGETEXT_LEFT,"ROUND - %d",Player->GetRound()+1);}
	
	Font->printf(801,0, HGETEXT_LEFT, "Lives");
	Font->printf(801,20,HGETEXT_LEFT, "%2d",Player->GetLIves());
	Font->printf(801,80,HGETEXT_LEFT, "Score");
	Font->printf(801,120,HGETEXT_LEFT, "%5.5d",Player->GetHiscore());
	Font->printf(801,200,HGETEXT_LEFT, "Level");
	Font->printf(801,240,HGETEXT_LEFT, "%d",Player->GetLevel());
	Font->printf(801,300,HGETEXT_LEFT, "Enemy");
	Font->printf(801,340,HGETEXT_LEFT, "%d",HowManyEnemies-numbOFenemy-2);
	Font->printf(801,400,HGETEXT_LEFT, "Time");
	Font->printf(801,440,HGETEXT_LEFT, "%5.0f",GameTime/10);
    hge->Gfx_EndScene();//вывод сцены на екран
    return false;
}
 
c_game::~c_game(void)
{
		Erase();
		hge->Texture_Free(g_tExplosion);
		hge->Texture_Free(g_tBackground);
		hge->Texture_Free(g_tBase);
		
		hge->Texture_Free(g_tGameover);
		hge->Texture_Free(g_tBonus);

		hge->Effect_Free(g_eExplosion);
		hge->Effect_Free(g_eBullets);
		hge->Effect_Free(BackMusic);
		hge->Effect_Free(BonusSound);
		

		for(int i=0;i<5;i++)
		{
			hge->Texture_Free(EnTexture[i]);
			hge->Texture_Free(BuTexture[i]);
		}


		for(auto i = Explosions.begin(); i != Explosions.end(); /**/)
		{
			  delete (*i).Animation;
			  i = Explosions.erase(i);
		}
        
        delete g_sBackground;

}
