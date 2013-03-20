// Murat Demir
// 040080223
// Bilgisayar Proje 2 - hw1
// Güneþ Sistemi

#include <iostream>
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>
#include <math.h>
#include <algorithm>
//#include <SDL\SDL.h>

#define M_PI 3.14

GLfloat targetcameraangleX = 0;
GLfloat targetcameraangleY = 0;
GLdouble angle = 0;
GLboolean isKeyDownZ = false;
GLboolean isKeyDownX = false;
GLfloat material_shininess[] = { 50 };

static void DrawBox(float);
void CameraGunes();
void Camera2();
void Camera3();

void SpecialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            targetcameraangleY+=45;
            break;
        case GLUT_KEY_RIGHT:
            targetcameraangleY-=45;
            break;
        case GLUT_KEY_UP:
            targetcameraangleX+=15;
            break;
        case GLUT_KEY_DOWN:
            targetcameraangleX-=15;
            break;
    }
}

void Key(unsigned char Key, int x, int y)
{
	switch(Key){
		case 'q':
				exit(0);
				break;
		case '1':
				CameraGunes();
				glutPostRedisplay();
				break;
		case '2':
				Camera2();
				break;
		case '3':
				Camera3();
				break;
		case 'z':
            isKeyDownZ = true;
            break;
        case 'x':
            isKeyDownX = true;
            break;
        case 'c':
            material_shininess[0]+=5;
            break;
        case 'v':
            material_shininess[0]-=5;
            break;
	}
}

static void KeyUp( unsigned char key, int x, int y){
    isKeyDownZ = false;
    isKeyDownX = false;
    
}

static void Init(){
	
	// Background Color
	glClearColor(0.2,0.2,0.2,1.0); // 1.0 mat pencere

	// Draw Lines (Wireframe)
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	
	//glOrtho(-1, 1, -1, 1, -1, 1);
	gluPerspective(8, 1, 1, 10000);
	glTranslated(0, 0, -100);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat) w / (GLfloat) h, 1, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0 ,-5);

	return;
}

static void Draw(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glPushMatrix();
	
	glColor3f(1, 1, 0);
	DrawBox(10);
	
	glPopMatrix();
	glutSwapBuffers();
}


static void timerCallback (int value)
{
	// Do timer processing
	angle+=0.4;
	
	// call back again after 10ms have passed
	glutTimerFunc(1, timerCallback, value);
	// Re-draw
	glutPostRedisplay();
}

void setupLight(){
   
	glEnable(GL_LIGHTING);
    
	glEnable(GL_NORMALIZE);

    GLfloat light_position[] = { 0.0, 0.0, 0.0, 0.1 }; // w = 1 YÖNSEL IÞIK KAYNAÐI
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_emission[] = {0.0, 0.0, -3.0, 1.0};
    
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightfv(GL_LIGHT0, GL_EMISSION, light_emission);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	int model_two_side = 1;
	int viewpoint = 0;
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    
    GLfloat global_ambient[] = { 0.2,  0.2, 0.2, 1.0 };
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, material_shininess);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glShadeModel(GL_AMBIENT);
}

int main (int argc, char ** argv)
{
    
    GLenum type;
	
	glutInit(&argc, argv);
	glutInitWindowSize(1000,600);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
	glutInitDisplayMode(type);
	glutCreateWindow("Project-1.....Sun System");
	
	glClearColor(0.0, 0, 1, 1.0);
    glEnable(GL_DEPTH_TEST);
    
    setupLight();
    
    Init();
	
	glShadeModel(GL_SMOOTH);
	timerCallback(0);
	glutDisplayFunc(Draw);
	//glutReshapeFunc(reshape);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutKeyboardUpFunc(KeyUp);
	
	
	glutMainLoop();
	
	
	return 0; 
}

void CameraGunes()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(0, 5, -3, 4, 0, 0, 0, 1, 0);
	DrawBox(10);
	glutSwapBuffers();
}

void Camera2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(-6, 0 , 0, 0, 100, -100, 0, 10, 0);
	DrawBox(10);
	
	
	glutSwapBuffers();
}
void Camera3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(4, 0 , 0, 0, 100, -100, 0, 10, 0);
	DrawBox(10);
	
	
	glutSwapBuffers();
}


static void DrawBox(float i){


	GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
	
	
	glTranslated(0,0,0);
	//gluLookAt(0,10,0, 0,0,0, 0,0,1);

	glPushMatrix(); //günes
	glColor3f(1,1,0);
	glTranslatef(0,0,-3);
	//glRotatef(angle,0,1,0);
	glRotatef(angle,0,1,0);
	gluSphere(quadric, 1.3,20,20);

	glPushMatrix(); // gezegen1
	glColor3f(0,1,0);
	glTranslatef(-6,0,-1);
	glRotatef(angle,0,1,0);
	gluSphere(quadric,0.7,20,20);
	
	glPushMatrix(); // uydu1.1
	glColor3f(1,0,0);
	glTranslatef(1.6+cosf(angle*M_PI/180),0,1+sinf(angle*M_PI/180));
	glRotatef(angle,0,1,0);
	gluSphere(quadric,0.2,20,20);
	glPopMatrix(); // uydu1.1
	
	glPushMatrix(); // uydu1.2
	glColor3f(1,1,1);
	glTranslatef(-0.9+cosf(angle*M_PI/180),0,-2+sinf(angle*M_PI/180));
	glRotatef(angle,0,1,0);
	gluSphere(quadric, 0.4,20,20);
	glPopMatrix(); // uydu1.2
	
	glPopMatrix(); // gezegen1
	 
	
	glPushMatrix(); // gezegen2
	glColor3f(1,0,1);
	glTranslatef(4,0,0);
	glRotatef(angle,0,1,0);
	gluSphere(quadric, 0.6,20,20);

	glPushMatrix(); // uydu2.1
	glColor3f(1,1,0);
	glTranslatef(-1.5+cosf(angle*M_PI/180),0,-1.5+sinf(angle*M_PI/180));
	glRotatef(angle,0,1,0);
	gluSphere(quadric, 0.2,20,20);
	glPopMatrix(); // uydu2.1

	glPushMatrix(); // uydu2.2
	glColor3f(0,0,3);
	glTranslatef(-1.1+cosf((angle)*M_PI/180),0,2+sinf(angle*M_PI/180));
	glRotatef(angle,0,1,0);
	gluSphere(quadric, 0.3,20,20);
	glPopMatrix(); // uydu2.2

	glPopMatrix(); // gezegen2
	
	glPopMatrix(); // günes
	glLoadIdentity();
}