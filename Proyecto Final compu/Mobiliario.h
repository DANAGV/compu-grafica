//#include <windows.h>  //Solo para Windows
						//#include <GL/gl.h>     // The GL Header File
						//#include <stdio.h>

						//#include <math.h>
#include "Main.h"
	class CMuebles
{
public:

	float text_der;
	float text_izq;



	void cama(GLuint text1, GLuint text2);
	void sillon(GLuint text1, GLuint text2, GLuint text3);
	void sillon2(GLuint text1, GLuint text2);
	void buro(GLuint text1, GLuint text2);
	void repisa(GLuint text1, GLuint text2, GLuint text3);
	void foco(GLuint text1);
	void refri(GLuint text1, GLuint text2);
	void tv(GLuint text1);
	void tapete(GLuint text1);
	void mesa(GLuint text1);
	void mesaS(GLuint text1);
	void escritorio(GLuint text1);
	void estufa(GLuint text1, GLuint text2, GLuint text3);
	void escritorio1(GLuint text1, GLuint text2);
	void silla(GLuint text1, GLuint text2);
	void arbol(float x, float y, GLuint t_arbol);
};

