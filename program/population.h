#ifndef POPULATION_H
#define POPULATION_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "people.h"
  
typedef struct{
  char name[128];
  People *people;
  int size; //size of population 8
  int iterator;  // internal iterator to control the actual population
}Population;
  
  boolean check(Population p, double x, double y, double radii);
  Population new_Population(char name[], int size);
  int add_people_to_population(Population *p, People a);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* POPULATION_H */
