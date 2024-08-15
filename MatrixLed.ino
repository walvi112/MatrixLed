#include "matrixLeds.h"
#include "stdint.h"

#define CS_PIN    10
#define MOSI_PIN  11
#define SCLK_PIN  13
#define MAX_DEVICE 4

void setup() {
  init_t();
  ScreenStartUp(MOSI_PIN, SCLK_PIN, CS_PIN);
  //SetLEDbyIndex(5, 1, 1);
   //SetAnimationbyFrame(IMAGES_REVERSE, 1, 500);
  
}

void loop() {
  SetAnimationbyFrame(4, 18, PACMAN , 30);
}
