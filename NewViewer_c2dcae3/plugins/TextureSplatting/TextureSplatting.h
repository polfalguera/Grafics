#ifndef _TEXTURESPLATTING_H
#define _TEXTURESPLATTING_H

#include "plugin.h" 

class TextureSplatting: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();
  private:
	QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs; 
    GLuint textureId0, textureId1, textureId2;
};

#endif
