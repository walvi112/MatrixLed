#include "matrixLeds.h"

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

uint8_t TEXT_FRAME[MAX_BUFFER];


unsigned long GetTextFrame(char c[], uint8_t padding)
{
  uint8_t frame_index = 0;
  int string_index = 0;
  uint8_t *font_pt;
  while (c[string_index] != '\n' && c[string_index] != '\0' && frame_index < MAX_BUFFER)
  {
    font_pt = FONT;
    if (c[string_index] > 127)
    {
      string_index++;
      continue;
    }
    
    
    
    for (uint8_t index = 0; index < c[string_index]; index++)
    {
      font_pt += (pgm_read_byte(font_pt) + 1);
    }
    uint8_t char_width = pgm_read_byte(font_pt);
    for (uint8_t index = 0; index < char_width; index++)
    {
      TEXT_FRAME[frame_index] = pgm_read_byte(++font_pt);
      frame_index++;
      delay(1);
    }
    for (uint8_t count = 0; count < padding; count++)
    {
      TEXT_FRAME[frame_index] = 0;
      frame_index++;
    }
    
    string_index++; 

  }

  return frame_index;
}

void AnimateText(char c[], uint8_t padding, unsigned long duration, enum Direction direction = D_LEFT)
{
  unsigned long text_length = GetTextFrame(c, padding);
  SetAnimationbyFrame(1, text_length , TEXT_FRAME , duration, direction);
}
