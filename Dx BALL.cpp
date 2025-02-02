#include "iGraphics.h"
#include <stdio.h>
#define TotalBricks 54
#define ssw 1100
#define ssh 700
int showB=0;
int red=255,green=255,blue=255;
int yaxismargin=100;
int xB=500,yB=yaxismargin+10,rB=10;
int dx=5,dy=7;
int xBrd=xB-40,yBrd=yB-20;
int dyBrd=10,dxBrd=80;
int page[5]={0,1},scr=0;
char score[10]="SCORE:";
char digit[3];
char finalscore[13]="SCORE:000";
int usernameflag=0;
char username[100],str[100];
int len=0;
FILE *file;
char highscore[10000];
int resumeflag=1;
typedef struct
{
    int x=0;
    int y=400;
    int dx=100;
    int dy=20;
    int show=1;
    int red;
    int blue;
    int green;
}brickvar;
brickvar brick[TotalBricks];

void ScoreCat(int SCR)
{

    for(int i=2;i>=0;i--)
    {
        digit[i]=SCR%10+'0';
        SCR/=10;
    }
    strcpy(finalscore,score);
    strcat(finalscore,digit);
}
void resumeinfoinput()
{
    file=fopen("Resume.txt","w");
    fprintf(file,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",xB,yB,dx,dy,xBrd,yBrd,scr,resumeflag);
    for(int i=0;i<TotalBricks;i++)
    {
        fprintf(file,"%d\t",brick[i].show);
    }
    fclose(file);

}
void resumeinfooutput()
{
    file=fopen("Resume.txt","r");
    fscanf(file,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",&xB,&yB,&dx,&dy,&xBrd,&yBrd,&scr,&resumeflag);
    for(int i=0;i<TotalBricks;i++)
    {
        fscanf(file,"%d\t",&brick[i].show);
    }
    fclose(file);
}

void fileinput()
{
    file=fopen("Highscores.txt","a");
    fprintf(file,"Name : %s\t\t Score:%d\n",username,scr);
    fclose(file);
}
void fileoutput()
{
    file=fopen("Highscores.txt","r");
    int l=0;
    while(!feof(file))
    {

        char ch=fgetc(file);
        //printf("%c",ch);
        highscore[l++]=ch;

    }
    l=0;
    fclose(file);
}
void highscorescr()
{
    iSetColor(255,255,255);
    fileoutput();
    iText(100,600,highscore,GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(10,150,200);
    iText(10,660,"BACK",GLUT_BITMAP_TIMES_ROMAN_24);
}
void usernamescr()
{
    if(usernameflag==0)
    {
        iSetColor(150,150,150);
        iText(300,450,"ENTER USERNAME BELOW:",GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(300,400,500,40);
    }
    if(usernameflag)
    {
        iSetColor(255,255,255);
        iText(300,450,"ENTER USERNAME BELOW:",GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(300,400,500,40);
        iText(300,420,str,GLUT_BITMAP_HELVETICA_18);
    }
    iText(200,200,"CLICK INSIDE THE BOX TO START TYPING");
}
void pausesc()
{
    iShowBMP(0,0,"Blacksc.bmp");
    iShowBMP(ssw/2,ssh/2,"PAUSE.bmp");
    iText(300,500,"THE GAME IS PAUSE",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(50,100,"PRESS P TO RESUME AND PRESS E TO EXIT");
}
void startmanu()
{
    //iShowBMP(0,0,"StartManu.bmp");
    iShowBMP(0,0,"logo.bmp");
    //iLine(0,100,ssw,100);
    iSetColor(10,150,200);
    iText(50,100,"START",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(800,100,"HIGHSCORES",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(ssw-100,100,"EXIT",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200,100,"RESUME",GLUT_BITMAP_TIMES_ROMAN_24);

}
void gameinterface()
{
    iSetColor(red,green,blue);
    iFilledCircle(xB,yB,rB);
    iFilledRectangle(xBrd,yBrd,dxBrd,dyBrd);
    iText(ssw-200,650,finalscore,GLUT_BITMAP_TIMES_ROMAN_24);
    iLine(0,100,ssw,100);
    iText(10,660,"BACK",GLUT_BITMAP_TIMES_ROMAN_24);

    for(int i=0;i< TotalBricks;i++)
    {
        if(brick[i].show)
        {
            iSetColor(brick[i].red,brick[i].green,brick[i].blue);
            iFilledRectangle(brick[i].x,brick[i].y,brick[i].dx,brick[i].dy);
        }
    }
}

void definebricks()
{
    int somx=100;
    int somy=450;
    for(int i=0;i<TotalBricks;i++)
    {
        brick[i].x=somx;
        brick[i].y=somy;
        brick[i].red=rand()%255;
        brick[i].green=rand()%255;
        brick[i].blue=rand()%255;
        somx+=100;
        if(somx>=1000)
        {
            somx=100;
            somy+=20;
        }
    }
}
void restart()
{
       showB=0;
       xB=500;
       yB=yaxismargin+10;
       xBrd=xB-40;
       yBrd=yB-20;
       dx=5;
       dy=7;
       scr=0;
       resumeflag=0;
       strcpy(finalscore,"SCORE:000");
       for(int i=0;i<TotalBricks;i++)
       {
           brick[i].show=1;
       }

}
void iDraw()
{
    iClear();
    if(page[3])
       usernamescr();
    if(page[0])
       gameinterface();
    if(page[1])
        startmanu();
    if(page[2])
        pausesc();
    if(page[4])
        highscorescr();
}
void iKeyboard(unsigned char key)
{
   /* if(key=='r')
        {
          resumeinfooutput();
          resumeflag=0;
          page[0]=1;
          for(int i=1;i<5;i++)
            page[i]=0;
        }*/
    if(usernameflag==1 && page[3]==1)
    {

        if(usernameflag == 1)
        {
            if(key == '\r')
            {
                usernameflag = 0;
                strcpy(username, str);
                for(int i = 0; i < len; i++)
                    str[i] = 0;
                len = 0;
                fileinput();
                restart();
                page[0]=0;
                page[1]=1;
                page[2]=0;
                page[3]=0;
                page[4]=0;
            }
            else
            {
                str[len++] = key;

            }
        }
    }

    if(key==' ' && page[0]==1)
    {
        if(showB==1)
            showB=0;
        else if(showB==0)
            showB=1;
    }
   /* if(page[1]==1 && key=='s' )
       {
         page[0]=1;
         page[1]=0;
         page[2]=0;
         page[3]=0;
       }*/
    if(key=='p' && !page[1] && !page[3])
    {
        if(!page[2])
        {
            page[0]=0;
            page[1]=0;
            page[2]=1;
            page[3]=0;
            page[4]=0;
            showB=0;
        }
        else if(page[2])
        {
             page[0]=1;
             page[1]=0;
             page[2]=0;
             page[3]=0;
             page[4]=0;

             if(!showB)
              showB=1;
        }
    }
    if(key=='e')
    {
        resumeflag=1;
        resumeinfoinput();
        exit(0);
    }
}
void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_LEFT)
    {
        if(xBrd>=0)
            xBrd-=10;

            if(showB==0)
            {
                if(xBrd>=0)
                   xB-=10;
            }
    }
    if(key==GLUT_KEY_RIGHT)
    {
         if(xBrd<=ssw-dxBrd)
            xBrd+=10;
        if(!showB)
        {
            if(xBrd<=ssw-dxBrd)
               xB+=10;

        }

    }

}
void iMouse(int button,int state,int mx,int my)
{
    if(mx>=50 && mx <=150 && my>=100 && my<=130 && button==GLUT_LEFT_BUTTON &&page[1])
    {
        page[0]=1;
        page[1]=0;
        page[2]=0;
        page[3]=0;
        page[4]=0;
        restart();
    }
    if(mx>=10 && mx<=70 && my>=660 &&my<=700 && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && (page[4] ||page[0]))
    {
        for(int i=0;i<5;i++)
        {
            if(i==1)
                page[i]=1;
            else
                page[i]=0;
        }
    }
    if(mx>=200 && mx <=280 && my>=100 && my<=130 && button==GLUT_LEFT_BUTTON &&page[1])
    {
        if(resumeflag==1)
          resumeinfooutput();
          //resumeflag=0;
          page[0]=1;
          for(int i=1;i<5;i++)
            page[i]=0;
            ScoreCat(scr);
        /*page[0]=1;
        page[1]=0;
        page[2]=0;
        page[3]=0;
        page[4]=0;*/
    }
     if(mx>=800 && mx <=950 && my>=100 && my<=130 && button==GLUT_LEFT_BUTTON &&page[1])
    {
        page[0]=0;
        page[1]=0;
        page[2]=0;
        page[3]=0;
        page[4]=1;
    }
    if(mx>=1000 && mx<=1050 && my>=100 && my<=130 && button==GLUT_LEFT_BUTTON && page[1])
    {
        exit(0);
    }
    if(mx>=300 && mx<=800 && my>=400 && my<=440 && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && page[3])
    {
        if(usernameflag==0)
          usernameflag=1;
        else if(usernameflag==1)
            usernameflag=0;
    }
}
void iMouseMove(int mx,int my)
{

}
void ballmove()
{
    /*if(resumeflag==1)
    {
        resumeinfooutput();
        resumeflag=0;
    }*/

    if(showB==1)
    {
        xB+=dx;
        yB+=dy;
        if(xB>=ssw||xB<=0)
            dx=-dx;
        if(yB>=ssh)
            dy=-dy;



        for(int i=0;i<TotalBricks;i++)
        {
            if(brick[i].show)
            {
                if(xB>=brick[i].x && xB<=brick[i].x+brick[i].dx)
                {
                    if(yB>=brick[i].y && yB<=brick[i].y+brick[i].dy)
                    {
                        dy=-dy;
                        brick[i].show=0;
                        scr++;
                        ScoreCat(scr);
                    }
                }
                else if(yB>=brick[i].y && yB<=brick[i].y+brick[i].dy)
                {
                    if(xB>=brick[i].x && xB<=brick[i].x+brick[i].dx)
                    {
                        dx=-dx;
                        brick[i].show=0;
                        scr++;
                        ScoreCat(scr);
                    }
                }
            }
        }
         if(xB>=xBrd && xB<=xBrd+dxBrd && yB >=yBrd && yB<=yBrd+dyBrd)
            dy=-dy;
        else if(yB<=yaxismargin)
            {
                page[3]=1;
                for(int i=0;i<3;i++)
                    page[i]=0;
                    page[4]=0;
            }

    }
}
int main ()
{
    //page[3]=1;
    definebricks();
    iSetTimer(25,ballmove);
    iInitialize(ssw,ssh,"Dx Ball");
}
