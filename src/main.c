#include <stdio.h>
#include <stdlib.h>
#include "cm.h"
#include "cp.h"
#include <time.h>

#define MAINSERVER
// #define PRINTOUT
#define PROFILE

int
main(int argc, char** argv){
  ChaosPool* pool = ChaosPoolBySize(5, 3);
  initializeChaosPoolWithRandomValues(pool);

  /*
  reset:
  free(pool);
  ChaosPool* pool = ChaosPoolBySize(2, 3);
  initializeChaosPoolWithRandomValues(pool);
  */

  #ifdef PRINTOUT
  printChaosPool(pool);
  #endif

  #ifdef PROFILE
  time_t t_start, t_end;
  t_start = time(NULL);
  #endif

  evolve(100000, pool);

  #ifdef PROFILE
  t_end = time(NULL) ;
  printf("calculating %d points\ntime elasped from %ld to %ld: %ld seconds\n", pool->overallSize, t_start, t_end, t_end-t_start);
  #endif

  #ifdef PRINTOUT
  printf("\n\n");
  printChaosPool(pool);
  #endif

  return 0;
}
