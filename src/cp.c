#include "cp.h"

/*
 * ChaosPool Management
 */

ChaosPool*
ChaosPoolBySize(int size, int dimension, int queueSize, double shc, double temperature, double distance){
  int overallSize = 1;
  for(int i = 0;i < dimension; i++){
    overallSize*=size;
  }
  int truePointSize = sizeof(Point*);
  int nsize = overallSize * truePointSize + sizeof(ChaosPool) - sizeof(Point*);
  ChaosPool* pool = (ChaosPool*)malloc(nsize);
  pool -> temperature = temperature;
  pool -> size = size;
  pool -> dimension = dimension;
  pool -> overallSize = overallSize;
  pool -> averageDistance = distance;
  pool -> offset = 0;
  pool -> taskQueue = newTaskQueueWithPool(queueSize, pool);
  pool -> shcm = shc * UNITMASS(dimension) * overallSize;
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
resetChaosPool(ChaosPool* pool){
  //
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
doCrossoverByPoints(Point* p1, Point* p2, double options[], int optc, ChaosPool* pool){
  //Crossover: exchange bits: low 32bits
  for(int i = 0; i < pool->dimension; i++){
    //TODO: the format of opts to be impl.
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
insertAtomicPoint(Point* point, ChaosPool* pool){
  double opts[] = {0.0};
  doCrossoverByPoints(point, getNextPoint(pool), opts, 1, pool);
}

Point*
getNextPoint(ChaosPool* pool){
  Point* np = pool->pool[pool->offset];
  pool->offset = regularizeIntegerToIndex(pool, getIntegerAmongPoint(np));
  return np;
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
  pool->entropy -= entropyDelta;
}

//Check the amount of entropy requested. If cannot afford it, try to return a reduced value.
bool
checkEntropy(double* entropyDelta, ChaosPool* pool){
  //
  return true;
}

/*
 * I/O Operations
 */
//Extract entropy according to specific entropy size
void
extractEntropy(char* dest, int length, double entropy, ChaosPool* pool){
  //
}

void
extractBits(char* dest, int bits, ChaosPool* pool, int priority){
  //
}

//Add pure entropy into the pool.
void
pourEntropy(double entropy, ChaosPool* pool){
  //
}

//adding kinetic energy into points.
void
heatPool(double heat, ChaosPool* pool){
  double averageHeat = heat / pool->overallSize;
  for(int i = 0; i < pool->overallSize; i++){
    pool->pool[i]->kenergy += averageHeat;
  }
}

//Add bytes with entropy into the pool.
void
addMaterialsWithEntropy(double entropy, char* material, int length, ChaosPool* pool){
  if(checkEntropy(&entropy, pool)){
    addEntropy(entropy, pool);
    addMaterialsWithoutEntropy(material, length, pool);
  }else{
    perror("NOTE: no enough space for input entropy, only part of the entropy will be accepted.\n");
  }
}

void
addRawMaterials(char* material, int length, ChaosPool* pool){
  addMaterialsWithEntropy(estimateEntropyInData(material, length), material, length, pool);
}

void
addMaterialsWithoutEntropy(char* material, int length, ChaosPool* pool){
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

int
regularizeIntegerToIndex(ChaosPool* pool, int integer){
  return ((1.0 * integer) / INT_MAX) * pool->overallSize;
}

//get a point according an int in a pool.
//NOTE: index here may be beyond the size of pool.
Point*
getPointAmongChaosPoolByIndex(int index, ChaosPool* pool){
  //
}

void
evaluatePoolEntropy(ChaosPool* pool){
  pool -> entropy = estimateEntropyInData((char*)pool->pool[0], pool->overallSize * pool->dimension * 4);
}

double
calculateCapacityOfDataBlock(int bits){
  //
}
