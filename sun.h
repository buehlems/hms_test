#ifndef SUN_H
#define SUN_H


/*
idea: get sunrise and sunset from http://www.atomzeit.eu in Berlin
correct these values to actual location, e.g. Boeblingen with formula:
sunrise(BB)=sunrise(B)+toffset-tamp*cos(omega*t+phi)
sunset(BB) =sunset(B) +toffset+tamp*cos(omega*t+phi)
all times in minutes
*/
typedef struct {
  byte d;
  byte m;
  int y;
} date;

class sun {
 public:
  sun(int year);
  bool dayofyear2monthday(int day, int &m, int &d);
  int monthday2dayofyear(int m, int d);
  int adjustSunRise(int day);
  int adjustSunSet(int day);
 private:
  // months: full year Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
  const int months[2][13] = { {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
			      {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366} };
  const int months_length = sizeof(months[0])/sizeof(months[0][0]);
  const float pi=3.141593;
   const float phi[2]= { (32.0-21.0)*2.0*pi/365.0 , (32.0-21.0)*2.0*pi/366.0 }; // approximation in normal/leap year
   const float omega[2] = { 2.0*pi/365.0 , (32.0-21.0)*2.0*pi/366.0 } ; // approximation in normal year

  const int toffset=17*60;
  const int tamp=19*60;

  bool isLeapYear(int year);
  
  int dayofyear; // day of the year
  bool leapyear;
};

#endif
