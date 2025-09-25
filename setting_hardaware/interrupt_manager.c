#include <xc.h>

void INTERRUPT_Initialize (void)
{
    RCONbits.IPEN = 1;      //enable Interrupt Priority mode
    INTCONbits.GIEH = 0;    //enable high priority interrupt
    INTCONbits.GIEL = 1;     //enable low priority interrupt
}
//enable=1 disable=0
