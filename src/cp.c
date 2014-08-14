#include "cp.h"

/*
 * ChaosPool Management
 */

ChaosPool*
ChaosPoolBySize(int size, int dimension){
  int overallSize = 1;
  for(int i = 0;i < dimension; i++){
    overallSize*=size;
  }
  int truePointSize = sizeof(Point*);
  int nsize = overallSize * truePointSize + sizeof(ChaosPool) - sizeof(Point*);
  ChaosPool* pool = (struct ChaosPool*)malloc(nsize);
  pool -> size = size;
  pool -> dimension = dimension;
  pool -> overallSize = overallSize;
  return pool;
}

void
swapPoints(int p1[], int p2[], ChaosPool* pool){
  int pv1 = 0, pv2 = 0;
  for(int i = 0; i < pool->dimension; i++){
    pv1 += pow(p1[i], pool->dimension - i);
    pv2 += pow(p2[i], pool->dimension - i);
  }
  Point** pc1 = &(pool->pool[pv1]);
  Point** pc2 = &(pool->pool[pv2]);
  Point* pc3 = *pc1;
  *pc1 = *pc2;
  *pc2 = pc3;
}

void
initializeChaosPoolWithRandomValues(ChaosPool* pool, int mode){
  for(int i = 0; i < pool->overallSize; i++){
    //Randomize the shape of point: specific type and dimension
    MutableDoubleArray* array = (MutableDoubleArray*)malloc(sizeof(MutableDoubleArray) + (pool->dimension - 1)*sizeof(double));
    for(int i = 0; i < pool->dimension; i++){
      array->val[i] = random(30);
    }
    pool->pool[i] = PointByValues(pool->dimension, array->val, LORENZ);
  }
}

void
printChaosPool(ChaosPool* pool){
  for(int i = 0; i < pool->overallSize; i++){
    printf("< ");
    for(int j = 0; j < pool->dimension; j++){
      printf(" %f ", pool->pool[i]->val[j]);
    }
    printf(">\n");
  }
}

/*
 * Atomic Pool Operations
 */
void
updatePoint(Point* point){
  update(point);
}

void
updateAllPoints(ChaosPool* pool){
  for(int i = 0; i < pool->overallSize; i++){
    update(pool->pool[i]);
  }
}

void
doRadiation(double intensity, Point* point, double duration){
  //
}

void
doCrossoverByPoints(Point* p1, Point* p2, double options[], int optc, ChaosPool* pool){
  //Crossover: exchange bits: low 32bits
  for(int i = 0; i < pool->dimension; i++){
    //
  }
}

void
doCrossoverByIndexes(int src[], int dest[], double options[], int optc, ChaosPool* pool){
  //assuming all points has the dimension set in pool
  int pv1 = 0, pv2 = 0;
  for(int i = 0; i < pool->dimension; i++){
    pv1 += pow(src[i], pool->dimension - i);
    pv2 += pow(dest[i], pool->dimension - i);
  }
  Point** pc1 = &(pool->pool[pv1]);
  Point** pc2 = &(pool->pool[pv2]);
  doCrossoverByPoints(*pc1, *pc2, options, optc, pool);
}

void
doBrownianMotion(double duration, ChaosPool* pool){
  //
}

/*
 * Managed Pool Operations
 */
void
evolve(int generations, ChaosPool* pool){
  for(int i = 0; i < generations; i++){
    updateAllPoints(pool);
  }
}

void
stir(double heat, ChaosPool* pool){
  //
}

void
radiate(double intensity, double scope, double duration, ChaosPool* pool){
  //
}

void
performClimateChange(int type, double options[], int optc, ChaosPool* pool){
  //
}

void
performCrossover(double scope, double intensity, double options[], ChaosPool* pool){
  //
}


/*
 * Entropy Management
 */
void
addEntropy(double entropyDelta, ChaosPool* pool){
  pool->entropy += entropyDelta;
}

void
reduceEntropy(double entropyDelta, ChaosPool* pool){
  //
}

//Check the amount of entropy requested. If cannot afford it, try to return a reduced value.
void
requestEntropy(double* entropy, ChaosPool* pool){
  //
}

/*
 * I/O Operations
 */
//Base function for entropy extract
void
extractEntropy(char* dest, double entropy, ChaosPool* pool){
  //
}

//Add pure entropy into the pool.
void
pourEntropy(double entropy, ChaosPool* pool){
  //
}

//Add entropy by heating the pool. Might be executed in stirring or adding kinetic energy into points.
void
heatPool(double heat, ChaosPool* pool){
  //
}

//Add bytes with entropy into the pool.
void
addMaterials(double entropy, char* material, int length, ChaosPool* pool){
  //
}

/*
 * Utils
 */
char*
expandBits(char* data, int destLength){
  //
}

//extract an int from a point, using hash-like functions
int
getIntegerAmongPoint(Point* point){
  //
}

//get a point according an int in a pool.
//NOTE: index here may be beyond the size of pool.
Point*
getPointAmongChaosPoolByIndex(int index, ChaosPool* pool){
  //
}
