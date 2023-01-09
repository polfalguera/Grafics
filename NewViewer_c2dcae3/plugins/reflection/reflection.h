#ifndef _REFLECTION_H
#define _REFLECTION_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class Reflection : public QObject, public Plugin
{
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")   
     Q_INTERFACES(Plugin)

 public:
    void onPluginLoad();
    bool paintGL();
 
 private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    GLuint textureId0;
    GLuint textureId1;
    GLuint textureId2;
 };
 
 #endif

