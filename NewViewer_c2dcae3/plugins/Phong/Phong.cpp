#include "Phong.h"
#include "glwidget.h"

void Phong::onPluginLoad()
{
	//Carregar shader, compile & link
	vs = new QOpenGLShader(QOpenGLShader::Vertex,this);
	vs->compileSourceFile("Phong.vert");

	fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
	fs->compileSourceFile("Phong.frag");


	program = new QOpenGLShaderProgram(this);
	program->addShader(vs); 
	program->addShader(fs); 
	program->link();

	//Donc valor a totes les variables necessaries per a fer els càlculs d'il·luminació
	lightAmbient = QVector3D(0.1,0.1,0.1);
    lightDiffuse = QVector3D(1,1,1);
    lightSpecular = QVector3D(1,1,1);

    lightPosition = QVector4D(0,0,0,1);
    
    materialAmbient = QVector3D(0.8, 0.8, 0.6);
    materialDiffuse = QVector3D(0.8, 0.8, 0.6);
    materialSpecular = QVector3D(1.0, 1.0, 1.0);
    materialShininess = 64.0;
}

void Phong::preFrame()
{
	program->bind(); //Activem shaders
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix(); //modelViewProjectionMatrix
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix()); //modelViewMatrix
	program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix()); //normalMatrix
	program->setUniformValue("matAmbient", QVector4D(materialAmbient,1));
	program->setUniformValue("matDiffuse", QVector4D(materialDiffuse,1));
	program->setUniformValue("matSpecular", QVector4D(materialSpecular,1));
	program->setUniformValue("matShininess", materialShininess);
	program->setUniformValue("lightAmbient", QVector4D(lightAmbient,1));
	program->setUniformValue("lightDiffuse", QVector4D(lightDiffuse,1));
	program->setUniformValue("lightSpecular", QVector4D(lightSpecular,1));
	program->setUniformValue("lightPosition", lightPosition);
}

void Phong::postFrame()
{
	program->release(); //Desactivem shaders
}

