#include <wiringPi.h>
#include <iostream>

using namespace std;

int enemySort(int num){
  if (num == 1)
    return 8;
  if (num == 2)
    return 9;
  if (num == 3)
    return 7;
  if (num == 4)
    return 0;
  if (num == 5)
    return 1;
  if (num == 6)
    return 2;
  if (num == 7)
    return 3;
  if (num == 8)
    return 4;
  if (num == 9)
    return 5;
  else
    return 404;
}

int towerSort(int num){
  if(num == 1)
    return 14;
  if (num == 2)
    return 6;
  if (num == 3)
    return 13;
  if (num == 4)
    return 12;
  else
    return 404;
}

//cristal = 10

void setup(){
  pinMode (14, OUTPUT);
  pinMode (12, OUTPUT);
  pinMode (13, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (2, OUTPUT);
  pinMode (1, OUTPUT);
  pinMode (0, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
}

void shoot(int tower){
  digitalWrite (towerSort(tower),  LOW) ; delay (70) ;
  digitalWrite (towerSort(tower), HIGH) ;
}

int main ()
{
  wiringPiSetup () ;
  pinMode (10, OUTPUT);
  pinMode (12, OUTPUT);
  for (;;)
  {
    digitalWrite (10, HIGH) ; delay (500) ;
    digitalWrite (12,  HIGH) ; delay (500) ;
    digitalWrite (12, LOW); delay(250);
  }
  return 0 ;
}
