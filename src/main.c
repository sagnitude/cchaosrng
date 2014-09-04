#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cm.h"
#include "scheduler.h"
#include "cp.h"

// #define PRINTOUT
// #define PROFILE
// #define CONTROL

int
main(int argc, char** argv){
  ChaosPool* pool = ChaosPoolBySize(2, 3, 20, DEFAULTSHC, DEFAULTTEMPERATURE, DEFAULTDISTANCE);
  initializeChaosPoolWithRandomValues(pool, ALLLORENZMODE);

  #ifdef PRINTOUT
  printChaosPool(pool);
  #endif

  #ifdef PROFILE
  clock_t t_start, t_end;
  t_start = clock();
  #endif

  evolve(1000000, pool);

  #ifdef PROFILE
  t_end = clock() ;
  printf("calculating %d points\n\
    time elasped from %ld to %ld: %ld milliseconds\n", pool->overallSize,
    1000*t_start/CLOCKS_PER_SEC, 1000*t_end/CLOCKS_PER_SEC,
    1000*(t_end-t_start)/CLOCKS_PER_SEC);
  #endif

  #ifdef PRINTOUT
  printf("\n\n");
  printChaosPool(pool);
  #endif

char ch = 'U';
printChaosPool(pool);
insertAtomicChar(&ch, pool);
insertAtomicChar(&ch, pool);
insertAtomicChar(&ch, pool);
insertAtomicChar(&ch, pool);
// insertAtomicChar(&ch, pool);
// insertAtomicChar(&ch, pool);
// insertAtomicChar(&ch, pool);
// insertAtomicChar(&ch, pool);
// insertAtomicChar(&ch, pool);
printChaosPool(pool);

  return 0;
}
