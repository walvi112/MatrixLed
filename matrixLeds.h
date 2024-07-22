#ifndef MATRIXLEDS_H
#define MATRIXLEDS_H

#include "stdint.h"
#include "Arduino.h"

#define CS_PIN    10
#define MOSI_PIN  11
#define SCLK_PIN  13

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


void SendCommand(uint8_t addr, uint8_t value);
void ScreenStartUp(void);
void SetScanLimit(uint8_t limit);
void SetScanIntensity(uint8_t intensity);
void ClearScreen(void);
void ShutDown(bool command);
void SetRow(uint8_t row, bool state);
void SetColumn(uint8_t col, bool state);

#endif
