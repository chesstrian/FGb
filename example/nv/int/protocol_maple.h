#ifndef stamp_maple_protocol

#define stamp_maple_protocol

typedef enum {
  FGB_COMPUTE_GBASIS=1,
  FGB_COMPUTE_RRFORM,
  FGB_COMPUTE_RRFORM_SQFR,
  FGB_COMPUTE_MINPOLY,
  FGB_COMPUTE_MINPOLY_SQFR,
  FGB_COMPUTE_GBASIS_NF,
  FGB_COMPUTE_GBASIS_NF_RECOMPUTE,
  FGB_COMPUTE_RADICAL_STRATEG1,
  FGB_COMPUTE_RADICAL_STRATEG2,
  FGB_COMPUTE_NOP,
  FGB_COMPUTE_GBASIS_MULTI,
  FGB_COMPUTE_MATRIXN
} FGB_TYP_COMPUTE;

typedef struct sFGB_Comp_Desc
{
  FGB_TYP_COMPUTE _compute;
  I32 _nb;
  I32 _force_elim;
  UI32 _off;
  UI32 _index;
  UI32 _zone;
  UI32 _memory;

  I32 _nb2;
  I32 _force_elim2;
  UI32 _bk2;
  I32 _aggressive2;
  I32 _dlim;
  I32 _skip;
} *FGB_Comp_Desc;


static char* maple_protocol_to_string(FGB_Comp_Desc env)
{
  switch (env->_compute) 
    {
    case FGB_COMPUTE_GBASIS:
      return "FGB_COMPUTE_GBASIS";
    case FGB_COMPUTE_RRFORM:
      return "FGB_COMPUTE_RRFORM";
    case FGB_COMPUTE_RRFORM_SQFR:
      return "FGB_COMPUTE_RRFORM_SQFR";
    case FGB_COMPUTE_MINPOLY:
      return "FGB_COMPUTE_MINPOLY";
    case FGB_COMPUTE_MINPOLY_SQFR:
      return "FGB_COMPUTE_MINPOLY_SQFR";
    case FGB_COMPUTE_GBASIS_NF:
      return "FGB_COMPUTE_GBASIS_NF";
    case FGB_COMPUTE_GBASIS_NF_RECOMPUTE:
      return "FGB_COMPUTE_GBASIS_NF_RECOMPUTE";
    case FGB_COMPUTE_RADICAL_STRATEG1:
      return "FGB_COMPUTE_RADICAL_STRATEG1";
    case FGB_COMPUTE_RADICAL_STRATEG2:
      return "FGB_COMPUTE_RADICAL_STRATEG2";
    case FGB_COMPUTE_NOP:
      return "FGB_COMPUTE_NOP";
    case FGB_COMPUTE_GBASIS_MULTI:
      return "FGB_COMPUTE_GBASIS_MULTI";
    case FGB_COMPUTE_MATRIXN:
      return "FGB_COMPUTE_MATRIXN";
    default:
      return "FGB_???";
    }
}

static FGB_TYP_COMPUTE string_to_maple_protocol(char* s)
{
  if (strcmp(s,"FGB_COMPUTE_RRFORM") EQ 0)
    return FGB_COMPUTE_RRFORM;
  if (strcmp(s,"FGB_COMPUTE_MINPOLY") EQ 0)
    return FGB_COMPUTE_MINPOLY;
  if (strcmp(s,"FGB_COMPUTE_MINPOLY_SQFR") EQ 0)
    return FGB_COMPUTE_MINPOLY_SQFR;
  if (strcmp(s,"FGB_COMPUTE_RRFORM_SQFR") EQ 0)
    return FGB_COMPUTE_RRFORM_SQFR;
  if (strcmp(s,"FGB_COMPUTE_GBASIS_NF") EQ 0)
    return FGB_COMPUTE_GBASIS_NF;
  if (strcmp(s,"FGB_COMPUTE_GBASIS_NF_RECOMPUTE") EQ 0)
    return FGB_COMPUTE_GBASIS_NF_RECOMPUTE;
  if (strcmp(s,"FGB_COMPUTE_RADICAL_STRATEG1") EQ 0)
    return FGB_COMPUTE_RADICAL_STRATEG1;
  if (strcmp(s,"FGB_COMPUTE_RADICAL_STRATEG2") EQ 0)
    return FGB_COMPUTE_RADICAL_STRATEG2;
  if (strcmp(s,"FGB_COMPUTE_NOP") EQ 0)
    return FGB_COMPUTE_NOP;
  if (strcmp(s,"FGB_COMPUTE_GBASIS_MULTI") EQ 0)
    return FGB_COMPUTE_GBASIS_MULTI;
  if (strcmp(s,"FGB_COMPUTE_MATRIXN") EQ 0)
    return FGB_COMPUTE_MATRIXN;
  return FGB_COMPUTE_GBASIS;
}
#endif /* ndef stamp_maple_protocol */
