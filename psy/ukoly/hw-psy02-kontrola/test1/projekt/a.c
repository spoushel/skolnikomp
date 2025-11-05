#include "a.h"
#include "b.h"

#include <math.h>

int fce_a(int x) {
  return (int)round( (x+prom_a)*real_a);
}

int main() {
  float x;

  if (scanf("%f", &x)==1) {
    printf("%f\n", fce_b(fce_a((int)round(x)), x/2));
  } 
  return 0;
}
