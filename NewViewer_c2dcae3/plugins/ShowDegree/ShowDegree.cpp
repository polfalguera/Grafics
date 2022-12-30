#include "ShowDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
	const Object obj = scene()->objects()[0];
	double nVertexsCara = obj.faces().size()*3;
	double  nVertexs = obj.vertices().size();
	grauMig = nVertexsCara / nVertexs;
}

void ShowDegree::onObjectAdd()
{
	const Object obj = scene()->objects()[0];
	double nVertexsCara = obj.faces().size()*3;
	double  nVertexs = obj.vertices().size();
	grauMig = nVertexsCara / nVertexs;

}

void ShowDegree::postFrame()
{
	QFont font;
  	font.setPixelSize(16);
  	painter.begin(glwidget());
  	painter.setFont(font);
	painter.drawText(15, 20, QString("Grau mig: " + QString::number(grauMig)));
	painter.end();
}

