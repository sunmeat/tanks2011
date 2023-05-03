#include "c_hiscores.h"

HGE* c_hiscores::hge=0;

c_hiscores::c_hiscores(int _length)
{
	FILE* file;
	id=1;
	hge = hgeCreate(HGE_VERSION); //Get interface to hge
	length=_length;
	numb=-1;
	list=new Plscore[length];
	for(int i=0;i<length;i++){ list[i].name=new char[20];}
	status=0;
	movespeed=0;
	Font = new hgeFont("image/font1.fnt");
	x=-200;
	bStatic=false;
	bVisible=true;
	bEnabled=true;
	if((file=fopen("hiscores.txt","rb"))==NULL){
		if((file=fopen("hiscores.txt","wb"))==NULL)
		{
			exit(0);

		}
		else{
			for(int i=0;i<length;i++)
			{
				int temp=20;
				char* tempname=new char[temp];
				strcpy(tempname,"emty");
				int hiscores=0;
				fwrite(&hiscores,sizeof(int),1,file);
				fwrite(tempname,sizeof(char),temp,file);
				

			}
		}
	}
	fclose(file);
	file=fopen("hiscores.txt","rb");
	for(int i=0;i<length;i++)
	{
		fread(&list[i].hiscore,sizeof(int),1,file);
		fread(list[i].name,sizeof(char),20,file);
		
	}
	rect.Set(x,y,800,800);
	fclose(file);

}

int c_hiscores::Addscore(c_player* Player)
{
	FILE*file;
	int tempr=0;
	list[length-1].hiscore=Player->GetHiscore();
	strcpy(list[length-1].name,Player->GetName());
	if(list[0].hiscore<list[length-1].hiscore)tempr=3;
	for(int p=0;p<length-1;p++){
		for(int i=length-1;i>p;i--){
			if(list[i].hiscore>list[i-1].hiscore){
				Plscore temp;
				temp.hiscore=list[i].hiscore;
				temp.name=list[i].name;
				list[i].hiscore=list[i-1].hiscore;
				list[i].name=list[i-1].name;
				list[i-1].hiscore=temp.hiscore;
				list[i-1].name=temp.name;
				if(tempr!=3)tempr=2;
			}
		}
	}
	
	if((file=fopen("hiscores.txt","w"))==NULL){
		exit(0);
	}

	for(int i=0;i<length;i++)
	{
		fwrite(&list[i].hiscore,sizeof(int),1,file);
		fwrite(list[i].name,sizeof(char),20,file);
	}
	fclose(file);
	return tempr;
}

void c_hiscores::Update(float dt)
{
	movespeed=dt*status*1000;
	x+=movespeed;
	if(x<-200)status=0;
	if(x>350)status=0;

}
void c_hiscores::Enter()
{
	x=-200;
	status=1;
}
void c_hiscores::Leave()
{
	x=350;
	status=-1;
}

void c_hiscores::Render()
{
	Font->SetColor(0xFF333399);
	Font->printf(x,y+250,HGETEXT_LEFT,"HISCORES:");
	for(int i=0;i<length-1;i++)
	{
		Font->printf(x,y+i*40+300,HGETEXT_LEFT,"%d  %s - %5.5d",i,list[i].name,list[i].hiscore);
	}
}

c_hiscores::~c_hiscores()
{
	for(int i=0;i<length;i++)
	{
		delete[]list[i].name;
	}
	delete[]list;
	delete Font;
}

bool c_hiscores::IsDone()
{
	if(movespeed==0) return true;
	else return false;
}



// This method is called when the control
// receives or loses keyboard input focus
void c_hiscores::Focus(bool bFocused)
{
	if(bFocused)
	{
		
	}
	else
	{
		
	}

}

// This method is called to notify the control
// that the mouse cursor has entered or left it's area
void c_hiscores::MouseOver(bool bOver)
{
	if(bOver) gui->SetFocus(id);
}


// This method is called to notify the control
// that the left mouse button state has changed.
// If it returns true - the caller will receive
// the control's ID
bool c_hiscores::MouseLButton(bool bDown)
{
	if(!bDown)
	{
		
		return true;
	}
	else 
	{
		
		
		return false;
	}
}

// This method is called to notify the
// control that a key has been clicked.
// If it returns true - the caller will
// receive the control's ID
bool c_hiscores::KeyClick(int key, int chr)
{
	if(key==HGEK_ENTER || key==HGEK_SPACE)
	{
		MouseLButton(true);
		return MouseLButton(false);
	}

	return false;
}