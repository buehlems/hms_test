/*

HMS: tests the hms classes
 */

#include <Arduino.h>
#include "hms.h"
#include "sun.h"
      
void printld(char *str,long v){
  Serial.print(str);
  Serial.println(v);
}

void printid(char *str,int v){
  Serial.print(str);
  Serial.println(v);
}


void setup() 
{
  Serial.begin(115200);

}

void testd2md(int day){
  int m,d;
  sun srs(2016); // sunrise/sunset

  Serial.println("");
  Serial.println("=== new ===");
  Serial.print("day ");
  Serial.print(day);
  Serial.print(" is ");
 
  if(!srs.dayofyear2monthday(day,m,d)){
    Serial.println("invalid");
  }else{
    Serial.print(d);
    Serial.print(".");
    Serial.print(m);
    printid(". check ",srs.monthday2dayofyear(m,d));
  }
}

void testmd2d(int m,int d){
  int day;
  sun srs(2016); // sunrise/sunset

  Serial.println("");
  Serial.println("=== new ===");
  Serial.print(d);  Serial.print(".");  Serial.print(m);  Serial.print(". ");
  Serial.print(" is ");
  day=srs.monthday2dayofyear(m,d);
  Serial.println(day);
}

void loop()
{

  int i=0;
  printid("sizeof int=",sizeof(i));
  long l=0;
  printid("sizeof long=",sizeof(l));
  minute M;
  int m=M.time2minutes(10,20);
  printid("10h+20m=",m);
  second S;
  long s=S.time2seconds(10,20,35);
  printld("10h+20m+35s=",s);
  printld("23h+20m+35s=",S.time2seconds(23,20,35));
  testd2md(-1); // invalid
  testd2md(0); // 1.1.
  testd2md(1); // 2.1.
  testd2md(30); // 31.1.
  testd2md(31); // 1.2.
  testd2md(58); // 28.2.
  testd2md(59); // 29.2./1.3.
  testd2md(60); // 1.3./2.3.
  testd2md(364); // 31.12.
  testd2md(365); // invalid/31.12.
  testd2md(366); // invalid

  testmd2d(1,1); 
  testmd2d(1,2); 
  testmd2d(2,1); 
  testmd2d(12,31); 
  testmd2d(0,12); // invalid
  testmd2d(-1,12); // invalid
  testmd2d(1,0); // invalid
  testmd2d(1,-1); // invalid
  testmd2d(1,31); 
  testmd2d(1,32); 
  testmd2d(2,28); 
  testmd2d(2,29); 
  testmd2d(2,30); 


  delay(10000);
}
