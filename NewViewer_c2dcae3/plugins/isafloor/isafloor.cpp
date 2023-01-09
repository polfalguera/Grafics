#include "isafloor.h"
#include "glwidget.h"

float calcularArea(Face f, const vector<Vertex> &vertices) {
	Point v1 = vertices[f.vertexIndex(0)].coord();
	Point v2 = vertices[f.vertexIndex(1)].coord();
	Point v3 = vertices[f.vertexIndex(2)].coord();

	Vector u = v2 - v1;
	Vector v = v3 - v1;

	Vector m = QVector3D::crossProduct(u,v);
	return m.length() / 2;
}

void Isafloor::onPluginLoad()
{
	//Carregar shader, compile & link
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("../isafloor/isafloor.vert");
	
	fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
	fs->compileSourceFile("../isafloor/isafloor.frag");
	
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	
	/* Fem el càlcul de la proporció */
	float areaTotal = 0.0;
	float areaTerra = 0.0;
	const Object obj = scene()->objects()[0];
	const vector<Face> &faces = obj.faces();
	const vector<Vertex> &vertices = obj.vertices();
	for (Face f: faces) {
		float area = calcularArea(f,vertices);
		float value = f.normal().z();
		if (value > 0.7) areaTerra += area;
		
		areaTotal += area;
	}
	
	lamda = areaTerra / areaTotal;
	cout << "TERRA: " << lamda << endl;		
}

void Isafloor::preFrame()
{
	program->bind(); //Activem els shaders
	program->setUniformValue("lamda",lamda);
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix",camera()->viewMatrix().normalMatrix());	
}

void Isafloor::postFrame()
{
	program->release();
}

