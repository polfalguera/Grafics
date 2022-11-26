#include "prova.h"
#include "glwidget.h"

void Prova::onPluginLoad()
{
	cout << "LOAD!" << endl;	
}

void Prova::preFrame()
{
	glEnable(GL_DEPTH_TEST); //glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);//multiplico por 1 lo que hay en el buffer de color y le sumo el color del fragmento multiplicado por su alpha.
	//glDepthMask(GL_FALSE); //No escribimos en el Z-buffer
}

void Prova::postFrame()
{
	
}

void Prova::onObjectAdd()
{
	cout << "HEM AFEGIT UN OBJECTE!" << endl;
	cout << "NÚMERO D'OBJECTES TOTAL = " << scene()->objects().size() << endl;
}

bool Prova::drawScene()
{
	return false; // return true only if implemented
}

bool Prova::drawObject(int)
{
	return false; // return true only if implemented
}

bool Prova::paintGL()
{
	return false; // return true only if implemented
}

void Prova::keyPressEvent(QKeyEvent *)
{
	
}

void Prova::mouseMoveEvent(QMouseEvent *)
{
	
}

