#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include "plugin.h"
#include <QElapsedTimer>
#include <QPainter>

class Framerate: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
  private:
	int num_frames;
	QPainter painter;

  public slots:
	void pintarFPS();
};

#endif
