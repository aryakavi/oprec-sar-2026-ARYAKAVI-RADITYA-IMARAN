#include <stdbool.h>

int deg_to_us(int deg) {
  if (deg < 0) deg = 0;
  if (deg > 180) deg = 180;
  return 500 + 1900 * deg / 180;
}
