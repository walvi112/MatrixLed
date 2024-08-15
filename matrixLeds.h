#ifndef MATRIXLEDS_H
#define MATRIXLEDS_H

#include "stdint.h"
#include "Arduino.h"

#ifndef MAX_DEVICE
#define MAX_DEVICE 4
#endif

#define N_ROWS  8 
#define N_COLS  8

#define T_COLS (8 * MAX_DEVICE)

#define SHUTDOWN_VAL  0
#define ON_VAL  255

const uint64_t IMAGES[] =
{
  0x0f0703010f070301, //on all LEDs
  0x000081C3663C1800, //V shape
  0x0066998142241800, //Heart shape
};

const uint64_t IMAGES_REVERSE[] =
{
  0x00183c7effff6600, //Heart shape
  0x3c4299a581a5423c, //Smile
  0x1f3e7cf8f87c3e1f, //Arrow
  0xffe7e7e7ff9999ff, //Creaper
  0x815a24ffdb7e3c18, //Squirt
  0x557f7f7f49493e1c, //Pacman
};

const uint8_t PACMAN[4][18]
{
  { 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x7e, 0xff, 0xe7, 0xc3, 0x81, 0x00 },
  { 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xe7, 0xe7, 0x42, 0x00 },
  { 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xe7, 0x66, 0x24 },
  { 0xfe, 0x7b, 0xf3, 0x7f, 0xf3, 0x7b, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c },
};



void init_t();
/* Send command to LED driver
    addr: registrer address
    value: value to send
    device_id: id of led Matrix (1-4)
*/
//void SendCommand(uint8_t addr, uint8_t value, uint8_t device_id);
/* Start up the screen*/
void ScreenStartUp(uint8_t mosi_pin, uint8_t sclk_pin, uint8_t cs_pin);
/* Set the scan limit
    limit: scan limit (0-7)
    device_id: id of led Matrix (1-4)
*/
void SetScanLimit(uint8_t limit, uint8_t device_id);
/* Set the scan intensity
    limit: scan intensity (0-15)
    device_id: id of led Matrix (1-4)
*/
void SetScanIntensity(uint8_t intensity, uint8_t device_id);
/*Clear the display
  direction: clear direction (0: bottom up, 1: up bottom, 2: left right, 3: right left)
  duration: duration of delay between rows/columns
  device_id: id of led Matrix (1-4)
*/
void ClearScreen(uint8_t device_id, uint8_t direction = 0, unsigned long duration = 0);
/*Shut down screen
    command : (0, 1)
    device_id: id of led Matrix (1-4)
*/
void ShutDown(bool command, uint8_t device_id);
/* Set row on/off
 *  row: row to set value (1-8)
 *  value: value to set (0-255)+
 *  device_id: device id to control (1-4)
*/
void SetRow(uint8_t row, uint8_t value, uint8_t device_id);
/* Set column on/off
 *  column: column to set value (1-8)
 *  value: value to set (0-255)
 *  device_id: device id to control (1-4)
*/
void SetColumn(uint8_t col, uint8_t value, uint8_t device_id);
/* Set led on/off
 *  row: row to set value (1-8)
 *  column: column to set value (1-8)
 *  state: state to set (0-1)
 *  device_id: id of led Matrix (1-4)
*/
void SetLED(uint8_t row, uint8_t col, bool state, uint8_t device_id);

void SetAnimation(uint64_t pattern, unsigned long duration);

void SetColumnbyIndex(uint8_t col, uint8_t value);

void SetLEDbyIndex(uint8_t row, uint8_t col, bool state);

void SetAnimationbyFrame(uint8_t num_frames, uint8_t frame_length , void *frames , unsigned long duration);

#endif
