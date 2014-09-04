#ifndef chaospool__
#define chaospool__
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include "common.h"
#include "cm.h"
#include "scheduler.h"

#define RANDOMMODE 1
#define ALLLORENZMODE 2

#define DEFAULTSHC 1.0

#define DEFAULTTEMPERATURE 20.0
#define DEFAULTDISTANCE 0.00001 //in meters
#define UNITMASS(x) 0.0001 * x //mass of a point with dimension
#define GRANULARITY_LOW 6
#define GRANULARITY_HIGH 7

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

struct ChaosPool{
  //core properties
  double temperature;
  //Specific Heat Capacity * mass
  double shcm;
  double entropy;
  //the measurement of volume
  double averageDistance;
  int size;
  int dimension;
  //the dimension of pool
  int overallSize;
  //control properties
  int offset;
  TaskQueue* taskQueue;
  //data
  Point* pool[1];
};

struct MutableDoubleArray{
  int length;
  double val[1];
};

/*
 * ChaosPool Management
 */
ChaosPool*
ChaosPoolBySize(int size, int dimension, int queueSize, double shc, double temperature, double distance);

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
private void
updatePoint(Point* point);

void
updateAllPoints(ChaosPool* pool);

void
doCrossoverByPoints(Point* p1, Point* p2, double options[], int optc, ChaosPool* pool);

void
doCrossoverByIndexes(int src[], int dest[], double options[], int optc, ChaosPool* pool);

private void
insertAtomicPoint(Point* point, ChaosPool* pool);

void
insertAtomicChar(char* ch, ChaosPool* pool);

private Point*
getNextPoint(ChaosPool* pool);

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
private void
addEntropy(double entropyDelta, ChaosPool* pool);

private void
reduceEntropy(double entropyDelta, ChaosPool* pool);

//Check the amount of entropy requested. If cannot afford it, try to return a reduced value.
bool
checkEntropy(double* entropyDelta, ChaosPool* pool);

/*
 * I/O Operations
 */
void
extractEntropy(char* dest, int length, double entropy, ChaosPool* pool);

void
extractBits(char* dest, int bits, ChaosPool* pool, int priority);

//Add pure entropy into the pool.
void
pourEntropy(double entropy, ChaosPool* pool);

//adding kinetic energy into points.
void
heatPool(double heat, ChaosPool* pool);

//Add bytes with entropy into the pool.
void
addMaterialsWithEntropy(double entropy, char* material, int length, ChaosPool* pool);

void
addRawMaterials(char* material, int length, ChaosPool* pool);

private void
addMaterialsWithoutEntropy(char* material, int length, ChaosPool* pool);

/*
 * Utils
 */
private char*
expandBits(char* data, int destLength);

private unsigned int
getIntegerAmongPoint(Point* point);

private int
regularizeIntegerToIndex(ChaosPool* pool, unsigned int integer);

//NOTE: index here may be beyond the size of pool.
private Point*
getPointAmongChaosPoolByIndex(int index, ChaosPool* pool);

private void
evaluatePoolEntropy(ChaosPool* pool);

#endif
