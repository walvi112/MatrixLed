#include "matrixLeds.h"

uint8_t row_value[8] = {0};
uint8_t SCLK_PIN, MOSI_PIN, CS_PIN, DEVICES;


void SendCommand(uint8_t addr, uint8_t value)
{
  
  digitalWrite(CS_PIN, LOW);
  for (int i = 1; i <= 4; i++)
  {
  shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, addr);
  shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, value);
  }


  digitalWrite(CS_PIN, HIGH);
}


void SetScanLimit(uint8_t limit)
{
  if (limit >= 0 && limit <= 7)
    SendCommand(OP_SCANLIMIT, limit);
}

void SetScanIntensity(uint8_t intensity)
{
  if (intensity >= 0 && intensity <= 15)
    SendCommand(OP_INTENSITY, intensity);
}

void ClearScreen(uint8_t direction = 0, unsigned long duration = 0)
{
  if (!direction)
    for(uint8_t addr = 1; addr <= 8; addr++)
    {
      row_value[addr-1] = 0;
      SendCommand(addr, row_value[addr-1]);    
    }
   else if (direction == 1)
   {
    for(uint8_t addr = 1; addr <= 8; addr++)
    {
      row_value[addr-1] = 0;
      SendCommand(addr, row_value[addr-1]);
      delay(duration);    
    }
   }
   else if (direction == 2)
   {
    for(uint8_t addr = 8; addr >= 1; addr--)
    {
      row_value[addr-1] = 0;
      SendCommand(addr, row_value[addr-1]);
      delay(duration);    
    }
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

void SetRow(uint8_t row, uint8_t value)
{
  if ( row >=1 && row <=8 && value >= 0 && value <= 255)
  {
    row_value[row-1] = value;
    SendCommand(row, row_value[row-1]);
  }
}

void SetColumn(uint8_t col, uint8_t value)
{
  if (col >=1 && col <=8 && value >= 0 && value <= 255)
  {
      for (uint8_t row = 1; row <= 8; row++)
      {
        if (value>>(row-1) & 1) 
        {
          row_value[row-1] |= (1<< (col - 1)); 
        }
        else
        {
          row_value[row-1] &= ~(1<< (col - 1)); 
        }
        SendCommand(row, row_value[row - 1]);
      }
  }
}

void SetLED(uint8_t row, uint8_t col, bool state)
{
  if (col >= 1 && col <= 8 && row >=1 && row <=8)
  {
    if (state)    
    {
      row_value[row - 1] |= (1<< (col - 1));
    }
    else
    {
      row_value[row - 1] &= ~(1<< (col - 1)); 
    }
    SendCommand(row, row_value[row-1]);
  }
}


void Welcome(void)
{
  ShutDown(0);
  for(int i = 4; i >= 0; i--)
  {
    SetRow(i, 255); 
    SetRow(9 - i, 255); 
    delay(100);
    SetRow(i, 0); 
    SetRow(9 - i, 0); 
  }

  for(int i = 4; i >= 0; i--)
  {
    SetColumn(i, 255); 
    SetColumn(9 - i, 255); 
    delay(100);
    SetColumn(i, 0); 
    SetColumn(9 - i, 0); 
  }
  ClearScreen();
}

void ScreenStartUp(uint8_t mosi_pin, uint8_t sclk_pin, uint8_t cs_pin, uint8_t devices)
{
  MOSI_PIN = mosi_pin; 
  SCLK_PIN = sclk_pin;
  CS_PIN = cs_pin;
  DEVICES = devices;
  
  pinMode(CS_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  SendCommand(OP_DISPLAYTEST, 0);
  SetScanLimit(7);
  SetScanIntensity(4);
  SetDecodeMode(0);
  ClearScreen();
  ShutDown(1);
  Welcome();
}
