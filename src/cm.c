#include <stdlib.h>
#include "cm.h"

#define LORENZ_RHO 28
#define LORENZ_SIGMA 10
#define LORENZ_BETA 8/3
#define DEBUG 1

#ifdef DEBUG
#include <stdio.h>
#endif

Point*
PointByDimension(int length){
  printf("accepting %d, returning %ld\n", length, sizeof(Point) * length);
  return (Point*)malloc(sizeof(Point) * length);
}

Point*
PointByValues(int argc, double vals[]){
  Point* temp = PointByDimension(argc);
  for(int i = 0; i < argc; i++){
    temp->val[i] = vals[i];
  }
  return temp;
}

void
lorenzUpdater(Point* vals, double interval){
  double dx = (vals->val[1] - vals->val[0]) * LORENZ_SIGMA;
  double dy = (LORENZ_RHO - vals->val[2]) * vals->val[0] - vals->val[1];
  double dz = vals->val[1] * vals->val[0] - vals->val[2] * LORENZ_BETA;
  vals->val[0] = dx * interval + vals->val[0];
  vals->val[1] = dy * interval + vals->val[1];
  vals->val[2] = dz * interval + vals->val[2];
}
