//muebles
#include "Mobiliario.h"
#include "figuras.h"


void CMuebles::cama(GLuint text1, GLuint text2) {
	CFiguras cama;
	glPushMatrix();//Cama
	glPushMatrix();
	glTranslatef(12, -2.5, 5.5);
	cama.prisma5(2, 1, 1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-12, -2.5, -5.5);
	cama.prisma5(2, 1, 1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(12, -2.5, -5.5);
	cama.prisma5(2, 1, 1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-12, -2.5, 5.5);
	cama.prisma5(2, 1, 1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 3, 0);
	cama.prisma5(3, 25, 12, text2, text2, text2, text2, text2, text2);//Colchon
	glPushMatrix();
	glTranslatef(-10, 2, 0);
	cama.prisma5(1, 3, 10, text2, text2, text2, text2, text2, text2);//Almoada
	glPopMatrix();
	glPopMatrix();
	cama.prisma5(3, 25, 12, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//Fincama
}
void CMuebles::sillon(GLuint text1, GLuint text2, GLuint text3) {
	CFiguras sillon;
	glPushMatrix();//Soffa
	glPushMatrix();
	glTranslatef(0, -3, -3.75);
	sillon.prisma5(6, 6, 6, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.5, 3.5, -3.75);
	sillon.prisma5(5, 1, 6, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -7.5);
	sillon.prisma5(12, 6, 1.5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	sillon.prisma5(12, 6, 1.5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//Fin Soffa


}
void CMuebles::sillon2(GLuint text1, GLuint text2) {
	CFiguras sillon2;
	glPushMatrix();//Soffa
				   /////////////////////Patas
	glPushMatrix();
	glTranslatef(4.3, -1.25, 1.3);
	sillon2.prisma5(.5, .3, .3, text2, text2, text2, text2, text2, text2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-4.3, -1.25, 1.3);
	sillon2.prisma5(.5, .3, .3, text2, text2, text2, text2, text2, text2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4.3, -1.25, -1.3);
	sillon2.prisma5(.5, .3, .3, text2, text2, text2, text2, text2, text2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-4.3, -1.25, -1.3);
	sillon2.prisma5(.5, .3, .3, text2, text2, text2, text2, text2, text2);
	glPopMatrix();
	////////////////////Fin patas
	glPushMatrix();//Respaldo
	glTranslatef(0, 1.5, -1.75);
	sillon2.prisma5(5, 9, .5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();//DesBRD
	glTranslatef(-4.75, .5, -.25);
	sillon2.prisma5(3, .5, 3.5, text2, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();//DesBRI
	glTranslatef(4.75, .5, -.25);
	sillon2.prisma5(3, .5, 3.5, text2, text1, text1, text1, text1, text1);
	glPopMatrix();
	sillon2.prisma5(2, 9, 3, text2, text1, text1, text1, text1, text1);
	glPopMatrix();//Fin Soffa


}
void CMuebles::buro(GLuint text1, GLuint text2) {
	CFiguras buro;

	glPushMatrix();	//buro
	glPushMatrix();
	glTranslatef(.5, 5.25, 0);
	buro.prisma5(.5, 5, 5.5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.25, 2.5, 0);
	buro.prisma5(3, 4, 4, text1, text2, text1, text1, text1, text1);
	glPopMatrix();
	buro.prisma5(10, 4, 5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//fin buro
}
void CMuebles::mesa(GLuint text1) {
	CFiguras mesa;
	glPushMatrix();	//Mesa
					/////////////////////////////////////////Patas
	glPushMatrix();
	glTranslatef(4.75, -3, 2.25);
	mesa.prisma5(5, .5, .5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-4.75, -3, 2.25);
	mesa.prisma5(5, .5, .5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4.75, -3, -2.25);
	mesa.prisma5(5, .5, .5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-4.75, -3, -2.25);
	mesa.prisma5(5, .5, .5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	////////////////////////////////////////Fin patas
	mesa.prisma5(1, 10, 5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//fin mesa
}
void CMuebles::mesaS(GLuint text1) {
	CFiguras mesaS;
	glPushMatrix();	//Mesa
					/////////////////////////////////////////Patas
	glPushMatrix();
	glTranslatef(2.4, -2, 2.4);
	mesaS.prisma5(3, .8, .8, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.4, -2, 2.4);
	mesaS.prisma5(3, .8, .8, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.4, -2, -2.4);
	mesaS.prisma5(3, .8, .8, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.4, -2, -2.4);
	mesaS.prisma5(3, .8, .8, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	////////////////////////////////////////Fin patas
	mesaS.prisma5(1, 6, 6, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//fin mesa
}
void CMuebles::repisa(GLuint text1, GLuint text2, GLuint text3) {
	CFiguras repisa;
	glPushMatrix();
			glPushMatrix();
				glTranslatef(0, 1.45, 4);
				repisa.prisma5(3, 4, .1, text1, text1, text1, text1, text1, text1);
			glPopMatrix();
			glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTranslatef(0, 1.5, 0);
			repisa.prisma5(3, 4, 7, text2, text2, text2, text2, text2, text3);
			glDisable(GL_BLEND);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 1.45, -4);
				repisa.prisma5(3, 4, .1, text1, text1, text1, text1, text1, text1);
			glPopMatrix();
		repisa.prisma5(.1, 4, 8, text1, text1, text1, text1, text1, text1);
	glPopMatrix();


}
void CMuebles::estufa(GLuint text1, GLuint text2, GLuint text3) {
	CFiguras estufa;
	glPushMatrix();
	glPushMatrix();
	glTranslatef(2.25, 0, 0);
	estufa.prisma5(3, .5, 3, text1, text3, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.87, 3, 0);
	estufa.prisma5(1, .25, 4, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	estufa.prisma5(5, 4, 4, text1, text1, text1, text1, text1, text2);
	glPopMatrix();


}
void CMuebles::foco(GLuint text1) {
	CFiguras foco;
	glPushMatrix();// Foco
	foco.cono(1, .5, 20, text1);
	glPopMatrix();//Fin Foco

}
void CMuebles::tapete(GLuint text1) {
	CFiguras tapete;
	glPushMatrix();// Foco
	tapete.prisma5(.05, 10, 10, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//Fin Foco

}
void CMuebles::refri(GLuint text1, GLuint text2) {
	CFiguras refri;
	glPushMatrix();// Foco
	glPushMatrix();
	glTranslatef(0, .5, 1.75);
	refri.prisma5(13, 4, .5, text2, text1, text1, text1, text1, text1);
	glPopMatrix();
	refri.prisma5(15, 5, 3, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//Fin Foco

}
void CMuebles::escritorio(GLuint text1) {
	CFiguras escritorio;
	glPushMatrix();//Escritorio
	glPushMatrix();
	glTranslatef(2.45, 4.55, .25);
	escritorio.prisma5(.1, 5, 3.5, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4.9, 0, 0);
	escritorio.prisma5(9, .1, 3, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.45, 2, 0);
	escritorio.prisma5(.1, 5, 3, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	escritorio.prisma5(9, .1, 3, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//Fin del Escritorio
}
void CMuebles::escritorio1(GLuint text1, GLuint text2) {
	CFiguras escritorio1;
	glPushMatrix();//Escritorio2
	glPushMatrix();
	glTranslatef(3, -4.4, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	escritorio1.cilindro(.3, 5, 20, text2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 6);
	glRotatef(20, 0, 0, 1);
	escritorio1.prisma5(9, .5, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -4.4, 6);
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	escritorio1.cilindro(.3, 5, 20, text2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 4.4, 3);
	escritorio1.prisma5(.2, 5, 8, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glRotatef(20, 0, 0, 1);
	escritorio1.prisma5(9, .5, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//Fin Escritorio2

}
void CMuebles::tv(GLuint text1) {
	CFiguras tv;
	glPushMatrix();//Mueble de la tele
	glPushMatrix();
	glTranslatef(0, 0, 6);
	tv.prisma5(11, 4, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 5.6, 3);
	tv.prisma5(.2, 4, 6.2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 2, 3);
	tv.prisma5(.2, 4, 6.2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -2, 3);
	tv.prisma5(.2, 4, 6.2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -5, 3);
	tv.prisma5(.2, 4, 6.2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -3.5, 4);
	tv.prisma5(3, 4, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	tv.prisma5(11, 4, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();//Fin de mueble de la tele


}
void CMuebles::silla(GLuint text1, GLuint text2) {
	CFiguras silla;
	glPushMatrix();
	glPushMatrix();
	glTranslatef(.9, -2, .9);
	silla.prisma5(4, .2, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.9, -2, .9);
	silla.prisma5(4, .2, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.9, -2, -.9);
	silla.prisma5(4, .2, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.9, -2, -.9);
	silla.prisma5(4, .2, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.9, 2, -.9);
	silla.prisma5(4, .2, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.6, 2, -.9);
	silla.prisma5(4, .1, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.4, 2, -.9);
	silla.prisma5(4, .1, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.2, 2, -.9);
	silla.prisma5(4, .1, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 2, -.9);
	silla.prisma5(4, .1, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.2, 2, -.9);
	silla.prisma5(4, .1, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.4, 2, -.9);
	silla.prisma5(4, .1, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.6, 2, -.9);
	silla.prisma5(4, .1, .1, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.9, 2, -.9);
	silla.prisma5(4, .2, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 4.1, -.9);
	silla.prisma5(.2, 2, .2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();
	silla.prisma5(.1, 2, 2, text1, text1, text1, text1, text1, text1);
	glPopMatrix();

}


void CMuebles::arbol(float x, float y, GLuint t_arbol)
{
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, t_arbol);

	for (int i = 0; i < 180; i += 20) {
		glPushMatrix();
		glRotatef(i, 0, 1, 0);
		glBegin(GL_QUADS); //plano
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 0.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, y, 0.0);
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);
}