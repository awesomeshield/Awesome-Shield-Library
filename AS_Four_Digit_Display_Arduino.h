/*
  Four_Digital_Display_Arduino.h

  This is a Suli-compatible Library.

  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2014-4-9

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __AS_Four_Digit_Display_ARDUINO_H__
#define __AS_Four_Digit_Display_ARDUINO_H__

#include "AS_Four_Digit_Display.h"
#include <Arduino.h>

class AS_Four_Digit_Display_Arduino{

public:

    void begin(int pinData, int pinClk, enum AS_brightness_t b=BRIGHT_TYPICAL)
    {
        AS_four_digit_init(pinData, pinClk);
        AS_four_digit_set_brightness(b);
    }

    void clear()
    {
        AS_four_digit_clear();
    }

    void display(int bitAddr, int num)
    {
        AS_Four_Digit_Display(bitAddr, num);
    }


    void pointOn()
    {
        AS_four_digit_set_point(1);
    }

    void pointOff()
    {
        AS_four_digit_set_point(0);
    }

};



#endif
