#include <stdbool.h>
#include <math.h>

#define TTL_MS 1000
#define CAM_LEFT_MM 50.0f

typedef enum { DUMMY, KORBAN, RERUNTUHAN, SAFEZONE } kelas_t;

typedef struct {
  kelas_t kelas;
  long age_ms;
  float conf;
  float bearing;
  float dist_mm;
} vision_t;

float ke_badan(float bearing_kamera, float dist_mm, float trim_derajat) {
  float b = bearing_kamera + trim_derajat;
  if (dist_mm > 1.0f)
    b -= atan2f(CAM_LEFT_MM, dist_mm) * 57.2958f;
  return b;
}

bool boleh_ambil(vision_t d, bool ada_korban_dengan_jarak) {
  if (d.kelas != KORBAN) return false;
  if (d.age_ms >= TTL_MS) return false;
  if (d.conf < 0.5f) return false;
  if (d.dist_mm <= 0.0f && ada_korban_dengan_jarak) return false;
  return true;
}
