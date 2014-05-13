#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void process_monomial(char *, I32[], char *[], int *);
void initialize_e(I32 *, int);
int getVirtualMemoryUsage();
int getPhisicalMemoryUsage();

void process_grobner(char const *filename, int n, int q, int display, int step, int block) {
  char const *comma = ",";
  char const *plus = "+";

  char *fileoutname = output_filename(q, n);
  FILE *fileout = fopen(fileoutname, "w");

  int n_polinomials;
  char *buffer = get_file_content(filename);
  remove_brakets(&buffer);
  str_trim(&buffer);

  char **polynomials = str_split(buffer, comma, &n_polinomials);

  if (polynomials) {
    clock_t time;
    int coefficient, n_monomials;

    Dpol_INT prev;
    double t0;
    global_nb = 0;
    const int nb_vars = n;
    char **vars = generate_vars(n);

    char **monomials;
    int i = 0, j, index, virtualMemory, phisicalMemory;

    FGB(enter)();
    FGB(init_urgent)(2, MAPLE_FGB_BIGNNI, "DRLDRL", 100000, 0);
    FGB(init)(1, 1, 0, log_output);
    {
      UI32 pr[] = { (UI32) (q) };
      FGB(reset_coeffs)(1, pr);
    }
    {
      FGB(reset_expos)(n, 0, vars);
    }

    I32 *e = malloc(sizeof(I32 *) * n);

    for (; *(polynomials + i); ++i) {
      char *polynomial = *(polynomials + i);
      str_trim(&polynomial);

      monomials = str_split(polynomial, plus, &n_monomials);

      prev = FGB(creat_poly)(n_monomials); // Length is number of monomials in polinomial.
      input_basis[global_nb++] = prev;

      index = 0;

      for (j = 0; *(monomials + j); ++j) {
        initialize_e(e, n);

        char *monomial = *(monomials + j);
        str_trim(&monomial);

        process_monomial(monomial, e, vars, &coefficient);

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
        fprintf(stderr, "[\n    ");
        fprintf(fileout, "[\n    ");
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

              if (j > 0) {
                fprintf(stderr, "+");
                fprintf(fileout, "+");
              }
              fprintf(stderr, "%d", Cfs[j]);
              fprintf(fileout, "%d", Cfs[j]);

              for (k = 0; k < nb_vars; k++)
                if (ei[k]) {
                  if (ei[k] == 1) {
                    fprintf(stderr, "*%s", vars[k]);
                    fprintf(fileout, "*%s", vars[k]);
                  } else {
                    fprintf(stderr, "*%s^%u", vars[k], ei[k]);
                    fprintf(fileout, "*%s^%u", vars[k], ei[k]);
                  }
                  is_one = 0;
                }
              if (is_one) {
                fprintf(stderr, "*1");
                fprintf(fileout, "*1");
              }
            }
          }

          if (i < (nb - 1)) {
            fprintf(stderr, ",\n    ");
            fprintf(fileout, ",\n    ");
          }
        }
        fprintf(stderr, "\n]\n");
        fprintf(fileout, "\n]\n");
      }
    }
    virtualMemory = getVirtualMemoryUsage();
    phisicalMemory = getPhisicalMemoryUsage();
    FGB(reset_memory)(); /* to reset Memory */
    FGB(exit)(); /* restore original GMP allocators */

    time = clock() - time;
    virtualMemory -= getVirtualMemoryUsage();
    phisicalMemory -= getPhisicalMemoryUsage();

    char *filestatsname = stats_filename(q, n);
    FILE *filestat = fopen(filestatsname, "w");

    fprintf(filestat, "%d %d %f %d #\n", q, n, t0, virtualMemory + phisicalMemory);

    fclose(filestat);
    fclose(fileout);
  }
}

char **generate_vars(int n) {
  char index[5];
  char **result = malloc(sizeof(char *) * 5 * n); // Five positions for x[i].

  int i;

  for (i = 0; i < n; ++i) {
    sprintf(index, "x[%d]", i + 1);
    *(result + i) = strdup(index);
  }

  return result;
}

void process_monomial(char *monomial, I32 e[], char *vars[], int *coefficient) {
  int k, l, length;

  char const *times = "*";
  char const *caret = "^";

  str_trim(&monomial);

  char **elements = str_split(monomial, times, &length);
  char *element;

  char **base_exp;
  int exp;

  for (k = 0; *(elements + k); ++k) {
    element = *(elements + k);
    str_trim(&element);

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

void initialize_e(I32 *e, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    e[i] = 0;
  }
}

int parseLine(char* line) {
  int i = strlen(line);
  while (*line < '0' || *line > '9')
    line++;
  line[i - 3] = '\0';
  i = atoi(line);
  return i;
}

int getVirtualMemoryUsage() { // Note: this value is in KB!
  FILE *file = fopen("/proc/self/status", "r");
  int result = -1;
  char line[128];

  while (fgets(line, 128, file) != NULL) {
    if (strncmp(line, "VmSize:", 7) == 0) {
      result = parseLine(line);
      break;
    }
  }
  fclose(file);
  return result;
}

int getPhisicalMemoryUsage() {
  FILE* file = fopen("/proc/self/status", "r");
  int result = -1;
  char line[128];

  while (fgets(line, 128, file) != NULL) {
    if (strncmp(line, "VmRSS:", 6) == 0) {
      result = parseLine(line);
      break;
    }
  }
  fclose(file);
  return result;
}
