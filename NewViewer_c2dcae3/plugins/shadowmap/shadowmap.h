#ifndef _SHADOWMAP_H
#define _SHADOWMAP_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class ShadowMap : public QObject, public Plugin
 {
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")   
     Q_INTERFACES(Plugin)

 public:
    void onPluginLoad();
    bool paintGL();
    void keyPressEvent(QKeyEvent*);   
 
 private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    GLuint textureId;
    Camera lightCamera;

    void drawQuad(const Point& p0, const Point& p1, const Point& p2, const Point& p3);
 };
 
 #endif
