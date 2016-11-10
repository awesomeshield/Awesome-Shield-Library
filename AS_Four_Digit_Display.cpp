/*
  Four_Digital_Display.cpp

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


#include "AS_Four_Digit_Display.h"

IO_T AS__pinDta;
IO_T AS__pinClk;


uint8 AS_Cmd_DispCtrl  = 0;
uint8 AS__PointFlag    = 0;     //AS__PointFlag=1:the clock point on


const int8 AS_TubeTab[] =
{
    0x3f,0x06,0x5b,0x4f,
    0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,
    0x39,0x5e,0x79,0x71
}; //0~9,A,b,C,d,E,F

// write a byte
void AS_writeByte(int8 wr_data)
{
    uint8 i,count1;
    for(i=0;i<8;i++)                                  //sent 8bit data
    {
        suli_pin_write(&AS__pinClk, HAL_PIN_LOW);
        if(wr_data & 0x01)suli_pin_write(&AS__pinDta, HAL_PIN_HIGH); //LSB first
        else suli_pin_write(&AS__pinDta,HAL_PIN_LOW);
        wr_data >>= 1;
        suli_pin_write(&AS__pinClk,HAL_PIN_HIGH);
    }
    suli_pin_write(&AS__pinClk,HAL_PIN_LOW);                 //wait for the ACK
    suli_pin_write(&AS__pinDta,HAL_PIN_HIGH);
    suli_pin_write(&AS__pinClk,HAL_PIN_HIGH);

    suli_pin_dir(&AS__pinDta, HAL_PIN_INPUT);
    while(suli_pin_read(&AS__pinDta))
    {
        count1 +=1;
        if(count1 == 200)//
        {
            suli_pin_dir(&AS__pinDta, HAL_PIN_OUTPUT);
            suli_pin_write(&AS__pinDta,HAL_PIN_LOW);
            count1 =0;
        }
        suli_pin_dir(&AS__pinDta, HAL_PIN_INPUT);
    }
    suli_pin_dir(&AS__pinDta, HAL_PIN_OUTPUT);
}

// send start signal to TM1637
void AS_start(void)
{
    suli_pin_write(&AS__pinClk, HAL_PIN_HIGH);//send start signal to TM1637
    suli_pin_write(&AS__pinDta, HAL_PIN_HIGH);
    suli_pin_write(&AS__pinDta, HAL_PIN_LOW);
    suli_pin_write(&AS__pinClk, HAL_PIN_LOW);
}

// End of transmission
void AS_stop(void)
{
    suli_pin_write(&AS__pinClk,HAL_PIN_LOW);
    suli_pin_write(&AS__pinDta,HAL_PIN_LOW);
    suli_pin_write(&AS__pinClk,HAL_PIN_HIGH);
    suli_pin_write(&AS__pinDta,HAL_PIN_HIGH);
}

//
void AS_AS_codingS(int8 *DispData)
{
    uint8 PointData;
    if(AS__PointFlag == POINT_ON)PointData = 0x80;
    else PointData = 0;
    for(uint8 i = 0;i < 4;i ++)
    {
        if(DispData[i] == 0x7f)DispData[i] = 0x00;
        else DispData[i] = AS_TubeTab[DispData[i]] + PointData;
    }
}

//
uint8 AS_coding(int8 DispData)
{
    uint8 PointData;
    if(AS__PointFlag == POINT_ON)PointData = 0x80;
    else PointData = 0;
    if(DispData == 0x7f) DispData = 0x00 + PointData;//The bit digital tube off
    else DispData = AS_TubeTab[DispData] + PointData;
    return DispData;
}

// initialize
void AS_four_digit_init(PIN_T data, PIN_T clk)
{

    suli_pin_init(&AS__pinDta, data);
    suli_pin_init(&AS__pinClk, clk);

    suli_pin_dir(&AS__pinDta, HAL_PIN_OUTPUT);
    suli_pin_dir(&AS__pinClk, HAL_PIN_OUTPUT);

    AS_four_digit_clear();
}

// set brightness
void AS_four_digit_set_brightness(enum AS_brightness_t b)           //set before calling display
{
    AS_Cmd_DispCtrl = 0x88 + b;
}

// show :
void AS_four_digit_set_point(bool disp_point)              //set before calling display
{
    AS__PointFlag = disp_point;
}

// display a bit
void AS_Four_Digit_Display(uint8 BitAddr,int8 DispData)
{
    uint8 SegData;
    SegData = AS_coding(DispData);
    AS_start();          //start signal sent to TM1637 from MCU
    AS_writeByte(ADDR_FIXED);//
    AS_stop();           //
    AS_start();          //
    AS_writeByte(BitAddr|0xc0);//
    AS_writeByte(SegData);//
    AS_stop();            //
    AS_start();          //
    AS_writeByte(AS_Cmd_DispCtrl);//
    AS_stop();           //
}

// clear display
void AS_four_digit_clear()
{
    AS_Four_Digit_Display(0x00,0x7f);
    AS_Four_Digit_Display(0x01,0x7f);
    AS_Four_Digit_Display(0x02,0x7f);
    AS_Four_Digit_Display(0x03,0x7f);
}
