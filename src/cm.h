#define CHAOSMODEL

typedef struct Point{
  double kenergy;
  //Customization of point dimension to be added.
  // int dimension;
  int type;
  double val[1];
} Point;

typedef Point LorenzChaosModel;

Point*
PointByDimension(int length);

Point*
PointByValues(int argc, double vals[]);

void
lorenzUpdater(Point* vals, double interval);

char*
PointToString(Point* p);
