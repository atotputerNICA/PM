#include <avr/io.h>
#include <util/delay.h>
#include "key.h"


int GetKeyPressed(int *row, int *col)
{
      uint8_t r,c;
      KEYPAD_PIN = 0x00;
      KEYPAD_PORT = 0x00;
      KEYPAD_DDR = 0x00;
      KEYPAD_PORT|= 0X0F;

      for(c=0;c<4;c++)
      {
         KEYPAD_DDR&=~(0X0F);

         KEYPAD_DDR|=(0X80>>c);
         for(r=0;r<4;r++)
         {
            if(!(KEYPAD_PIN & (0X08 >>r)))
            {
               // return keyboard[r][c];//(r*4+c);
							 *row = r;
							 *col = c;
							 return 1;
            }
         }
      }

      return 0;//Indicate No key pressed
}
