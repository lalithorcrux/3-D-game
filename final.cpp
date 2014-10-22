//Final

#pragma comment(lib, "winmm.lib")
#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
#include <GL/freeglut.h>
#include<time.h>
#include "imageloader.h"
#include <iostream>
#include<string.h>
#include <MMSystem.h>
#include<gl/freeglut_ext.h>
#include<windows.h>
using namespace std;	
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}


static GLint fogMode;


GLuint _textureId; //The id of the texture
GLuint _textureId1; //The id of the texture
GLuint _textureId2; //The id of the texture
GLuint _textureId3; //The id of the texture
GLuint _textureId4; //The id of the texture
GLuint _textureId5; //The id of the texture



#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define RAD2DEG(deg) (deg * 180 / PI)
#define rot_x(deg) (glRotatef(deg,1,0,0) )
#define rot_y(deg) (glRotatef(deg,0,1,0) )
#define rot_z(deg) (glRotatef(deg,0,0,1) )
#define g 9.8

struct Tile
{
	int fl;
	int tot;
	int u;
	int v;
};

typedef struct Tile Tile;
void printtext(int x, int y, const unsigned char *String);
// Function Declarations
void drawScene();
void update(int value);
void shake(int value);
void drawBall(float rad);
void handleMouseclick(int button, int state, int x1, int y1);
void initRendering();
void handleKeypress1(unsigned char key, int x1, int y1);
void handleResize(int w, int h);
void func_left();void func_right();void func_up();void func_down();
void drawCube(float x, float y, float z,float a) ;
void elbow_hand();
void handleKeypress2(int key, int x, int y);
void handleMotion(int x, int y);
int up_check(int x,int y);
int hole_check(int x,int y);
int stop_check(int x,int y);
int spring_check(int x,int y);
void drawthisSphere();
// Variable Declarations

Tile tile;
int h1[10],h2[10],stop1[10],stop2[10],u1[20],u2[20];
int sp1[10]={-7,5,2,-2,4,6,9,2,2,-5}; // spring action
int sp2[10]={7,3,-7,-3,1,-9,1,7,-1,7};
//int u1[20]={-1,-4,-9,-9,9,-3,6,-7,8,-8,1,5,-5,-4,-1,-8,7,7,-6,2};
//int u2[20] ={ 2,5,4,-4,4,-7,-8,9,-6,-7,6,0,1,2,-2,6,9,7,5,7};
float ball_x = 1.0f;
char str[125];
float ball_y = 0.0f;
int spf=0;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float max_height=1.0;
int r[2],s[2];
int lamp[10]={0};
int coins[21][21]={0};
int coin_x[20],coin_z[20];
int score=0;
float man_x = 0,man_y = 0,man_z = 0,d1 = 0 ,d2 = 0,d3 = -1,theta = 0,alpha=DEG2RAD(45),c_ang=0.0f;//,u_x=1/sqrt(2),u_y=1/sqrt(2),c_ang=0.0;
int flag_x = 0,z,deg=1,shake_fl=0,spr_fl=0;
int m2 = 1,inc=1;
int i,k = 0,fp_view=0,tower_view=0,tp_view=0,tile_view=0,hel_view=0;
int count = 0,flag = 0; // both these are used for jump
float hflag[20];
float tflag[20]={0};
int dog_x,dog_z;
//int flag_y = 0 ;
int jump = 0,proj_flag=0;
// Global Variables
float t=0,T;
float box_len = 4.0f;
float high = 0,h=0,zoom=0,drown=0,drown_flag=0,col_flag=0,buff2;
int  init_x,init_y,inc_flag=0,dir;
float z_angle=0,x_angle=0;
int windowWidth;
int windowHeight;
GLfloat angle = 0.0; //set the angle of rotation

class Human{
	public:
		GLUquadricObj * obj;
		void drawLeg(float x,float y,float z)
		{
			gluCylinder(obj,x,y,z,10,10); // base radius at z=0,top radius at z=height,height,slices,stacks
		}

		void drawHuman()
		{
			if(hflag[16]==1)
			{
				glTranslatef(0,hflag[15],0);
			}
			if(hel_view==1)
			{
				glTranslatef(0,1,0);
			}
			glPushMatrix();

			if(up_check(man_x,man_z)==1)
			{
				glTranslatef(0,h+buff2,0);
			}

			if(hole_check(man_x,man_z)==1)
			{
				drown_flag=1;
				glTranslatef(0,drown,0);
			}
			/*if(stop_check(man_x,man_z)==1)
			  {
			  drown_flag=1;
			  glTranslatef(0,drown,0);
			  }*/

			glPushMatrix();
			//glTranslatef(-10,0,10);
			//guLookAt(-10,0,10,-10+man_x,man_y,10+man_z,0,1,0);l
			glPushMatrix();
			glColor3f(1.0f,1.0f,1.0f);
			rot_x(90);
			glPushMatrix();
			glTranslatef(0.0, 0.0,0.2); //  decreasing z moves the obj away from us;but here as rotation 
			// is done,z=y
			glColor3f(238,0,0);
			gluCylinder(obj,0.4,0.4,0.7,10,10);  //drew the cylinder starting from 0,0,0.2
			glColor3f(1.0f,1.0f,1.0f);
			glPopMatrix();// came back to center of face(sphere)
			glPushMatrix();//this is center with rotation

			glTranslatef(0.0, 0.0,0.9);// came to lower circular part of the cylinder
			gluDisk(obj,0,0.4,10,10);//drawn b/w legs and stomach - top cover base cover
			glPopMatrix(); // came back again to center
			glutSolidSphere(0.2,20,20); //Face
			glTranslatef(0.2, 0.0,0.9);// Came to to prev drawn disk's position glTranslate(0.0+0.2,0.0+0.0,0.9+0.0)
			glPushMatrix();
			rot_x(-r[i]);
			glColor3f(0.100,0.149,0.237);
			gluCylinder(obj,0.15,0.15,0.4,10,10); // right upper
			glTranslatef(0.0,0.0,0.4);
			gluCylinder(obj,0.15,0.15,0.4,10,10); // right lower
			glPopMatrix();
			glTranslatef(-0.4, 0.0,0.0);// for left leg
			glPushMatrix();
			rot_x(-r[(i+1)%2]);
			gluCylinder(obj,0.15,0.15,0.4,10,10);
			glTranslatef(0.0,0.0,0.4);
			gluCylinder(obj,0.15,0.15,0.4,10,10); // drawing Legs
			glColor3f(1.0f,1.0f,1.0f);
			glPopMatrix();//returning  to the center of the sphere
			glPopMatrix(); // back to orginal axis

			elbow_hand();

			glPopMatrix();
			glPushMatrix();
			glTranslatef(0.0,0.0,-0.2);
			glPopMatrix();
			glPopMatrix();
			/*glBegin(GL_POINTS);
			  glColor3f(1.0,0.0,0.0);
			  glVertex3f(0.0,0.0,0.0);
			  glEnd();
			 */

		} // till here found

		Human()
		{
			obj = gluNewQuadric();
			gluQuadricNormals(obj, GLU_SMOOTH);   // Create Smooth Normals ( NEW )
			gluQuadricTexture(obj, GL_TRUE); 
			//constructor
		}

};

void back()
{
	PlaySound(TEXT("poc.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
	return;
}
//Tree tree;
Human robo;

int main(int argc, char **argv) {
	//tree.x=2,tree.y=-1,tree.z=-15;
	PlaySound(TEXT("poc.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
	i=0;  // initialisation
	for(int l=0;l<=1;l++)
	{
		r[l]=0;s[l]=0;
	}
	//hflag[1] = (rand()%20)-10;

	srand(time(NULL));
	for(z=0;z<20;z++)
	{
		hflag[z]=0;
		if(z<10)
		{	
			stop1[z]=(rand()%21)-10;
			stop2[z]=(rand()%21)-10;
			h1[z]=(rand()%21)-10;
			h2[z]=(rand()%21)-10;

			/*while((int)stop1[z]%2!=0)
			  {
			  stop1[z] = (rand()%21)-10;
			  }
			  while((int)stop2[z]%2!=0)
			  {
			  stop2[z] = (rand()%21)-10;
			  }
			  while((int)h1[z]%2!=0)
			  {
			  h1[z] = (rand()%21)-10;
			  }
			  while((int)h2[z]%2!=0)
			  {
			  h2[z] = (rand()%21)-10;
			  }*/
		}
		u1[z]=(rand()%21)-10;
		u2[z]=(rand()%21)-10;

		//printf("h1[%d]=%d,h2[z]=%d,u1[z]=%d,u2[z]=%d\n",z,h1[z],h2[z],u1[z],u2[z]);
	}
	for(z=0;z<20;z++)
	{
		int xz1,xz2;
xxx1:
		xz1 = (rand()%21)-10;
		xz2 = (rand()%21)-10;
		
		if(xz1==0 && xz2==0)
		{
			goto xxx1;
		}
		if(up_check(xz1,xz2)==1)
		{
			goto xxx1;
		}
		if(hole_check(xz1,xz2)==1)
		{
			goto xxx1;
		}
		coin_x[z]=xz1;
		coin_z[z]=xz2;
		//printf("%d %d\n",coin_x[z],coin_z[z]);
	}
	//printf("lamps are here\n");
	for(z=0;z<5;z++)
	{
		int xz1,xz2,xz3;
xxx2:
		xz1 = (rand()%21)-10;
		xz2 = (rand()%21)-10;
		if(xz1==0 && xz2==0)
		{
			goto xxx2;
		}
		if(up_check(xz1,xz2)==1)
		{
			goto xxx2;
		}
		if(hole_check(xz1,xz2)==1)
		{
			goto xxx2;
		}
		lamp[z*2]=xz1;
		lamp[z*2+1]=xz2;
		//printf("%d %d\n",lamp[2*z],lamp[2*z+1]);
	}
xxx3:
	dog_x = (rand()%21)-10;
	//dog_z = (rand()%21)-10;
	if(up_check(dog_x,0)==1)
	{
		goto xxx3;
	}
	if(hole_check(dog_x,0)==1)
	{
		goto xxx3;
	}
	dog_z=0;
	//T= (2*u_y )/g; // time of flight
	//u=(2*g)/sin(2*alpha);
	//printf("r[0]-%d r[1]-%d i-%d s[0]-%d s[1]-%d\n",r[0],r[1],i,s[0],s[1]);  
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	//windowWidth = w * 0.66;
	//windowHeight = h * 0.66;
	windowWidth = 1000;
	windowHeight = 1000;
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth)*0.5, (h - windowHeight)*0. );

	glutCreateWindow("Man");  // Setup the window
	initRendering();

	// Register callbacks
	tile.fl=0;
	tile.tot=0;
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutMotionFunc(handleMotion);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);
	glutTimerFunc(0.1,shake, 0);
	glutMainLoop();
	return 0;
}

// Function to draw objects on the screen
void drawScene()
{
	if(tflag[11]==1)
	{
		glEnable(GL_FOG);
		{
			GLfloat fogColor[4] = {1.0, 1.0, 1.0, 1.0};

			fogMode = GL_EXP;
			glFogi (GL_FOG_MODE, fogMode);
			glFogfv (GL_FOG_COLOR, fogColor);
			glFogf (GL_FOG_DENSITY, 0.075);
			glHint (GL_FOG_HINT, GL_DONT_CARE);
			glFogf (GL_FOG_START, 1.0);
			glFogf (GL_FOG_END, 5.0);
		}
	}
	/*if(spr_fl==1)
	  {
	  printf("asdd\n");
	  PlaySound(TEXT("chime.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
	  }*/
	//printf("it entered\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawthisSphere();
	//printf("flag is %d\n",proj_flag);

	//Add directed light
	GLfloat lightColor1[] = {0.8f, 0.0f, 0.9f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 2.0f, -1.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


	GLfloat ambientColor[] = {0.6f, 0.6f, 0.2f, 1.0f}; //Color(0.2, 0.2, 0.2)
	//GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color(0.2, 0.2, 0.2)
	//GLfloat ambientColor[] = {1.9f, 1.8f, 1.8f, 1.5f}; //Color(0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);

	//printf("%f\n",hflag[5]);
	/*if(hole_check(man_x,man_z)==1)
	  {
	  exit(0);
	  }*/

	if(score>=2)
	{
		if(tflag[11]==0)
		{
			tflag[11]=1;
			score=0;
			tflag[4]=0;
		}
		else
		{
			tflag[3]=1;
		}

	}
	if(tflag[4]>=100000)
	{
		tflag[6]=1;
	}
	if(tflag[6]==1)
	{		
		tflag[7] = tflag[4];
		strcpy(str,"You Lost the Game");
		printtext(450,950,(const unsigned char*)str);
		strcpy(str,"Time taken is more than 100 seconds");
		//itoa(tflag[5]/1000, str+14,10);
		//strcat(str, " sec.");
		printtext(425,900,(const unsigned char*)str);
		strcpy(str,"Better luck next time !!!!!");
		printtext(450,850,(const unsigned char*)str);
		//Sleep(10000);
		//exit(1);
	}

	if(tflag[11]==1)
	{
		if(tflag[12]==0)
		{
			tflag[5] = tflag[4];
			strcpy(str,"You Passed level 1.");
			printtext(450,950,(const unsigned char*)str);
			strcpy(str,"Time taken is  ");
			itoa(tflag[5]/1000, str+14,10);
			strcat(str, " sec.");
			printtext(450,900,(const unsigned char*)str);
			/*if(tflag[9]>=10000)
			  {
			  exit(1);
			  }*/
			//Sleep(10000);
			int a,c;
			for(a=0;a<20;a++)
			{
				for(c=0;c<20;c++)
				{
					coins[a][c]=0;
				}
			}
			tflag[12]=1;
		}
		//Sleep(10000);
		//exit(1);
	}





	if(tflag[3]==1)
	{
		tflag[5] = tflag[4];
		strcpy(str,"You Won the Game");
		printtext(450,950,(const unsigned char*)str);
		strcpy(str,"Time taken is  ");
		itoa(tflag[5]/1000, str+14,10);
		strcat(str, " sec.");
		printtext(450,900,(const unsigned char*)str);
		if(tflag[9]>=10000)
		{
			exit(1);
		}
		//Sleep(10000);
		//exit(1);
	}
	if(tflag[1]==1 && tflag[3]==0)
	{
		glPushMatrix();
		glScalef(2,2,2);
		strcpy(str,"Your Score: ");
		itoa(score, str+12,10);
		strcat(str, " coins. Your Game is over");

		printtext(450,950,(const unsigned char*)str);
		strcpy(str,"Try again later !!!!!");
		printtext(450,900,(const unsigned char*)str);
		glPopMatrix();
		if(tflag[2]>=10000)
		{
			exit(0);
		}
		//Sleep(5000);
		//char str1[25] = "Game Over";
		//printtext(160,110,(const unsigned char*)str1);
	}

	else if(tflag[3]==0)
	{
		strcpy(str,"Your Score: ");
		itoa(score, str+12,10);
		strcat(str, " coins. Time is ");
		itoa(tflag[4]/1000, str+29,10);
		strcat(str, " sec");
		printtext(450,900,(const unsigned char*)str);
	}

	//if(tflag[1]==0)
	//{

	if(hflag[0]==0)
	{
		hflag[1] = (rand()%21)-10;
		hflag[2] = (rand()%21)-10;
		hflag[3] = (rand()%21)-10;
		hflag[4] = (rand()%21)-10;
		hflag[11] = (rand()%21)-10;
		hflag[12] = (rand()%21)-10;
		/*while((int)hflag[1]%2!=0)
		  {
		  hflag[1] = (rand()%21)-10;
		  }
		  while((int)hflag[2]%2!=0)
		  {
		  hflag[2] = (rand()%21)-10;
		  }
		  while((int)hflag[3]%2!=0)
		  {
		  hflag[3] = (rand()%21)-10;
		  }
		  while((int)hflag[3]%2!=0)
		  {
		  hflag[3] = (rand()%21)-10;
		  }*/
		//hflag[2] = (rand()%21)-10;
		//hflag[3] = (rand()%21)-10;
		//hflag[4] = (rand()%21)-10;
		hflag[0]=1;
		//printf("%f %f %f %f %f %f\n",hflag[1],hflag[2],hflag[3],hflag[4],hflag[11],hflag[12]);
	}

	//printf("%f %f\n",man_x,man_z);

	if(man_x>10 || man_x<-10 || man_z>10 || man_z<-10)
	{
		//printf("%f %f\n",man_x,man_z);
		tflag[1]=1;
		exit(0);
	}
	//printf("%f %f\n",man_x,man_z);
	//printf("%f %f %f\n",d1,d2,d3);
	if(flag_x == 2){
		if(m2 == 0){

			if(d3 == 0){
				if(d1 == -1)
				{
					if(tflag[3]!=1 && tflag[6]!=1 && tflag[1]!=1)
					{
						man_x -= 1;
						int zxc;
						for(zxc=0;zxc<5;zxc++)
						{
							if(man_x==lamp[2*zxc] && man_z==lamp[2*zxc+1])
							{
								man_x=man_x+1;
							}
						}
					}
				}
				else if(d1 == 1)
				{
					if(tflag[3]!=1 && tflag[6]!=1 && tflag[1]!=1)
					{
						man_x += 1;
						int zxc;
						for(zxc=0;zxc<5;zxc++)
						{
							if(man_x==lamp[2*zxc] && man_z==lamp[2*zxc+1])
							{
								man_x=man_x-1;
							}
						}
					}
				}
				hflag[6] = man_x;
				//hflag[7] = hflag[6];
			}
			else if(d1 == 0){
				if(d3 == -1)
				{
					if(tflag[3]!=1 && tflag[6]!=1 && tflag[1]!=1)
					{
						man_z -=1;
						int zxc;
						for(zxc=0;zxc<5;zxc++)
						{
							if(man_x==lamp[2*zxc] && man_z==lamp[2*zxc+1])
							{
								man_z=man_z+1;
							}
						}
					}
				}
				else if(d3 == 1)
				{
					if(tflag[3]!=1 && tflag[6]!=1 && tflag[1]!=1)
					{
						man_z +=  1;
						int zxc;
						for(zxc=0;zxc<5;zxc++)
						{
							if(man_x==lamp[2*zxc] && man_z==lamp[2*zxc+1])
							{
								man_z=man_z-1;
							}
						}
					}

				}
				hflag[8] = man_z;
				//hflag[9] = hflag[8];
			}
			flag_x = 0;
			if(k == 0){
				if(i==0)i=1;
				else if(i==1) i=0;
			}
			if(k==0) k=1;
			else if(k==1) k=0;
		}
		m2 = (m2+1)%20;
	}
	else if(flag_x == 1){
		if(m2 == 0){

			if(d3 == 0){
				if(d1 == -1)
				{
					if(tflag[3]!=1 && tflag[6]!=1 && tflag[1]!=1)
					{
						man_x +=  1;
						int zxc;
						for(zxc=0;zxc<5;zxc++)
						{
							if(man_x==lamp[2*zxc] && man_z==lamp[2*zxc+1])
							{
								man_x=man_x-1;
							}
						}
					}
				}
				else if(d1 == 1)
				{
					if(tflag[3]!=1 && tflag[6]!=1 && tflag[1]!=1)
					{
						man_x -= 1;
						int zxc;
						for(zxc=0;zxc<5;zxc++)
						{
							if(man_x==lamp[2*zxc] && man_z==lamp[2*zxc+1])
							{
								man_x=man_x+1;
							}
						}
					}
				}
				hflag[6] = man_x;
			}
			else  if(d1 == 0){
				if(d3 == -1)
				{
					if(tflag[3]!=1 && tflag[6]!=1 && tflag[1]!=1)
					{
						man_z +=  1;
						int zxc;
						for(zxc=0;zxc<5;zxc++)
						{
							if(man_x==lamp[2*zxc] && man_z==lamp[2*zxc+1])
							{
								man_z=man_z-1;
							}
						}
					}
				}
				else if(d3 == 1)
				{
					if(tflag[3]!=1 && tflag[6]!=1 && tflag[1]!=1)
					{
						man_z -= 1;
						int zxc;
						for(zxc=0;zxc<5;zxc++)
						{
							if(man_x==lamp[2*zxc] && man_z==lamp[2*zxc+1])
							{
								man_z=man_z+1;
							}
						}
					}
				}
				hflag[8] = man_z;
			}
			flag_x = 0;
			if(k == 0){
				if(i==0) i=1;
				else if(i==1) i=0;
			}

			k = (k+1)%2;
		}
		m2 = (m2+1)%20;
	}
	// Draw Box
	if(fp_view==1)
	{
		//printf("ent %f %f %f\n",d1,d2,d3);
		gluLookAt(man_x+0.3*d1,man_y,man_z+0.3*d3,man_x+2*d1,man_y+2*d2,man_z+2*d3,0,1,0);
	}
	if(tp_view==1)
	{

		//printf("%f, %f,%f,%f,%f,%f\n",man_x-2*d1,man_y,man_z-2*d3,man_x,man_y,man_z);
		gluLookAt(man_x-2*d1,man_y,man_z-2*d3,man_x,man_y,man_z,0,1,0);
	}
	if(tower_view==1)
	{
		//gluLookAt(man_x-10*d1,man_y,man_z-10*d3,man_x,man_y,man_z,0,1,0);
		//printf("%f, %f,%f,%f,%f,%f\n",man_x-10*d1,man_y,man_z-10*d3,man_x,man_y,man_z);
		gluLookAt(-1.000000,-1.000000,19.000000,-1.000000,0.000000,9.000000,0,1,0);
	}
	if(tile_view==1)
	{
		//printf("tile coordinartes are %d %d amd mans coordinates are %f %f %f\n",tile.u,tile.v,man_x,man_y,man_z);
		//	printf("gggg\n");
		gluLookAt(tile.u,5,tile.v,man_x,man_y,man_z,0,1,0);
	}
	if(hel_view==1)
	{
		gluLookAt(0.000000, -0.000000,16.000000,man_x-2*d1,man_y,man_z-2*d3,0,1,0);
	}

	//printf("tile coordinartes are %d %d amd mans coordinates are %f %f %f\n",tile.u,tile.v,man_x,man_y,man_z);
	glPushMatrix();
	glTranslatef(0,0,zoom);
	//glTranslatef(0.0f, 0.0f, -5.0f);
	rot_z(z_angle);
	rot_x(x_angle);
	//glColor3f(1.0f, 0.0f, 0.0f);

	//glColor3f(1.0f, 1.0f, 0.0f);

	//gluLookAt(0,2,2,0,0,0,0,1,0); org
	if(fp_view == 0)
	{
		gluLookAt(0,1,2,0,0,0,0,1,0);
	}

	glPushMatrix();
	glTranslatef(man_x,man_y,man_z);
	rot_y(theta); // y coordinates of the obj don't change while turning right or left

	if(jump == 0)
	{
		robo.drawHuman();
	}
	else if(jump == 1){


		if(count==0){
			if(flag == 0)
			{
				high += deg*0.01;
			}
			//printf("high = %f\n",high);
			if(high >=  max_height)
			{
				flag = 1;
			}
			if(flag == 1)
			{
				high -=  deg*0.01;
			}
		}
		if(high < (0.0+spr_fl*0.5)){
			high = (0.0+spr_fl*0.5);
			flag = 0;
			count = 0;
			jump = 0;
		}

		count = (count+1)%2;
		glPushMatrix();
		glTranslatef(0.0,high,0.0);
		robo.drawHuman();
		//sleep(1);
		glPopMatrix();
	}


	glPopMatrix();
	//drawCube(-0.5,0.3,-0.4,0.2);

	float b=-2.1,a,c; // 2.9 org
	int ping=0,x=0,cv;
	float p,side,buff; // buff is used for synchronizing block and robo
	if(hel_view==0)
	{
		p=10;side=1,buff=0;
	}
	else
	{
		p=10;side=1,buff=0.8;
	}
	glPushMatrix();
	glTranslatef(0.0,-5.0,0.0);
	glColor3f(0,1,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(10.0f, 10.0f);
	glVertex3f(100.0,0.0,100.0);
	glTexCoord2f(10.0f, 0.0f);
	glVertex3f(-100.0,0.0,100.0);
	glTexCoord2f(0.0f, 10.0f);
	glVertex3f(-100.0,0.0,-100.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(100.0,0.0,-100.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	//glRotatef(30,0,0,1);
	glColor3f(248,248,255);
	spr_fl=0;
	deg=1;
	jump=0;
	max_height=1.0;
	for( a=-p*side;a<=p*side;a+=side)
	{
		x++;
		for( c=-p*side;c<=p*side;c+=side)
		{
			glColor3f(248,248,255);
			int cv,flagxz=0,zxc;
			//if((int)(a+c)%2==0)
			//{
			if(ping==0)
			{
				//glColor3f(1,1,0);
				//glColor3f(1,0,0);
			}
			else
			{
				//glColor3f(1,1,1);
			}
			/*if(tflag[1]==1)
			  {
			  glPushMatrix();
			  glScalef(1,1,1);
			  glEnable(GL_TEXTURE_2D);
			  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			  glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			  glEnable(GL_TEXTURE_GEN_T);
			  glBindTexture(GL_TEXTURE_2D, _textureId5);
			//glutSolidCube(2);
			drawCube(a,b+buff+4,c,side);
			glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
			//	glutSolidCube(2);
			glPopMatrix();
			//drawCube(a,b+buff,c,2);
			}*/

			//ping=(ping+1+x)%2;
			ping=(ping+1)%2;

			//if(hel_view==1)
			//{

			if( up_check(a,c)==1 )
			{
				srand(time(NULL));
				buff2= (float)((rand()%19)+2) / 20 ;
				glPushMatrix();
				glScalef(1,1,1);
				glEnable(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glEnable(GL_TEXTURE_GEN_T);
				if((int)(a+c)%2==0)
				{
					glBindTexture(GL_TEXTURE_2D, _textureId1);
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, _textureId2);
				}
				//glutSolidCube(2);
				drawCube(a,b+h+buff+buff2,c,side);
				glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
				//	glutSolidCube(2);
				glPopMatrix();

				//drawCube(a,b+h+buff+buff2,c,side);
			}
			else if( up_check(a,c)==0 && hole_check(a,c)==0)
			{
				if(ping==0)
				{
					//glColor3f(1,0,0);
				}
				else
				{
					//glColor3f(1,1,1);
				}
				if(tile.fl==1 && a==tile.u && c==tile.v)
				{
					glColor3f(0,0,255);
					//glColor3f(0,197,205);
				}
				if((a==hflag[1] && c==hflag[2]) || (a==hflag[3] && c==hflag[4]))
				{
					//printf("%f %f %f %f %f %f\n",a,c,hflag[1],hflag[2],hflag[3],hflag[4]);
					glColor3f(0,0,0);
				}
				//printf("it entered\n");
				for(zxc=0;zxc<5;zxc++)
				{
					//printf("it entered\n");
					if(((int)a==lamp[zxc*2]) && ((int)c==lamp[zxc*2+1]))
					{
						//printf("it entered\n");
						//printf("%f %d %f %d\n",a,lamp[2*zxc],c,lamp[2*zxc+1]);
						glPushMatrix();
						glTranslatef(a,b+buff+0.8,c);
						glRotatef(90,1,0,0);
						GLUquadricObj *quadratic;
						quadratic = gluNewQuadric();
						glColor3f(0.3,0.1,0.8);
						gluCylinder(quadratic,0.25,0.5,0.2,32,32);
						glTranslatef(0,0,-2);
						glColor3f(0.3,0.9,0.5);
						gluCylinder(quadratic,0.25,0.25,2.0,32,32);
						glColor3f(0.6,0.9,0.8);
						gluCylinder(quadratic,0.5,0.25,0.2,32,32);
						glColor3f(248,248,255);
						glTranslatef(0,0,-0.3);
						gluCylinder(quadratic,0.30,0.30,0.3,32,32);
						glTranslatef(0,0,-0.2);
						glColor3f(0.6,0.9,0.8);
						gluCylinder(quadratic,0.25,0.5,0.2,32,32);
						//glTranslatef(-1*a,-1*(b+buff+1.5),-1*c);
						glPopMatrix();
					}
				}

				if(coins[(int)a+10][(int)c+10]==0)
				{
					for(cv=0;cv<20;cv++)
					{
						if(coin_x[cv]==(int)a && coin_z[cv]==(int)c)
						{

							glPushMatrix();
							//printf("%f %f\n",a,c);
							glTranslatef(a,b+buff+1.5,c);
							glScalef(1,1,0.1);
							/*glPushMatrix();
							  glScalef(1,1,1);
							  glEnable(GL_TEXTURE_2D);
							  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
							  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
							  glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
							  glEnable(GL_TEXTURE_GEN_T);
							  glBindTexture(GL_TEXTURE_2D, _textureId4);
							  glPushMatrix();
							  rot_y(c_ang);
							  glutSolidCube(0.5);
							  glPopMatrix();
							//drawCube(a,b+buff,c,side);
							glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
							glDisable(GL_TEXTURE_GEN_T);
							glDisable(GL_TEXTURE_2D);

							//	glutSolidCube(2);
							glPopMatrix();*/
							glColor3f(0.255,0.215,0);
							rot_z(c_ang);
							glutSolidCube(0.5);


							//glutSolidCube(0.5);
							glTranslatef(-1*a,-1*(b+buff+1.5),-1*c);
							//glTranslatef(0,-1,0);
							glPopMatrix();
							if((int)man_x==coin_x[cv] && (int)man_z==coin_z[cv])
							{
								score++;
								PlaySound(TEXT("chime.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
								coins[(int)a+10][(int)c+10]=1;
								Sleep(300);
								back();
							}


						}
					}
				}
				if(a==man_x && c==man_z)
				{
					glColor3f(0,255,0);

					if(spring_check(a,c)==1)
					{
						//glColor3f(0.238,0,0.238);
						jump=1;
						spr_fl=1;
						//	printf("foff");
						/*if (spf==0)
						  {
						  PlaySound(TEXT("jump.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
						  spf=1;

						  }*/
						//back();

						deg=15;
						max_height=4.0;
						//PlaySound(TEXT("jump.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
					}
					//printf("Score is %d\n",score);
					//col_flag=1;
					//glColor3f(0,238,0);
				}
				if(spring_check(a,c)==1)
				{
					glColor3f(0.238,0,0.238);
					//glTranslatef(

				}

				glPushMatrix();
				glScalef(1,1,1);
				glEnable(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glEnable(GL_TEXTURE_GEN_T);
				if((int)(a+c)%2==0)
				{
					glBindTexture(GL_TEXTURE_2D, _textureId1);
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, _textureId2);
				}
				//glBindTexture(GL_TEXTURE_2D, _textureId1);
				//glutSolidCube(2);
				if(hflag[16]==1)
				{
					if(a==man_x && c==man_z)
					{
						glTranslatef(0,hflag[15],0);
					}
				}
				drawCube(a,b+buff,c,side);
				if(hflag[16]==1)
				{
					if(a==man_x && c==man_z)
					{
						glTranslatef(0,-1*hflag[15],0);
					}
				}

				//drawCube(a,b+buff,c,side);
				glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
				//	glutSolidCube(2);
				glPopMatrix();
				//drawCube(a,b+buff,c,side);
			}
			else  // holes
			{
				glColor3f(248,248,255);
			}
			if(spring_check(a,c)==1)
			{
				glColor3f(0.238,0,0.238);
				glPushMatrix();
				glTranslatef(a,-1.5,c);
				glutSolidSphere(0.5,32,32);
				glPopMatrix();
			}
			//}
			/*else
			  {
			  if(ping==0)
			  {
			//glColor3f(1,1,0);
			//glColor3f(1,0,0);
			}
			else
			{
			//glColor3f(1,1,1);
			}


			//ping=(ping+1+x)%2;
			ping=(ping+1)%2;

			//if(hel_view==1)
			//{
			if( up_check(a,c)==1 )
			{
			srand(time(NULL));
			buff2= (float)((rand()%19)+2) / 20 ;
			glPushMatrix();
			glScalef(1,1,1);
			glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			glEnable(GL_TEXTURE_GEN_T);
			glBindTexture(GL_TEXTURE_2D, _textureId2);
			//glutSolidCube(2);
			drawCube(a,b+h+buff+buff2,c,side);
			glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
			//	glutSolidCube(2);
			glPopMatrix();

			//drawCube(a,b+h+buff+buff2,c,side);
			}
			else if( up_check(a,c)==0 && hole_check(a,c)==0)
			{
			if(ping==0)
			{
			//glColor3f(1,0,0);
			}
			else
			{
			//glColor3f(1,1,1);
			}
			if(tile.fl==1 && a==tile.u && c==tile.v)
			{
			glColor3f(0,0,255);
			//glColor3f(0,197,205);
			}
			if((a==hflag[1] && c==hflag[2]) || (a==hflag[3] && c==hflag[4])) // Teleporting
			{
			//printf("%f %f %f %f %f %f\n",a,c,hflag[1],hflag[2],hflag[3],hflag[4]);
			//glColor3f(0.5,0.1,0.9);
			glColor3f(128,0,128);
			}
			if(coins[(int)a+10][(int)c+10]==0)
			{
			//score++;
			for(cv=0;cv<10;cv++)
			{
			if(coin_x[cv]==(int)a && coin_z[cv]==(int)c)
			{
			glPushMatrix();
			//printf("%f %f\n",a,c);
			glTranslatef(a,b+buff+1.5,c);
			glScalef(1,1,0.1);



			glPushMatrix();
			glScalef(1,1,1);

			glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			glEnable(GL_TEXTURE_GEN_T);
			glBindTexture(GL_TEXTURE_2D, _textureId4);
			glPushMatrix();
			rot_y(c_ang);
			glutSolidCube(0.5);
			glPopMatrix();
			//drawCube(a,b+buff,c,side);
			glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
			//	glutSolidCube(2);
			glPopMatrix();


			//glutSolidCube(0.5);
			glTranslatef(-1*a,-1*(b+buff+1.5),-1*c);
			//glTranslatef(0,-1,0);
			glPopMatrix();
			if((int)man_x==coin_x[cv] && (int)man_z==coin_z[cv])
			{
				score++;
				coins[(int)a+10][(int)c+10]=1;
			}
		}
		}
		}
		if(a==man_x && c==man_z)
		{
			glColor3f(0,255,0);

			if(spring_check(a,c)==1)
			{
				//glColor3f(0.238,0,0.238);
				jump=1;
				spr_fl=1;
				deg=15;
				max_height=4.0;
			}
			//col_flag=1;
			//glColor3f(0,238,0);
		}



		glPushMatrix();
		glScalef(1,1,1);
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		glEnable(GL_TEXTURE_GEN_T);
		glBindTexture(GL_TEXTURE_2D, _textureId2);
		//glutSolidCube(2);
		drawCube(a,b+buff,c,side);
		glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
		//	glutSolidCube(2);
		glPopMatrix();
		//drawCube(a,b+buff,c,side);
		}
		else  // holes
		{
			//glColor3f(248,248,255);
		}
		}*/
		/*}
		  else
		  {
		  drawCube(a,b,c,side);
		  }*/

		//	printf("%f %f %f\n",a,b,c);
		}
		}
		glPopMatrix();

		glPushMatrix();

		/*for( a=-p*side;a<=p*side;a+=side)
		  {
		  for( c=-p*side;c<=p*side;c+=side)
		  {
		  glColor3f(248,248,255);
		  }
		  }*/
		glPopMatrix();

		//drawCube(-0.5,1.5,0.5,1.2);

		//}
		/*else
		  {				
		  glPushMatrix();
		  glScalef(1,1,1);
		  glEnable(GL_TEXTURE_2D);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		  glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		  glEnable(GL_TEXTURE_GEN_T);
		  glBindTexture(GL_TEXTURE_2D, _textureId5);
		//glutSolidCube(2);
		//drawCube(0,b+h+buff+2,0,2);
		glColor3f(1,0,0);
		glutSolidCube(1);
		glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
		//	glutSolidCube(2);
		glPopMatrix();
		//char str[25] = "Your Score: ";
		char str1[25] = "Game Over";
		//itoa(score, str+12,10);
		//strcat(str, " coins");
		printtext(100,110,(const unsigned char*)str1);
		//printtext(120,130,(const unsigned char*)str1);
		}*/
		glPopMatrix(); 
		glutSwapBuffers();
}

void elbow_hand()
{
	glPushMatrix();//elbow
	rot_x(s[i]); // right elbow
	glTranslatef(0.37,-0.3,0.0);
	rot_z(-60);
	glTranslatef(0.1,0.0,0.0);
	glPushMatrix();
	glScalef(0.15,0.1,0.05);
	glScalef(2,2,2); // increase from the normal size
	glColor3f(238,0,0);
	glutSolidCube(1.0);
	glPopMatrix();
	glTranslatef(0.25,0.0,0.0);// drawing hand
	rot_z(-30);
	glTranslatef(0.1,0.0,0.0);
	glScalef(0.4,0.15,0.1);
	glColor3f(0.729f,0.423f,0.286f);
	glutSolidCube(1.0);

	glPopMatrix();

	glPushMatrix();
	rot_x(s[(i+1)%2]);
	glTranslatef(-0.37,-0.3,0.0);//elbow
	rot_z(60);
	glTranslatef(-0.1,0.0,0.0);
	glPushMatrix();
	glScalef(0.15,0.1,0.05);
	glScalef(2,2,2); // increase from the normal size
	glColor3f(238,0,0);
	glutSolidCube(1.0);
	glPopMatrix();
	glTranslatef(-0.25,0.0,0.0);
	rot_z(30);//hand
	glTranslatef(-0.1,0.0,0.0);
	glScalef(0.4,0.15,0.1);
	glColor3f(0.729f,0.423f,0.286f);
	glutSolidCube(1.0);
	glPopMatrix();
}

int up_check(int x,int y)
{  
	int i;

	for(i=0;i<20;i++)
	{
		if(x==u1[i] && y==u2[i])
		{
			return 1;
		}
	}
	return 0;

}

int hole_check(int x,int y)
{
	int i;

	for(i=0;i<10;i++)
	{
		if(x==h1[i] && y==h2[i])
			return 1;
	}
	return 0;

}
int spring_check(int x,int y)
{
	int i;

	for(i=0;i<10;i++)
	{
		if(x==sp1[i] && y==sp2[i])
			return 1;
	}
	return 0;

}
void drawCube(float x, float y, float z,float a) 
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glBegin(GL_QUADS); 
	// Bottom Face

	glNormal3d(0,-1,0);
	glVertex3f(-a/2,-a/2 ,-a/2);
	glVertex3f(a/2, -a/2, -a/2);
	glVertex3f(a/2, a/2, -a/2);
	glVertex3f(-a/2, a/2, -a/2);




	//Left Face
	glNormal3d(-1,0,0);
	glVertex3f(-a/2, -a/2, -a/2);
	glVertex3f(-a/2, a/2, -a/2);
	glVertex3f(-a/2, a/2, a/2);
	glVertex3f(-a/2, -a/2, a/2);

	//Front Face
	glNormal3d(0,0,1);
	glVertex3f(-a/2, -a/2, -a/2);
	glVertex3f(-a/2, -a/2, a/2);
	glVertex3f(a/2, -a/2, a/2);
	glVertex3f(a/2, -a/2, -a/2);

	rot_x(x_angle);


	//Top Face
	glNormal3d(0,1,0);
	glVertex3f(-a/2, -a/2, a/2);
	glVertex3f(a/2, -a/2, a/2);
	glVertex3f(a/2, a/2, a/2);
	glVertex3f(-a/2, a/2, a/2);

	//Right Face


	glNormal3d(1,0,0);
	glVertex3f(a/2,-a/2 ,-a/2 );
	glVertex3f(a/2, -a/2, a/2);
	glVertex3f(a/2, a/2, a/2);
	glVertex3f(a/2, a/2,-a/2);

	//Back Face
	glNormal3d(0,0,-1);
	glVertex3f(-a/2, a/2, -a/2);
	glVertex3f(-a/2, a/2, a/2);
	glVertex3f(a/2, a/2, a/2);
	glVertex3f(a/2, a/2, -a/2);
	glEnd();


	glPopMatrix();
}


void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// Setting a background color
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	if(tflag[11]==1)
	{
		glEnable(GL_FOG);
		{
			GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};

			fogMode = GL_EXP;
			glFogi (GL_FOG_MODE, fogMode);
			glFogfv (GL_FOG_COLOR, fogColor);
			glFogf (GL_FOG_DENSITY, 0.35);
			glHint (GL_FOG_HINT, GL_DONT_CARE);
			glFogf (GL_FOG_START, 1.0);
			glFogf (GL_FOG_END, 5.0);
		}
	}
	Image* image = loadBMP("water.bmp");//bmp
	//Image* image = loadBMP("g1.bmp");//bmp
	_textureId = loadTexture(image);
	delete image;
	Image* image1 = loadBMP("tiles.bmp");//bmp
	//Image* image1 = loadBMP("w1.bmp");//bmp
	_textureId1 = loadTexture(image1);
	delete image1;
	//Image* image2 = loadBMP("bl1.bmp");//bmp
	Image* image2 = loadBMP("vtr1.bmp");//bmp
	_textureId2 = loadTexture(image2);
	delete image2;
	Image* image3 = loadBMP("birds.bmp");//bmp
	_textureId3 = loadTexture(image3);
	delete image3;
	Image* image4 = loadBMP("goldcoin.bmp");//bmp
	_textureId4 = loadTexture(image4);
	delete image4;
	Image* image5 = loadBMP("gameover.bmp");//bmp
	_textureId5 = loadTexture(image5);
	delete image5;
}


void shake(int value)
{
	if(jump==1)
	{
		if(shake_fl==0)
		{	
			func_up();	
		}
		else if(shake_fl==1)
		{
			func_down();
		}
		shake_fl=(shake_fl+1)%2;
		//printf("(%d,%d,%d,%d)\n",r[0],s[0],r[1],s[1]);
	}
}
// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {



	// Handle ball collisions with box
	if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
		ball_velx *= -1;
	if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
		ball_vely *= -1;

	// Update position of ball
	ball_x += ball_velx;
	ball_y += ball_vely;
	if(tflag[3]==1)
	{
		tflag[9]=tflag[9]+10;
	}

	if(hflag[6]==hflag[7] && hflag[8]==hflag[9] && hflag[5]>=5000)
	{
		hflag[16]=1;
		hflag[15]=hflag[15]-1;
		if(hflag[5]>=6000)
		{
			tflag[1] = 1;
			//exit(0);
		}
	}
	else if(hflag[6]!=hflag[7] || hflag[8]!=hflag[9])
	{
		hflag[7] = hflag[6];
		hflag[9] = hflag[8];
		hflag[5]=0;
	}
	/*if(flag_x==1 || flag_x==2)
	  {
	  }*/
	if(tflag[3]==0)
	{
		tflag[4] = tflag[4] + 10;
	}
	else
	{
		tflag[4] = tflag[4];
	}
	tflag[2] = tflag[2] + 10;
	hflag[5] = hflag[5] + 10;
	//printf("%f\n",hflag[5]);
	srand(time(NULL));
	int x=rand()%10+1;
	if(inc==1)
	{
		h+=0.010*x;
	}
	if(h>=4)
	{
		inc=0;
	}

	if(inc==0)
	{
		h-=0.010*x;
	}
	if(h<=-4)
	{
		inc=1;
	}

	if(drown_flag==1)
	{

		drown-=0.01;
		if(drown<=-2)
		{
			tflag[1]=1;
			/*glPushMatrix();
			  glScalef(1,1,1);
			  glTranslatef(man_x,5,man_z);
			  glEnable(GL_TEXTURE_2D);
			  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			  glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			  glEnable(GL_TEXTURE_GEN_T);
			  glBindTexture(GL_TEXTURE_2D, _textureId5);
			//glutSolidCube(2);

			glutSolidCube(2);
			glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
			//	glutSolidCube(2);
			glPopMatrix();
			Sleep(5000);*/
			//exit(0);
		}
	}

	if(proj_flag==1)
	{
		if(d1==0)
		{
			man_z+=d3*dir*0.02;
			if(inc_flag==0)
				man_y+=0.05;
		}

		if(d3==0)
		{
			man_x+=d1*dir*0.02;
			if(inc_flag==0)
				man_y+=0.05;
		}

		if(man_y>=2)
		{
			inc_flag=1;
		} 	

		if(inc_flag==1)
			man_y-=0.05;

		if(man_y<=0)
		{
			proj_flag=0;
			inc_flag=0;
		}

		//printf(" man %f,%f,%f\n",man_x,man_y,man_z);
	}

	c_ang+=2.5;
	if(c_ang>360)
	{
		c_ang=0;
	}

	glutTimerFunc(10, update, 0);
}

void handleKeypress2(int key, int x1, int y1)
{
	if (key == GLUT_KEY_RIGHT){
		func_right();

	}
	if (key == GLUT_KEY_LEFT){
		func_left();	  

	}
	if (key == GLUT_KEY_DOWN){
		func_down();

	}

	if (key == GLUT_KEY_UP){
		func_up();
	}

}
void handleKeypress1(unsigned char key, int x1, int y1)
{

	if (key == 27) {
		exit(0);     // escape key is pressed
	}

	if(key == 'j'){
		jump = 1;
	}
	if(key=='f')
	{
		fp_view=(fp_view+1)%2;
	}
	if(key=='t')
	{
		tp_view=(tp_view+1)%2;
	}
	if(key=='u')
	{
		tower_view=(tower_view+1)%2;
	}
	if(key=='i')
	{
		tile_view=(tile_view+1)%2;
	}
	if(key=='h')
	{
		hel_view=(hel_view+1)%2;
	}

	if(key=='s')
	{
		tile.fl=1;
		tile.tot++;
		int r,s;
		r=tile.tot/21;
		s=tile.tot%21;
		tile.u=-10+r;
		tile.v=-10+s;
	}
	if(key=='e')
	{
		tile.fl=0;
	}

	if(key=='r')
	{
		dir=1;
		proj_flag=1;
	}

	if(key=='l')
	{
		dir=-1;
		proj_flag=1;
	}
	if(key=='p')
	{
		if(man_x==hflag[1] && man_z==hflag[2])
		{
			man_x = hflag[3];
			man_z = hflag[4];
		}
		else if(man_x==hflag[3] && man_z==hflag[4])
		{
			man_x = hflag[1];
			man_z = hflag[2];
		}
	}
}



void handleMouseclick(int button, int state, int x1, int y1) 
{

	if (state == GLUT_DOWN)  // mouse pressed
	{
		//tower_view=1;
		if (button == GLUT_LEFT_BUTTON)
		{
			init_x=x1;
			init_y=y1;
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
		}
		if(button==3)
		{
			zoom+=0.5;
		}
		if(button==4)
		{
			zoom-=0.5;
		}
	}
	else // released
	{

	}
}

void handleMotion(int x, int y)
{
	int dx,dy; 
	dx=x-init_x;
	dy=y-init_y;

	init_x=x;
	init_y=y;

	z_angle+=dx;
	x_angle+=dy;

}
// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 2000000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void func_right()
{
	for(int i=0;i<=1;i++)
	{
		r[i]=0;
		s[i]=0;
	}

	if(d3 == 0)
	{
		d3 = d1;
		d1 = 0;
	}

	else if(d1 == 0)
	{
		d1 = -d3;
		d3 = 0;
	}
	theta = theta + 90;

}

void func_left()
{
	for(int i=0;i<=1;i++)
	{
		r[i]=0;
		s[i]=0;
	}
	if(d3 == 0.0)
	{
		d3 = -d1;
		d1 = 0;
	}

	else if(d1 == 0.0)
	{
		d1 = d3;
		d3 = 0;
	}

	theta = (theta + 90);
}

void func_down()
{
	r[0] +=30;
	s[0] -= 20;

	if(s[0] == -40)
		s[0] = 0;
	if(r[0] == 60)
		r[0] = 0;
	r[1] -= 20;
	s[1] +=  30;

	if(r[1] == -40)
		r[1] = 0;
	if(s[1] == 60)
		s[1] = 0;
	m2 = 0;
	flag_x = 1;
}

void func_up()
{
	r[0] +=30;
	s[0] -= 20;
	if(s[0] == -40)
		s[0] = 0;
	if(r[0] == 60)
		r[0] = 0;

	r[1] -= 20;
	s[1] += 30;

	if(r[1] == -40)
		r[1] = 0;
	if(s[1] == 60)
		s[1] = 0;

	m2 = 0;
	flag_x = 2;
}

void drawthisSphere()
{
	glPushMatrix();
	glTranslatef(0.0,-5.0,0.0);
	//glColor3f(0,1,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId3);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glBegin(GL_QUADS);
	/*glNormal3f(0.0,1.0,0.0);
	  glTexCoord2f(10.0f, 10.0f);
	  glVertex3f(100.0,0.0,100.0);
	  glTexCoord2f(10.0f, 0.0f);
	  glVertex3f(-100.0,0.0,100.0);
	  glTexCoord2f(0.0f, 10.0f);
	  glVertex3f(-100.0,0.0,-100.0);
	  glTexCoord2f(0.0f, 0.0f);
	  glVertex3f(100.0,0.0,-100.0);*/
	glutSolidSphere(100.0,32,32);
	//glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void printtext(int x, int y, const unsigned char *String)
{
	//(x,y) is from the bottom left of the window
	//printf("%c\n",String[0]);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();	
	glLoadIdentity();
	glOrtho(0, windowWidth, 0, windowHeight, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x,y);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, String);

	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	return;
}


//printtext(450,900,(const unsigned char*)"YOU LOST");
