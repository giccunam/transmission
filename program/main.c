#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 


#include "people.h"
#include "population.h"
#include "montecarlo.h"

int main(int argn, char **argv){

  People a1, a2, a3, a4, a5;
  Population p;
  MonteCarlo mc;
  int steps, prints, npeople;
  double radii;
  double A, B; //limits for wide and height AxB where (0,0) is in the center of the region.
  float v_A, v_B; //limits to velocity
  int i;
  double x0, x1, v0, v1;
  double dt, rt;
  boolean check_coordinates;

  steps = 2000;
  prints = 1;
  npeople = 128;
  radii = 2.0;
  A = 100.0;
  B = 100.0;
  v_A = 1.0;
  v_B = 1.0;
  dt = 0.1;
  rt = 1000.0; //recovery time (in steps)

  //age, gender [0=man,1=woman], status [0=healty, 1=sick, 2=immune, -1=dead], time_recovery [hours], position [x,y], direction [x,y]
  //a1 = new_People(18, 1, 0, 0.0, 0.0, 0.0, 0.0, 0.0);
  //a2 = new_People(28, 0, 1, 1000.0, -5.0, 0.0, 1.0, 0.0);
  //a3 = new_People(18, 1, 0, 0.0, 5.0, 0.0, -1.0, 0.0);
  //a1 = new_People(18, 1, 0, 0.0, 0.0, 0.0, 0.0, 0.0);
  //a2 = new_People(28, 0, 1, 1000.0, 5.0, 0.0, -1.0, 0.0);
  //a1 = new_People(18, 1, 0, 0.0, 0.0, 0.0, 0.0, 0.0);
  //a2 = new_People(28, 0, 1, 1000.0, 0.0, 5.0, 0.0, -1.0);
  //a2 = new_People(28, 0, 1, 1000.0, -5.0, 5.0, 1.0, -1.0);
  //a1 = new_People(18, 1, 0, 0.0, -5.0, 0.0, 2.0, 0.0);
  //a2 = new_People(28, 0, 1, 1000.0, 5.0, 0.0, -2.0, 0.0);
  //a3 = new_People(38, 1, 0, 0.0, -2.0, 5.0, -1.0, -1.0);
  //a4 = new_People(48, 0, 0, 0.0, 4.0, 6.0, -2.0, -1.0);
  //a5 = new_People(60, 1, 0, 0.0, -6.0, -8.0, 1.0, 2.0);

  p = new_Population("Mexico", npeople);
  srand(time(0));
  //sick
  v0 = (((float)rand() / (float)RAND_MAX) * v_A) - (v_A / 2.0);
  v1 = (((float)rand() / (float)RAND_MAX) * v_B) - (v_B / 2.0);
  add_people_to_population(&p, new_People(18, 1, 1, rt, 0, 0, v0, v1));

  for (i = 1; i < npeople; i++) {
    check_coordinates = false;
    while (!(check_coordinates)) {
      x0 = (((float)rand() / (float)RAND_MAX) * A) - (A / 2.0);
      x1 = (((float)rand() / (float)RAND_MAX) * B) - (B / 2.0);
      check_coordinates = check(p, x0, x1, radii);
    }
    v0 = (((float)rand() / (float)RAND_MAX) * v_A) - (v_A / 2.0);
    v1 = (((float)rand() / (float)RAND_MAX) * v_B) - (v_B / 2.0);
    add_people_to_population(&p, new_People(18, 1, 0, 0.0, x0, x1, v0, v1));
  }

  mc = new_MonteCarlo("Test", p, A, B);
  printf("# %i\t%i\t%lf\t%lf\t%lf\t%lf\t%lf\n", steps / prints, p.iterator, -A / 2, A / 2, -B / 2, B / 2, radii / 2.0);
  run_MonteCarlo(mc, steps, prints, radii, dt, rt);

  return 0;
}
