#include "SeleccioObjectesMouse.h"
#include "glwidget.h"

void SeleccioObjectesMouse::onPluginLoad()
{
    QString vs_color_src =
    "#version 330 core\n"
    "layout (location=0) in vec3 vertex;"
    "uniform mat4 modelViewProjectionMatrix;"
    "void main() {"
    "   gl_Position=modelViewProjectionMatrix*(vec4(vertex, 1));"
	"}";
    vsColor = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vsColor-> compileSourceCode(vs_color_src);
	cout << "VS Color log: " << vsColor->log().toStdString() << endl;
	
    QString fs_color_src =
    "#version 330 core\n"
    "uniform vec4 color;"
    "out vec4 fragColor;"
    "void main() {"
    "   fragColor=color;"
    "}";
	fsColor = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsColor->compileSourceCode(fs_color_src);
    cout << "FS Color log:" << fsColor->log().toStdString() << endl;

    programColor = new QOpenGLShaderProgram(this);
    programColor->addShader(vsColor);
    programColor->addShader(fsColor);
    programColor->link();
    cout << "Link Color log:" << programColor->log().toStdString() << endl;
    
    created=false;
    scene()->setSelectedObject(-1);
}

void SeleccioObjectesMouse::postFrame()
{ 
    int seleccionat=scene()->selectedObject();
    if (seleccionat>=0 && seleccionat<(int)scene()->objects().size()) {
        programBox->bind();
        
        // crear buffers
        GLWidget& g = *glwidget();
        g.makeCurrent();
        if (!created) {
            created=true;
            // dades
            GLfloat cube_vertices[]={
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
            GLfloat cube_colors[]={
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
            // VAO Capsa
            g.glGenVertexArrays(1, &cubeVAO);
            g.glBindVertexArray(cubeVAO);
            
            // VBOs Capsa  
            g.glGenBuffers(1, &verticesVBO);
            g.glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
            g.glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
            g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            g.glEnableVertexAttribArray(0);
            
            g.glGenBuffers(1, &colorVBO);
            g.glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
            g.glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
            g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
            g.glEnableVertexAttribArray(2);
            
            g.glBindVertexArray(0);
        }
        
        // establir modelViewProjection
        QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
        programBox->setUniformValue("modelViewProjectionMatrix", MVP);
        
        const Object &obj = scene()->objects()[seleccionat];
        programBox->setUniformValue("boundingBoxMin",obj.boundingBox().min());
        programBox->setUniformValue("boundingBoxMax",obj.boundingBox().max());
        g.glBindVertexArray(cubeVAO);
        g.glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // activar pintar nomes linies
        g.glDrawArrays(GL_TRIANGLES, 0, 36);
        g.glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // desactivar
        g.glBindVertexArray(0);
    }
}

void SeleccioObjectesMouse::mouseReleaseEvent(QMouseEvent* e)
{
    // a)
    if(!(e->button() & Qt::LeftButton)) return;
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    // b)
    g.glClearColor(1,0,0,0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    

    // c)
    programColor->bind();
    
    // d)

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programColor->setUniformValue("modelViewProjectionMatrix", MVP); 
    
    
    // e)
    for(unsigned int i = 0; i < scene()->objects().size(); ++i)
    {
        GLubyte color[4];
        color[0] = i + 1;
        color[1] = color[2] = 0;
        programColor -> setUniformValue("color", QVector4D(color[0]/255.0,color[1]/255.,color[2]/255.,1.0));
        drawPlugin() -> drawObject(i);
    }
    
    // f)
    int x = e -> x();
    int y = glwidget() -> height() - e->y();
    GLubyte read[4];
    glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,read); 
    
    // g)
    if(read[0] != 0) scene()->setSelectedObject(read[0] - 1);
     
    // h)
    g.update();

}
