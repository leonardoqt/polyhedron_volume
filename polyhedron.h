#include "vec.h"

#ifndef MY_POLYHEDRON
#define MY_POLYHEDRON
class polyhedron;

class polyhedron
{
private:
	int num_vert, num_surf;
	vec *vertex;
	vec *noise;			// add to vertex first and then removed
	int **surf;			// n by 3
	int *convex_surf;	// store if surface is convex surface
	vec center;
	double volume;

public:
	void init(int);
	void import_vertex(double**);	// n by 3
	double get_volume();
};

#endif
