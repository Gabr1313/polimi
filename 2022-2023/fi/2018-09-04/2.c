#define ISTANT_LEN 12

typedef struct envConditions_s {
  float degree;
  int humidity;
  char istant[ISTANT_LEN];
  struct envConditions_s* next;
} envConditions_t;
