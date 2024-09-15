#include "matrixLeds.h"

#define ROW_VALUE_INDEX ((row - 1) + 8 * (device_id - 1))

#define OP_NOOP 0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE 9
#define OP_INTENSITY 10
#define OP_SCANLIMIT 11
#define OP_SHUTDOWN 12
#define OP_DISPLAYTEST 15

uint8_t row_value[8 * MAX_DEVICE] = { 0 };
uint8_t device_to_refresh[MAX_DEVICE] = { 0 };
uint8_t TEXT_FRAME[MAX_BUFFER];


uint8_t SCLK_PIN, MOSI_PIN, CS_PIN, DEVICES;


void InitSerial() {
  Serial.begin(9600);
}

void SendCommand(uint8_t addr, uint8_t value, uint8_t device_id) {

  digitalWrite(SCLK_PIN, LOW);
  digitalWrite(CS_PIN, LOW);

  for (int i = MAX_DEVICE; i > 0; i--) {
    if (i == device_id) {
      shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, addr);
      shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, value);
    } else {
      shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, 0);
      shiftOut(MOSI_PIN, SCLK_PIN, MSBFIRST, 0);
    }
  }
  digitalWrite(CS_PIN, HIGH);
}

uint8_t getDeviceidfromCol(int col) {
  if (col >= 1 && col <= T_COLS) {
    if (col <= N_COLS) {
      return 1;
    } else if (col <= N_COLS * 2) {
      return 2;
    } else if (col <= N_COLS * 3) {
      return 3;
    } else if (col <= N_COLS * 4) {
      return 4;
    }
  }
}

void device_refresh() {
  for (uint8_t device_id = 1; device_id <= MAX_DEVICE; device_id++) {
    if (device_to_refresh[device_id - 1] == 1)
      device_to_refresh[device_id - 1] = 0;
    for (int row = 1; row <= N_ROWS; row++) {
      SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
    }
  }
}

void SetScanLimit(uint8_t limit, uint8_t device_id) {
  if (limit >= 0 && limit <= 7)
    SendCommand(OP_SCANLIMIT, limit, device_id);
}

void SetScanIntensity(uint8_t intensity, uint8_t device_id) {
  if (intensity >= 0 && intensity <= 15)
    SendCommand(OP_INTENSITY, intensity, device_id);
}

void ClearScreenDevice(uint8_t device_id, enum Direction direction = D_BOT, unsigned long duration = 0) {
  for (uint8_t addr = 1; addr <= N_ROWS; addr++) {
    switch(direction)
    {
      case D_BOT:
        SetRow(addr, 0, device_id);
        break;
      case D_TOP:
        SetRow(9 - addr, 0, device_id);
        break;
      case D_LEFT:
        SetColumn(addr, 0, device_id);
        break;
      case D_RIGHT:
        SetColumn(9 - addr, 0, device_id);
        break;
    }
    delay(duration);
  }
}

void ClearScreen(enum Direction direction = D_BOT, unsigned long duration = 0) 
{
  for (uint8_t addr = 1; addr <= N_ROWS; addr++)
  {
    for(uint8_t device_id = 1; device_id <= MAX_DEVICE; device_id++)
    {
      switch(direction)
      {
      case D_BOT:
        SetRow(addr, 0, device_id);
        break;
      case D_TOP:
        SetRow(9 - addr, 0, device_id);
        break;
      case D_LEFT:
        SetColumn(addr, 0, device_id);
        break;
      case D_RIGHT:
        SetColumn(9 - addr, 0, device_id);
        break;
      }
    }
    delay(duration);
  } 
}

void ShutDown(bool command, uint8_t device_id) {
  if (command) {
    SendCommand(OP_SHUTDOWN, 0, device_id);
  } else {
    SendCommand(OP_SHUTDOWN, 1, device_id);
  }
}

void SetDecodeMode(uint8_t code, uint8_t device_id) {
  SendCommand(OP_NOOP, code, device_id);
}

void SetRow(uint8_t row, uint8_t value, uint8_t device_id) {
  if ((row >= 1 && row <= N_ROWS) & (value >= 0 & value <= 255) & (device_id >= 1 && device_id <= MAX_DEVICE)) {
    row_value[ROW_VALUE_INDEX] = value;
    SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
  }
}

void SetColumn(uint8_t col, uint8_t value, uint8_t device_id) {
  if ((col >= 1 && col <= N_COLS) & (value >= 0 && value <= 255) & (device_id >= 1 && device_id <= MAX_DEVICE)) {
    for (uint8_t row = 1; row <= 8; row++) {
      if (value >> (row - 1) & 1) {
        row_value[ROW_VALUE_INDEX] |= (1 << (col - 1));
      } else {
        row_value[ROW_VALUE_INDEX] &= ~(1 << (col - 1));
      }
      SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
    }
  }
}

void SetLED(uint8_t row, uint8_t col, bool state, uint8_t device_id) {
  if ((col >= 1 && col <= N_COLS) & (row >= 1 && row <= N_ROWS)) {
    if (state) {
      row_value[ROW_VALUE_INDEX] |= (1 << (col - 1));
    } else {
      row_value[ROW_VALUE_INDEX] &= ~(1 << (col - 1));
    }
    SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
  }
}

void SetAnimation(uint64_t pattern, unsigned long duration) {
  uint8_t current_device = 1;
  for (uint8_t index = 0; index < N_COLS * MAX_DEVICE + N_COLS; index++) {
    for (uint8_t row = 1; row <= N_COLS; row++) {
      uint8_t this_row = (uint8_t)(pattern >> N_COLS * (row - 1));
      if ((current_device - 1) != 0) {
        SetRow(row, this_row << (index % N_COLS) + 1, current_device - 1);
      }
      SetRow(row, this_row >> (7 - index % N_COLS), current_device);
    }
    delay(duration);
    if (index % N_COLS == 7) {
      current_device += 1;
    }
  }
}

static void ModArray_SetColumnbyIndex(int col, uint8_t value) {
  if (col >= 1 && col <= T_COLS) {
    uint8_t device_id = getDeviceidfromCol(col);
    col = (col - 1) % N_COLS + 1;
    for (uint8_t row = 1; row <= N_ROWS; row++) {
      if (value >> (row - 1) & 1) {
        row_value[ROW_VALUE_INDEX] |= (1 << (col - 1));
      } else {
        row_value[ROW_VALUE_INDEX] &= ~(1 << (col - 1));
      }
    }
  }
}

void SetColumnbyIndex(uint8_t col, uint8_t value) {
  if ((col >= 1 && col <= T_COLS) & (value >= SHUTDOWN_VAL && value <= ON_VAL)) {
    uint8_t device_id = getDeviceidfromCol(col);
    col = (col - 1) % N_COLS + 1;
    for (uint8_t row = 1; row <= N_ROWS; row++) {
      if (value >> (row - 1) & 1) {
        row_value[ROW_VALUE_INDEX] |= (1 << (col - 1));
      } else {
        row_value[ROW_VALUE_INDEX] &= ~(1 << (col - 1));
      }

      SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
    }
  }
}

void SetLEDbyIndex(uint8_t row, uint8_t col, bool state) {
  if ((col >= 1 && col <= T_COLS) & (row >= 1 && row <= N_ROWS)) {
    uint8_t device_id = getDeviceidfromCol(col);
    col = (col - 1) % N_COLS + 1;

    if (state) {
      row_value[ROW_VALUE_INDEX] |= (1 << (col - 1));
    } else {
      row_value[ROW_VALUE_INDEX] &= ~(1 << (col - 1));
    }
    SendCommand(row, row_value[ROW_VALUE_INDEX], device_id);
  }
}

static unsigned long GetTextFrame(char c[], uint8_t padding) {
  uint8_t frame_index = 0;
  int string_index = 0;
  uint8_t *font_pt;
  memset(TEXT_FRAME, 0, sizeof(TEXT_FRAME));
  while (c[string_index] != '\n' && c[string_index] != '\0' && frame_index < MAX_BUFFER) {
    font_pt = FONT;
    if (c[string_index] > 127) {
      string_index++;
      continue;
    }

    for (uint8_t index = 0; index < c[string_index]; index++) {
      font_pt += (pgm_read_byte(font_pt) + 1);
    }
    uint8_t char_width = pgm_read_byte(font_pt);
    for (uint8_t index = 0; index < char_width; index++) {
      TEXT_FRAME[frame_index] = pgm_read_byte(++font_pt);
      frame_index++;
      delay(1);
    }
    for (uint8_t count = 0; count < padding; count++) {
      TEXT_FRAME[frame_index] = 0;
      frame_index++;
    }

    string_index++;
  }

  return frame_index;
}

void AnimateText(char c[], uint8_t padding, unsigned long duration, enum Direction direction = D_LEFT) {
  unsigned long text_length = GetTextFrame(c, padding);
  SetAnimationbyFrame(1, text_length, TEXT_FRAME, duration, direction);
}


void DisplayText(char c[], uint8_t padding) {
  unsigned long frame_length = GetTextFrame(c, padding);
  uint8_t(*frame)[frame_length] = (uint8_t(*)[frame_length])TEXT_FRAME;
  int ref_col = (T_COLS - frame_length) / 2 + 1;
  int current_col;
  for (uint8_t pixel_col = 0; pixel_col < frame_length; pixel_col++) {
    current_col = ref_col + pixel_col;
    if (current_col >= 1 && current_col <= T_COLS) {
      ModArray_SetColumnbyIndex(current_col, frame[0][pixel_col]);
      device_to_refresh[getDeviceidfromCol(current_col) - 1] = 1;
    }
  }
  device_refresh();
}

void SetAnimationbyFrame(uint8_t num_frames, uint8_t frame_length, void *frames, unsigned long duration, enum Direction direction) {
  int ref_col, des_col, sign_dir;
  switch (direction) {
    case D_TOP:
      return;
    case D_BOT:
      return;
    case D_LEFT:
      ref_col = -frame_length + 1;
      des_col = T_COLS;
      sign_dir = 1;
      break;
    case D_RIGHT:
      ref_col = T_COLS;
      des_col = -frame_length + 1;
      ;
      sign_dir = -1;
      break;
  }

  uint8_t current_frame = 0;
  uint8_t(*frame)[frame_length] = (uint8_t(*)[frame_length])frames;

  while (sign_dir * ref_col <= sign_dir * des_col) {
    int current_col;
    //delete previous graphic
    for (uint8_t pixel_col = 0; pixel_col < frame_length; pixel_col++) {
      current_col = ref_col + pixel_col;
      if (current_col >= 1 && current_col <= T_COLS) {
        ModArray_SetColumnbyIndex(current_col, SHUTDOWN_VAL);
        device_to_refresh[getDeviceidfromCol(current_col) - 1] = 1;
      }
    }
    //shift reference column and set net graphic
    ref_col += sign_dir;
    for (uint8_t pixel_col = 0; pixel_col < frame_length; pixel_col++) {
      current_col = ref_col + pixel_col;
      if (current_col >= 1 && current_col <= T_COLS) {
        ModArray_SetColumnbyIndex(current_col, frame[current_frame][pixel_col]);
        device_to_refresh[getDeviceidfromCol(current_col) - 1] = 1;
      }
    }
    device_refresh();
    delay(duration);
    current_frame++;
    if (current_frame >= num_frames)
      current_frame = 0;
  }
}

void Welcome(uint8_t device_id) {
  ShutDown(0, device_id);
  for (uint8_t i = MAX_DEVICE; i >= 1; i--) {
    SetRow(i, ON_VAL, device_id);
    SetRow(9 - i, ON_VAL, device_id);
    delay(50);
    SetRow(i, SHUTDOWN_VAL, device_id);
    SetRow(9 - i, SHUTDOWN_VAL, device_id);
  }

  for (uint8_t i = MAX_DEVICE; i >= 1; i--) {
    SetColumn(i, ON_VAL, device_id);
    SetColumn(9 - i, ON_VAL, device_id);
    delay(50);
    SetColumn(i, SHUTDOWN_VAL, device_id);
    SetColumn(9 - i, SHUTDOWN_VAL, device_id);
  }

  ClearScreenDevice(device_id);
}

void ScreenStartUp(uint8_t mosi_pin, uint8_t sclk_pin, uint8_t cs_pin) {
  MOSI_PIN = mosi_pin;
  SCLK_PIN = sclk_pin;
  CS_PIN = cs_pin;

  pinMode(CS_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  for (int device_id = 1; device_id <= MAX_DEVICE; device_id++) {
    SendCommand(OP_DISPLAYTEST, 0, device_id);
    SetScanLimit(7, device_id);
    SetScanIntensity(2, device_id);
    SetDecodeMode(0, device_id);
    ClearScreenDevice(device_id);
    ShutDown(1, device_id);
    Welcome(device_id);
  }
}
