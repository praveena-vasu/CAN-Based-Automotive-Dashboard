#include <xc.h>
#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "msg_id.h"
#include "uart.h"
#include "string.h"

unsigned char event[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C_"};

uint16_t get_speed()
{
    // Implement the speed function
    uint16_t msg_id; 
    uint8_t data[3]; 
    uint8_t len;
    
    uint8_t str[3]; 
    unsigned short speed = 0;
    speed = read_adc(CHANNEL4) / 10.33;
    str[0] = speed / 10 + '0';
    str[1] = speed % 10 + '0';
    str[3] = '\0';
    
    can_transmit(SPEED_MSG_ID, str, 2);
    __delay_ms(80);
    can_receive(&msg_id, data, &len);
    
    clcd_puts("SPEED: ", LINE1(0));
    clcd_putch(data[0], LINE1(7));
    clcd_putch(data[1], LINE1(8));
}

unsigned char get_gear_pos()
{
    // Implement the gear function
    static unsigned char index = 0, flag = 0;
    unsigned char current;
    current = read_switches(STATE_CHANGE);
    uint16_t msg_id; 
    uint8_t data[3]; 
    uint8_t len;
    uint8_t str[3]; 
    
    if(!flag)
    {
        clcd_puts("GEAR : ", LINE2(0));
        strcpy(str, event[index]);
        can_transmit(GEAR_MSG_ID, str, 2);
        __delay_ms(80);
        //can_receive(&msg_id, data, &len);
        data[2] = '\0';
        //clcd_puts(data, LINE2(7));
        //clcd_print(event, LINE2(7), index);
    }
    else
    {
        CLEAR_DISP_SCREEN;
        //clcd_print(event, LINE2(7), index);
        strcpy(str, event[index]);
        can_transmit(GEAR_MSG_ID, str, 2);
        __delay_ms(80);
        //can_receive(&msg_id, data, &len);
        data[2] = '\0';
        //clcd_puts(data, LINE2(7));
    }
    
    if((flag) && (current == 1 || current == 2))
    {
        index = 1;
        flag = 0;
    }
    else if(current == 1)
    {
        if(index < 7 && index >= 0)
            index++;
    }
    else if(current == 2)
    {
        if(index > 1 && index <= 7)
            index--;
    }
    else if(current == 3)
    {
        index = 8;
        flag = 1;
    }
}
