#include "ecu2_sensor.h"
#include "digital_keypad.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "ssd.h"
#define _XTAL_FREQ          20000000

uint16_t get_rpm()
{
    //Implement the rpm function
    uint16_t msg_id; 
    uint8_t data[5]; 
    uint8_t len;
    uint8_t str[5];
    
    uint8_t ssd[4];
    unsigned short rpm = read_adc(CHANNEL4);
    rpm = (rpm / 10.23) * 60;
    str[0] = '0' + (rpm / 1000);
    str[1] = '0' + ((rpm / 100) % 10);
    str[2] = '0' + ((rpm / 10) % 10);
    str[3] = '0' + (rpm % 10);
    str[4] = '\0';
    
    can_transmit(RPM_MSG_ID, str, 4);
    __delay_ms(80);
    //can_receive(&msg_id, data, &len);
    
//    ssd[0] = digit[data[0] - '0'];
//    ssd[1] = digit[data[1] - '0'];
//    ssd[2] = digit[data[2] - '0'];
//    ssd[3] = digit[data[3] - '0'];
    //display(ssd);
}

uint16_t get_engine_temp()
{
    //Implement the engine temperature function
}

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    uint16_t msg_id; 
    uint8_t data[1]; 
    uint8_t len;
    unsigned static char str;  
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    if(key == SWITCH1)
    {
        str = '1';
    }
    else if(key == SWITCH3)
    {
        str = '2';
    }
    else if(key == SWITCH2)
    {
        str = '0';
    }
    can_transmit(INDICATOR_MSG_ID, &str, 1);
    __delay_ms(80);
    //can_receive(&msg_id, data, &len);
    
    if(data[0] == '1')
        return e_ind_left;
    else if(data[0] == '2')
        return e_ind_right;
    else if(data[0] == '0')
        return e_ind_off;
}
