//Semestre 2019 - 1
//****************************************************************************//
//****************************************************************************//
//************** Alumno (s): *************************************************//
//*************	Garcia Villavicencio Danahe			Grupo de lab: 06	******//
//*************	Carlos								Grupo de lab:       ******//
//*************	González Gutiérrez Luis Manuel		Grupo de lab: 0     ******//
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

//*Solo para Visual Studio 2015
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5;
float rotY = 0;
float rotX = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;


//animacion brazo
float rotp11 = 0.0;
float rotp12 = 0.0;
float rotp21 = 0.0;
float rotp22 = 0.0;
float rotp3 = 0.0;
float rotp4 = 0.0;
bool brazo = FALSE;
bool brazo1 = FALSE;
bool brazo2 = FALSE;
bool brazo3 = FALSE;
bool brazo4 = FALSE;
bool brazo5 = FALSE;


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
int FrameIndex2 = 10; //introducir datos
int FrameIndex3 = 10;
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

int font = (int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 0.0f, 0.0f, 1.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };


//texturas
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
CTexture puertaEntrada;
CTexture puertaPasillo;
CTexture metal;
CTexture madera1;
CTexture madera2;
CTexture esfera;
CTexture pista;
CTexture pista2;
CTexture reja;
CTexture aplanado;
CTexture pared_auditorio;
CTexture alfombra;
CTexture techo_auditorio;
CTexture duela;
CTexture estrado;
CTexture entrada;
CTexture puerta_auditorio;

//INTERIOR
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
CTexture cubiculo;

CFiguras fig1; // sky
CFiguras casa;
CFiguras fig7;	//Para crear Monito
CFiguras fig2; //auditorio

CModel moto;
CModel coche;
CModel avion;
CModel piratas;
CModel banca;
CModel maceta;
CModel recepcion;
CModel silla;
CModel sofa;
CModel mesa;
CModel reloj;
CModel comedor;
CModel microfono;
CModel bancos;

CMuebles mueble;
float moverAgua = 0;


//Funcion para planos 
void plano(GLuint textura3) {
	glBindTexture(GL_TEXTURE_2D, textura3);
	glBegin(GL_POLYGON);

	glTexCoord2f(1, 0); glVertex2f(-0.5, -0.5);
	glTexCoord2f(1, 1); glVertex2f(-0.5, 0.5);
	glTexCoord2f(0, 1); glVertex2f(0.5, 0.5);
	glTexCoord2f(0, 0); glVertex2f(0.5, -0.5);


	glEnd();

}

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
	text1.LoadBMP("texturas/02.bmp");
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

	agua.LoadTGA("texturas/agua.tga");
	agua.BuildGLTexture();
	agua.ReleaseImage();

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

	/**tree.LoadTGA("texturas/tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();**/

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

	puertaEntrada.LoadTGA("texturas/puertaEntrada.tga");
	puertaEntrada.BuildGLTexture();
	puertaEntrada.ReleaseImage();

	puertaPasillo.LoadTGA("texturas/puertaPasillo.tga");
	puertaPasillo.BuildGLTexture();
	puertaPasillo.ReleaseImage();

	tree.LoadTGA("texturas/tree01.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	barandal.LoadTGA("texturas/barandal.tga");
	barandal.BuildGLTexture();
	barandal.ReleaseImage();

	na.LoadTGA("texturas/nada.tga");
	na.BuildGLTexture();
	na.ReleaseImage();

	tig.LoadTGA("texturas/colcha.tga");
	tig.BuildGLTexture();
	tig.ReleaseImage();

	pista.LoadTGA("texturas/carretera.tga");
	pista.BuildGLTexture();
	pista.ReleaseImage();

	pista2.LoadTGA("texturas/carretera2.tga");
	pista2.BuildGLTexture();
	pista2.ReleaseImage();

	maderac.LoadTGA("texturas/maderac.tga");
	maderac.BuildGLTexture();
	maderac.ReleaseImage();

	reja.LoadTGA("texturas/reja.tga");
	reja.BuildGLTexture();
	reja.ReleaseImage();
	//textura brazo

	esfera.LoadTGA("texturas/esfera.tga");
	esfera.BuildGLTexture();
	esfera.ReleaseImage();

	madera1.LoadTGA("texturas/madera1.tga");
	madera1.BuildGLTexture();
	madera1.ReleaseImage();

	madera2.LoadTGA("texturas/madera2.tga");
	madera2.BuildGLTexture();
	madera2.ReleaseImage();

	metal.LoadTGA("texturas/metal.tga");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	aplanado.LoadTGA("texturas/aplanado.tga");
	aplanado.BuildGLTexture();
	aplanado.ReleaseImage();

	pared_auditorio.LoadTGA("texturas/pared_auditorio.tga");
	pared_auditorio.BuildGLTexture();
	pared_auditorio.ReleaseImage();

	alfombra.LoadTGA("texturas/alfombra.tga");
	alfombra.BuildGLTexture();
	alfombra.ReleaseImage();

	duela.LoadTGA("texturas/duela.tga");
	duela.BuildGLTexture();
	duela.ReleaseImage();

	techo_auditorio.LoadTGA("texturas/techo_teatro.tga");
	techo_auditorio.BuildGLTexture();
	techo_auditorio.ReleaseImage();

	estrado.LoadTGA("texturas/estrado.tga");
	estrado.BuildGLTexture();
	estrado.ReleaseImage();

	entrada.LoadTGA("texturas/entrada.tga");
	entrada.BuildGLTexture();
	entrada.ReleaseImage();

	puerta_auditorio.LoadTGA("texturas/puerta_auditorio.tga");
	puerta_auditorio.BuildGLTexture();
	puerta_auditorio.ReleaseImage();

	cubiculo.LoadTGA("texturas/cubiculo.tga");
	cubiculo.BuildGLTexture();
	cubiculo.ReleaseImage();

	//modelos 3d

	moto._3dsLoad("models/moto.3ds");
	coche._3dsLoad("models/coche.3ds");
	avion._3dsLoad("models/avion.3ds");
	piratas._3dsLoad("models/piratas.3ds");
	banca._3dsLoad("models/banca.3ds");
	maceta._3dsLoad("models/maceta.3ds");
	recepcion._3dsLoad("models/recepcion.3ds");
	silla._3dsLoad("models/silla.3ds");
	sofa._3dsLoad("models/sofa.3ds");
	mesa._3dsLoad("models/mesa.3ds");
	reloj._3dsLoad("models/reloj.3ds");
	comedor._3dsLoad("models/comedor.3ds");
	microfono._3dsLoad("models/microfono.3ds");
	bancos._3dsLoad("models/bancos.3ds");

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

void monito(void)
{
	glPushMatrix();
	glPushMatrix();//Pecho
	glTranslatef(0.0, -1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	fig1.prisma(6.0, 0.9, 1, text2.GLindex, 0);
	glPushMatrix();
	glTranslatef(0.0, 2.0, 0.0);
	fig1.prisma(1.0, 3.0, 1, text2.GLindex, 0);
	glPopMatrix();

	glPushMatrix();//Cuello
	glTranslatef(0, 3.0, 0.0);
	fig1.cilindro(0.25, 0.5, 15, 0);
	glPushMatrix();//Cabeza
	glTranslatef(0, 0.5, 0);
	fig1.prisma(0.5, 2, 1, text2.GLindex, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho-->
	glTranslatef(1.25, 1.65, 0);
	fig1.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(0, 1.0, 0.0, 0.0);
	//glRotatef(-90, 0, 1, 0);
	glTranslatef(0.75, 0, 0);
	fig1.prisma(0.7, 1.5, 0.7, 0, 0);
	glPushMatrix();
	glTranslatef(1.0, 0, 0);
	fig1.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	fig1.prisma(0.7, 1.5, 0.7, 0, 0);
	glPushMatrix();
	glTranslatef(1.0, 0, 0);
	fig1.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	fig1.prisma(0.7, 1.5, 0.7, 0, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo <--
	glRotatef(180, 0, 1, 0);
	glTranslatef(1.25, 0.65, 0);
	fig1.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(0, 1.0, 0.0, 0.0);
	//glRotatef(-90, 0, 1, 0);
	glTranslatef(0.75, 0, 0);
	fig1.prisma(0.7, 1.5, 0.7, 0, 0);
	glPushMatrix();
	glTranslatef(1.0, 0, 0);
	fig1.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	fig1.prisma(0.7, 1.5, 0.7, 0, 0);
	glPushMatrix();
	glTranslatef(1.0, 0, 0);
	fig1.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	fig1.prisma(0.7, 1.5, 0.7, 0, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glColor3f(0, 0, 1);
	glTranslatef(-.9, -4, 0);
	fig1.prisma(2, 3, 1, 0, 0);
	glPopMatrix();
	glPopMatrix();
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPopMatrix();
	//glEndList();
	glPopMatrix();
	return;
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

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera_ptr->mPos.x, objCamera_ptr->mPos.y, objCamera_ptr->mPos.z,
		objCamera_ptr->mView.x, objCamera_ptr->mView.y, objCamera_ptr->mView.z,
		objCamera_ptr->mUp.x, objCamera_ptr->mUp.y, objCamera_ptr->mUp.z);

	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(250.0, 130.3, 250.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//___________________________OTRAS COSAS_________________________________-

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
	glTranslatef(105, -4.7, 95);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, posY, posX);
	glRotatef(rotY, 1, 0, 0);
	glRotatef(rotX, 0, 1, 0);
	glScalef(.002, .002, .002);
	glDisable(GL_COLOR_MATERIAL);
	moto.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//sofa
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(60, -3.5, 35);
	glRotatef(180, 0, 1, 0);
	glScalef(.05, .05, .05);
	sofa.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//sofa
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(65, -3.5, 25);
	glRotatef(-90, 0, 1, 0);
	glScalef(.05, .05, .05);
	sofa.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//reloj
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(10.2, 10, 20);
	glRotatef(90, 0, 1, 0);
	glScalef(.2, .2, .2);
	reloj.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//mesa
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(55, -3.5, 25);
	glScalef(.1, .1, .1);
	mesa.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//maceta
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(52, -3.3, 16.5);
	glRotatef(180, 0, 1, 0);
	glScalef(.2, .2, .2);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//maceta
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-66, -3.3, 33);
	glRotatef(180, 0, 1, 0);
	glScalef(.2, .2, .2);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//maceta
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-66, -3.3, 47);
	glRotatef(180, 0, 1, 0);
	glScalef(.2, .2, .2);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//maceta
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(63, -3.5, 44);
	glRotatef(180, 0, 1, 0);
	glScalef(.2, .2, .2);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//recepción
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(20, -3.2, 20);
	glRotatef(270, 0, 1, 0);
	glScalef(.005, .005, .005);
	recepcion.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//silla
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(30, -3.2, 20);
	glRotatef(90, 0, 1, 0);
	glScalef(.16, .16, .16);
	silla.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//comedor
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-60, -3.5, 40);
	glScalef(.1, .1, .1);
	comedor.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//auditorio
	glPushMatrix();
	glTranslatef(20, 18, -80);
	glRotatef(90, -90, 0, 0);
	//glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	fig2.prisma5(50, 1, 50, aplanado.GLindex, pared_auditorio.GLindex, aplanado.GLindex, aplanado.GLindex, aplanado.GLindex, aplanado.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//auditorio
	glPushMatrix();
	glTranslatef(70, 18, -80);
	glRotatef(90, -90, 0, 0);
	glRotatef(180, 0, 1, 0);
	//glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	fig2.prisma5(50, 1, 50, aplanado.GLindex, pared_auditorio.GLindex, aplanado.GLindex, aplanado.GLindex, aplanado.GLindex, aplanado.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//auditorio
	glPushMatrix();
	glTranslatef(45, 18, -105);
	glRotatef(90, -90, 0, 0);
	glRotatef(-90, 0, 0, 1);
	//glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	fig2.prisma5(50, 1, 50, aplanado.GLindex, pared_auditorio.GLindex, aplanado.GLindex, aplanado.GLindex, aplanado.GLindex, aplanado.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//auditorio
	glPushMatrix();
	glTranslatef(45, 20, -55);
	//glRotatef(90, -90, 0, 0);
	//glRotatef(-90, 0, 0, 1);
	glScalef(50, 50, 1);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(entrada.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//alfombra
	glPushMatrix();
	glTranslatef(45, -3.2, -80);
	glRotatef(90, -90, 0, 0);
	glScalef(51, 50, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(alfombra.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//escalon
	glPushMatrix();
	glTranslatef(45, 6, -100);
	glRotatef(90, -90, 0, 0);
	glRotatef(-90, 0, 0, 1);
	//glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	fig2.prisma12(50, 5, 5, duela.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//escalon
	glPushMatrix();
	glTranslatef(45, 4, -95);
	glRotatef(90, -90, 0, 0);
	glRotatef(-90, 0, 0, 1);
	//glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	fig2.prisma12(50, 5, 5, duela.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//escalon
	glPushMatrix();
	glTranslatef(45, 2, -90);
	glRotatef(90, -90, 0, 0);
	glRotatef(-90, 0, 0, 1);
	//glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	fig2.prisma12(50, 5, 5, duela.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//escalon
	glPushMatrix();
	glTranslatef(45, 0, -85);
	glRotatef(90, -90, 0, 0);
	glRotatef(-90, 0, 0, 1);
	//glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	fig2.prisma12(50, 5, 5, duela.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//estrado
	glPushMatrix();
	glTranslatef(45, 0, -60);
	glRotatef(90, -90, 0, 0);
	glRotatef(-90, 0, 0, 1);
	//glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	fig2.prisma12(25, 8, 3, estrado.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	/*bancos
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(35, 6, -100);
	glScalef(.01, .01, .01); glRotatef(180, 0, 1, 0);
	bancos.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//bancos
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(55, 6, -100);
	glScalef(.01, .01, .01); glRotatef(180, 0, 1, 0);
	bancos.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//bancos
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(35, 4, -95);
	glScalef(.01, .01, .01); glRotatef(180, 0, 1, 0);
	bancos.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//bancos
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(55, 4, -95);
	glScalef(.01, .01, .01); glRotatef(180, 0, 1, 0);
	bancos.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//bancos
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(35, 2, -90);
	glScalef(.01, .01, .01); glRotatef(180, 0, 1, 0);
	bancos.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//bancos
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(55, 2, -90);
	glScalef(.01, .01, .01); glRotatef(180, 0, 1, 0);
	bancos.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();*/

	//microfono
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(45, 1.5, -60);
	glScalef(.15, .15, .15); glRotatef(180, 0, 1, 0);
	microfono.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//techo_auditorio
	glPushMatrix();
	glTranslatef(45, 42.0, -80);
	glRotatef(90, -90, 0, 0);
	glScalef(51, 50, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(techo_auditorio.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//puerta auditorio
	glPushMatrix();
	glTranslatef(55, 4.6, -52);
	//glRotatef(90, 0, 0, 1);
	glRotatef(45, 0, 1, 0);
	glScalef(8, 25, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(puerta_auditorio.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//AUTOMOVIL
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(60, -3.5, 90);
	glRotatef(180, 0, 1, 0);
	//glTranslatef(0, posY, posX);
	//glRotatef(rotY, 1, 0, 0);
	//glRotatef(rotX, 0, 1, 0);
	glScalef(6, 6, 6);
	glDisable(GL_COLOR_MATERIAL);
	coche.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//AUTOMOVIL
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(95, -4.5, -90);
	glRotatef(0, 0, 1, 0);
	glTranslatef(0, posY, posX);
	glRotatef(rotY, 1, 0, 0);
	glRotatef(rotX, 0, 1, 0);
	glScalef(3, 4, 3);
	glDisable(GL_COLOR_MATERIAL);
	coche.GLrender(NULL, _SHADED, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();


	//PASTO
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0, -5.01, 0);
	casa.prisma(.1, 250, 250, pasto.GLindex, pasto.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//cubiculos
	glPushMatrix();
	glTranslatef(-61, 8, 20);
	glRotatef(-90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(cubiculo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//cubiculos
	glPushMatrix();
	glTranslatef(-61, 8, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(cubiculo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	//cubiculos
	glPushMatrix();
	glTranslatef(-61, 8, -20);
	glRotatef(-90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(cubiculo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//cubiculos
	glPushMatrix();
	glTranslatef(-61, 8, -40);
	glRotatef(-90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(cubiculo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//cubiculos
	glPushMatrix();
	glTranslatef(-39, 8, 20);
	glRotatef(-90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(cubiculo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//cubiculos
	glPushMatrix();
	glTranslatef(-39, 8, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(cubiculo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	//cubiculos
	glPushMatrix();
	glTranslatef(-39, 8, -20);
	glRotatef(-90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(cubiculo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//cubiculos
	glPushMatrix();
	glTranslatef(-39, 8, -40);
	glRotatef(-90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(cubiculo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//pared_cubiculos
	glPushMatrix();
	glTranslatef(-34, 8, 30);
	glRotatef(-180, 0, 1, 0);
	glScalef(10, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//pared_cubiculos
	glPushMatrix();
	glTranslatef(-66, 8, 30);
	glRotatef(-180, 0, 1, 0);
	glScalef(10, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	// PISO DEL EDIFICIO 
		//INICIA PISO RECEPCION

	glPushMatrix();
	glTranslatef(60, -3.5, 40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60, -3.5, 20);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -3.5, 40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -3.5, 20);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, -3.5, 40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, -3.5, 20);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	// TERMINA PISO RECEPCION
	// INICIA PISO PASILLO
	glPushMatrix();
	glTranslatef(0, -3.5, 40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, -3.5, 40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	// TERMINA PISO PASILLO

	//INICIA PISO CUBICULOS A AUDITORIO
	glPushMatrix();
	glTranslatef(-40, -3.5, 40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, -3.5, 20);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, -3.5, 40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, -3.5, 20);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, -3.5, 0);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, -3.5, 0);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, -3.5, -20);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, -3.5, -20);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, -3.5, -40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, -3.5, -40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	// TERMINA PASILLO AUDITORIO

	glPushMatrix();
	glTranslatef(30, 25, 50);
	glScalef(80, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, 25, 50);
	glScalef(60, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 25, 30);
	glScalef(40, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	// PAREDES CON SALIDAS
	glPushMatrix();
	glTranslatef(-35, 25, -50);
	glScalef(10, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65, 25, -50);
	glScalef(10, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 14, -50);
	glScalef(20, 5, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 35, -50);
	glScalef(20, 40, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60, 25, 10);
	glScalef(20, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 25, 10);
	glScalef(20, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 14, 10);
	glScalef(20, 5, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 35, 10);
	glScalef(20, 40, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//puerta recepcion
	glPushMatrix();
	glTranslatef(40, 3.9, 10);
	glRotatef(90, 0, 0, 1);
	glScalef(15, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(puertaEntrada.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//puerta tracera
	glPushMatrix();
	glTranslatef(-50, 3.9, -50);
	glRotatef(90, 0, 0, 1);
	glScalef(15, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(puertaEntrada.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	// PAREDES SOBRE EJE Z
	glPushMatrix();
	glTranslatef(70, 25, 30);
	glRotatef(90, 0, 10, 0);
	glScalef(40, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 25, 20);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70, 25, 0);
	glRotatef(90, 0, 10, 0);
	glScalef(100, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30, 25, -10);
	glRotatef(90, 0, 10, 0);
	glScalef(80, 60, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(gris.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	// FIN PAREDES SOBRE EJE Z

	//Techos
	glPushMatrix();
	glTranslatef(40, 16.5, 30);
	glRotatef(90, -90, 0, 0);
	glScalef(60, 40, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 16.5, 40);
	glRotatef(90, -90, 0, 0);
	glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 16.5, 30);
	glRotatef(90, -90, 0, 0);
	glScalef(40, 40, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 16.5, -10);
	glRotatef(90, -90, 0, 0);
	glScalef(40, 40, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 16.5, -40);
	glRotatef(90, -90, 0, 0);
	glScalef(40, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(piso2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//PUERTA PASILLO
	glPushMatrix();
	glTranslatef(-5, 6, 40);
	glRotatef(90, 0, 1, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(puertaPasillo.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//DECORACION DE LA ALBERCA
//ESCALERA
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, -5, -80);
	casa.cilindro(.5, 30, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, -5, -85);
	casa.cilindro(.5, 30, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, -4, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, -2, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 0, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 2, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 4, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 6, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 8, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 10, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 12, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 14, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 16, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 18, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 20, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 22, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-65, 24, -84.5);
	glRotatef(90, 1, 0, 0);
	casa.cilindro(.2, 4.2, 30, tubo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//TRAMPOLIN
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-57.9, 26, -82.5);
	casa.prisma2(2, 15, 6, blanco.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//LOSETA DE ALREDEDOR
	//derecha
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-63, -3.9, -80);
	casa.prisma2(2, 4, 40, marmol.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//arriba
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-40, -3.9, -100);
	glRotatef(90, 0, 1, 0);
	casa.prisma2(2, 4, 50, marmol.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//izquierda
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-17, -3.9, -80);
	casa.prisma2(2, 4, 42.5, marmol.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//abajo
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-40, -3.9, -60);
	glRotatef(90, 0, 1, 0);
	casa.prisma2(2, 4, 50, marmol.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//ALBERCA
	glPushMatrix();
	glTranslatef(-40, -4.2, -80);
	glScalef(2.2, 1, 1.2);
	glDisable(GL_LIGHTING);
	casa.prisma2(1, 20, 30, piso3.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//ANIMACION DEL AGUA
	glPushMatrix();
	glTranslatef(-62, -3.1, -62);
	glRotatef(-90, 1, 0, 0);
	glScalef(4.7, 1.5, 6);
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

	// Camino de salidas
	glPushMatrix();
	glTranslatef(40, -3.5, 0);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -3.5, -20);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -3.5, -40);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -3.5, -60);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -3.5, -80);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60, -3.5, -80);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, -3.5, -80);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, -3.5, -80);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -3.5, -80);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, -3.5, -80);
	glRotatef(90, -90, 0, 0);
	glScalef(10, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, -3.5, -55);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 10, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(camino.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//Carretera de fuera
	glPushMatrix();
	glTranslatef(100, -3.5, 0);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 245, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(pista.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//reja
	glPushMatrix();
	glTranslatef(80, 6.5, -100);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, -60);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, -40);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, -20);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, 0);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, 20);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, 40);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, 50);
	glRotatef(90, 0, 10, 0);
	glScalef(10, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, 85);
	glRotatef(90, 0, 10, 0);
	glScalef(10, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 6.5, 100);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(50, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-90, 6.5, 110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, 100);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, 80);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, 60);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, 40);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, 20);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, 0);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, -20);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, -40);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, -60);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, -80);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 6.5, -100);
	glRotatef(90, 0, 10, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-90, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-10, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(50, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 6.5, -110);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(reja.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//ESTACIONAMIENTO Y ACCESO A CARROS PARA ALBERCA
	glPushMatrix();
	glTranslatef(80, -3.5, 65);
	glRotatef(90, -90, 0, 0);
	glScalef(20, 20, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(pista2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -3.5, 75);
	glRotatef(90, -90, 0, 0);
	glScalef(60, 40, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(pista2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, -3.5, 75);
	glRotatef(90, -90, 0, 0);
	glScalef(60, 40, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(pista2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70, -3.5, 75);
	glRotatef(90, -90, 0, 0);
	glScalef(40, 40, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(pista2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-82.5, -3.5, 35);
	glRotatef(90, -90, 0, 0);
	glScalef(15, 80, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(pista2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-82.5, -3.5, -50);
	glRotatef(90, -90, 0, 0);
	glScalef(15, 90, 0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);//LUZ
	plano(pista2.GLindex);
	glEnable(GL_LIGHTING);//LUZ
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//______________________________________DETALLES______________________-

	//justina
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 0, 1);
	glTranslatef(30, 0, 30);
	glTranslatef(0, posY, posX);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotX, 1, 0, 0);
	glScalef(2, 2, 2);
	monito();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();


	//brazo
	glPushMatrix();
	glTranslatef(20, 0.7, -8.0);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0, -0.5, 0.0f);
	glRotated(rotp12, 0, 1, 0);
	glRotated(rotp11, 0, 0, 1);			//cambiar angulo
									//cambiar angulo
	glPushMatrix(); //parte1
	glTranslatef(0.0f, 0.5f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glRotated(rotp21 + 100, 0, 1, 0);		//cambiar angulo
	glRotated(rotp22 + 100, 1, 0, 0);      //cambiar angulo
	glPushMatrix(); //parte2
	glTranslatef(0.0f, -0.5f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0, -0.5f, 0.0f);
	glRotated(90, 1, 0, 0);
	glRotated(rotp3, 0, 0, 1);				//cambiar angulo
	glPushMatrix();//parte3
	glTranslatef(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0, -0.5f, 0.0f);
	glRotated(90, 1, 0, 0);
	glRotated(-rotp4, 1, 0, 0);		//cambiar angulo
	glPushMatrix();//parte4
	glTranslatef(0.0f, 0.5f, 0.0f);
	fig1.prisma9(1, 0.2, 0.2, metal.GLindex);
	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	fig1.esfera(0.15, 50, 50, esfera.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();//parte4
	glTranslatef(0.0, 0.5f, 0.0f);
	glRotated(90, 1, 0, 0);
	glRotated(rotp4, 1, 0, 0);			//cambiar angulo
	glPushMatrix();//parte5
	glTranslatef(0.0f, 0.5f, 0.0f);
	fig1.prisma9(1, 0.2, 0.2, metal.GLindex);
	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	fig1.esfera(0.15, 50, 50, esfera.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	fig1.esfera(0.2, 50, 50, esfera.GLindex);
	fig1.prisma9(1, 0.2, 0.2, metal.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.5, 0);
	fig1.esfera(0.2, 50, 50, esfera.GLindex);
	glPopMatrix();
	fig1.prisma9(1, 0.2, 0.2, metal.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -0.45, 0);
	fig1.esfera(0.15, 50, 50, esfera.GLindex);
	glPopMatrix();
	fig1.prisma9(1, 0.2, 0.2, metal.GLindex);
	glPopMatrix();
	//	glPopMatrix();
	glEnable(GL_LIGHTING);
	//glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0, -0.5, 0.0f);
	glRotated(rotp12 + 45, 0, 1, 0); //cambiar angulo
	fig1.prisma9(0.1, 0.4, 0.4, madera1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0, -0.6, 0.0f);
	fig1.prisma9(0.2, 1, 1, madera2.GLindex);
	glEnable(GL_LIGHTING);
	//		glPopMatrix();
	glPopMatrix();  //fin2
	glPopMatrix(); // fin 1




	/////////////////////////////////////////

	glutSwapBuffers();
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

	/*if (brazo)
	{

		//brazo
		if (brazo5 == TRUE) {
			rotp11 = 0.0;
			rotp12 = 0.0;
			rotp21 = 0.0;
			rotp22 = 0.0;
			rotp3 = 0.0;
			rotp4 = 0.0;
			brazo5 = FALSE;
			brazo = TRUE;
		}

		if (brazo == TRUE) {
			if (rotp11 == 10) {
				brazo1 = TRUE;
				brazo = FALSE;
			}
			else {
				rotp11++;
			}
		}

		if (brazo1 == TRUE) {
			if (rotp12 == 10) {
				brazo2 = TRUE;
				brazo1 ^= FALSE;
			}
			else {
				rotp12++;
			}

		}

		if (brazo2 == TRUE) {

			if (rotp21 == 45) {
				brazo3 = TRUE;
				brazo2 = FALSE;
			}
			else {
				rotp21++;
			}
		}

		if (brazo3 == TRUE) {

			if (rotp22 == 45) {
				brazo4 = TRUE;
				brazo3 = FALSE;
			}
			else {
				rotp22++;
			}
		}

		if (brazo4 == TRUE) {

			if (rotp3 == 10) {
				brazo4 = FALSE;
				brazo = TRUE;
			}
			else {
				rotp3++;
				rotp4++;
			}
		}
	}
	*/


	glutPostRedisplay();
}

//mouse
void mouseMove(int x, int y) {

	//printf("x=%d\n",x);
	//printf("y=%d\n", y);
	if (x > 500)
	{
		objCamera.Rotate_View(CAMERASPEED + .01f);
		glutWarpPointer(500, 500);
	}
	if (x < 500)
	{
		objCamera.Rotate_View(-CAMERASPEED - 0.01f);
		glutWarpPointer(500, 500);
	}
	if (y < 500)
	{
		g_lookupdown -= 0.7f;
		glutWarpPointer(500, 500);
	}
	if (y > 500)
	{
		g_lookupdown += 0.7f;
		glutWarpPointer(500, 500);
	}
}


void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 400.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}



void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.8);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.8));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.8));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.8);
		break;

	case 'M': //CANCION DE Mi nana (Piano)
		PlaySound(TEXT("musica8.WAV"), NULL, SND_LOOP | SND_ASYNC);
		break;
	case 'm':
		PlaySound(NULL, NULL, 0);
		break;

	case 'N'://cancion all again
		PlaySound(TEXT("musica1.WAV"), NULL, SND_LOOP | SND_ASYNC);
		break;
	case 'n':
		PlaySound(NULL, NULL, 0);
		break;

		//TECLA DE GUARDADO PARA LOS KEYFRAMES

	case 'l':
		PlaySound(NULL, NULL, 0);
	case 'L':
		if (play == false && (FrameIndex > 1))
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
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
		break;

		//ANIMACION BRAZO
	case 'y':
	case 'Y':
		brazo5 ^= TRUE;
		break;

	case '1':
		posX++;
		posX += 0.5;
		printf("%f \n", posX);
		break;

	case '2':
		posX--;
		posX -= 0.5;
		printf("%f \n", posX);
		break;

		//case ' ':		//Poner algo en movimiento
		//	g_fanimacion^= true; //Activamos/desactivamos la animacíon
		//	break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
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
		objCamera.Rotate_View(CAMERASPEED);
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
	//glutIdleFunc(animacionbrazo);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutPassiveMotionFunc(mouseMove); //Indicamos a GLUT la funcion de manejo de la camara con el mouse
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMainLoop();

	return 0;
}