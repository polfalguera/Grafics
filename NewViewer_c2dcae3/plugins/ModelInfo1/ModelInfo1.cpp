#include "ModelInfo1.h"
#include "glwidget.h"

  // ps - Número de polígons
// vs - Número de vèrtexs
// pr - Percentatge de polígons que són triangle
void ModelInfo1::calculs(int& ps, int& vs, double& pr) {
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

void ModelInfo1::postFrame()
{
	cout << "Número total d'objectes: " << scene()->objects().size() << endl;
	int nPoligons = 0;
	int nVertexs = 0;
	double percentatge = 0;
	calculs(nPoligons,nVertexs,percentatge);
	
	cout << "Número total de polígons: " << nPoligons << endl;
	cout << "Número total de vèrtexs: " << nVertexs << endl;
	cout << "Percentatge de polígons que són triangle: " << percentatge << "%" << endl;

}

