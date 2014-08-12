#define CHAOSPOOL

#ifndef CHAOSMODEL
#include "cm.h"
#endif

#define interval 0.00001
//Using macros to customize the update functions for different types: instead of function pointers
#define update(point) lorenzUpdater(point, interval)

typedef struct ChaosPool{
  double entropy;
  int size;
  int dimension;
  //the dimension of pool
  int overallSize;
  Point* pool[1];
} ChaosPool;

/*
 * ChaosPool Management
 */

struct ChaosPool*
ChaosPoolBySize(int size, int dimension);

void
swapPoints(int p1[], int p2[], ChaosPool* pool);

void
initializeChaosPoolWithRandomValues(ChaosPool* pool);

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
doRadiation(double intensity, int pos[], double duration, ChaosPool* pool);

void
doCrossover(int src[], int dest[], double options[], int optc, ChaosPool* pool);

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
