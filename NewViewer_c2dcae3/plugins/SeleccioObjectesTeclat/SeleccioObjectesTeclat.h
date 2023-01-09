#ifndef _SELECCIOOBJECTESTECLAT_H
#define _SELECCIOOBJECTESTECLAT_H

#include "plugin.h" 

class SeleccioObjectesTeclat: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
	 void keyPressEvent(QKeyEvent *e);
  private:
	 QOpenGLShaderProgram* program;
	 QOpenGLShader* vs;
	 QOpenGLShader* fs;
	
	 bool created;
	 GLuint VAO;
	 GLuint VBO_coords;
	 GLuint VBO_colors;
};

#endif
