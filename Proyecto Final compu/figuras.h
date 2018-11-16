//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma (float altura, float largo, float profundidad, GLuint text, GLuint tex2);//Funcíon creacion 
	void prisma2(float altura, float largo, float profundidad, GLuint text);
	void prisma3(float altura, float largo, float profundidad, GLuint text, GLuint text2);//Funcíon creacion prisma
	void prisma4(float altura, float largo, float profundidad, GLuint text, GLuint text2);//Funcíon creacion prisma
	void prisma5(float altura, float largo, float profundidad, GLuint text, GLuint text1, GLuint text2, GLuint text3, GLuint text4, GLuint text5);  //Funcion creacion prisma
	void prisma6(float altura, float largo, float profundidad, GLuint text, GLuint text2);
	void prisma7(float altura, float largo, float profundidad, GLuint text, GLuint text2);
	void prisma8(float altura, float largo, float profundidad, GLuint text);
	void prisma9(float altura, float largo, float profundidad, GLuint text);
	void prisma10(float altura, float largo, float profundidad, GLuint text);
	void prisma11(float altura, float largo, float profundidad, GLuint text);
	void prisma12(float altura, float largo, float profundidad, GLuint text);
	void skybox(float altura, float largo, float profundidad, GLuint text);	//Funcion creacion cielo
	

	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);

};
