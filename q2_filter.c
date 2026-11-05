#include <stdbool.h>

typedef struct {
  int cls;        
  float conf;     
  long age_ms;    
  float bearing;  
  float dist;    
} det_t;

bool mau_ambil(det_t d) {
  return d.cls == 1 && d.age_ms < 1000 && d.conf >= 0.5f;
}
