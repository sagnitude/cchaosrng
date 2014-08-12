#include <stdio.h>
#include <stdlib.h>
#include "cm.h"
#include "cp.h"

#define MAINSERVER

int
main(int argc, char** argv){
  ChaosPool* pool = ChaosPoolBySize(2, 3);
  initializeChaosPoolWithRandomValues(pool);

  /*
  reset:
  free(pool);
  ChaosPool* pool = ChaosPoolBySize(2, 3);
  initializeChaosPoolWithRandomValues(pool);
  */

  printChaosPool(pool);
  evolve(1000, pool);

  printf("\n\n");
  printChaosPool(pool);

  return 0;
}
