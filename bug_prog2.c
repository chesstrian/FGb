/* Example: we compute a Groebner Basis modulo a small prime number */

/* The following macro should be 1 to call FGb modulo a prime number */
#define LIBMODE 1  
#define CALL_FGB_DO_NOT_DEFINE
#include "call_fgb.h"

#define FGb_MAXI_BASE 100000

static Dpol input_basis[FGb_MAXI_BASE];
static I32 global_nb=-1;
static Dpol output_basis[FGb_MAXI_BASE];

void compute_prog2(int want_display,int step0, int bk0)
{
  Dpol_INT prev;
  double t0;  global_nb=0;
  const int nb_vars=5;
  char* vars[5]={"x1","x2","x3","x4","x5"}; /* name of the variables (can be anything) */

  FGB(enter)(); /* First thing to do : GMP origmal memory allocators are saved */

  FGB(init_urgent)(2,MAPLE_FGB_BIGNNI,"DRLDRL",100000,0); /* meaning of the second parameter:
							     2 is the number of bytes of each coefficients 
							     so the maximal prime is 65521<2^16
							     1 is the number of bytes of each exponent : 
							     it means that each exponent should be < 128 */
  FGB(init)(1,1,0,log_output); /* do not change */
  {
    UI32 pr[]={(UI32)(65521)}; /* We compute in GF(65521)[x1,x2,x3,x4,x5] */
    FGB(reset_coeffs)(1,pr);
  }
  {
    FGB(reset_expos)(5,0,vars);  /* Define the monomial ordering: DRL(k1,k2) where 
				  k1 is the size of the 1st block of variables 
				  k2 is the size of the 2nd block of variables 
				  and k1+k2=nb_vars is the total number of variables
				 */
  }
  /* ================================================== */
  /* Creat the first polynomial  */
  prev=FGB(creat_poly)(4); /* number of monomials in the polynomial (here 4) */
  input_basis[global_nb++]=prev;  /* fill the array of input polynomials with the first polynomial */
  /* Creat the first monomial  = coef * terme */
  {
    /* Creat the first term: power product x1^e[1]*...*xn^e[n] */
    I32 e[5]={0,1,1,0,0};  /* monomial: x2*x3 */
    FGB(set_expos2)(prev,0,e,nb_vars); /* arguments:
				    0: the first monomial
				    nb_vars: the number of variables
				  */
  }
  /* Creat the first coefficient (here 2) */
  FGB(set_coeff_I32)(prev,0,2); /* arguments:
				    0: the first coefficient
				    2: value of the coefficient (modulo the prime number)
				  */

  /* Creat the second term: power product x1^e[1]*...*xn^e[n] */
  {
    I32 e[5]={0,1,0,0,1}; /* x2*x5 */
    FGB(set_expos2)(prev,1,e,nb_vars);  /* second monomial */
  }
  FGB(set_coeff_I32)(prev,1,2); /* second coefficient */
  {
    I32 e[5]={1,0,0,1,0}; /* x1*x4 */
    FGB(set_expos2)(prev,2,e,nb_vars); /* third monomial */
  }
  FGB(set_coeff_I32)(prev,2,2); /* third coefficient */
  {
    I32 e[5]={0,0,0,1,0}; /* x4 */
    FGB(set_expos2)(prev,3,e,nb_vars); /* fourth monomial */
  }
  FGB(set_coeff_I32)(prev,3,65520); /* fourth coefficient */

  FGB(full_sort_poly2)(prev); /* it is recommended to sort each polynomial */

  /* We creat the second polynomial */
  prev=FGB(creat_poly)(5);
  input_basis[global_nb++]=prev;
  {
    I32 e[5]={0,1,1,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,0,2);
  {
    I32 e[5]={0,1,0,0,0};
    FGB(set_expos2)(prev,1,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,1,65520);
  {
    I32 e[5]={0,0,0,1,1};
    FGB(set_expos2)(prev,2,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,2,2);
  {
    I32 e[5]={0,0,1,1,0};
    FGB(set_expos2)(prev,3,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,3,2);
  {
    I32 e[5]={1,1,0,0,0};
    FGB(set_expos2)(prev,4,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,4,2);
  FGB(full_sort_poly2)(prev);


  /* We creat the third polynomial */
  prev=FGB(creat_poly)(5);
  input_basis[global_nb++]=prev;
  {
    I32 e[5]={0,2,0,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,0,1);
  {
    I32 e[5]={1,0,1,0,0};
    FGB(set_expos2)(prev,1,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,1,2);
  {
    I32 e[5]={0,1,0,1,0};
    FGB(set_expos2)(prev,2,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,2,2);
  {
    I32 e[5]={0,0,1,0,1};
    FGB(set_expos2)(prev,3,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,3,2);
  {
    I32 e[5]={0,0,1,0,0};
    FGB(set_expos2)(prev,4,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,4,65520);
  FGB(full_sort_poly2)(prev);

  /* We creat the 4th polynomial */
  prev=FGB(creat_poly)(6);
  input_basis[global_nb++]=prev;
  {
    I32 e[5]={0,0,0,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,0,65520);
  {
    I32 e[5]={0,0,0,0,1};
    FGB(set_expos2)(prev,1,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,1,2);
  {
    I32 e[5]={0,0,0,1,0};
    FGB(set_expos2)(prev,2,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,2,2);
  {
    I32 e[5]={0,0,1,0,0};
    FGB(set_expos2)(prev,3,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,3,2);
  {
    I32 e[5]={0,1,0,0,0};
    FGB(set_expos2)(prev,4,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,4,2);
  {
    I32 e[5]={1,0,0,0,0};
    FGB(set_expos2)(prev,5,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,5,1);
  FGB(full_sort_poly2)(prev);

  /* We creat the 5th polynomial */
  prev=FGB(creat_poly)(6);
  input_basis[global_nb++]=prev;
  {
    I32 e[5]={0,2,0,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,0,2);
  {
    I32 e[5]={1,0,0,0,0};
    FGB(set_expos2)(prev,1,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,1,65520);
  {
    I32 e[5]={0,0,0,0,2};
    FGB(set_expos2)(prev,2,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,2,2);
  {
    I32 e[5]={0,0,0,2,0};
    FGB(set_expos2)(prev,3,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,3,2);
  {
    I32 e[5]={0,0,2,0,0};
    FGB(set_expos2)(prev,4,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,4,2);
  {
    I32 e[5]={2,0,0,0,0};
    FGB(set_expos2)(prev,5,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,5,1);
  FGB(full_sort_poly2)(prev); /* sort the last polynomial according the selected monomial ordering */

  {
    int nb;
    const int n_input=5; /* we have 5 polynomials on input */
    struct sFGB_Comp_Desc Env;
    FGB_Comp_Desc env=&Env;
    env->_compute=FGB_COMPUTE_GBASIS; /* The following function can be used to compute Gb, NormalForms, RR, ... 
				         Here we want to compute a Groebner Basis */
    env->_nb=0; /* parameter is used when computing NormalForms (see an example in bug_prog2.c */
    env->_force_elim=0; /* if force_elim=1 then return only the result of the elimination 
			   (need to define a monomial ordering DRL(k1,k2) with k2>0 ) */
    env->_off=0;       /* should be 0 for modulo p computation	*/
    
    env->_index=50000; /* This is is the maximal size of the matrices generated by F4 
			  you can increase this value according to your memory */
    env->_zone=0;    /* should be 0 */
    env->_memory=0;  /* should be 0 */
    /* Other parameters :
       t0 is the CPU time (reference to a double)
       bk0 : should be 0 
       step0 : this is the number primes for the first step
               if step0<0 then this parameter is automatically set by the library
     */
    nb=FGB(groebner)(input_basis,n_input,output_basis,1,0,&t0,bk0,step0,0,env);
    /* The value nb returned by the library is the number of polynomials */
    if (want_display)
      {
	int i;
	fprintf(stderr,"[\n");
	for(i=0;i<nb;i++)
	  {
#if 0
	    /* Use this fuction to print the result */
	    FGB(see_Dpol)(output_basis[i]);
#endif /*  0 */

	    /* Import the internal representation of each polynomial computed by FGb */
	    {
	      const I32 nb_mons=FGB(nb_terms)(output_basis[i]); /* Number of Monomials */
	      UI32* Mons=(UI32*)(malloc(sizeof(UI32)*nb_vars*nb_mons));
	      I32* Cfs=(I32*)(malloc(sizeof(I32)*nb_mons));
	      int code=FGB(export_poly)(nb_vars,nb_mons,Mons,Cfs,output_basis[i]);
	      I32 j;
	      for(j=0;j<nb_mons;j++)
		{
		  
		  I32 k,is_one=1;
		  UI32* ei=Mons+j*nb_vars;
		  
		  if (j>0) fprintf(stderr,"+");
		  fprintf(stderr,"%d",Cfs[j]);

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
