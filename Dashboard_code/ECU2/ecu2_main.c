/*
 * File               :   ECU2 main.c
 * Name Of The Project: CAN Based Automotive Dashboard
 * Job                : Transmit data from ECU2(Indicator & RPM) to ECU3
 */


#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "ssd.h"

void init_config()
{
    TRISB &= 0X3C;
    PORTB &= 0X3C;
    init_can();
    init_ssd_control();
    init_adc();
    init_digital_keypad();
   
}

int main()
{
    //call the functions
    init_config();
    unsigned static long wait = 0;
    while(1)
    {
        get_rpm();
        process_indicator();
//        if(process_indicator() == e_ind_left)
//        {
//            RB0 = 0;
//            RB1  = 0;
//            if(++wait == 5)
//            {
//                RB0 = !RB0;
//                RB1 = !RB1;
//                wait = 0;
//            }
//        }
//        else if(process_indicator() == e_ind_right)
//        {
//            RB6 = 0;
//            RB7 = 0;
//            if(++wait == 5)
//            {
//                RB6 = !RB6;
//                RB7 = !RB7;
//                wait = 0;
//            }
//        }
//        else if(process_indicator() == e_ind_off)
//        {
//            RB0 = 0;
//            RB1 = 0;
//            RB6 = 0;
//            RB7 = 0;
//        } 
    }
}
