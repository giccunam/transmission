#ifndef PEOPLE_H
#define PEOPLE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef int boolean;
#define true 1
#define false 0

  
typedef struct{
  double age;
  int gender; // [0=man,1=woman], 
  int status; // [0=healty, 1=sick, 2=immune, -1=dead],
  double time_recovery;// [hours]
  double position[2]; //[x,y] m
  double velocity[2]; // [x,y] m
  boolean updated;
}People;



  People new_People(double age, int gender, int status, double time_recovery, double p_x, double p_y, double r_x, double r_y); 

  void print_People(People people);
  
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* PEOPLE_H */
