#include "matrixLeds.h"
#include "stdint.h"

#define CS_PIN    10
#define MOSI_PIN  11
#define SCLK_PIN  13
#define MAX_DEVICE 4


void setup() {
  ScreenStartUp(MOSI_PIN, SCLK_PIN, CS_PIN);
  //SetLEDbyIndex(5, 2, 1);
  


}

void loop() {
  //AnimateText("Bonjour la FRANCE", 1, 100);
  SetAnimationbyFrame(3, 18 , PACMAN , 100, D_LEFT);
  
}
