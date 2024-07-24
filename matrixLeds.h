#ifndef MATRIXLEDS_H
#define MATRIXLEDS_H

#include "stdint.h"
#include "Arduino.h"



#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

/* Send command to LED driver
    addr: registrer address
    value: value to send
*/
void SendCommand(uint8_t addr, uint8_t value);
/* Start up the screen*/
void ScreenStartUp(uint8_t mosi_pin, uint8_t sclk_pin, uint8_t cs_pin, uint8_t devices);
/* Set the scan limit
    limit: scan limit (0-7)
*/
void SetScanLimit(uint8_t limit);
/* Set the scan intensity
    limit: scan intensity (0-15)
*/
void SetScanIntensity(uint8_t intensity);
/*Clear the display*/
void ClearScreen(uint8_t direction = 0, unsigned long duration = 0);
/*Shut down screen
    command : (0, 1)
*/
void ShutDown(bool command);
/* Set row on/off
 *  row: row to set value (1-8)
 *  value: value to set (0-255)
*/
void SetRow(uint8_t row, uint8_t value);
/* Set column on/off
 *  column: column to set value (1-8)
 *  value: value to set (0-255)
*/
void SetColumn(uint8_t col, uint8_t value);
/* Set led on/off
 *  row: row to set value (1-8)
 *  column: column to set value (1-8)
 *  state: state to set (0-1)
*/
void SetLED(uint8_t row, uint8_t col, bool state);

#endif
