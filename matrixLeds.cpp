#include "matrixLeds.h"

#define ROW_VALUE_INDEX  ((row-1) + 8 * (device_id - 1))

uint8_t row_value[8 * MAX_DEVICE] = {0};
uint8_t SCLK_PIN, MOSI_PIN, CS_PIN, DEVICES;

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

void init_t()
{
  Serial.begin(9600);
}

void SendCommand(uint8_t addr, uint8_t value, uint8_t device_id)
{
//  uint8_t data[MAX_DEVICE * 2] = {0};
//  data[device_id + 1] = addr;
//  data[device_id] = value;
  
  digitalWrite(SCLK_PIN, LOW);
  digitalWrite(CS_PIN, LOW);
  
  for (int i = MAX_DEVICE; i > 0; i--)
  {
    if (i == device_id)
    {
       shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, addr);
       shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, value);
    }
    else
    {
       shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, 0);
       shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, 0);
    }
  }
  digitalWrite(CS_PIN, HIGH);
}


void SetScanLimit(uint8_t limit, uint8_t device_id)
{
  if (limit >= 0 && limit <= 7)
    SendCommand(OP_SCANLIMIT, limit, device_id);
}

void SetScanIntensity(uint8_t intensity, uint8_t device_id)
{
  if (intensity >= 0 && intensity <= 15)
    SendCommand(OP_INTENSITY, intensity, device_id);
}

void ClearScreen(uint8_t device_id, uint8_t direction = 0, unsigned long duration = 0)
{
    for(uint8_t addr = 1; addr <= N_ROWS; addr++)
    {
      if (direction == 0)
      {
        SetRow(addr, 0, device_id);  
      }
      else if (direction == 1)
      {
        SetRow(9 - addr, 0, device_id);
      }
      else if (direction == 2)
      {
        SetColumn(addr, 0, device_id);
      } 
      else if (direction == 3)
      {
        SetColumn(9 - addr, 0, device_id);
      } 
      delay(duration);   
    }
}

void ShutDown(bool command, uint8_t device_id)
{
  if (command)
  {
    SendCommand(OP_SHUTDOWN, 0, device_id);
  }
  else
  {
    SendCommand(OP_SHUTDOWN, 1, device_id);
  }
}

void SetDecodeMode(uint8_t code, uint8_t device_id)
{
   SendCommand(OP_NOOP, code, device_id);
}

void SetRow(uint8_t row, uint8_t value, uint8_t device_id)
{
  if ((row >=1 && row <=N_ROWS) & (value >= 0 & value <= 255) & (device_id >= 1 && device_id <= MAX_DEVICE))
  {
    row_value[ROW_VALUE_INDEX] = value;
    SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
  }
}

void SetColumn(uint8_t col, uint8_t value, uint8_t device_id)
{
  if ((col >=1 && col <=N_COLS) & (value >= 0 && value <= 255) & (device_id >= 1 && device_id <= MAX_DEVICE))
  {
      for (uint8_t row = 1; row <= 8; row++)
      {
        if (value>>(row-1) & 1) 
        {
          row_value[ROW_VALUE_INDEX] |= (1<< (col - 1)); 
        }
        else
        {
          row_value[ROW_VALUE_INDEX] &= ~(1<< (col - 1)); 
        }
        SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
      }
  }
}

void SetLED(uint8_t row, uint8_t col, bool state, uint8_t device_id)
{
  if ((col >= 1 && col <= N_COLS) & (row >=1 && row <=N_ROWS))
  {
    if (state)    
    {
      row_value[ROW_VALUE_INDEX] |= (1<< (col - 1));
    }
    else
    {
      row_value[ROW_VALUE_INDEX] &= ~(1<< (col - 1)); 
    }
    SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
  }
}

void SetAnimation(uint64_t pattern, unsigned long duration)
{
  uint8_t current_device = 1;
  for (uint8_t  index = 0; index < 8 * MAX_DEVICE + 8; index++)
  {
    for (uint8_t row = 1; row <= 8; row++)
    {
        uint8_t this_row = (uint8_t) (pattern >> 8 * (row-1));
        if ((current_device - 1) != 0)
        {
          SetRow(row, this_row << (index%8) + 1, current_device - 1);
        }
        SetRow(row, this_row >> (7 - index % 8), current_device);    // 7-0    0 7  0 7 0 7 0 7 0 7       0index % 8 = 0 

    }
    delay(duration);
    if (index % 8 == 7)
    {
        current_device += 1;
    }
  }
    
}


void Welcome(uint8_t device_id)
{
  ShutDown(0, device_id);
  for (uint8_t i = MAX_DEVICE; i >= 1; i--)
  {
    SetRow(i, 255, device_id); 
    SetRow(9 - i, 255, device_id); 
    delay(50);
    SetRow(i, 0, device_id); 
    SetRow(9 - i, 0, device_id);
  }
 
  for (uint8_t i = MAX_DEVICE; i >= 1; i--)
  {
    SetColumn(i, 255, device_id); 
    SetColumn(9 - i, 255, device_id); 
    delay(50);
    SetColumn(i, 0, device_id); 
    SetColumn(9 - i, 0, device_id); 
  }

  ClearScreen(device_id);
}

void ScreenStartUp(uint8_t mosi_pin, uint8_t sclk_pin, uint8_t cs_pin)
{
  MOSI_PIN = mosi_pin; 
  SCLK_PIN = sclk_pin;
  CS_PIN = cs_pin;
  
  pinMode(CS_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  for (int device_id = 1; device_id <= MAX_DEVICE; device_id ++)
  {
    SendCommand(OP_DISPLAYTEST, 0, device_id);
    SetScanLimit(7,device_id);
    SetScanIntensity(4, device_id);
    SetDecodeMode(0, device_id);
    ClearScreen(device_id);
    ShutDown(1, device_id);
    Welcome(device_id);
  }

}
