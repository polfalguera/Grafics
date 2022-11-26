#include "AnimateVertices1.h"
#include "glwidget.h"

#include <QCoreApplication>

void AnimateVertices1::onPluginLoad()
{
	//Carregar shader, compile & link
	QString vs_src = 
		"#version 330 core\n"

		"layout (location = 0) in vec3 vertex;"
		"layout (location = 1) in vec3 normal;"
		"layout (location = 2) in vec3 color;"

		"out vec4 frontColor;"

		"uniform mat4 modelViewProjectionMatrix;"
		"uniform mat3 normalMatrix;"

		"uniform float amplitude = 0.1;"
		"uniform float freq = 1;" 

		"const float PI = 3.141592;"

		"uniform float time;"

		"void main() {"
			"vec3 N = normalize(normalMatrix * normal);"
			"frontColor = vec4(N.z);"
			"vec3 dt = (amplitude*sin(2*PI*freq*time)) * normal;"
			"gl_Position = modelViewProjectionMatrix * vec4(vertex+dt, 1.0);"
		"}";
		vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
		vs->compileSourceCode(vs_src);
		cout << "VS log:" << vs->log().toStdString() << endl;
		
		QString fs_src = 
			"#version 330 core\n"

			"in vec4 frontColor;"
			"out vec4 fragColor;"

			"void main() {"
				"fragColor = frontColor;"
			"}";
		fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
		fs->compileSourceCode(fs_src);
		cout << "FS log:" << fs->log().toStdString() << endl;
		
		program = new QOpenGLShaderProgram(this);
		program->addShader(vs);
		program->addShader(fs);
		program->link();
		cout << "Link log:" << program->log().toStdString() << endl;
		
		timer.start();
}

void AnimateVertices1::preFrame()
{
	program->bind(); //Activem els shaders
	program->setUniformValue("time",float(timer.elapsed()/1000.0));
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix",camera()->viewMatrix().normalMatrix());
}

void AnimateVertices1::postFrame()
{
	program->release(); //Desactivem els shaders
}


