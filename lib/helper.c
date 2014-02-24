#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "file.h"
#include "helper.h"

#define LIBMODE 1
#define CALL_FGB_DO_NOT_DEFINE
#include "call_fgb.h"

#define FGb_MAXI_BASE 100000

static Dpol input_basis[FGb_MAXI_BASE];
static I32 global_nb = -1;
static Dpol output_basis[FGb_MAXI_BASE];

void process_grobner(char const *filename, int display, int step, int block) {
  char const *comma = ",";
  char const *plus = "+";

  int length;
  char const *buffer = str_trim(remove_brakets(get_file_content(filename)));

  char **polynomials = str_split(buffer, comma, &length);

  if (polynomials) {
    int coefficient;

    Dpol_INT prev;
    double t0;
    global_nb = 0;
    int const nb_vars = 10;
    char *vars[10] = { "x[1]", "x[2]", "x[3]", "x[4]", "x[5]", "x[6]", "x[7]", "x[8]", "x[9]", "x[10]" };

    I32 e[10];

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

    char **monomials;

    int i = 0, j = 0;

    for (; *(polynomials + i); ++i) {
      monomials = str_split(str_trim(*(polynomials + i)), plus, &length);

      prev = FGB(creat_poly)(length); // Length is number of monomials in polinomial.
      input_basis[global_nb++] = prev;

      for (; *(monomials + j); ++j) {
        process_monomial(str_trim(*(monomials + j)), &coefficient);

        fprintf(stdout, "Coefficient: %d.\n", coefficient);

        break;
      }

      break;
    }
  }
}

void process_monomial(char const *monomial, int *coefficient) {
  fprintf(stdout, "Monomial: %s.\n", monomial);

  char const *times = "*";
  char const *caret = "^";

  int k;
  char **elements = str_split(str_trim(monomial), times, &k);
  char *element;

  for (k = 0; *(elements + k); ++k) {

    element = str_trim(*(elements + k));
    fprintf(stdout, "Elements: %s.\n", element);

    if (k == 0) {
      *coefficient = atoi(element);
      if (*coefficient == 0) {
        *coefficient = 1;
      }
    } else {

    }
  }
}
