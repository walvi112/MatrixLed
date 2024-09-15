#include "matrixLeds.h"
#include "stdint.h"

#define CS_PIN    10
#define MOSI_PIN  11
#define SCLK_PIN  13
#define MAX_DEVICE 4
#define MAX_BUFFER 300ul

void setup() {
  ScreenStartUp(MOSI_PIN, SCLK_PIN, CS_PIN);
}

void loop() {
  AnimateText("Welcome", 1, 50, D_RIGHT);
  SetColumnbyIndex(28, 24);
  SetColumnbyIndex(29, 24);
  SetAnimationbyFrame(4, 18 , PACMAN , 50, D_LEFT);
  SetAnimationbyFrame(4, 18 , PACMAN_BACK , 50, D_RIGHT);
  DisplayText("arduino", 1);
  delay(2000);
  AnimateText(" ", 1, 100, D_RIGHT);
  DisplayText("LEDS", 1);
  delay(2000);
  ClearScreen(D_BOT, 100);
  

}