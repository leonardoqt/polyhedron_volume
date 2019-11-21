#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vec.h"
#include "polyhedron.h"

using namespace std;

int main()
{
	srand(time(0));
	int num_vertex;
	double **vertex;
	
	cin>>num_vertex;
	
	vertex = new double*[num_vertex];
	for(int t1=0; t1<num_vertex; t1++)
		vertex[t1] = new double[3];
	
	for(int t1=0; t1<num_vertex; t1++)
		cin>>vertex[t1][0]>>vertex[t1][1]>>vertex[t1][2];
	
	polyhedron p1;
	p1.init(num_vertex);
	p1.import_vertex(vertex);
	cout<<p1.get_volume()<<endl;
	
	return 0;
}
