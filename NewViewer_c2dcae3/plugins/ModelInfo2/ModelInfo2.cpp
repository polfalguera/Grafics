#include "ModelInfo2.h"
#include "glwidget.h"

// ps - Número de polígons
// vs - Número de vèrtexs
// pr - Percentatge de polígons que són triangle
void ModelInfo2::calculs(int& ps, int& vs, double& pr) {
	int n = scene()->objects().size();
	for (int i = 0; i < n; ++i) {
		Object& obj = scene()->objects()[i];
		int m = obj.faces().size(); 
		ps += m;
		for (int j = 0; j < m; ++j) {
			int vertexs = obj.faces()[j].numVertices();
			vs += vertexs;
			if (vertexs == 3) ++pr;
		}
	} 
	pr = pr / ps * 100;
}

void ModelInfo2::postFrame()
{
	int nObjectes = scene()->objects().size();
	int nPoligons = 0;
	int nVertexs = 0;
	double percentatge = 0;
	calculs(nPoligons,nVertexs,percentatge);
	
	QFont font;
  	font.setPixelSize(16);
  	painter.begin(glwidget());
  	painter.setFont(font);
	int x = 15;
	int y = 20;
	painter.drawText(x, y, QString("Nº objectes: " + QString::number(nObjectes)));
	painter.drawText(x, y+20, QString("Nº poligons: " + QString::number(nPoligons)));
	painter.drawText(x, y+40, QString("Nº vertexs: " + QString::number(nVertexs)));
	if (nObjectes == 0) percentatge = 0;
	painter.drawText(x, y+60, QString("Porcentatge triangles: " + QString::number(percentatge) + "%"));    
	painter.end();
}


