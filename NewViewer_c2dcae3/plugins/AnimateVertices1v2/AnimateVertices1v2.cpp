#include "AnimateVertices1v2.h"
#include "glwidget.h"

#include <QCoreApplication>

void AnimateVertices1v2::onPluginLoad()
{
	//Carregar shader, compile & link
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("animate-vertices1.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;
	
	fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
	fs->compileSourceFile("animate-vertices1.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;
	
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;
	
	timer.start();
}

void AnimateVertices1v2::preFrame()
{
	program->bind(); //Activem els shaders
	program->setUniformValue("time",float(timer.elapsed()/1000.0));
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix",camera()->viewMatrix().normalMatrix());
}

void AnimateVertices1v2::postFrame()
{
	program->release(); //Desactivem els shaders
}


