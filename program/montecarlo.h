#ifndef MONTECARLO_H
#define MONTECARLO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "population.h"
  
typedef struct{
  char name[128];
  Population population;
  int steps;
  int prints;
  double A; //wide
  double B; //high
}MonteCarlo;

  MonteCarlo new_MonteCarlo(char name[], Population population, double A, double B);
  int run_MonteCarlo(MonteCarlo mc, int steps, int prints, double radii, double dt, double rt);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* MONTECARLO_H */
