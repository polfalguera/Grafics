#include "DrawBoundingBox.h"
#include "glwidget.h"

void DrawBoundingBox::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("DrawBoundingBox.vert");
	
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("DrawBoundingBox.frag");
	
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	
	created = false;
}

void DrawBoundingBox::postFrame()
{	
	GLWidget &g = *glwidget();
	g.makeCurrent();
	
	// 1. Creem els VBO buffers
	if (!created) {
		created = true;
		
		// Creem i activem el VAO buit
		g.glGenVertexArrays(1,&VAO);
		g.glBindVertexArray(VAO);
		
		// Creem VBO amb les coordenades normalitzades [0,1]
		float coords[] = {
			1, 1, 1,
			0, 1, 1,
			1, 0, 1,
			0, 0, 1,
			1, 0, 0,
			0, 0, 0,
			1, 1, 0,
			0, 1, 0,
			1, 1, 1,
			0, 1, 1,
			0, 1, 1,
			0, 1, 0,
			0, 0, 1,
			0, 0, 0,
			1, 0, 1,
			1, 0, 0,
			1, 1, 1,
			1, 1, 0
		};
		g.glGenBuffers(1,&VBO_coords);
		g.glBindBuffer(GL_ARRAY_BUFFER,VBO_coords);
		g.glBufferData(GL_ARRAY_BUFFER,sizeof(coords),coords,GL_STATIC_DRAW);
		g.glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
		g.glEnableVertexAttribArray(0);
		
		float colors[] = {
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0
		};
		g.glGenBuffers(1,&VBO_colors);
		g.glBindBuffer(GL_ARRAY_BUFFER,VBO_colors);
		g.glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
		g.glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0); // 1 es per les normals
		g.glEnableVertexAttribArray(2);
        
        g.glBindVertexArray(0); 
    }
    program->bind();
       	
    QMatrix4x4 MVP = camera()->projectionMatrix()*camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);
	
	Scene* scn = scene();
	const vector<Object> &objs = scn->objects();
	for (int i = 0; i < (int)objs.size(); ++i) {
		program->setUniformValue("boundingBoxMax",objs[i].boundingBox().max());
		program->setUniformValue("boundingBoxMin",objs[i].boundingBox().min());
		g.glBindVertexArray(VAO);
		g.glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // activar pintar nomes linies
		g.glDrawArrays(GL_TRIANGLE_STRIP,0,18);
		g.glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // desactivar
		g.glBindVertexArray(0);
	}
	
	program->release();
}

