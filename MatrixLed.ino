
#include "matrixLeds.h"
#include "stdint.h"

#define CS_PIN    10
#define MOSI_PIN  11
#define SCLK_PIN  13
#define MAX_DEVICE 4

//uint8_t device_id = 1;
uint8_t image = 0;

void shutdown_devices(void)
{
  ShutDown(1, 1);
  ShutDown(1, 2);
  ShutDown(1, 3);
  ShutDown(1, 4);
}

void setup() {
  init_t();
  ScreenStartUp(MOSI_PIN, SCLK_PIN, CS_PIN);
//  device_id = 1;


  
}

void loop() {
  if (image >= 6)
    image = 0;
  SetAnimation(IMAGES_REVERSE[image++], 10);

 
  
}
