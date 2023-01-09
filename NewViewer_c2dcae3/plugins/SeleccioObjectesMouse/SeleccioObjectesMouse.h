#ifndef _SELECCIOOBJECTESMOUSE_H
#define _SELECCIOOBJECTESMOUSE_H

#include "plugin.h" 
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class SeleccioObjectesMouse: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)
    
public:
    void onPluginLoad();
    void postFrame();
    
    void mouseReleaseEvent(QMouseEvent *e);

private:
    
	void drawDrawColorScene();

	void setSelectedObject(int selected);
    
    QOpenGLShaderProgram* programBox;
    QOpenGLShader* vsBox;
    QOpenGLShader* fsBox;
    
    QOpenGLShaderProgram* programColor;
    QOpenGLShader* vsColor;
    QOpenGLShader* fsColor;
    
    bool created;
    GLuint cubeVAO;
    GLuint verticesVBO;
    GLuint colorVBO;
    
};

#endif
