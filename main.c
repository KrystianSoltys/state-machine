#include <avr/io.h>
#include <avr/interrupt.h>

#define PIN_KEY PIND
#define PORT_LED PORTD

static uint32_t ct=0, ct_ovf=0;

void SetupIO();
void SetupTimer(uint16_t ms);
void SetupKeys(uint8_t* aK1, uint8_t* aK2, uint8_t* aK3, uint8_t* aK4);
void SetupLeds(uint8_t L1, uint8_t L2, uint8_t L3, uint8_t L4);

static uint8_t aK1,aK2,aK3,aK4,L1,L2,L3,L4;

ISR (TIMER0_OVF_vect)
{
    ct++;
    if(ct >= ct_ovf)
    {
        SetupKeys(&aK1, &aK2, &aK3, &aK4);


        //Declarations
        ////////////////////////////////////////
        //    char x1,x2, Z1, Z2, Z3, Z4;
        ////////////////////////////////////////


        //Loop instructions
        ////////////////////////////////////////
        //   x1 = aK1; x2 = aK2;
        ////////////////////////////////////////


        //Display
        ////////////////////////////////////////
        //L1 = Z1; L2 = Z2; L3=Z3; L4=Z4;
        L1 = aK1; L2 = aK2; L3 = aK3; L4=aK4;
        ////////////////////////////////////////

        SetupLeds(L1, L2, L3, L4);
        ct=0;
    }

    TCNT0 = 0x00;
}

int main(void) {

    SetupIO();
    SetupTimer(100); //cycle duration in ms

    while(1){}
}




void SetupIO()
{
    PORT_LED = 0x0F;   //setup as input
    DDRD = 0xF0;    //setup as output
}

void SetupTimer(uint16_t ms)
{
    TIMSK0 |= (1 << TOIE0); //TIM1 interrupts on
    TCCR0B |= (1 << CS00);
    ct_ovf = (F_CPU*ms) / 256 / 1000;
    sei();  //enable interrupts
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


