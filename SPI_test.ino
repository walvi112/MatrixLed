
#include "matrixLeds.h"
#include "stdint.h"

#define CS_PIN    10
#define MOSI_PIN  11
#define SCLK_PIN  13
#define MAX_DEVICE  4

void setup() {
  ScreenStartUp(MOSI_PIN, SCLK_PIN, CS_PIN, MAX_DEVICE);
}

void loop() {
  // put your main code here, to run repeatedly:

  SetColumn(4, 4);
  
  
  
  
}
