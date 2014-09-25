#ifndef chaosmodel__
#define chaosmodel__
#include "common.h"
#include <stdlib.h>
#include <stdio.h>

#define TYPECOUNT 2
#define RANDOMTYPE 0
#define LORENZ 1

#define LORENZ_RHO 28
#define LORENZ_SIGMA 10
#define LORENZ_BETA 8/3
#define DEBUG 1

struct Point{
  double kenergy;
  double entropy;
  //Customization of point dimension to be added.
  int dimension;
  int type;
  double val[1];
};

private Point*
PointByDimension(int length);

Point*
PointByValues(int argc, double vals[], int type);

void
lorenzUpdater(Point* vals, double interval);

char*
PointToString(Point* p);

/*
 * Atomic Point Operations
 */
void
endureRadiation(Point* point, double intensity, double duration);

#endif
