#ifndef _MODELINFO1_H
#define _MODELINFO1_H

#include "plugin.h" 

class ModelInfo1: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void postFrame();

  private:
	 void calculs(int& ps, int& vs, double& pr);
	// add private methods and attributes here
};

#endif
