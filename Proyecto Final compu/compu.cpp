//Semestre 2019 - 1
//****************************************************************************//
//****************************************************************************//
//************** Alumno (s): *************************************************//
//*************	Garcia Villavicencio Danahe			Grupo de lab: 06	******//
//*************	Carlos								Grupo de lab:       ******//
//*************										Grupo de lab: 0     ******//
//************* Vite Camilo Hazael					Grupo de lab : 0	******//
//****************************************************************************//
//****************************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "Mobiliario.h"
#include <stdlib.h>
#include <stdio.h>
#include <MMSystem.h>
#include <Windows.h> //librerias para la musica
#include "cmodel/CModel.h"

//Solo para Visual Studio 2015
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5;
float rotY = 0;
float rotX = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;

#define MAX_FRAMES 9 //cantidad de frames que vamos a guardar

//linea del tiempo
int i_max_steps = 90;
int i_curr_steps = 0;

///////////////////////////////

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para Posicion Z
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para Incremento Z
	float rotY;
	float rotYinc;
	float rotX;
	float rotXinc;
	float rotZ;
	float rotZinc;
}FRAME;




FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 10;			//introducir datos
int FrameIndex2 = 10;			//introducir datos
bool play = false;
int playIndex = 0;

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

//CAMARAS PARA EL CAMBIO
CCamera objCamera;
CCamera objCamera2;
CCamera objCamera3;
CCamera objCamera4;
CCamera objCamera5;
CCamera objCamera6;
CCamera objCamera7;
CCamera objCamera8;
CCamera * objCamera_ptr;
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 0.0f, 0.0f, 1.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

CTexture text1;
CTexture piso;
CTexture piso2;
CTexture arbusto;
CTexture camino;
CTexture gris;
CTexture pasto;
CTexture piso3;
CTexture ventana2;
CTexture tree;
CTexture marmol;
CTexture blanco;
CTexture tubo;
CTexture text2; //monito
CTexture pavimento;
CTexture pared;
CTexture agua;

//INTERIOR DE LA CASA
CTexture maderac;
CTexture mesac;
CTexture paredes;
CTexture barandal;
CTexture pisor;
CTexture alacenacapa;
CTexture alacenac;
CTexture cena;
CTexture ammumu;
CTexture esdla;
CTexture paredesint; 
CTexture tig;
CTexture ventana;
CTexture lib;
CTexture lib2;
CTexture lib3;
CTexture na;


CFiguras fig1;
CFiguras casa;
CFiguras fig7;	//Para crear Monito


CModel moto;
CModel coche;
CModel avion;
CModel piratas;

CMuebles mueble;
float moverAgua = 0;


//se salvan o guardan los frames
void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].rotY = rotY;
	KeyFrame[FrameIndex].rotX = rotX;

	FrameIndex++;
}

//se resetean los frames ya que no los podemos mantener guardados
void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	rotY = KeyFrame[0].rotY;
	rotX = KeyFrame[0].rotX;
}

//calculos de la escala inicial a la escala final
//se define el incremento, se checa el final - el inicial y se divide entre el numero de cuadros...... eso nos da la interpolacion
void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].rotYinc = (KeyFrame[playIndex + 1].rotY - KeyFrame[playIndex].rotY) / i_max_steps;
	KeyFrame[playIndex].rotXinc = (KeyFrame[playIndex + 1].rotX - KeyFrame[playIndex].rotX) / i_max_steps;

}



//ANIMACION PARA QUE AVION VUELE
bool avionvuela = false;
float vuelax = 0;
float vuelay = 0;
float vuelaz = 0;

float posZ;		//Variable para Posicion Z
float rotZ;
float incZ;
bool suma2 = true;

//se salvan o guardan los frames
void saveFrame2(void)
{

	printf("frameindex %d\n", FrameIndex2);

	KeyFrame[FrameIndex2].posX = posX;
	KeyFrame[FrameIndex2].posZ = posZ;
	KeyFrame[FrameIndex2].rotZ = rotZ;
	KeyFrame[FrameIndex2].rotX = rotX;

	FrameIndex++;
}

//se resetean los frames ya que no los podemos mantener guardados
void resetElements2(void)
{
	posX = KeyFrame[0].posX;
	posZ = KeyFrame[0].posZ;
	rotZ = KeyFrame[0].rotZ;
	rotX = KeyFrame[0].rotX;

}



void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On

	//AQUI SE COLOCAN LAS TEXTURAS//
	text1.LoadBMP("texturas/01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	piso.LoadTGA("texturas/piso.tga");
	piso.BuildGLTexture();
	piso.ReleaseImage();

	piso2.LoadTGA("texturas/piso2.tga");
	piso2.BuildGLTexture();
	piso2.ReleaseImage();

	piso3.LoadTGA("texturas/piso3.tga");
	piso3.BuildGLTexture();
	piso3.ReleaseImage();

	pared.LoadTGA("texturas/pared.tga");
	pared.BuildGLTexture();
	pared.ReleaseImage();

	arbusto.LoadTGA("texturas/arbusto.tga");
	arbusto.BuildGLTexture();
	arbusto.ReleaseImage();

	camino.LoadTGA("texturas/camino.tga");
	camino.BuildGLTexture();
	camino.ReleaseImage();

	ventana.LoadTGA("texturas/ventana.tga");
	ventana.BuildGLTexture();
	ventana.ReleaseImage();

	gris.LoadTGA("texturas/gris.tga");
	gris.BuildGLTexture();
	gris.ReleaseImage();

	pasto.LoadTGA("texturas/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	tree.LoadTGA("texturas/tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	marmol.LoadTGA("texturas/marmol.tga");
	marmol.BuildGLTexture();
	marmol.ReleaseImage();

	blanco.LoadTGA("texturas/blanco.tga");
	blanco.BuildGLTexture();
	blanco.ReleaseImage();

	pavimento.LoadTGA("texturas/pavimento.tga");
	pavimento.BuildGLTexture();
	pavimento.ReleaseImage();

	pisor.LoadTGA("texturas/pisor.tga");
	pisor.BuildGLTexture();
	pisor.ReleaseImage();

	tree.LoadTGA("texturas/tree01.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	barandal.LoadTGA("texturas/barandal.tga");
	barandal.BuildGLTexture();
	barandal.ReleaseImage();

	cena.LoadTGA("texturas/cena.tga");
	cena.BuildGLTexture();
	cena.ReleaseImage();

	ammumu.LoadTGA("texturas/ammumu.tga");
	ammumu.BuildGLTexture();
	ammumu.ReleaseImage();

	esdla.LoadTGA("texturas/esdla.tga");
	esdla.BuildGLTexture();
	esdla.ReleaseImage();

	na.LoadTGA("texturas/nada.tga");
	na.BuildGLTexture();
	na.ReleaseImage();

	tig.LoadTGA("texturas/colcha.tga");
	tig.BuildGLTexture();
	tig.ReleaseImage();


	moto._3dsLoad("models/moto.3ds");
	coche._3dsLoad("models/coche.3ds");
	avion._3dsLoad("models/avion.3ds");
	piratas._3dsLoad("models/piratas.3ds");

	objCamera.Position_Camera(10, 2.5f, 13, 10, 2.5f, 10, 0, 1, 0);
	objCamera2.Position_Camera(-35, 50, 100, 0, 25, -1, 0, 1, 0);
	objCamera3.Position_Camera(-75, 50, -120, -20, -50, 30, 0, 1, 0);
	objCamera4.Position_Camera(50, 20, 55, 80, -15, -50, 0, 1, 0);
	objCamera5.Position_Camera(-40, 10, 15, -80, -30, 80, 0, 1, 0);
	objCamera6.Position_Camera(93, 30, -85, 50, -25, -50, 0, 1, 0);
	objCamera7.Position_Camera(-100, 20, 120, 0, 25, -1, 0, 1, 0);
	objCamera8.Position_Camera(95, 20, 75, 80, -35, -50, 0, 1, 0);;
	objCamera_ptr = &objCamera;


	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 0;
	KeyFrame[0].rotX = 0;
	KeyFrame[0].rotY = 0;

	KeyFrame[1].posX = 0;
	KeyFrame[1].posY = 4;
	KeyFrame[1].rotX = 0;
	KeyFrame[1].rotY = 0;

	KeyFrame[2].posX = 0;
	KeyFrame[2].posY = 5.5;
	KeyFrame[2].rotX = 0;
	KeyFrame[2].rotY = 0;

	KeyFrame[3].posX = 0;
	KeyFrame[3].posY = 7;
	KeyFrame[3].rotX = 0;
	KeyFrame[3].rotY = 0;

	KeyFrame[4].posX = 0;
	KeyFrame[4].posY = 8.5;
	KeyFrame[4].rotX = 0;
	KeyFrame[4].rotY = 0;

	KeyFrame[5].posX = 1.5;
	KeyFrame[5].posY = 8.5;
	KeyFrame[5].rotX = 0;
	KeyFrame[5].rotY = 0;

	KeyFrame[6].posX = 3;
	KeyFrame[6].posY = 8.5;
	KeyFrame[6].rotX = 0;
	KeyFrame[6].rotY = 0;

	KeyFrame[7].posX = 3.8;
	KeyFrame[7].posY = 8.5;
	KeyFrame[7].rotX = 0;
	KeyFrame[7].rotY = -90;

	KeyFrame[8].posX = 3.8;
	KeyFrame[8].posY = 10;
	KeyFrame[8].rotX = 0;
	KeyFrame[8].rotY = -90;

	KeyFrame[9].posX = 3.8;
	KeyFrame[9].posY = 11.5;
	KeyFrame[9].rotX = 0;
	KeyFrame[9].rotY = -90;

}


void arbol()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glBindTexture(GL_TEXTURE_2D, tree.GLindex);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	
	glPushMatrix();

		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(objCamera_ptr->mPos.x, objCamera_ptr->mPos.y, objCamera_ptr->mPos.z,
			objCamera_ptr->mView.x, objCamera_ptr->mView.y, objCamera_ptr->mView.z,
			objCamera_ptr->mUp.x, objCamera_ptr->mUp.y, objCamera_ptr->mUp.z);

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(250.0, 130.3, 250.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

//___________________________OTRAS COSAS_________________________________-


			//ARBOLES
			glPushMatrix();
				glTranslatef(-5, -5, 90);
				glScalef(2, 2, 2);
				arbol();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-35, -5, 90);
				glScalef(2, 2, 2);
				arbol();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(100, -5, 90);
				glScalef(2, 2, 2);
				arbol();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20, -5, 90);
				glScalef(2, 2, 2);
				arbol();
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-35, -5, 90);
				glScalef(2, 2, 2);
				arbol();
			glPopMatrix();

			//AVION
			glPushMatrix();
				glTranslatef(-60 + vuelax, 80, -30 + vuelaz);
				glRotatef(45, 0, 1, 0);
				glScalef(.05, .05, .05);
				glDisable(GL_COLOR_MATERIAL);
				avion.GLrender(NULL, _SHADED, 1.0);
				glEnable(GL_COLOR_MATERIAL);
			glPopMatrix();

			//MOTO
			glPushMatrix();
				glDisable(GL_COLOR_MATERIAL);
				glTranslatef(50, -3.5, 90);
				glRotatef(180,0,1,0);
				glScalef(.002, .002, .002);
				moto.GLrender(NULL, _SHADED, 1.0);
				glEnable(GL_COLOR_MATERIAL);
			glPopMatrix();

			//AUTOMOVIL
			glPushMatrix();
				glDisable(GL_COLOR_MATERIAL);
				glTranslatef(60, -3.5, 90);
				glRotatef(180,0,1,0);
				glScalef(6, 6, 6);
				coche.GLrender(NULL, _SHADED, 1.0);
				glEnable(GL_COLOR_MATERIAL);
			glPopMatrix();


			//PASTO
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0, -5.01, 0);
				casa.prisma(.1, 250, 250, pasto.GLindex,pasto.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//DECORACION DE LA ALBERCA
	//ESCALERA
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(-95, -5, -80);
			casa.cilindro(.5, 30, 30, tubo.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(-95, -5, -85);
			casa.cilindro(.5, 30, 30, tubo.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(-95, -4, -84.5);
			glRotatef(90, 1, 0, 0);
			casa.cilindro(.2, 4.2, 30, tubo.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(-95, -2, -84.5);
			glRotatef(90, 1, 0, 0);
			casa.cilindro(.2, 4.2, 30, tubo.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(-95, 0, -84.5);
			glRotatef(90, 1, 0, 0);
			casa.cilindro(.2, 4.2, 30, tubo.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 2, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 4, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 6, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 8, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 10, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 12, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 14, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 16, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 18, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 20, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 22, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-95, 24, -84.5);
				glRotatef(90, 1, 0, 0);
				casa.cilindro(.2, 4.2, 30, tubo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//TRAMPOLIN
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-87.9, 26, -82.5);
				casa.prisma2(2, 15, 6, blanco.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//LOSETA DE ALREDEDOR
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-92.01, -3.9, -82.5);
				casa.prisma2(2, 4, 60, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-30, -3.9, -114.51);
				glRotatef(90, 0, 1, 0);
				casa.prisma2(2, 4, 128, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(32.01, -3.9, -82.5);
				casa.prisma2(2, 4, 60, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-30, -3.9, -50.49);
				glRotatef(90, 0, 1, 0);
				casa.prisma2(2, 4, 128, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//PILARES DE DECORACION
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-92, -2.3, -50.5);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0, 20, 0);
						casa.prisma2(1, 4, 4, marmol.GLindex);
					glPopMatrix();
					casa.cilindro(1, 20, 30, marmol.GLindex);
				glPopMatrix();
				casa.prisma2(1, 4, 4, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();


			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-92, -2.3, -114.51);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0, 20, 0);
						casa.prisma2(1, 4, 4, marmol.GLindex);
					glPopMatrix();
					casa.cilindro(1, 20, 30, marmol.GLindex);
				glPopMatrix();
				casa.prisma2(1, 4, 4, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-14, -2.3, -50.51);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0, 20, 0);
						casa.prisma2(1, 4, 4, marmol.GLindex);
					glPopMatrix();
					casa.cilindro(1, 20, 30, marmol.GLindex);
				glPopMatrix();
				casa.prisma2(1, 4, 4, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-14, -2.3, -114.51);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0, 20, 0);
						casa.prisma2(1, 4, 4, marmol.GLindex);
					glPopMatrix();
					casa.cilindro(1, 20, 30, marmol.GLindex);
				glPopMatrix();
				casa.prisma2(1, 4, 4, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(2, -2.3, -50.51);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0, 20, 0);
						casa.prisma2(1, 4, 4, marmol.GLindex);
					glPopMatrix();
					casa.cilindro(1, 20, 30, marmol.GLindex);
				glPopMatrix();
				casa.prisma2(1, 4, 4, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(2, -2.3, -114.51);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0, 20, 0);
						casa.prisma2(1, 4, 4, marmol.GLindex);
					glPopMatrix();
					casa.cilindro(1, 20, 30, marmol.GLindex);
				glPopMatrix();
				casa.prisma2(1, 4, 4, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(32, -2.3, -50.51);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0, 20, 0);
						casa.prisma2(1, 4, 4, marmol.GLindex);
					glPopMatrix();
					casa.cilindro(1, 20, 30, marmol.GLindex);
				glPopMatrix();
				casa.prisma2(1, 4, 4, marmol.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(32, -2.3, -114.51);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0, 20, 0);
						casa.prisma2(1, 4, 4, marmol.GLindex);
						glPopMatrix();
						casa.cilindro(1, 20, 30, marmol.GLindex);
					glPopMatrix();
					casa.prisma2(1, 4, 4, marmol.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();


			//ALBERCA
			glPushMatrix();
				glScalef(2, 1, 1.5);
				glTranslatef(-5, 0, 25);
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glTranslatef(-20, -4.2, -80);
					casa.prisma2(1., 40, 40, piso3.GLindex);
					glEnable(GL_LIGHTING);
			glPopMatrix();


			//ANIMACION DEL AGUA
			glPushMatrix();
				glTranslatef(-39, -3.1, -61);
				glRotatef(-90, 1, 0, 0);
				glDisable(GL_LIGHTING);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, agua.GLindex);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					glNormal3f(0, 0, 1);
					glTexCoord2f(0 + moverAgua, 0 + moverAgua);	glVertex3f(0, 0, 0);
					glTexCoord2f(1 + moverAgua, 0 + moverAgua);	glVertex3f(38, 0, 0);
					glTexCoord2f(1 + moverAgua, 1 + moverAgua);	glVertex3f(38, 38, 0);
					glTexCoord2f(0 + moverAgua, 1 + moverAgua);	glVertex3f(0, 38, 0);
				glEnd();
				glBindTexture(GL_TEXTURE_2D, agua.GLindex);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					glNormal3f(0, 0, 1);
					glTexCoord2f(0 - moverAgua, 0 - moverAgua);	glVertex3f(0, 0, 0);
					glTexCoord2f(1 - moverAgua, 0 - moverAgua);	glVertex3f(38, 0, 0);
					glTexCoord2f(1 - moverAgua, 1 - moverAgua);	glVertex3f(38, 38, 0);
					glTexCoord2f(0 - moverAgua, 1 - moverAgua);	glVertex3f(0, 38, 0);
				glEnd();
			glPopMatrix();
	
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(10, -4.2, -80);
				casa.prisma2(1., 20, 40, piso3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(5, -3.1, -68);
				glRotatef(-90, 1, 0, 0);
				glDisable(GL_LIGHTING);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, agua.GLindex);
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					glNormal3f(0, 0, 1);
					glTexCoord2f(0 + moverAgua, 0 + moverAgua);	glVertex3f(0, 0, 0);
					glTexCoord2f(1 + moverAgua, 0 + moverAgua);	glVertex3f(10, 0, 0);
					glTexCoord2f(1 + moverAgua, 1 + moverAgua);	glVertex3f(10, 25, 0);
					glTexCoord2f(0 + moverAgua, 1 + moverAgua);	glVertex3f(0, 25, 0);
				glEnd();
				glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					glNormal3f(0, 0, 1);
					glTexCoord2f(0 - moverAgua, 0 - moverAgua);	glVertex3f(0, 0, 0);
					glTexCoord2f(1 - moverAgua, 0 - moverAgua);	glVertex3f(10, 0, 0);
					glTexCoord2f(1 - moverAgua, 1 - moverAgua);	glVertex3f(10, 25, 0);
					glTexCoord2f(0 - moverAgua, 1 - moverAgua);	glVertex3f(0, 25, 0);
				glEnd();
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-20, -3, -80);
				casa.prisma9(1, 38.1, 38.1, piso3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(10, -3, -80);
				casa.prisma9(1, 10.1, 25.1, piso3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(2, -3, -80);
				casa.prisma10(1, 6, 38.1, piso3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(17.1, -3, -80);
				casa.prisma10(1, 4, 25.1, piso3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(12.1, -3, -64.2);
				casa.prisma2(1, 14.3, 6.6, piso3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(12.1, -3, -95.75);
				casa.prisma2(1, 14.3, 6.6, piso3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glDisable(GL_LIGHTING);
			glRotatef(90,0,1,0);
			glTranslatef(10.1, 10.1, -40);
			casa.prisma6(30, 45, 35, gris.GLindex, piso2.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		//PAREDES Edificio
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(89.3, 10, 42.2);
			casa.prisma6(29.99, 6.55, .5, gris.GLindex, piso3.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(89.3, 10, 13);
			glRotatef(90,0,1,0);
			casa.prisma6(29.99, 100.55, .5, gris.GLindex, piso3.GLindex);
		glPopMatrix();

		glPushMatrix(); //tracera
			glTranslatef(27, 10, -32);
			casa.prisma2(29.99, 100.55, .5, gris.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(50.83, 10, 42.2);
			casa.prisma2(29.99, 6.3, .5, gris.GLindex);
		glPopMatrix();

		glPushMatrix();//techo
			glTranslatef(-2, 25, 0);
			glRotatef(90,1,0,0);
			casa.prisma2(100, 184, .2, gris.GLindex);
		glPopMatrix();//fin techo

		glPushMatrix();
			glTranslatef(70, -1, 42.2);
			casa.prisma(8.1, 32, .5, gris.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-19.3, 10, 42.2);
			casa.prisma2(29.99, 85.55, .5, gris.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-30.83, -10, 42.2);
			casa.prisma2(29.99, 60.3, .5, gris.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-23, 10, 32.2);
			glRotatef(90,0,1,0);
			casa.prisma2(29.99, 39.5, .5, gris.GLindex);
		glPopMatrix();

		//ventana
		glPushMatrix();
			glTranslatef(70, 25.25, 41.2);
			glPushMatrix();
			glTranslatef(0, -11, 0);
			casa.prisma2(25, 35, .5, ventana.GLindex);
			glPopMatrix();
		glPopMatrix();

//______________________________________DETALLES______________________-

		//ARBUSTOS ENTRADA

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(-89.9, -2.5, 88);
				glRotatef(90, 0, 1, 0);
				casa.prisma11(5, 4, 28, arbusto.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(110.9, -2.5, 98);
				glRotatef(90, 0, 1, 0);
				casa.prisma11(5, 4, 28, arbusto.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();	
		/////////////////////////////////////////

	glutSwapBuffers ( );
	glPopMatrix();
}


//animacion para que el avion vuele
void animacion()
{
	if (avionvuela)
	{
		if (vuelax > 150)
		{
			suma2 = false;
		}
		if (vuelax < 0)
		{
			suma2 = true;
		}
		if (suma2)
		{
			vuelax += 2;
		}
		else
		{
			vuelax -= 2;
		}
		vuelaz += .5;
		if (vuelaz > 100)
		{
			vuelay = 0;
			vuelaz = 0;
		}

	}

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 400.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.8 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.8));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.8));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.8 );
			break;

		case 'M': //CANCION DE TOKIO    
			PlaySound(TEXT("musica6.WAV"), NULL, SND_LOOP | SND_ASYNC);
			break;
		case 'm':
			PlaySound(NULL, NULL, 0);
			break;

		case 'N':
			PlaySound(TEXT("musica5.WAV"), NULL, SND_LOOP | SND_ASYNC);
			break;
		case 'n':
			PlaySound(NULL, NULL, 0);
			break;
	
			//TECLA DE GUARDADO PARA LOS KEYFRAMES

		case 'l':
			PlaySound(NULL, NULL, 0);
		case 'L':
			if (play == false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
			{
				play = false;
			}
			PlaySound(TEXT("musica3.WAV"), NULL, SND_LOOP | SND_ASYNC);
			break;

		case 'k':		//
		case 'K':
			if (FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		//case ' ':		//Poner algo en movimiento
		//	g_fanimacion^= true; //Activamos/desactivamos la animacíon
		//	break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

	case GLUT_KEY_F1:
		objCamera_ptr = &objCamera;
		break;

	case GLUT_KEY_F2:
		objCamera_ptr = &objCamera2;
		break;

	case GLUT_KEY_F3:
		objCamera_ptr = &objCamera3;
		break;

	case GLUT_KEY_F4:
		objCamera_ptr = &objCamera4;
		break;

	case GLUT_KEY_F5:
		objCamera_ptr = &objCamera5;
		break;

	case GLUT_KEY_F6:
		objCamera_ptr = &objCamera6;
		break;

	case GLUT_KEY_F7:
		objCamera_ptr = &objCamera7;
		break;

	case GLUT_KEY_F8:
		objCamera_ptr = &objCamera8;
		break;


    default:
		break;
  }
  glutPostRedisplay();
}


void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex > 1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
	case 2:	//Save KeyFrame
		if (FrameIndex2 < MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 3:	//Play animation
		if (play == false && FrameIndex2 > 1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}


void menu(int id)
{

}



int main(int argc, char** argv)   // Main Function
{
	int submenu;
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(1200, 680);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto Final Lab."); // Nombre de la Ventana
											 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop(); 

	return 0;
}