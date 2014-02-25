#include <stdio.h>

#include "helper.h"
#include "call_fgb.h"

int main(int argc, char **argv) {
  if (argc < 5) {
    fprintf(stderr, "Usage: %s <file> <n> <q> <display> <step> <block>.\n", argv[0]);
    return -1;
  }

  char const *filename = argv[1];
  int n = atoi(argv[2]);
  int q = atoi(argv[3]);

  int const kmax = 1;
  int want_display = argc > 4 ? atoi(argv[4]) : 0;
  int step0 = argc > 5 ? atoi(argv[5]) : -1;
  int bk0 = argc > 6 ? atoi(argv[6]) : 0;

  if (want_display) {
    fprintf(stdout, "Version FGb/int %d FGb/modp:%d\n\n", FGb_int_internal_version(), FGb_internal_version());
  }

  int k;

  for (k = 0; k < kmax; ++k) {
    int const dsp = k < kmax - 1 ? 0 : want_display;

    fprintf(stdout, "****************************** Compute gbasis mod p ******************************\n");
    /* compute modulo a small prime number  < 2^16, */
    process_grobner(filename, n, q, dsp, step0, bk0);
  }

  return 0;
}
