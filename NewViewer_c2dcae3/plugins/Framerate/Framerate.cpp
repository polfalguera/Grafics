#include "Framerate.h"
#include "glwidget.h"
#include <QTimer>

void Framerate::onPluginLoad()
{
	num_frames = 0;
    QTimer *frameTimer = new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()), this, SLOT(pintarFPS()));
    frameTimer->start(1000);
}

void Framerate::postFrame()
{
	++num_frames;
}

void Framerate::pintarFPS() {

	cout << num_frames << endl;
	
	num_frames = 0;
}
