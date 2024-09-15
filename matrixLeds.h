#ifndef MATRIXLEDS_H
#define MATRIXLEDS_H

#include "stdint.h"
#include "Arduino.h"

#ifndef MAX_DEVICE
#define MAX_DEVICE 4
#endif

#ifndef MAX_BUFFER
#define MAX_BUFFER 300ul
#endif

#define N_ROWS  8 
#define N_COLS  8

#define T_COLS (8 * MAX_DEVICE)

#define SHUTDOWN_VAL  0
#define ON_VAL  255

enum Direction {D_BOT, D_TOP, D_LEFT, D_RIGHT};


const uint8_t IMAGES[7][8] =
{
  {0x30, 0x18, 0x0c, 0x06, 0x06, 0x0c, 0x18, 0x30}, //V shape     0
  {0x30, 0x78, 0x7c, 0x3e, 0x3e, 0x7c, 0x78, 0x30}, //Heart shape 1
  {0x3c, 0x42, 0xa9, 0x85, 0x85, 0xa9, 0x42, 0x3c}, //Smile       2
  {0x18, 0x3c, 0x7e, 0xff, 0xff, 0xe7, 0xc3, 0x81}, //Arrow       3
  {0xff, 0x9f, 0x9f, 0xf1, 0xf1, 0x9f, 0x9f, 0xff}, //Creaper     4
  {0x32, 0x74, 0xd8, 0xf4, 0xf4, 0xd8, 0x74, 0x32}, //Squirt      5
};


const uint8_t PACMAN[4][18]
{
  { 0x7f, 0xde, 0xcf, 0xfe, 0xdf, 0xce, 0x7f, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x7e, 0xff, 0xe7, 0xc3, 0x81, 0x00 },
  { 0x7f, 0xce, 0xdf, 0xfe, 0xcf, 0xde, 0x7f, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xe7, 0xe7, 0x42, 0x00 },
  { 0x7f, 0xde, 0xcf, 0xfe, 0xdf, 0xce, 0x7f, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xe7, 0x66, 0x24 },
  { 0x7f, 0xce, 0xdf, 0xfe, 0xcf, 0xde, 0x7f, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c },
};

const uint8_t PACMAN_BACK[4][18]
{
  { 0x7f, 0xde, 0xcf, 0xfe, 0xdf, 0xce, 0x7f, 0x00, 0x00, 0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c, 0x00 },
  { 0x7f, 0xce, 0xdf, 0xfe, 0xcf, 0xde, 0x7f, 0x00, 0x00, 0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c, 0x00 },
  { 0x7f, 0xde, 0xcf, 0xfe, 0xdf, 0xce, 0x7f, 0x00, 0x00, 0x00, 0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c },
  { 0x7f, 0xce, 0xdf, 0xfe, 0xcf, 0xde, 0x7f, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c },
};

const uint8_t PROGMEM FONT[]
{
  0,    // 0 - 'Empty Cell'
  5, 124, 218, 242, 218, 124,    // 1 - 'Sad Smiley'
  5, 124, 214, 242, 214, 124,    // 2 - 'Happy Smiley'
  5, 56, 124, 62, 124, 56,   // 3 - 'Heart'
  5, 24, 60, 126, 60, 24,   // 4 - 'Diamond'
  5, 56, 234, 190, 234, 56,   // 5 - 'Clubs'
  5, 56, 122, 254, 122, 56,   // 6 - 'Spades'
  4, 0, 24, 60, 24,   // 7 - 'Bullet Point'
  5, 255, 231, 195, 231, 255,   // 8 - 'Rev Bullet Point'
  4, 0, 24, 36, 24,   // 9 - 'Hollow Bullet Point'
  5, 255, 231, 219, 231, 255,   // 10 - 'Rev Hollow BP'
  5, 12, 18, 92, 96, 112,   // 11 - 'Male'
  5, 100, 148, 158, 148, 100,   // 12 - 'Female'
  5, 2, 254, 160, 160, 224,    // 13 - 'Music Note 1'
  5, 2, 254, 160, 164, 252,    // 14 - 'Music Note 2'
  5, 90, 60, 231, 60, 90,   // 15 - 'Snowflake'
  5, 254, 124, 56, 56, 16,    // 16 - 'Right Pointer'
  5, 16, 56, 56, 124, 254,    // 17 - 'Left Pointer'
  5, 40, 68, 254, 68, 40,   // 18 - 'UpDown Arrows'
  5, 255, 255, 255, 255, 255,   // 19 - 'Full Block'
  5, 240, 240, 240, 240, 240,   // 20 - 'Half Block Bottom'
  3, 255, 255, 255,   // 21 - 'Half Block LHS'
  5, 0, 0, 0, 255, 255,   // 22 - 'Half Block RHS'
  5, 240, 240, 240, 240, 240,    // 23 - 'Half Block Top'
  5, 16, 32, 126, 32, 16,   // 24 - 'Up Arrow'
  5, 8, 4, 126, 4, 8,   // 25 - 'Down Arrow'
  5, 16, 16, 84, 56, 16,   // 26 - 'Right Arrow'
  5, 16, 56, 84, 16, 16,   // 27 - 'Left Arrow'
  5, 85, 0, 170, 0, 85,    // 28 - '30% shading'
  5, 85, 170, 85, 170, 85,   // 29 - '50% shading'
  5, 12, 28, 124, 28, 12,    // 30 - 'Up Pointer'
  5, 96, 112, 124, 112, 96,    // 31 - 'Down Pointer'
  1, 0,    // 32 - 'Space'
  1, 250,    // 33 - '!'
  3, 224, 0, 224,   // 34 - '""'
  5, 40, 254, 40, 254, 40,    // 35 - '#'
  5, 34, 82, 255, 82, 76,   // 36 - '$'
  5, 198, 200, 16, 38, 198,    // 37 - '%'
  5, 108, 146, 146, 108, 18,    // 38 - '&'
  1, 224,   // 39 - '''
  3, 124, 130, 130,    // 40 - '('
  3, 130, 130, 124,    // 41 - ')'
  5, 16, 84, 56, 84, 16,    // 42 - '*'
  5, 16, 16, 124, 16, 16 ,   // 43 - '+'
  2, 6, 7,   // 44 - ','
  4, 16, 16, 16, 16,    // 45 - '-'
  2, 6, 6,    // 46 - '.'
  5, 6, 8, 16, 32, 192,   // 47 - '/'
  5, 124, 138, 146, 162, 124,    // 48 - '0'
  3, 32, 64, 254,    // 49 - '1'
  5, 142, 146, 146, 146, 98,   // 50 - '2'
  5, 130, 146, 146, 146, 108,    // 51 - '3'
  5, 240, 16, 16, 16, 254,    // 52 - '4'
  5, 242, 146, 146, 146, 12,    // 53 - '5'
  5, 124, 146, 146, 146, 12,    // 54 - '6'
  5, 192, 128, 128, 128, 254,   // 55 - '7'
  5, 108, 146, 146, 146, 108,    // 56 - '8'
  5, 96, 146, 146, 146, 124,   // 57 - '9'
  2, 54, 54,    // 58 - ':'
  2, 54, 55,    // 59 - ';'
  3, 16, 40, 68,   // 60 - '<'
  4, 40, 40, 40, 40,   // 61 - '='
  3, 68, 40, 16,   // 62 - '>'
  5, 0, 154, 144, 144, 96,   // 63 - '?'
  5, 62, 65, 93, 89, 78,    // 64 - '@'
  5, 126, 144, 144, 144, 126,    // 65 - 'A' 
  5, 254, 146, 146, 146, 108,   // 66 - 'B'
  5, 124, 130, 130, 130, 130,    // 67 - 'C'
  5, 254, 130, 130, 130, 124,   // 68 - 'D'
  5, 254, 146, 146, 146, 130,   // 69 - 'E'
  5, 254, 144, 144, 144, 128,   // 70 - 'F'
  5, 124, 130, 130, 146, 158,   // 71 - 'G'
  5, 254, 16, 16, 16, 254,     // 72 - 'H'
  3, 130, 254, 130,   // 73 - 'I'
  5, 12, 130, 130, 130, 252,    // 74 - 'J'
  5, 254, 16, 40, 68, 130,    // 75 - 'K'
  5, 254, 2, 2, 2, 2,        // 76 - 'L'
  5, 254, 64, 32, 64, 254,   // 77 - 'M'
  5, 254, 64, 16, 4, 254,    // 78 - 'N'
  5, 124, 130, 130, 130, 124,    // 79 - 'O'
  5, 254, 144, 144, 144, 96,   // 80 - 'P'
  5, 252, 130, 130, 134, 126,   // 81 - 'Q'
  5, 254, 144, 152, 148, 98,   // 82 - 'R'
  5, 140, 146, 146, 146, 98,    // 83 - 'S'
  5, 128, 128, 254, 128, 128,   // 84 - 'T'
  5, 252, 2, 2, 2, 252,     // 85 - 'U'
  5, 248, 4, 2, 4, 248,     // 86 - 'V'
  5, 252, 2, 12, 2, 252,    // 87 - 'W'
  5, 198, 40, 16, 40, 198,   // 88 - 'X'
  5, 192, 32, 30, 32, 192,   // 89 - 'Y'
  5, 134, 138, 146, 162, 194,    // 90 - 'Z'
  3, 254, 130, 130,   // 91 - '['
  5, 192, 32, 16, 8, 6,    // 92 - '\'
  3, 130, 130, 254,  // 93 - ']'
  5, 32, 64, 128, 64, 32,   // 94 - '^'
  4, 1, 1, 1, 1,     // 95 - '_'
  3, 128, 64, 32,  // 96 - '`'
  4, 44, 42, 42, 30,   // 97 - 'a'
  4, 252, 18, 18, 12,   // 98 - 'b'
  4, 28, 34, 34, 34,     // 99 - 'c'
  4, 28, 34, 34, 254,    // 100 - 'd'
  4, 28, 42, 42, 26,    // 101 - 'e'
  4, 32, 126, 160, 128,    // 102 - 'f'
  4, 24, 37, 37, 62,   // 103 - 'g'
  4, 254, 32, 32, 30,   // 104 - 'h'
  1, 190,   // 105 - 'i'
  3, 33, 161, 62,   // 106 - 'j'
  4, 254, 8, 20, 34,   // 107 - 'k'
  1, 254,   // 108 - 'l'
  5, 62, 32, 30, 32, 30,   // 109 - 'm'
  4, 62, 32, 32, 30,    // 110 - 'n'
  4, 28, 34, 34, 28,    // 111 - 'o'
  4, 63, 36, 36, 24,   // 112 - 'p'
  4, 24, 36, 36, 63,   // 113 - 'q'
  4, 62, 32, 32, 16,    // 114 - 'r'
  4, 44, 42, 42, 26,    // 115 - 's'
  3, 32, 254, 32,   // 116 - 't'
  4, 60, 2, 2, 62,   // 117 - 'u'
  4, 56, 4, 2, 62,   // 118 - 'v'
  5, 60, 2, 12, 2, 60,    // 119 - 'w'
  4, 54, 8, 8, 54,    // 120 - 'x'
  4, 56, 5, 5, 62,   // 121 - 'y'
  4, 38, 42, 42, 50,   // 122 - 'z'
  4, 16, 108, 130, 130,   // 123 - '{'
  1, 254,   // 124 - '|'
  4, 130, 130, 108, 16,   // 125 - '}'
  4, 128, 64, 128, 64,    // 126 - '~'
  5, 254, 130, 130, 130, 254,    // 127 - 'Hollow Block'
};

/* Serial init*/
void InitSerial();

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
void ClearScreenDevice(uint8_t device_id, enum Direction direction = D_BOT, unsigned long duration = 0);

/*Clear the whole display
  duration: duration of delay between rows/columns
  device_id: id of led Matrix (1-4)
*/
void ClearScreen(enum Direction direction = D_BOT, unsigned long duration = 0);

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

/* Set animation (obsolete, use the SetAnimationbyFrame instead)
 *  pattern: array of uint64_t value for each column
 *  duration: animation speed
*/
void SetAnimation(uint64_t pattern, unsigned long duration);

/* Set column value for each column 
 *  col: column to set (1-8*Total_device)
 *  value: uint8_t column value
*/
void SetColumnbyIndex(uint8_t col, uint8_t value);

/* Set led value for row,column
 *  row: row to set (1-8)
 *  col: column to set (1-8*Total_device)
 *  state: on(1)/off(0)
*/
void SetLEDbyIndex(uint8_t row, uint8_t col, bool state);

/* Set frame animation (sprite)
 *  num_frames: number of sprite
 *  frame_length: number of column of each frame
 *  frame: array of frames
 *  duration: animation speed
 *  direction: animation direction
*/
void SetAnimationbyFrame(uint8_t num_frames, uint8_t frame_length , void *frames , unsigned long duration, enum Direction direction);

/* Set text animation
 *  c: text to display
 *  padding: columns of space between characters
 *  duration: animation speed
 *  direction: animation direction
*/
void AnimateText(char c[], uint8_t padding, unsigned long duration, enum Direction direction = D_LEFT);

/* Display text
 *  c: text to display
 *  padding: columns of space between characters
*/
void DisplayText(char c[], uint8_t padding);



#endif
