#include <avr/io.h>
#include <util/delay.h>

#define PIN_KEY PIND
#define PORT_LED PORTD

void SetupKeys(uint8_t* aK1, uint8_t* aK2, uint8_t* aK3, uint8_t* aK4);
void SetupLeds(uint8_t L1, uint8_t L2, uint8_t L3, uint8_t L4);


int main(void) {

    PORT_LED = 0x0F;   //setup as input
    DDRD = 0xF0;    //setup as output

    uint8_t aK1,aK2,aK3,aK4,L1,L2,L3,L4;


    //Declarations
    ////////////////////////////////////////

    char a,b,c,d;

    ////////////////////////////////////////


    while (1)
    {

        SetupKeys(&aK1, &aK2, &aK3, &aK4);

        //Loop instructions
        /////////////////////////////////

        a=aK1; b=aK2; c=aK3; d=aK4;

        //code goes here


        L1 = a; L2 = b; L3 = c; L4 = d;
        //////////////////////////////////


        SetupLeds(L1, L2, L3, L4);

        _delay_ms(100);

    }

}

void SetupLeds(uint8_t L1, uint8_t L2, uint8_t L3, uint8_t L4)
{
    if(L4)  PORT_LED |= 0b00010000;
    else    PORT_LED &= 0b11101111;

    if(L3)  PORT_LED |= 0b00100000;
    else    PORT_LED &= 0b11011111;

    if(L2)  PORT_LED |= 0b01000000;
    else    PORT_LED &= 0b10111111;

    if(L1)  PORT_LED |= 0b10000000;
    else    PORT_LED &= 0b01111111;
}

void SetupKeys(uint8_t* aK1, uint8_t* aK2, uint8_t* aK3, uint8_t* aK4)
{
    *aK4 = !(PIN_KEY & 0x01);
    *aK3 = !(PIN_KEY & 0x02);
    *aK2 = !(PIN_KEY & 0x04);
    *aK1 = !(PIN_KEY & 0x08);
}
