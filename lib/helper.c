#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "str.h"
#include "file.h"

#define LIBMODE 1
#define CALL_FGB_DO_NOT_DEFINE
#include "call_fgb.h"

#include "helper.h"

#define FGb_MAXI_BASE 100000

static Dpol input_basis[FGb_MAXI_BASE];
static I32 global_nb = -1;
static Dpol output_basis[FGb_MAXI_BASE];

void process_monomial(char const *, I32[], char *[], int *);

void process_grobner(char const *filename, int display, int step, int block) {
  char const *comma = ",";
  char const *plus = "+";

  int n_polinomials;
  char const *buffer = str_trim(remove_brakets(get_file_content(filename)));

  char **polynomials = str_split(buffer, comma, &n_polinomials);

  if (polynomials) {
    clock_t time;
    int coefficient, n_monomials;

    Dpol_INT prev;
    double t0;
    global_nb = 0;
    // const int nb_vars = 10;
    // const int nb_vars = 5;
    const int nb_vars = 3;
    // char *vars[10] = { "w[1]", "w[2]", "w[3]", "w[4]", "w[5]", "w[6]", "w[7]", "w[8]", "w[9]", "w[10]" };
    // char *vars[5] = { "x1", "x2", "x3", "x4", "x5" };
    char *vars[3] = { "x", "y", "z" };

    FGB(enter)();
    FGB(init_urgent)(2, MAPLE_FGB_BIGNNI, "DRLDRL", 100000, 0);
    FGB(init)(1, 1, 0, log_output);
    {
      UI32 pr[] = { (UI32) (65521) };
      FGB(reset_coeffs)(1, pr);
    }
    {
      FGB(reset_expos)(3, 0, vars);
    }

    char **monomials;

    int i = 0, j, index;

    for (; *(polynomials + i); ++i) {
      monomials = str_split(str_trim(*(polynomials + i)), plus, &n_monomials);

      prev = FGB(creat_poly)(n_monomials); // Length is number of monomials in polinomial.
      input_basis[global_nb++] = prev;

      index = 0;

      for (j = 0; *(monomials + j); ++j) {
        // I32 e[10] = { 0 };
        // I32 e[5] = { 0 };
        I32 e[3] = { 0 };

        process_monomial(str_trim(*(monomials + j)), e, vars, &coefficient);

        {
          FGB(set_expos2)(prev, index, e, nb_vars);
        }

        FGB(set_coeff_I32)(prev, index++, coefficient);
      }

      FGB(full_sort_poly2)(prev);

    }

    {
      time = clock();
      int nb;
      const int n_input = n_polinomials;
      struct sFGB_Comp_Desc Env;
      FGB_Comp_Desc env = &Env;
      env->_compute = FGB_COMPUTE_GBASIS;
      env->_nb = 0;
      env->_force_elim = 0;
      env->_off = 0;

      env->_index = 500000;
      env->_zone = 0;
      env->_memory = 0;

      nb = FGB(groebner)(input_basis, n_input, output_basis, 1, 0, &t0, block, step, 0, env);

      if (display) {
        int i;
        fprintf(stderr, "[\n");
        for (i = 0; i < nb; i++) {
#if 0
          /* Use this function to print the result */
          FGB(see_Dpol)(output_basis[i]);
#endif /*  0 */

          /* Import the internal representation of each polynomial computed by FGb */
          {
            const I32 nb_mons = FGB(nb_terms)(output_basis[i]); /* Number of Monomials */
            UI32* Mons = (UI32*) (malloc(sizeof(UI32) * nb_vars * nb_mons));
            I32* Cfs = (I32*) (malloc(sizeof(I32) * nb_mons));
            int code = FGB(export_poly)(nb_vars, nb_mons, Mons, Cfs, output_basis[i]);
            I32 j;
            for (j = 0; j < nb_mons; j++) {

              I32 k, is_one = 1;
              UI32* ei = Mons + j * nb_vars;

              if (j > 0)
                fprintf(stderr, "+");
              fprintf(stderr, "%d", Cfs[j]);

              for (k = 0; k < nb_vars; k++)
                if (ei[k]) {
                  if (ei[k] == 1)
                    fprintf(stderr, "*%s", vars[k]);
                  else
                    fprintf(stderr, "*%s^%u", vars[k], ei[k]);
                  is_one = 0;
                }
              if (is_one)
                fprintf(stderr, "*1");
            }
          }

          if (i < (nb - 1))
            fprintf(stderr, ",");

        }
        fprintf(stderr, "]\n");
      }
    }
    FGB(reset_memory)(); /* to reset Memory */
    FGB(exit)(); /* restore original GMP allocators */

    time = clock() - time;
    fprintf(stdout, "Takes %ju clicks (%f seconds).\n", time, ((float) time) / CLOCKS_PER_SEC);
  }
}

void process_monomial(char const *monomial, I32 e[], char *vars[], int *coefficient) {
  int k, l, length;

  char const *times = "*";
  char const *caret = "^";

  char **elements = str_split(str_trim(monomial), times, &length);
  char *element;

  char **base_exp;
  int exp;

  for (k = 0; *(elements + k); ++k) {
    element = str_trim(*(elements + k));

    if (k == 0) {
      *coefficient = atoi(element);
      if (*coefficient == 0) {
        *coefficient = 1;
      } else {
        continue;
      }
    }

    base_exp = str_split(element, caret, &length);

    for (l = 0; strcmp(*(base_exp), *(vars + l)) != 0; ++l)
      ;

    if (length == 1) {
      exp = 1;
    } else {
      exp = atoi(*(base_exp + 1));
    }

    e[l] = exp;
  }
}
