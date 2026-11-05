#define MAX_OFFSET_MM 35.0f

float diminta(float speed_mms, float tran_ms) {
  return speed_mms * tran_ms / 1000.0f;
}

float nyata(float speed_mms, float tran_ms) {
  float s = diminta(speed_mms, tran_ms);
  if (s > MAX_OFFSET_MM) s = MAX_OFFSET_MM;
  if (s < -MAX_OFFSET_MM) s = -MAX_OFFSET_MM;
  return s;
}
