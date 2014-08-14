#include "cm.h"


Point*
PointByDimension(int length){
  return (Point*)malloc(sizeof(Point) + (length - 1) * sizeof(double));
}

Point*
PointByValues(int argc, double vals[], int type){
  Point* temp = PointByDimension(argc);
  for(int i = 0; i < argc; i++){
    temp->val[i] = vals[i];
  }
  //Random-distributed kenergy, not exactly randomly generated.
  temp->kenergy = 0;
  temp->dimension = argc;
  temp->type = type;
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
