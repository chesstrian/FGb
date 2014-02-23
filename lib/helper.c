#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "file.h"
#include "helper.h"
#include "utilities.h"

#define LIBMODE 1
#define CALL_FGB_DO_NOT_DEFINE
#include "call_fgb.h"

#define FGb_MAXI_BASE 100000

static Dpol input_basis[FGb_MAXI_BASE];
static I32 global_nb = -1;
// static Dpol output_basis[FGb_MAXI_BASE];

void process_grobner(char const *filename, int display, int step, int block) {
  char *buffer;

  if (get_file_content(filename, &buffer) == FILE_CONTENT_READ) {
    char *poly = NULL;
    char **polys = NULL;
    char const *comma = ",";

    char *mono = NULL;
    char **monos = NULL;
    char const *plus = "+";

    int length;

    remove_brakets(&buffer);
    polys = str_split(buffer, comma, &length);

    Dpol_INT prev;
    double t0;
    global_nb = 0;
    int const nb_vars = 10;
    char *vars[10] = { "x[1]", "x[2]", "x[3]", "x[4]", "x[5]", "x[6]", "x[7]", "x[8]", "x[9]", "x[10]" };

    if (polys) {
      FGB(enter)();
      FGB(init_urgent)(2, MAPLE_FGB_BIGNNI, "DRLDRL", 100000, 0);
      FGB(init)(1, 1, 0, log_output);
      {
        UI32 pr[] = { (UI32) (65521) };
        FGB(reset_coeffs)(1, pr);
      }
      {
        FGB(reset_expos)(10, 0, vars);
      }

      int i;
      for (i = 0; *(polys + i); ++i) {
        poly = str_trim(*(polys + i));
        monos = str_split(poly, plus, &length);

        if (monos) {
          prev = FGB(creat_poly)(length);
          input_basis[global_nb++] = prev;

          int j;
          for (j = 0; *(monos + j); ++j) {
            mono = str_trim(*(monos + j));
            fprintf(stdout, "Super monomial: %s.\n", mono);
          }
        }
      }
    }
  }
}
