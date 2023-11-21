#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "population.h"
#include "people.h"

boolean check(Population p, double x, double y, double radii) {
  double distance;
  int i;
  for (i = 0; i < p.iterator; i++) {
    distance = sqrt(pow(p.people[i].position[0] - x, 2) + pow(p.people[i].position[1] - y, 2));
    if (distance <= radii) {
      return false;
    }
  }
  return true;
}

Population new_Population(char name[], int size) {
  Population p;
  sprintf(p.name, "%s", name);
  p.people = malloc(size * sizeof(People));
  p.size = size;
  p.iterator = 0;
  return p;
}

int add_people_to_population(Population *p, People a) {
  if (p->iterator < p->size) {
    p->people[p->iterator] = a;
    p->iterator++;
    return 1;
  } else {
    return 0;
  }
}
