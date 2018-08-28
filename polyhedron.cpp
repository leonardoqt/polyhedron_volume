//#include <iostream>
#include <cstdlib>
#include <cmath>
#include "polyhedron.h"

using namespace std;

void polyhedron :: init(int num)
{
	num_vert = num;
	num_surf = num*(num-1)*(num-2) / 6;
	vertex = new vec[num];
	noise = new vec[num];
	surf = new int*[num_surf];
	convex_surf = new int[num_surf];
	for (int t1=0; t1<num_surf; t1++)
		surf[t1] = new int[3];
}

void polyhedron :: import_vertex(double ** dat)
{
	for(int t1=0; t1<num_vert; t1++)
		vertex[t1] = dat[t1];
	for(int t1=0,current=0; t1<num_vert-2; t1++)
	for(int t2=t1+1; t2<num_vert-1; t2++)
	// find surface registration
	for(int t3=t2+1; t3<num_vert; t3++)
	{
		surf[current][0] = t1;
		surf[current][1] = t2;
		surf[current][2] = t3;
		current++;
	}
}

double polyhedron :: get_volume()
{
	vec temp;
	// find center;
	temp.clean();
	for (int t1=0; t1<num_vert; t1++)
		temp = temp + vertex[t1];
	center = temp / num_vert;
	
	// add noise to each vertex;
	for (int t1=0; t1<num_vert; t1++)
	{
		temp = vertex[t1] - center;
		temp = temp / temp.norm();
		noise[t1] = temp * (rand()/(double)RAND_MAX * 0.000001);
		vertex[t1] = vertex[t1] + noise[t1];
	}

	// check if surface is convex surface
	for (int t1=0; t1<num_surf; t1++)
	{
		temp = (vertex[surf[t1][0]]-vertex[surf[t1][1]])^(vertex[surf[t1][0]]-vertex[surf[t1][2]]);
		convex_surf[t1]=1;
		for (int t2=0; t2<num_vert; t2++)
			if (t2 != surf[t1][0] && t2 != surf[t1][1] && t2 != surf[t1][2])
			if ( ((center - vertex[surf[t1][0]])*temp) * ((vertex[t2] - vertex[surf[t1][0]])*temp) < 0)
			{
				convex_surf[t1]=0;
				break;
			}
//		std::cout<<convex_surf[t1]<<'\t'<<surf[t1][0]<<surf[t1][1]<<surf[t1][2]<<endl;
	}

	// calculate volume as sum of all tetrahedron
	for (int t1=0; t1<num_vert; t1++)
		vertex[t1] = vertex[t1] - noise[t1];
	volume = 0;
	for (int t1=0; t1<num_surf; t1++)
		if (convex_surf[t1] == 1)
			volume += fabs( ((center-vertex[surf[t1][0]])^(center-vertex[surf[t1][1]])) * (center-vertex[surf[t1][2]]) );
	volume /= 6;

	return volume;
}
