#include "matrixLeds.h"

uint8_t row_value[8] = {0};

void SendCommand(uint8_t addr, uint8_t value)
{
  digitalWrite(CS_PIN, LOW);
  shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, addr);
  shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, value);
  digitalWrite(CS_PIN, HIGH);
}


void SetScanLimit(uint8_t limit)
{
  SendCommand(OP_SCANLIMIT, limit);
}

void SetScanIntensity(uint8_t intensity)
{
  SendCommand(OP_INTENSITY, intensity);
}

void ClearScreen(void)
{
  for(uint8_t addr = 1; addr <= 8; addr++)
  {
    row_value[addr-1] = 0;
    SendCommand(addr, row_value[addr-1]);
    
  }
}

void ShutDown(bool command)
{
  if (command)
  {
    SendCommand(OP_SHUTDOWN, 0);
  }
  else
  {
    SendCommand(OP_SHUTDOWN, 1);
  }
}

void SetDecodeMode(uint8_t code)
{
   SendCommand(OP_NOOP, code);
}

void SetRow(uint8_t row, bool state)
{
  if (state)
  {
    row_value[row-1] = 255;
    
  }
  else
  {
    row_value[row-1] = 0;
  }
  SendCommand(row, row_value[row-1]);
}

void SetColumn(uint8_t col, bool state)
{
  for (uint8_t row = 1; row <= 8; row++)
  {
      if (state)
      {
          row_value[row-1] |= (1<< (8 -col)); 
      }
      else
      {
          row_value[row-1] &= ~(1<< (8 -col)); 
      }
      SendCommand(row, row_value[row-1]);
  }

}


void Welcome(void)
{
  ShutDown(0);
  for(int i = 4; i >= 0; i--)
  {
    SetColumn(i, HIGH); 
    SetColumn(9 - i, HIGH); 
    delay(100);
    SetColumn(i, LOW); 
    SetColumn(9 - i, LOW); 
  }

  for(int i = 4; i >= 0; i--)
  {
    SetRow(i, HIGH); 
    SetRow(9 - i, HIGH); 
    delay(100);
    SetRow(i, LOW); 
    SetRow(9 - i, LOW); 
  }
  ClearScreen();
}

void ScreenStartUp(void)
{
  pinMode(CS_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  SendCommand(OP_DISPLAYTEST, 0);
  SetScanLimit(7);
  SetScanIntensity(8);
  SetDecodeMode(0);
  ClearScreen();
  ShutDown(1);
  Welcome();
}
