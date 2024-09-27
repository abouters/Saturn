#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "CAN.h"
#include <Saturn.h>
#include <Metro.h>

CanControl DriveCan(2);
Saturn saturn = Saturn(&DriveCan, 0);
Metro countup = Metro(2000);
Metro send_timing = Metro(1);
bool flag = 0;

void setup() {
  saturn.init();
}

void loop(){
  if(countup.check()) flag = !flag;

  if(flag){
    saturn.setTargetDgree(2, 45);
  }else{
    saturn.setTargetDgree(2, 90);
  }

  if(send_timing.check()) saturn.send();
}