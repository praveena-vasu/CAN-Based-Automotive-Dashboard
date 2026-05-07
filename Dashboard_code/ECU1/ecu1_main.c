/*
 * File               : ECU1 main.c
 * Name Of The Project: CAN Based Automotive Dashboard
 * Job                : Transmit data from ECU1(Speed &Gear) to ECU3
 */


#include<xc.h>
#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "msg_id.h"
#include "uart.h"

void init_configuration()
{
    init_clcd();
    init_adc();
    init_matrix_keypad();
    init_can();
}

void main()
{
    CLEAR_DISP_SCREEN;
    init_configuration();
    while(1)
    {
        get_speed();
        get_gear_pos();
    }
}
