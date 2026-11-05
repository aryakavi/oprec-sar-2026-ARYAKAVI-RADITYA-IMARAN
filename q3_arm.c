#include <math.h>

#define L1_MM 120.0f
#define L2_MM  60.0f

void fk(float q1, float q2, float *x, float *z) {
  *x = L1_MM * cosf(q1) + L2_MM * cosf(q1 + q2);
  *z = L1_MM * sinf(q1) + L2_MM * sinf(q1 + q2);
}
