#include <stdlib.h>
#include <math.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#define CHAOSPOOL

#define RANDOMMODE 1
#define ALLLORENZMODE 2

#ifndef CHAOSMODEL
#include "cm.h"
#endif

#define interval 0.00001
//Using macros to customize the update functions for different types: instead of function pointers
#define update(point) switch(point->type){\
  case LORENZ:\
    lorenzUpdater(point, interval);\
    break;\
  default:\
    break;\
}
#define random(x) (x * 1.0 * rand()) / (RAND_MAX + 1)
#define rangeRandom(x, y) random(y - x) - x
#define randomInt(x) rand()%x
#define typeCount 1
#define DEBUG 1

typedef struct ChaosPool{
  double entropy;
  int size;
  int dimension;
  //the dimension of pool
  int overallSize;
  Point* pool[1];
} ChaosPool;

typedef struct MutableDoubleArray{
  int length;
  double val[1];
}MutableDoubleArray;

/*
 * ChaosPool Management
 */

struct ChaosPool*
ChaosPoolBySize(int size, int dimension);

void
swapPoints(int p1[], int p2[], ChaosPool* pool);

void
initializeChaosPoolWithRandomValues(ChaosPool* pool, int mode);

void
resetChaosPool(ChaosPool* pool);

void
printChaosPool(ChaosPool* pool);

/*
 * Atomic Pool Operations
 */
void
updatePoint(Point* point);

void
updateAllPoints(ChaosPool* pool);

void
doRadiation(double intensity, Point* point, double duration);

void
doCrossoverByPoints(Point* p1, Point* p2, double options[], int optc, ChaosPool* pool);

void
doCrossoverByIndexes(int src[], int dest[], double options[], int optc, ChaosPool* pool);

//TODO: is this just a kind of chaos movement?
void
doBrownianMotion(double duration, ChaosPool* pool);

/*
 * Managed Pool Operations
 */
void
evolve(int generations, ChaosPool* pool);

void
stir(double heat, ChaosPool* pool);

void
radiate(double intensity, double scope, double duration, ChaosPool* pool);

void
performClimateChange(int type, double options[], int optc, ChaosPool* pool);

void
performCrossover(double scope, double intensity, double options[], ChaosPool* pool);

/*
 * Entropy Management
 */
void
addEntropy(double entropyDelta, ChaosPool* pool);

void
reduceEntropy(double entropyDelta, ChaosPool* pool);

//Check the amount of entropy requested. If cannot afford it, try to return a reduced value.
void
requestEntropy(double* entropy, ChaosPool* pool);

/*
 * I/O Operations
 */
//Base function for entropy extract
void
extractEntropy(char* dest, double entropy, ChaosPool* pool);

//Add pure entropy into the pool.
void
pourEntropy(double entropy, ChaosPool* pool);

//Add entropy by heating the pool. Might be executed in stirring or adding kinetic energy into points.
void
heatPool(double heat, ChaosPool* pool);

//Add bytes with entropy into the pool.
void
addMaterials(double entropy, char* material, int length, ChaosPool* pool);

/*
 * Utils
 */
char*
expandBits(char* data, int destLength);

int
getIntegerAmongPoint(Point* point);

//NOTE: index here may be beyond the size of pool.
Point*
getPointAmongChaosPoolByIndex(int index, ChaosPool* pool);
