#ifndef _ANIMATEVERTICES1_H
#define _ANIMATEVERTICES1_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram> 
#include <QElapsedTimer>

class AnimateVertices1: public QObject, public Plugin
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
    QOpenGLShader *fs, *vs;
    
    QElapsedTimer timer;
};

#endif
