#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("letezo parancs visszateresi erteke: %d\n", system("ls"));
  printf("nem letezo parancs visszateresi erteke: %d\n", system("nemletezo"));
  return 0;
}
