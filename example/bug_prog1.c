/* Example: we compute a Groebner Basis or NormalForm over the integers */
 
/* The following macro should be 2 to call FGb over the integers */
#define LIBMODE 2

/* To remove verbosity define the following macro to 1 and define your own I/O function (see at the end of this file) */
#define USE_MY_OWN_IO 0


/* ---------------------------------------------------------------------- */

#if USE_MY_OWN_IO
#define CALL_FGB_DO_NOT_DEFINE
#endif /*  USE_MY_OWN_IO */

#include "call_fgb.h"

/* Only needed if GMP is used to import the coefficients */
#include "gmp.h"

#define FGb_MAXI_BASE 100000

static Dpol input_basis[FGb_MAXI_BASE];
static I32 global_nb=-1;
static Dpol output_basis[FGb_MAXI_BASE];

void compute_prog1(int want_display,int step0, int bk0, int want_nf)
{
  const int nb_vars=6;
  Dpol_INT prev;
  double t0;  global_nb=0;
  char* vars[6]={"x1","x2","x3","x4","x5","x6"}; /* name of the variables (can be anything) */

  FGB(enter)(); /* First thing to do : GMP origmal memory allocators are saved */


  FGB(init_urgent)(4,2,"DRLDRL",100000,0); /* Do not change the following parameters
					      4 is the number of bytes of each coefficients 
					        so the maximal prime is <2^32
					      2 is the number of bytes of each exponent : 
					        it means that each exponent should be < 2^15 */
  FGB(init)(1,1,0,log_output);/* do not change */
  FGB(reset_coeffs)(1); /* We compute in Q[x1,x2,x3,x4,x5,x6] */

  {
    FGB(reset_expos)(nb_vars,0,vars); /* Define the monomial ordering: DRL(k1,k2) where 
					 k1 is the size of the 1st block of variables 
					 k2 is the size of the 2nd block of variables 
					 and k1+k2 is the total number of variables
				      */
  }
  /* Compute a Groebner Basis of [f0,f1,f2,...,f7] 
     We have first to export the 8 polynomials to FGb
     ==================================================
     Creat the first polynomial  */
  prev=FGB(creat_poly)(2); /* number of monomials in the polynomial (here 2 so that poly = monom0 + monom1) */
  input_basis[global_nb++]=prev;  /* fill the array of input polynomials with the first polynomial */

  /* Creat the first monomial  = coef * terme */
  {
    /* Creat the first term: power product x1^e[1]*...*xn^e[n] */
    I32 e[6]={0,1,0,1,0,1}; /* x2*x4*x6 */
    FGB(set_expos2)(prev,0,e,nb_vars); /* arguments:
					  0: index of the first monomial
					  nb_vars: the number of variables
				  */
  }
  /* Creat the first coefficient (here -1) */
  {
    mpz_t u;
    mpz_init_set_str(u,"-1", 10);
    FGB(set_coeff_gmp)(prev,0,u); /* arguments:
				    0: index of the first coefficient
				    2: gmp number
				  */
  }
  /* Creat the second term: power product x1^e[1]*...*xn^e[n] */
  {
    I32 e[6]={0,0,1,1,1,0}; /* x3*x4*x5 */
    FGB(set_expos2)(prev,1,e,nb_vars); /* second monomial */
  }
  /* Coefficient of the second monomial */
  {
    mpz_t u;
    mpz_init_set_str(u,"1", 10);
    FGB(set_coeff_gmp)(prev,1,u); /* arguments:
				    1: index of the second coefficient
				    2: gmp number
				  */
  }
  FGB(full_sort_poly2)(prev);/* it is recommended to sort each polynomial */

  /* We creat the second polynomial */
  prev=FGB(creat_poly)(6);
  input_basis[global_nb++]=prev;
  {
    I32 e[6]={0,1,0,0,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  {
    I32 u[2]={-1,10};
    FGB(set_coeff_raw)(prev,0,u,2); /* another way to export of bignum (not recommended) */
  }
  {
    I32 e[6]={0,0,1,0,0,0};
    FGB(set_expos2)(prev,1,e,6);
  }
  {
    I32 u[2]={1,10};
    FGB(set_coeff_raw)(prev,1,u,2);
  }
  {
    I32 e[6]={0,0,0,0,2,0};
    FGB(set_expos2)(prev,2,e,6);
  }
  {
    I32 u[2]={-1,9};
    FGB(set_coeff_raw)(prev,2,u,2);
  }
  {
    I32 e[6]={0,0,0,0,0,2};
    FGB(set_expos2)(prev,3,e,6);
  }
  {
    I32 u[2]={1,9};
    FGB(set_coeff_raw)(prev,3,u,2);
  }
  {
    I32 e[6]={0,0,0,1,1,0};
    FGB(set_expos2)(prev,4,e,6);
  }
  {
    I32 u[2]={1,18};
    FGB(set_coeff_raw)(prev,4,u,2);
  }
  {
    I32 e[6]={0,0,0,1,0,1};
    FGB(set_expos2)(prev,5,e,6);
  }
  {
    I32 u[2]={-1,18};
    FGB(set_coeff_raw)(prev,5,u,2);
  }
  FGB(full_sort_poly2)(prev);

  /* We creat the third polynomial */
  prev=FGB(creat_poly)(2);
  input_basis[global_nb++]=prev;
  {
    I32 e[6]={0,0,0,0,0,0};
    FGB(set_expos2)(prev,0,e,6);
  }
  {
    I32 u[6]={-1,-1944645207,1306237158,272831181,1468426720,3};
    FGB(set_coeff_raw)(prev,0,u,6);
  }
  {
    I32 e[6]={0,0,0,2,0,0};
    FGB(set_expos2)(prev,1,e,6);
  }
  {
    I32 u[6]={1,0,0,0,-192937984,3};
    FGB(set_coeff_raw)(prev,1,u,6);
  }
  FGB(full_sort_poly2)(prev);

  /* We creat the 4th polynomial */
  prev=FGB(creat_poly)(4);
  input_basis[global_nb++]=prev;
  {
    I32 e[6]={0,0,0,0,0,0};
    FGB(set_expos2)(prev,0,e,6);
  }
  {
    I32 u[2]={-1,1};
    FGB(set_coeff_raw)(prev,0,u,2);
  }
  {
    I32 e[6]={0,0,0,2,0,0};
    FGB(set_expos2)(prev,1,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,1,u,2);
  }
  {
    I32 e[6]={0,0,0,0,2,0};
    FGB(set_expos2)(prev,2,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,2,u,2);
  }
  {
    I32 e[6]={0,0,0,0,0,2};
    FGB(set_expos2)(prev,3,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,3,u,2);
  }
  FGB(full_sort_poly2)(prev);

  /* We creat the 5th polynomial */
  prev=FGB(creat_poly)(3);
  input_basis[global_nb++]=prev;
  {
    I32 e[6]={1,0,0,1,0,0};
    FGB(set_expos2)(prev,0,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,0,u,2);
  }
  {
    I32 e[6]={0,1,0,0,1,0};
    FGB(set_expos2)(prev,1,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,1,u,2);
  }
  {
    I32 e[6]={0,0,1,0,0,1};
    FGB(set_expos2)(prev,2,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,2,u,2);
  }
  FGB(full_sort_poly2)(prev);

  /* We creat the 6th polynomial */
  prev=FGB(creat_poly)(15);
  input_basis[global_nb++]=prev;
  {
    I32 e[6]={0,0,0,0,0,0};
    FGB(set_expos2)(prev,0,e,6);
  }
  {
    I32 u[2]={1,1944};
    FGB(set_coeff_raw)(prev,0,u,2);
  }
  {
    I32 e[6]={1,1,0,1,1,0};
    FGB(set_expos2)(prev,1,e,6);
  }
  {
    I32 u[2]={-1,200};
    FGB(set_coeff_raw)(prev,1,u,2);
  }
  {
    I32 e[6]={1,0,1,1,0,1};
    FGB(set_expos2)(prev,2,e,6);
  }
  {
    I32 u[2]={-1,200};
    FGB(set_coeff_raw)(prev,2,u,2);
  }
  {
    I32 e[6]={0,1,1,0,1,1};
    FGB(set_expos2)(prev,3,e,6);
  }
  {
    I32 u[2]={-1,200};
    FGB(set_coeff_raw)(prev,3,u,2);
  }
  {
    I32 e[6]={1,0,0,0,0,0};
    FGB(set_expos2)(prev,4,e,6);
  }
  {
    I32 u[2]={-1,900};
    FGB(set_coeff_raw)(prev,4,u,2);
  }
  {
    I32 e[6]={0,0,0,2,0,0};
    FGB(set_expos2)(prev,5,e,6);
  }
  {
    I32 u[2]={-1,2025};
    FGB(set_coeff_raw)(prev,5,u,2);
  }
  {
    I32 e[6]={2,0,0,0,0,0};
    FGB(set_expos2)(prev,6,e,6);
  }
  {
    I32 u[2]={1,100};
    FGB(set_coeff_raw)(prev,6,u,2);
  }
  {
    I32 e[6]={0,2,0,0,0,0};
    FGB(set_expos2)(prev,7,e,6);
  }
  {
    I32 u[2]={1,100};
    FGB(set_coeff_raw)(prev,7,u,2);
  }
  {
    I32 e[6]={0,0,2,0,0,0};
    FGB(set_expos2)(prev,8,e,6);
  }
  {
    I32 u[2]={1,100};
    FGB(set_coeff_raw)(prev,8,u,2);
  }
  {
    I32 e[6]={0,1,0,1,1,0};
    FGB(set_expos2)(prev,9,e,6);
  }
  {
    I32 u[2]={1,900};
    FGB(set_coeff_raw)(prev,9,u,2);
  }
  {
    I32 e[6]={0,0,1,1,0,1};
    FGB(set_expos2)(prev,10,e,6);
  }
  {
    I32 u[2]={1,900};
    FGB(set_coeff_raw)(prev,10,u,2);
  }
  {
    I32 e[6]={2,0,0,2,0,0};
    FGB(set_expos2)(prev,11,e,6);
  }
  {
    I32 u[2]={-1,100};
    FGB(set_coeff_raw)(prev,11,u,2);
  }
  {
    I32 e[6]={1,0,0,2,0,0};
    FGB(set_expos2)(prev,12,e,6);
  }
  {
    I32 u[2]={1,900};
    FGB(set_coeff_raw)(prev,12,u,2);
  }
  {
    I32 e[6]={0,2,0,0,2,0};
    FGB(set_expos2)(prev,13,e,6);
  }
  {
    I32 u[2]={-1,100};
    FGB(set_coeff_raw)(prev,13,u,2);
  }
  {
    I32 e[6]={0,0,2,0,0,2};
    FGB(set_expos2)(prev,14,e,6);
  }
  {
    I32 u[2]={-1,100};
    FGB(set_coeff_raw)(prev,14,u,2);
  }
  FGB(full_sort_poly2)(prev);

  /* We creat the 7th polynomial */
  prev=FGB(creat_poly)(28);
  input_basis[global_nb++]=prev;
  {
    I32 e[6]={0,0,0,0,0,0};
    FGB(set_expos2)(prev,0,e,6);
  }
  {
    I32 u[2]={1,405};
    FGB(set_coeff_raw)(prev,0,u,2);
  }
  {
    I32 e[6]={1,1,0,1,1,0};
    FGB(set_expos2)(prev,1,e,6);
  }
  {
    I32 u[2]={-1,200};
    FGB(set_coeff_raw)(prev,1,u,2);
  }
  {
    I32 e[6]={1,0,1,1,0,1};
    FGB(set_expos2)(prev,2,e,6);
  }
  {
    I32 u[2]={-1,200};
    FGB(set_coeff_raw)(prev,2,u,2);
  }
  {
    I32 e[6]={0,1,1,0,1,1};
    FGB(set_expos2)(prev,3,e,6);
  }
  {
    I32 u[2]={-1,200};
    FGB(set_coeff_raw)(prev,3,u,2);
  }
  {
    I32 e[6]={1,0,0,0,0,0};
    FGB(set_expos2)(prev,4,e,6);
  }
  {
    I32 u[2]={1,360};
    FGB(set_coeff_raw)(prev,4,u,2);
  }
  {
    I32 e[6]={0,1,0,0,0,0};
    FGB(set_expos2)(prev,5,e,6);
  }
  {
    I32 u[2]={-1,180};
    FGB(set_coeff_raw)(prev,5,u,2);
  }
  {
    I32 e[6]={0,0,1,0,0,0};
    FGB(set_expos2)(prev,6,e,6);
  }
  {
    I32 u[2]={-1,180};
    FGB(set_coeff_raw)(prev,6,u,2);
  }
  {
    I32 e[6]={0,0,0,2,0,0};
    FGB(set_expos2)(prev,7,e,6);
  }
  {
    I32 u[2]={-1,324};
    FGB(set_coeff_raw)(prev,7,u,2);
  }
  {
    I32 e[6]={0,0,0,0,2,0};
    FGB(set_expos2)(prev,8,e,6);
  }
  {
    I32 u[2]={-1,81};
    FGB(set_coeff_raw)(prev,8,u,2);
  }
  {
    I32 e[6]={0,0,0,0,0,2};
    FGB(set_expos2)(prev,9,e,6);
  }
  {
    I32 u[2]={-1,81};
    FGB(set_coeff_raw)(prev,9,u,2);
  }
  {
    I32 e[6]={2,0,0,0,0,0};
    FGB(set_expos2)(prev,10,e,6);
  }
  {
    I32 u[2]={1,100};
    FGB(set_coeff_raw)(prev,10,u,2);
  }
  {
    I32 e[6]={0,2,0,0,0,0};
    FGB(set_expos2)(prev,11,e,6);
  }
  {
    I32 u[2]={1,100};
    FGB(set_coeff_raw)(prev,11,u,2);
  }
  {
    I32 e[6]={0,0,2,0,0,0};
    FGB(set_expos2)(prev,12,e,6);
  }
  {
    I32 u[2]={1,100};
    FGB(set_coeff_raw)(prev,12,u,2);
  }
  {
    I32 e[6]={0,1,0,1,1,0};
    FGB(set_expos2)(prev,13,e,6);
  }
  {
    I32 u[2]={-1,360};
    FGB(set_coeff_raw)(prev,13,u,2);
  }
  {
    I32 e[6]={0,0,1,1,0,1};
    FGB(set_expos2)(prev,14,e,6);
  }
  {
    I32 u[2]={-1,360};
    FGB(set_coeff_raw)(prev,14,u,2);
  }
  {
    I32 e[6]={0,0,1,0,1,1};
    FGB(set_expos2)(prev,15,e,6);
  }
  {
    I32 u[2]={1,180};
    FGB(set_coeff_raw)(prev,15,u,2);
  }
  {
    I32 e[6]={1,0,0,1,1,0};
    FGB(set_expos2)(prev,16,e,6);
  }
  {
    I32 u[2]={1,180};
    FGB(set_coeff_raw)(prev,16,u,2);
  }
  {
    I32 e[6]={0,1,0,0,1,1};
    FGB(set_expos2)(prev,17,e,6);
  }
  {
    I32 u[2]={1,180};
    FGB(set_coeff_raw)(prev,17,u,2);
  }
  {
    I32 e[6]={1,0,0,1,0,1};
    FGB(set_expos2)(prev,18,e,6);
  }
  {
    I32 u[2]={1,180};
    FGB(set_coeff_raw)(prev,18,u,2);
  }
  {
    I32 e[6]={2,0,0,2,0,0};
    FGB(set_expos2)(prev,19,e,6);
  }
  {
    I32 u[2]={-1,100};
    FGB(set_coeff_raw)(prev,19,u,2);
  }
  {
    I32 e[6]={1,0,0,2,0,0};
    FGB(set_expos2)(prev,20,e,6);
  }
  {
    I32 u[2]={-1,360};
    FGB(set_coeff_raw)(prev,20,u,2);
  }
  {
    I32 e[6]={0,2,0,0,2,0};
    FGB(set_expos2)(prev,21,e,6);
  }
  {
    I32 u[2]={-1,100};
    FGB(set_coeff_raw)(prev,21,u,2);
  }
  {
    I32 e[6]={0,0,2,0,0,2};
    FGB(set_expos2)(prev,22,e,6);
  }
  {
    I32 u[2]={-1,100};
    FGB(set_coeff_raw)(prev,22,u,2);
  }
  {
    I32 e[6]={0,0,0,1,1,0};
    FGB(set_expos2)(prev,23,e,6);
  }
  {
    I32 u[2]={1,324};
    FGB(set_coeff_raw)(prev,23,u,2);
  }
  {
    I32 e[6]={0,1,0,0,2,0};
    FGB(set_expos2)(prev,24,e,6);
  }
  {
    I32 u[2]={1,180};
    FGB(set_coeff_raw)(prev,24,u,2);
  }
  {
    I32 e[6]={0,0,1,0,0,2};
    FGB(set_expos2)(prev,25,e,6);
  }
  {
    I32 u[2]={1,180};
    FGB(set_coeff_raw)(prev,25,u,2);
  }
  {
    I32 e[6]={0,0,0,0,1,1};
    FGB(set_expos2)(prev,26,e,6);
  }
  {
    I32 u[2]={-1,162};
    FGB(set_coeff_raw)(prev,26,u,2);
  }
  {
    I32 e[6]={0,0,0,1,0,1};
    FGB(set_expos2)(prev,27,e,6);
  }
  {
    I32 u[2]={1,324};
    FGB(set_coeff_raw)(prev,27,u,2);
  }
  FGB(full_sort_poly2)(prev);

  /* We creat the 8th polynomial */
  prev=FGB(creat_poly)(4);
  input_basis[global_nb++]=prev;
  {
    I32 e[6]={0,0,0,0,0,0};
    FGB(set_expos2)(prev,0,e,6);
  }
  {
    I32 u[2]={-1,1};
    FGB(set_coeff_raw)(prev,0,u,2);
  }
  {
    I32 e[6]={2,0,0,0,0,0};
    FGB(set_expos2)(prev,1,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,1,u,2);
  }
  {
    I32 e[6]={0,2,0,0,0,0};
    FGB(set_expos2)(prev,2,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,2,u,2);
  }
  {
    I32 e[6]={0,0,2,0,0,0};
    FGB(set_expos2)(prev,3,e,6);
  }
  {
    I32 u[2]={1,1};
    FGB(set_coeff_raw)(prev,3,u,2);
  }
  FGB(full_sort_poly2)(prev); /* sort the last polynomial according the selected monomial ordering */

  {
    int np=0;
    const int n_input=(want_nf ? 8 : 6); /* number of input polynomials  */
    int nb;
    struct sFGB_Comp_Desc Env;
    FGB_Comp_Desc env=&Env;
    /* The following function can be used to compute Gb, NormalForms, RR, ... 
       Here we want to compute a Groebner Basis or a NormalForm */
    if (want_nf)
      {
	env->_compute=FGB_COMPUTE_GBASIS_NF;
	env->_nb=2; /* If we want to compute a normalForm : 
		       [f0,f1,...,f7] is the list of input polynomials 
		       If nenv->_nb=2 it means that we want to compute a normalForm of [f0,f1] wrt to G=[f2,f3,...,f7] 
		       Please note that G should be a Groebner Basis */
      }
    else
      {
	env->_compute=FGB_COMPUTE_GBASIS;
	env->_nb=0;
      }
    env->_force_elim=0; /* if force_elim=1 then return only the result of the elimination 
			   (need to define a monomial ordering DRL(k1,k2) with k2>0 ) */
    env->_off=0;        /* use to select another subset of prime numbers */
    env->_index=1000000; /* This is is the maximal size of the matrices generated by F4 
			  you can increase this value according to your memory */
    env->_zone=0;        /* should be 0 */
    env->_memory=0;      /* should be 0 */

    step0=-1; /* step0 : this is the number primes for the first step
                if step0<0 then this parameter is automatically set by the library
	      */

    /* Other parameters :
       t0 is the CPU time (reference to a double)
       bk0 : should be 0 
    */
    nb=FGB(groebner)(input_basis,n_input,output_basis,1,0,&t0,bk0,step0,0,env);
    /* The value nb returned by the library is the number of polynomials */
    if (want_display)
      {
	int i=0;
	if (want_nf)
	  {
	    fprintf(stderr,"%d pseudo normalForm have been computed\n[\n",nb/2);
	    i=1;
	    /* In that case: the output is [c1,q1,c2,q2,...] where ci is a coefficient of the pseudo NormalForm (see after) */
	  }
	else
	  fprintf(stderr,"%d polys in gbasis\n[\n",nb);

	for(;i<nb;i+=1+want_nf)
	  {
#if 0
	    /* Use this internal FGb fuction to print the result */
	    see_Dpol_INT(output_basis[i]);
#endif /*  0 */


	    /* Import the internal representation of each polynomial computed by FGb */
	    {
	      const I32 nb_mons=FGB(nb_terms)(output_basis[i]); /* Number of Monomials */
	      UI32* Mons=(UI32*)(malloc(sizeof(UI32)*nb_vars*nb_mons));
	      mpz_ptr* cfs=FGB(export_poly_INT_gmp)(nb_vars,nb_mons,Mons,output_basis[i]);
	      I32 j;
	      if (want_nf)
		fprintf(stderr,"(");
		
	      for(j=0;j<nb_mons;j++)
		{
		  
		  I32 k,is_one=1;
		  UI32* ei=Mons+j*nb_vars;
		  
		  if (j>0) fprintf(stderr,"+");
		  mpz_out_str(stderr,10,cfs[j]);

		  for(k=0;k<nb_vars;k++)
		    if (ei[k])
		      {
			if (ei[k] == 1)
			  fprintf(stderr,"*%s",vars[k]);
			else
			  fprintf(stderr,"*%s^%u",vars[k],ei[k]);
			is_one=0;
		      }
		  if (is_one)
		    fprintf(stderr,"*1");
		}
	      free(Mons);
	    }
	    if (want_nf)
	      {
		/* Since we are working with Integers this is a pseudoNormalForm : 
		     The result of pseudoNF(p,G) is a coeffiecient AND a polynomial q such that
		             NormalForm (c * p, G) = q
		   we have to display the coefficient c */

		const I32 nb_mons=FGB(nb_terms)(output_basis[i-1]); /* Number of Monomials */
		UI32* Mons=(UI32*)(malloc(sizeof(UI32)*nb_vars*nb_mons));
		mpz_ptr* cfs=FGB(export_poly_INT_gmp)(nb_vars,nb_mons,Mons,output_basis[i-1]);
		if (nb_mons != 1) 
		  {
		    fprintf(stderr,"Bug in NF !\n");
		    exit(1);
		  }
		fprintf(stderr,")/");
		mpz_out_str(stderr,10,cfs[0]);
		free(Mons);

	      }

	    if (i<(nb-1))
	      fprintf(stderr,",");
	  }
	fprintf(stderr,"]\n");
      }
  }
  FGB(reset_memory)(); /* to reset Memory */
  FGB(exit)(); /* restore original GMP allocators */
}

/* ---------------------------------------------------------------------- */
/* To remove verbosity you can redefine your own I/O function  */
/* Option: redefine Input/Output */


/* ---------------------------------------------------------------------- */
#if USE_MY_OWN_IO
FILE* log_output;
void info_Maple(const char* s)
{
  /* 
     if (verbose)
     {
     fprintf(stderr,"%s",s);
     fflush(stderr);
     }
  */
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
/* ---------------------------------------------------------------------- */
#endif /*  USE_MY_OWN_IO */
