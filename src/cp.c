#include "cp.h"
#include <stdlib.h>
#include <math.h>

#define random(x) (double)(rand()%(x*1000000))/1000000
#define randomInt(x) rand()%x
#define typeCount 1
#define DEBUG 1

#ifdef DEBUG
#include <stdio.h>
#endif

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
initializeChaosPoolWithRandomValues(ChaosPool* pool){
  for(int i = 0; i < pool->overallSize; i++){
    //Randomize the shape of point: specific type and dimension
    pool->pool[i] = (Point*)malloc(sizeof(Point) - sizeof(double) + sizeof(double) * pool->dimension);
    for(int j = 0; j < pool->dimension; j++){
      pool->pool[i]->val[j] = random(30);
    }
  }
}

void
printChaosPool(ChaosPool* pool){
  for(int i = 0; i < pool->overallSize; i++){
    printf("< ");
    for(int j = 0; j < pool->dimension; j++){
      printf(" %lf ", pool->pool[i]->val[j]);
    }
    printf(">\n");
  }
}

/*
 * Atomic Entropy Operations
 */
void updateAllPoints(ChaosPool* pool){
  for(int i = 0; i < pool->overallSize; i++){
    update(pool->pool[i]);
  }
}

/*
 * Managed Entropy Operations
 */
void
evolve(int generations, ChaosPool* pool){
  for(int i = 0; i < generations; i++){
    updateAllPoints(pool);
  }
}


/*
 * Entropy Management
 */
