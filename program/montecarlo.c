#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include "montecarlo.h"
#include "population.h"
#include "people.h"

#define M_PI 3.14159265358979323846

int healthcare(People *k){
  k->time_recovery -= 1.0;
  if (k->time_recovery <= 0.0){
    k->status = 2; //immune
    k->time_recovery = 0.0;
  }
  return 1;
}

/**
 * @brief Updates the trajectory of two people after a collision
 * 
 * @param k Pointer to the first person
 * @param m Pointer to the second person
 * @param radii The radius of the people
 * @param A The width of the simulation area
 * @param B The height of the simulation area
 * @return int Returns 1 if the update was successful
 */
int updateTrajectory(People *k, People *m, double radii, double A, double B){
  double v1, v2;
  double v1x, v1y, v2x, v2y, a, b, c, d, x1, y1, x2, y2, phi, theta1, theta2, pi2;
  double epsilon = 1e-10;
  double u, w, mycos1, mysin1;
  double norm, dot_product;

  // Get the velocities and positions of the two people
  v1x = k->velocity[0];
  v1y = k->velocity[1];
  v2x = m->velocity[0];
  v2y = m->velocity[1];
  x1 = k->position[0];
  y1 = k->position[1];
  x2 = m->position[0];
  y2 = m->position[1];

  // Check if the two people have collided with the left and right walls
  // If they have, update their positions accordingly
  if (x1 < 0.0 && (A + x1) < radii && x2 > 0.0 && (A - x2) < radii) {
    x2 = -2.0 * A + x2;
  }
  if (x1 > 0.0 && (A - x1) < radii && x2 < 0.0 && (A + x2) < radii) {
    x1 = -2.0 * A + x1;
  }

  // Check if the two people have collided with the top and bottom walls
  // If they have, update their positions accordingly
  if (y1 < 0.0 && (B + y1) < radii && y2 > 0.0 && (B - y2) < radii) {
    y2 = -2.0 * B + y2;
  }
  if (y1 > 0.0 && (B - y1) < radii && y2 < 0.0 && (B + y2) < radii) {
    y1 = -2.0 * B + y1;
  }
  
  // Calculate the distance between the two people
  norm = fabsf(pow(x1-x2,2.0)+pow(y1-y2,2.0));

  // Calculate the dot product of the velocities and the distance vector
  dot_product = (v1x-v2x)*(x1-x2) + (v1y-v2y)*(y1-y2);

  // Update the velocity of the first person
  k->velocity[0] = v1x - (dot_product/norm)*(x1-x2);
  k->velocity[1] = v1y - (dot_product/norm)*(y1-y2);

  // Calculate the distance between the two people (again)
  norm = fabsf(pow(x2-x1,2.0)+pow(y2-y1,2.0));

  // Calculate the dot product of the velocities and the distance vector (again)
  dot_product = (v2x-v1x)*(x2-x1) + (v2y-v1y)*(y2-y1);

  // Update the velocity of the second person
  m->velocity[0] = v2x - (dot_product/norm)*(x2-x1);
  m->velocity[1] = v2y - (dot_product/norm)*(y2-y1);

  // Return 1 to indicate that the update was successful
  return 1;  
}

/**
 * Check if two people intersect given their positions, radii, and borders.
 * If they intersect, update their status and time to recovery.
 * 
 * @param k Pointer to the first person
 * @param m Pointer to the second person
 * @param radii The radius of the people
 * @param rt The time to recovery
 * @param A The border in the X-axis
 * @param B The border in the Y-axis
 * 
 * @return true if the people intersect, false otherwise
 */
boolean intersection(People *k, People *m, double radii, double rt, double A, double B){
  double a, b, c, d, distance;

  // Get the positions of the people
  a = k->position[0];
  b = k->position[1];
  c = m->position[0];
  d = m->position[1];

  // Check if the people are crossing the left border
  if (a < 0.0 && (A+a) < radii && c > 0.0 && (A-c) < radii) {
    c = -2.0*A+c;
  }

  // Check if the people are crossing the right border
  if (a > 0.0 && (A-a) < radii && c < 0.0 && (A+c) < radii) {
    a = -2.0*A+a;
  }

  // Check if the people are crossing the bottom border
  if (b < 0.0 && (B+b) < radii && d > 0.0 && (B-d) < radii) {
    d = -2.0*B+d;
  }

  // Check if the people are crossing the top border
  if (b > 0.0 && (B-b) < radii && d < 0.0 && (B+d) < radii) {
    b = -2.0*B+b;
  }
  
  // Calculate the distance between the people
  distance = sqrt(pow(c-a,2) + pow(d-b,2));

  // If the people intersect, update their status and time to recovery
  if (distance <= radii){
    if ((k->status==1) && (m->status==0)){
      m->status=1;
      m->time_recovery = rt;
    } else if ((k->status==0) && (m->status==1)) {
      k->status=1;
      k->time_recovery = rt;
    }    
    return true;
  } else {
    return false;
  }
}

int interaction(Population *population, double radii, double rt, double A, double B){
  int k, m;
  for (k=0; k<population->iterator; k++){
    // Update the position of the people
    for (m=k+1; m<population->iterator; m++){
      // Update the position of the people
      if (intersection(&population->people[k], &population->people[m], radii, rt, A, B)){
        updateTrajectory(&population->people[k], &population->people[m], radii, A, B);
      }
    }
  }
  return 1;
}

int integrate(People *people, double dt, double x_A, double x_B, double y_A, double y_B){
  // v = d/dt  ->  d = v*dt
  double d, v;
  // Update in X
  v = people->velocity[0];
  d = v*dt;
  people->position[0] += d;
  
  // Update in Y
  v = people->velocity[1];
  d = v*dt;
  people->position[1] += d;

  return 1;
}

int fix_borders(People *people, double dt, double x_A, double x_B, double y_A, double y_B, double radii){
    // Son dos variables que inicializó Victor, pero no las usaremos
    double d, v;

    // Le asignas la velocidad en X a la variable v
    v = people->velocity[0];
    // Le asignas la distancia en X a la variable d, pero de nuevo, no la usaremos
    d = v*dt;

    // Checas que, incluyendo el radio, no se salga de los límites en X
    if (people->position[0] - radii < x_A || people->position[0] + radii > x_B) {
        // Si se sale, inviertes la velocidad en X
        people->velocity[0] = -people->velocity[0];
    }  // Si no, no haces nada y de actualizas la posición en X
    people->position[0] += people->velocity[0] * dt;

    // Lo mismo va para la posición en Y
    v = people->velocity[1];
    d = v*dt;

    // Checas que, incluyendo el radio, no se salga de los límites en Y & so on, and so forth...
    if (people->position[1] - radii < y_B || people->position[1] + radii > y_A) {
        people->velocity[1] = -people->velocity[1];
    }
    people->position[1] += people->velocity[1] * dt;
    // Peeeero NO CAMBIA NADA
    return 1;
}

MonteCarlo new_MonteCarlo(char name[], Population population, double A, double B){
  MonteCarlo mc;
  sprintf(mc.name, "%s", name);
  mc.population = population;
  mc.steps = 0;
  mc.prints = 0;
  mc.A = A;
  mc.B = B;
  return mc;
}

int run_MonteCarlo(MonteCarlo mc, int steps, int prints, double radii, double dt, double rt) {
  int i = 0;
  int j;
  int k;
  double x_A, x_B, y_A, y_B;
  int healty, sick, immune, dead;

  x_A = -mc.A / 2;
  x_B = mc.A / 2;
  y_A = mc.B / 2;
  y_B = -mc.B / 2;

  j = 0;

  healty = 0;
  sick = 0;
  immune = 0;
  dead = 0;
  for (k = 0; k < mc.population.iterator; k++) {
    switch (mc.population.people[k].status) {
      case 0:
        healty++;
        break;
      case 1:
        sick++;
        break;
      case 2:
        immune++;
        break;
      case -1:
        dead++;
        break;
      default:
        printf("Warnning: no status recognized!\n");
    }
  }
  printf("# %i\t%i\t%i\t%i\t%i\n", 0, healty, sick, immune, dead);
  for (k = 0; k < mc.population.iterator; k++) {
    print_People(mc.population.people[k]);
  }

  for (i = 0; i < steps; i++) {
    interaction(&mc.population, radii, rt, x_B, y_A);

    for (k = 0; k < mc.population.iterator; k++) {
      integrate(&mc.population.people[k], dt, x_A, x_B, y_A, y_B);
      if (mc.population.people[k].status == 1) {
        healthcare(&mc.population.people[k]);
      }
    }

    for (k = 0; k < mc.population.iterator; k++) {
      fix_borders(&mc.population.people[k], dt, x_A, x_B, y_A, y_B, radii);
    }

    j++;
    if (j == prints) {
      healty = 0;
      sick = 0;
      immune = 0;
      dead = 0;
      for (k = 0; k < mc.population.iterator; k++) {
        switch (mc.population.people[k].status) {
          case 0:
            healty++;
            break;
          case 1:
            sick++;
            break;
          case 2:
            immune++;
            break;
          case -1:
            dead++;
            break;
          default:
            printf("Warnning: no status recognized!\n");
        }
      }
      printf("# %i\t%i\t%i\t%i\t%i\n", i + 1, healty, sick, immune, dead);
      for (k = 0; k < mc.population.iterator; k++) {
        print_People(mc.population.people[k]);
      }
      j = 0;
    }
  }
  return 1;
}
