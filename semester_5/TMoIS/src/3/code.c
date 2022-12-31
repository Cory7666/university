#include <stdio.h>

int f(int* args)
{
  const int result = 3 * (args[2] - 2 * args[0]) + (args[1] - args[2] + 1) / 2;
  return result;
}

void f_pointers (int* result, int* args)
{
  volatile int tmp;
  int sign;

  *result = args[0] << 1;
  *result = args[2] - *result;
  *result = *result * 3;
  tmp = args[1] - args[2];
  ++tmp;
  sign = tmp & 0x80000000;
  tmp = tmp >> 1;
  tmp = tmp | sign;
  ++tmp;
  *result = *result  + tmp;
}

int main (void)
{
  volatile int arg1 = -0xFFFF, arg2 = 4, arg3 = 8, answer = 0;
  int args[] = {arg1, arg2, arg3};
  answer = f(args);
  printf("%d %d %d -> %d\n", args[0], args[1], args[2], answer);
  
  f_pointers(&answer, args);
  printf("%d %d %d -> %d\n", args[0], args[1], args[2], answer);
  return 0;
}
