#include <stdio.h>
#include <stdlib.h>
#include "style.h"

#define MAPLE_FGB_BIGNNI 2
#ifndef LIBMODE
#define LIBMODE 2
#endif /* ndef LIBMODE */

#if LIBMODE==2
#define FGB(fn) FGb_int_ ## fn
#else
#define FGB(fn) FGb_ ## fn
#endif /*  LIBMODE==2 */


typedef void* Expos;
typedef void* Dpol;
typedef Dpol Dpol_INT;

#include "protocol_maple.h"

extern String FGB(alloc)(UI32 n);
extern void FGB(reset_memory)();
extern void FGB(init_urgent)(UI32 szDom,UI32 szNNI,String expos,UI32 maxi_FGb_BASE,Boolean rec);
extern void FGB(init)(Boolean wp,Boolean wp2,Boolean wc,FILE* file);
extern Dpol FGB(creat_poly)(UI32 n);
extern Expos FGB(assign_expos)(I32* buf,I32 n);
extern void FGB(reset_expos)(UI32 bl1,UI32 bl2,char** liste);
#if LIBMODE EQ 2
extern void FGB(reset_coeffs)(UI32 n);
extern void FGB(set_coeff_raw)(Dpol p,UI32 i0,UI32* buf,UI32 sz);
extern void FGB(enter_INT)();
extern void FGB(exit_INT)();
#include "gmp.h"
extern mpz_ptr* FGB(export_poly_INT_gmp)(I32 n,I32 m,I32* E,Dpol_INT p);
#else
extern void FGB(reset_coeffs)(UI32 n,UI32* p);
extern void FGB(set_coeff_I32)(Dpol p,UI32 i0,I32 buf);
extern void FGB(set_expos_d)(Dpol p,UI32 i0,Expos buf);
extern void FGB(full_sort_poly)(Dpol p);
extern I32 FGB(export_poly)(I32 n,I32 m,I32* E,I32* P,Dpol p);
#endif /*  LIBMODE EQ 2 */
extern UI32 FGB(groebner)(Dpol* p,UI32 n,Dpol* q,Boolean mini,UI32 elim,double* t0,const UI32 bk0,const UI32 pas0,const Boolean elim0,FGB_Comp_Desc env);
extern UI32 FGB(hilbert)(Dpol* p,const UI32 n_orig,Dpol* q,Boolean mini,UI32 elim,double* t0,UI32 bk0,UI32 pas0,Boolean elim0);
extern UI32 FGB(nb_terms)(Dpol p);
extern void FGB(set_expos2)(Dpol p,UI32 i0,I32* e,const UI32 nb);
extern void FGB(full_sort_poly2)(Dpol p);
extern I32 FGB(export_poly_INT)(I32 n,I32 m,I32* E,UI32* P,UI32* Plim,Dpol p,UI32* B);

#if LIBMODE EQ 2
#define FGb_int_enter FGb_int_enter_INT
#define FGb_int_exit  FGb_int_exit_INT
#else /*  LIBMODE EQ 2 */
static void inline FGb_nop() {}
#define FGb_enter FGb_nop
#define FGb_exit FGb_nop
#endif /*  LIBMODE EQ 2 */


#ifndef CALL_FGB_DO_NOT_DEFINE
FILE* log_output;
void info_Maple(const char* s)
{
  fprintf(stderr,"%s",s);
  fflush(stderr);
}

void FGb_int_error_Maple(const char* s)
{
  fprintf(stderr,"%s",s);
  fflush(stderr);
  exit(3);
}

void FGb_error_Maple(const char* s)
{
  FGb_int_error_Maple(s);
}

void FGb_checkInterrupt()
{
}

void FGb_int_checkInterrupt()
{
}

void FGb_push_gmp_alloc_fnct(void *(*alloc_func) (size_t),
			     void *(*realloc_func) (void *, size_t, size_t),
			     void (*free_func) (void *, size_t))
{
}

void FGb_pop_gmp_alloc_fnct()
{
}
#else
extern FILE* log_output;
#endif /* ndef CALL_FGB_DO_NOT_DEFINE */
