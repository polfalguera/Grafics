#include "ResaltatObjecteSeleccionat.h"
#include "glwidget.h"

void ResaltatObjecteSeleccionat::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("resaltat.vert");
	
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("resaltat.frag");
	
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	
	created = false;
}

void ResaltatObjecteSeleccionat::postFrame()
{
	int seleccionat = scene()->selectedObject();
	if (seleccionat >= 0 && seleccionat < (int)scene()->objects().size()) {
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
				0,0,0,
                0,0,1,
                0,1,0,
                
                0,0,1,
                0,1,0,
                0,1,1,
                
                1,0,0,
                1,0,1,
                1,1,0,
                
                1,0,1,
                1,1,0,
                1,1,1,
                
                0,0,0,
                0,0,1,
                1,0,0,
                
                0,0,1,
                1,0,0,
                1,0,1,
                
                0,1,0,
                0,1,1,
                1,1,0,
                
                0,1,1,
                1,1,0,
                1,1,1,
                
                0,0,0,
                0,1,0,
                1,0,0,
                
                0,1,0,
                1,0,0,
                1,1,0,
                
                0,0,1,
                0,1,1,
                1,0,1,
                
                0,1,1,
                1,0,1,
                1,1,1
			};
			g.glGenBuffers(1,&VBO_coords);
			g.glBindBuffer(GL_ARRAY_BUFFER,VBO_coords);
			g.glBufferData(GL_ARRAY_BUFFER,sizeof(coords),coords,GL_STATIC_DRAW);
			g.glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
			g.glEnableVertexAttribArray(0);
			
			float colors[] = {
				1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0
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
		const Object &obj = scn->objects()[seleccionat];
		program->setUniformValue("boundingBoxMin",obj.boundingBox().min());
		program->setUniformValue("boundingBoxMax",obj.boundingBox().max());
		g.glBindVertexArray(VAO);
		g.glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // activar pintar nomes linies
		g.glDrawArrays(GL_TRIANGLES, 0, 36);
		g.glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // desactivar
		g.glBindVertexArray(0);

		program->release();
	}
}
