
#include "matrixLeds.h"
#include "stdint.h"

#define CS_PIN    10
#define MOSI_PIN  11
#define SCLK_PIN  13
#define MAX_DEVICE 4

uint64_t image = IMAGES_REVERSE[0];
uint8_t device_id = 1;


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
//    if (device_id > MAX_DEVICE)
//    {
//      device_id = 1;
//    }
//    uint64_t image = IMAGES_REVERSE[device_id-1];
//    for (int i = 1; i <= N_ROWS; i++)
//    {
//       SetRow(i, image>>(8*i-8) & 0xff , device_id); 
//
//    }
//   delay(300);
//   ClearScreen(device_id, 0, 0);
//   device_id += 1;
//
//  
SetAnimation(IMAGES_REVERSE[0], 100);
SetAnimation(IMAGES_REVERSE[1], 100);
SetAnimation(IMAGES_REVERSE[2], 100);
SetAnimation(IMAGES_REVERSE[3], 100);
  
}
