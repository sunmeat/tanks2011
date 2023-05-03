#include "c_menu.h"

HGE* c_menu ::hge = 0;

c_menu::c_menu(c_player* Player,c_hiscores*_List)
{
	hge=hgeCreate(HGE_VERSION);
	this->Player=Player;
	t_BackGr=hge->Texture_Load("image/menu/BG.jpg");
	t_Mouse=hge->Texture_Load("image/menu/cursor.png");
	
	t_MenuItems[0]=hge->Texture_Load("image/menu/New_Game.png");
	t_MenuItems[1]=hge->Texture_Load("image/menu/Hiscore.png");
	t_MenuItems[2]=hge->Texture_Load("image/menu/Help.png");
	t_MenuItems[3]=hge->Texture_Load("image/menu/About.png");
	t_MenuItems[4]=hge->Texture_Load("image/menu/Exit.png");
	
	t_Help=hge->Texture_Load("image/menu/AboutSC.png");
	t_About=hge->Texture_Load("image/menu/HelpSC.png");
	t_Slider=hge->Texture_Load("image/menu/Slider.png");
	Sound=hge->Effect_Load("sound/menu.wav");
	
	s_Backgr=new hgeSprite(t_BackGr,0,0,1280,800);
	s_Mouse=new hgeSprite(t_Mouse,0,0,19,19);
	
	gui=new hgeGUI();

	gui->AddCtrl(new c_menu_item(1,t_MenuItems[0],Sound,t_Slider,450,300));
	gui->AddCtrl(new c_menu_item(2,t_MenuItems[1],Sound,t_Slider,450,380));
	gui->AddCtrl(new c_menu_item(3,t_MenuItems[2],Sound,t_Slider,450,460));
	gui->AddCtrl(new c_menu_item(4,t_MenuItems[3],Sound,t_Slider,450,540));
	gui->AddCtrl(new c_menu_item(5,t_MenuItems[4],Sound,t_Slider,450,620));
		
	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(s_Mouse);
	gui->SetFocus(1);
	gui->Enter();

	guiHelp=new hgeGUI();
	guiHelp->AddCtrl(new c_menu_item(1,t_About,Sound,t_Slider,0,0,900,800));
	guiHelp->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	guiHelp->SetCursor(s_Mouse);
	guiHelp->SetFocus(1);

	guiAbout=new hgeGUI();
	guiAbout->AddCtrl(new c_menu_item(1,t_Help,Sound,t_Slider,0,0,900,800));
	guiAbout->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	guiAbout->SetCursor(s_Mouse);
	guiAbout->SetFocus(1);

	guiHiscores=new hgeGUI();
	Hiscores=_List;
	Player->Dead();
	guiHiscores->AddCtrl(Hiscores);
	guiHiscores->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	guiHiscores->SetCursor(s_Mouse);
	guiHiscores->SetFocus(1);

	status=1;

	Font = new hgeFont("image/font1.fnt");
}

bool c_menu::Frame()
{
	float dt=hge->Timer_GetDelta();
	int id;
	int hid;
	int aid;
	int hsid;
	static int lastid=0;
	static int lasthid=0;
	static int lastaid=0;
	static int lasthsid=0;

	// If ESCAPE was pressed, tell the GUI to finish
	if(hge->Input_GetKeyState(HGEK_ESCAPE)) { lastid=5; gui->Leave(); }
	
	// We update the GUI and take an action if
	// one of the menu items was selected
	id=gui->Update(dt);
	hid=guiHelp->Update(dt);
	aid=guiAbout->Update(dt);
	hsid=guiHiscores->Update(dt);
	if(status == 1 && id == -1)
	{
		switch(lastid)
		{
			case 1:
				gui->Leave();
				return true;
				break;
			case 2:
				gui->Leave();
				status=4;
				guiHiscores->Enter();
				break;
			case 3:
				gui->Leave();
				guiHelp->SetFocus(1);
				guiHelp->Enter();
				status=3;
				break;
			case 4:
				gui->Leave();
				guiAbout->SetFocus(1);
				guiAbout->Enter();
				status=2;
				break;
			case 5:
				gui->Leave();
				status=5;
				return true;
				break;
			
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	
	if(status == 3 && hid == -1)
	{
		switch(lasthid)
		{
			case 1:
				guiHelp->Leave();
				gui->SetFocus(1);
				gui->Enter();
				status=1;
				break;
		}
	}
	else if(hid) { lasthid=hid; guiHelp->Leave(); }

	if(status == 2 && aid == -1)
	{
		switch(lastaid)
		{
			case 1:
				guiAbout->Leave();
				gui->SetFocus(1);
				gui->Enter();
				status=1;
				break;
		}
	}
	else if(aid) { lastaid=aid; guiAbout->Leave(); }

	if(status == 4 && hsid == -1)
	{
		
		switch(lasthsid)
		{
			case 1:
				guiHiscores->Leave();
				gui->SetFocus(1);
				gui->Enter(); 
				status=1;
				break;
		}
	}
	else if(hsid) { lasthsid=hsid; guiHiscores->Leave();}

	return false;
}

bool c_menu::Render()
{
	s_Backgr->Render(0,0);
	if(status==1)gui->Render();
	if(status==3)guiHelp->Render();
	if(status==2)guiAbout->Render();
	if(status==4)guiHiscores->Render();
	return false;
	
}

c_menu::~c_menu(void)
{
	for(int i=0;i<4;i++)
	{
		hge->Texture_Free(t_MenuItems[i]);
	}
	hge->Texture_Free(t_Slider);
	hge->Texture_Free(t_About);
	hge->Texture_Free(t_Help);
	hge->Texture_Free(t_BackGr);
	hge->Texture_Free(t_Mouse);
	hge->Effect_Free(Sound);

	delete s_Backgr;
	delete s_Mouse;
}
