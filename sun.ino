#include "sun.h"

/****f* 
  *  NAME
  *    sun - constructor
  *  SYNOPSIS
  *   a=sun(2017);
  *  FUNCTION
  *    init a sunrise/sunset
  *  INPUTS
  *    year    - year. Needed for decision leap year normal year
  *  RESULT
  *    ---
   ******
*/
sun::sun(int year) {
  isLeapYear(year);
  printid("leapyear=",leapyear); // debug
}

/****f* 
  *  NAME
  *   isLeapYear -- 
  *  SYNOPSIS
  *   l=isLeapYear(2017);
  *  FUNCTION
  *    checks for leap year (%4, %100)
  *  INPUTS
  *    y       - year (e.g. 2017)
  *  RESULT
  *    t if leap year
   ******
*/
bool sun::isLeapYear(int year) {
  if(year%4==0 && year%100!=0){
    leapyear=true;
  }else{
    leapyear=false;
  }
  return leapyear;
}


/****f* 
  *  NAME
  *    dayofyear2monthday -- converts a day to month/day
  *  SYNOPSIS
  *   dayofyear2monthday(120,d,m);
  *  FUNCTION
  *    
  *  INPUTS
  *    day     - the day. 1.1. is 0
  *    m       - the month (1 is January)
  *    d       - day of the month (1. is 1)
  *  RESULT
  *    t - conversion okay
   ******
*/
bool sun::dayofyear2monthday(int day, int &m, int &d) {
  const int *mptr=months[leapyear];
  // check if day is valid

  if(day >= mptr[months_length-1] || day < 0){
    return(false);
  }

  // search the month
  m=1;
  while(m<months_length && day>=mptr[m]){
    m++;
  }
  d=day-mptr[m-1]+1;
  return(true);
}

/****f* 
  *  NAME
  *    monthday2dayofyear
  *  SYNOPSIS
  *   d=monthday2day(10,23);
  *  FUNCTION
  *    calculates the number of the day from the beginning of the year
  *  INPUTS
  *    m       - the month (1 is January)
  *    d       - day of the month (1. is 1)
  *  RESULT
  *    the day. 1.1. is 0 (negative if error)
   ******
*/
int sun::monthday2dayofyear(int m, int d){
  const int *mptr=months[leapyear];

  if(m<1 || m>12 || d<1 ){
    return -1;
  }
  
  m--;
  int day=mptr[m]+d-1;
  // check if day is valid
  if(day >= mptr[m+1]){ // day exceeds next entry in month table?
    return -1; // error
  }else{
    return day;
  }
}

/****f* 
  *  NAME
  *    adjustSunRise -- converts a day to month/day
  *  SYNOPSIS
  *   adjustSunRise(120);
  *  FUNCTION
  *   returns the adjustment for the sunrise in minutes (e.g. from Berlin to BB)
  *  INPUTS
  *    day     - the day. 1.1. is 0
  *  RESULT
  *    adjustment in minutes
   ******
*/
int sun::adjustSunRise(int day){
  const int *mptr=months[leapyear];
  if(day<0 || day>=mptr[months_length]){
    return 0; // day is invalid
  }
  int adj=toffset-tamp*cos(omega[leapyear]*day+phi[leapyear]);
  return adj;
}

/****f* 
  *  NAME
  *    adjustSunSet -- converts a day to month/day
  *  SYNOPSIS
  *   adjustSunSet(120);
  *  FUNCTION
  *   returns the adjustment for the sunset in minutes (e.g. from Berlin to BB)
  *  INPUTS
  *    day     - the day. 1.1. is 0
  *  RESULT
  *    adjustment in minutes
   ******
*/
int sun::adjustSunSet(int day){
  const int *mptr=months[leapyear];
  if(day<0 || day>=mptr[months_length]){
    return 0; // day is invalid
  }
  int adj=toffset+tamp*cos(omega[leapyear]*day+phi[leapyear]);
  return adj;
}