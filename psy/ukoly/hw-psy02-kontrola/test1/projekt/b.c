#include "b.h"

float fce_b(int s, float x) {
  int i;
  float out=x;

  for (i=0; i<s; i++) {
    out=out*(out+x);
  }

  return out;
}