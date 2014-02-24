#include <stdio.h>

#include "helper.h"
#include "call_fgb.h"

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <file> <display> <step> <block>.\n", argv[0]);
    return -1;
  }

  char const *filename = argv[1];

  int const kmax = 1;
  int want_display = argc > 2 ? atoi(argv[2]) : 0;
  int step0 = argc > 3 ? atoi(argv[3]) : -1;
  int bk0 = argc > 4 ? atoi(argv[4]) : 0;

  if (want_display) {
    fprintf(stdout, "Version FGb/int %d FGb/modp:%d\n\n", FGb_int_internal_version(), FGb_internal_version());
  }

  int k;

  for (k = 0; k < kmax; ++k) {
    int const dsp = k < kmax - 1 ? 0 : want_display;

    fprintf(stdout, "****************************** Compute gbasis mod p ******************************\n");
    /* compute modulo a small prime number  < 2^16, */
    process_grobner(filename, dsp, step0, bk0);
  }

  return 0;
}
