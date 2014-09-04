#include "utils.h"

double
estimateEntropyInData(char* data, int length){
  //
}

char
rolloverXor(char ch, void* data, int length){
  for(int i = 0; i < length; i++){
    *((char*)data++) ^= ch;
  }
  return *((char*)data-1);
}

void
print_float_hex(float f){
  union{
    float f;
    int i
  }test;
  test.f=f;
  printf("%#010x\n",test.i);
}

void
print_double_hex(double f){
  union{
    double f;
    int i
  }test;
  test.f=f;
  printf("%#010x\n",test.i);
}
