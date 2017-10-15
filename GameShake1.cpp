#include<time.h>
#include<cstdlib>
#include<W:\Program Files\Torrent\My documents\Visual Studio 2010\Projects\GameShake1\Open GL\glut.h>
#include<Windows.h>
#include<cstdio>
#include<string>

int N=25,M=20;
int Scale=23;

int w=Scale*N;
int h=Scale*M;
//int dirk=0;
int End,count=0;

int pause=0;

int dir,num=4;

struct
{
	int x;
	int y;
} s[100];

class Fructs
{
public: int x,y;
	void New()
	{
		srand (time(NULL));
		x=rand()%N;
		y=rand()%M;
	}
	void DrawApple()
	{
		glColor3f(0.0,1.0,0.0);
		glRectf(x*Scale,y*Scale,(x+1)*Scale,(y+1)*Scale);
	}
}m;
void PrintChar(double x, double y, char *d)
{
	glColor3f(0.0,1.0,1.0);
	glRasterPos2i(x,y);
	int a=strlen(d);
	for(int i=0; i<a; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,d[i]);
}
void DrawField()
{
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_LINES);
	for(int i=0;i<w+1;i+=Scale)
	{
		glVertex2f(i,0);
		glVertex2f(i,h);
	}
	for(int j=0;j<h+1;j+=Scale)
	{
		glVertex2f(0,j);
		glVertex2f(w,j);
	}
	glEnd();
}

void Tick()
{
	for(int i=num;i>0;i--)
	{
		s[i].x=s[i-1].x;
		s[i].y=s[i-1].y;
	}
	
	/*if(dir==0)
		if(dirk!=2)
		{
			s[0].y+=1;
			dirk=dir;
		}
		else
		s[0].x+=1;
		printf("%d%d",dir,dirk);
	if(dir==1)
		if(dirk!=3)
		{
			s[0].x-=1;
			dirk=dir;
		}
		else
		s[0].y-=1;
		printf("%d%d",dir,dirk);
	if(dir==2)
		if(dirk!=0)
		{
			s[0].x+=1;
			dirk=dir;
		}
		else
		s[0].y+=1;
		printf("%d%d",dir,dirk);
	if(dir==3)
		if(dirk!=1)
		{
			s[0].y-=1;
			dirk=dir;
		}
		else
		s[0].x-=1;
		printf("%d%d",dir,dirk);*/
	if(dir==0) s[0].y+=1;
	if(dir==1) s[0].x-=1;
	if(dir==2) s[0].x+=1;
	if(dir==3) s[0].y-=1;
		if((s[0].x==m.x) && (s[0].y==m.y))
		{
			num++;
			m.New();
			for(int i=1;i<num;i++)
				if((s[i].x==m.x)&&(s[i].y==m.y))
					m.New();
			count++;
		}
		
		if(s[0].x>N-1) End=1;
		if(s[0].x<0) End=1;
		if(s[0].y>M-1)End=1;
		if(s[0].y<0) End=1;
		for(int i=1;i<num;i++)
			if((s[0].x==s[i].x) && (s[0].y==s[i].y))
				End=1;
}

void DrawSnake()
{
	glColor3f(0.0,0.0,1.0);
	for(int i=0;i<num;i++)
	{
		glRectf(s[i].x*Scale, s[i].y*Scale,(s[i].x+1)*Scale,(s[i].y+1)*Scale);
	}
}

void MyKeyboard(int key,int a,int b)
{
	switch(key)
	{	
		/*case 32: dir=4; break;*/
		case 101: dir=0; break;//вверх
		case 102: dir=2; break;//вниз
		case 100: dir=1; break;//влево
		case 103: dir=3; break;//вправо
	}
}
void score()
{
	PrintChar(10,480,"Score:");
	char a[5];
	itoa(count,a,10);
	PrintChar(100,480,a);
}
//void OnPause()
//{
//	pause=1;
//	PrintChar(250,250,"Game over");
//}
//void OffPause()
//{
//	pause=0;
//}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	m.DrawApple();
	DrawField();
	DrawSnake();
	
	if(End==1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		PrintChar(250,250,"Game over");
	}
	score();
	glFlush();
}
void timer(int=0)
{
	display();
	if((dir==4)&&(pause==0))
	{
		pause=1;
		dir=5;
	}
	if((dir==4)&&(pause==1))
		pause=0;
	if(pause==0)
		Tick();
	glutTimerFunc(55,timer,0);
}

int main(int argc,char **argv)
{
	m.New();
	s[0].x=10;
	s[0].y=10;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w,h);
	glutCreateWindow("Shake");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,640,0,530);

	glutDisplayFunc(display);
	glutTimerFunc(50,timer,0);
	glutSpecialFunc(MyKeyboard);

	glutMainLoop();

}