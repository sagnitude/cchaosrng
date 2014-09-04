#ifndef utils__
#define utils__

double
estimateEntropyInData(char* data, int length);

char
rolloverXor(char ch, void* data, int length);

void
print_float_hex(float f);

void
print_double_hex(double f);

#endif
