//#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <stdio.h>
#include "OBJ_Loader.h"
#include <fstream>
#include "SOIL.h"


GLfloat T = 0;
GLfloat Cx=0,Cy=0,Cz=3, t =0,l=0;
GLuint texture;
GLuint texture2;


GLuint LoadTexture( const char * filename )
{
  GLuint texture;
  int width, height;
  unsigned char * data;

  FILE * file;
  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

  for(int i = 0; i < width * height ; ++i)
  {
    int index = i*3;
    unsigned char B,R;
    B = data[index];
    R = data[index+2];

    data[index] = R;
    data[index+2] = B;
  }

  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );

  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
  free( data );

  return texture;
}



//globals
GLuint elephant;
float elephantrot;
char ch='1';
//other functions and main
//wavefront .obj loader code begins
void loadObj(char *fname)
{
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;
    elephant=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(elephant, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_POINTS);
        while(!(feof(fp)))
        {
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v')
            {
                glVertex3f(x,y,z);
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}
//wavefront .obj loader code ends here
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    //glOrtho(-25,25,-2,2,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}
void drawElephant()
{
    glPushMatrix();
        glTranslatef(-0.5,-0.25,-0.50);
        glColor3f(1.0,0.5,0.27);
        glScalef(0.15,0.15,0.15);
        //glRotatef(elephantrot,0,1,0);
        glCallList(elephant);
    glPopMatrix();
    elephantrot=elephantrot+0.6;
    if(elephantrot>360)elephantrot=elephantrot-360;
}







void Spin()
{
    T = T + t;
    if(T>360)
        T = 0;
    glutPostRedisplay();
}

void Key(unsigned char ch,int x,int y)
{
    switch(ch)
    {
        case 'x' : Cx = Cx - 0.5;   break;
        case 'X' : Cx = Cx + 0.5;   break;

        case 'y' : Cy = Cy - 0.5;   break;
        case 'Y' : Cy = Cy + 0.5;   break;

        case 'z' : Cz = Cz - 0.5;   break;
        case 'Z' : Cz = Cz + 0.5;   break;
        case 't' : t = t + 0.5;   break;
        case 'l' : l = l + 1.5;   break;
        case 'L' : l = l - 1.5;   break;
    }
    glutPostRedisplay();
}


void Draw()
{

    GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat white[] = {1.0f,1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f,0.0f, 0.0f, 0.0f};
    GLfloat green[]={0.0f,1.0f,0.0f,1.0f};
    GLfloat blue[]={0.0f,0.0f,1.0f,1.0f};
    GLfloat orange[]={1.0f,0.3f,0.0f,1.0f};
    GLfloat yellow[]={1.0f,1.0f,0.0f,1.0f};
    GLfloat violet[]={1.0f,0.0f,1.0f,1.0f};



            /*Lighting*/
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glEnable(GL_LIGHTING);   // Enable Lighting
    glDepthFunc(GL_LEQUAL);  // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


    /*Light values*/
    GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightDiffuse[]= { 2.0f, 1.8f, 1.8f, 1.8f };
    GLfloat LightPosition[]= { 14.0f, 13.0f, 12.0f, 12.0f };
    /*Setting light values*/
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, green ); // Sets specular component of light 0 to red,
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
    //glEnable(GL_CULL_FACE);

    if(l > 0 ){
        glDisable(GL_LIGHT1);
    }



    

    GLfloat Pos[] = {0,1,0,1};
    GLfloat Col[] = {1,0,0,1};

    GLfloat M[] = {0,1,0,1};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glLightfv(GL_LIGHT0,GL_POSITION,Pos);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,Col);


    gluLookAt(Cx,Cy,Cz,0,0,0,0,1,0); //////////


    

///////////////////////////////////////////////////////////////////
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, violet );
        glPushMatrix();
            glTranslatef(-0.5,-1.5,-0.5);
            glScalef(2,0.05,1);
            //glRotatef(T,0,1,0);
            glutSolidCube(1);
        glPopMatrix();
    glPopAttrib();

/////////////////////////////////////////////////////////////////////////
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, violet );
        glPushMatrix();
            glTranslatef(-0.5,0.5,-0.5);
            
            glScalef(2,0.05,1);
            glutSolidCube(1);
        glPopMatrix();
    glPopAttrib();
////////////////////////////////////////////////////////////////////////////////


    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, violet );
        glPushMatrix();
            glTranslatef(-1.5,-0.5,-0.5);
            
            glScalef(0.05,2,1);
            glutSolidCube(1);
        glPopMatrix();
    glPopAttrib();
///////////////////////////////////////////////////////////////////////////////////


    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, violet );
        glPushMatrix();
            glTranslatef(0.5,-0.5,-0.5);
            glScalef(0.05,2,1);
            glutSolidCube(1);
        glPopMatrix();
    glPopAttrib();


/////////////////////////////////////////////////////////////////////////////////////
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, black );
        glPushMatrix();
            glTranslatef(-0.5,-0.5,-1.5);
            
            glScalef(2,2,1);
            glutSolidCube(1);
        glPopMatrix();
    glPopAttrib();

/////////////////////////////////////////////////////////////////////////////////////////




    glPushAttrib(GL_ALL_ATTRIB_BITS);
        //glClear(GL_COLOR_BUFFER_BIT );
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,blue);
        glPushMatrix();
            glTranslatef(-0.50,-0.25,-0.50);
            glRotatef(T,0,1,0);
            glutSolidTeapot(0.15);

        glPopMatrix();
    glPopAttrib();



    glPushAttrib(GL_ALL_ATTRIB_BITS);
        //glClear(GL_COLOR_BUFFER_BIT );
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,blue);
        glPushMatrix();
            glTranslatef(0.30,-0.25,-0.50);
            //glRotatef(T,0,1,0);
            glutSolidTorus(0.05,0.15,10,10);

        glPopMatrix();
    glPopAttrib();

    drawElephant();


    glPushMatrix();
    //glClear(GL_COLOR_BUFFER_BIT);
      glTranslatef(-0.30,-0.25,-0.8);
	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, texture);
	  glBegin(GL_QUADS);
	  glTexCoord2f(0, 0);			glVertex3f(0.2, 0.2, 0);
	  glTexCoord2f(0.5, 0);		glVertex3f(0.5, 0.5, 0);
	  glTexCoord2f(0.5, 0.5);		glVertex3f(0.5, 0.5, 0);
	  glTexCoord2f(0, 0.5);			glVertex3f(0.2, 0.5, 0);
	  glEnd();
	  glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    glPushMatrix();
    //glClear(GL_COLOR_BUFFER_BIT);
      glTranslatef(-0.30,-0.70,-0.8);
	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, texture2);
	  glBegin(GL_QUADS);
	  glTexCoord2f(0, 0);			glVertex3f(0.2, 0.2, 0);
	  glTexCoord2f(0.5, 0);		glVertex3f(0.5, 0.5, 0);
	  glTexCoord2f(0.5, 0.5);		glVertex3f(0.5, 0.5, 0);
	  glTexCoord2f(0, 0.5);			glVertex3f(0.2, 0.5, 0);
	  glEnd();
	  glDisable(GL_TEXTURE_2D);
	glPopMatrix();
    glFlush();
    

/*
/*
    glPushMatrix();
        glTranslatef(-0.5,-0.5,-0.5);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5,-0.5,-0.5);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5,-0.5,0.5);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.5,-0.5,0.5);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);
    glPopMatrix();
*/
//    glPushAttrib(GL_ALL_ATTRIB_BITS);
//        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,M);
//        glPushMatrix();
//            glTranslatef(0,0.25,0);
//            glutSolidTeapot(0.25);
//        glPopMatrix();
//    glPopAttrib();

    glutSwapBuffers();
}

void MyInit()
{
    glEnable(GL_DEPTH_TEST);
    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,2,10);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glEnable(GL_LIGHTING); 

}

int main(int argC,char *argV[])
{
    glutInit(&argC,argV);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Table & TeaPot");
    MyInit();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);
    glutIdleFunc(Spin);
    loadObj("bunny.obj");
    gluOrtho2D(0,1,0,1);
    texture = SOIL_load_OGL_texture("hindu.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB);
    texture2 = SOIL_load_OGL_texture("dog.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB);
    glutMainLoop();
    return 0;
}