/*
 * File               : ECU3 main.c
 * Name Of The Project: CAN Based Automotive Dashboard
 * Job                : Receive Data from ECU1 & ECU2
 */
#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "isr.h"
#include "timer0.h"


unsigned static flag = 0;
static int init_leds() {
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
}

void __interrupt() isr()
{
    static unsigned count = 0;
    if(TMR0IF == 1)
    {
        TMR0 = TMR0 + 8;
        if(++count == 10000)
        {
            flag = !flag;
            count = 0;
        }
        TMR0IF = 0;
    }
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    init_leds();

    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
    init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();
    uint16_t msg_id; 
    uint8_t data[5]; 
    uint8_t len;
    unsigned long wait = 0;
    CLEAR_DISP_SCREEN;

    /* ECU1 main loop */
    while (1) {
        // Read CAN Bus data and handle it
        process_canbus_data();
        clcd_puts(" SPD", LINE1(0));
        clcd_puts(" GR", LINE1(4));
        clcd_puts(" RPM", LINE1(7));
        clcd_puts(" IND", LINE1(11));
        can_receive(&msg_id, data, &len);
        if(msg_id == SPEED_MSG_ID)
        {
            clcd_putch(data[0], LINE2(1));
            clcd_putch(data[1], LINE2(2));
        }
        else if(msg_id == GEAR_MSG_ID)
        {
            data[2] = '\0';
            clcd_puts(data, LINE2(5));
        }
        else if(msg_id == RPM_MSG_ID)
        {
            clcd_putch(data[0], LINE2(8));
            clcd_putch(data[1], LINE2(9));
            clcd_putch(data[2], LINE2(10));
            clcd_putch(data[3], LINE2(11));
        }
        else if(msg_id == INDICATOR_MSG_ID)
        {
            if(data[0] == '1')
            {
                RB6 = 0;
                RB7 = 0;
                if(flag)
                {
                    clcd_puts("<-", LINE2(13));
                    RB0 = 1;
                    RB1  = 1;
                }
                else
                {
                    RB0 = !RB0;
                    RB1 = !RB1;
                }
            }
            else if(data[0] == '2')
            {
                RB0 = 0;
                RB1 = 0;
                if(flag)
                {
                    clcd_puts("->", LINE2(13));
                    RB6 = 1;
                    RB7 = 1;
                }
                else
                {
                    RB6 = !RB6;
                    RB7 = !RB7;
                }
            }
            else if(data[0] == '0')
            {
                clcd_puts("--", LINE2(13));
                RB0 = 0;
                RB1 = 0;
                RB6 = 0;
                RB7 = 0;
            }
        }
    }
    return;
}

