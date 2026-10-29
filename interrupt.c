#include <LPC21xx.h>
#include "interrupt.h"

volatile u8 admin_menu_flag = 0;

void MENU_ISR(void) __irq
{
    // Set the flag so the main program can handle the menu change.
    admin_menu_flag = 1;

    // Clear the interrupt and signal the end of the ISR.
    EXTINT = (1 << 0);
    VICVectAddr = 0x00;
}

void EINT0_INIT(void)
{
    // Select P0.1 as EINT0.
    PINSEL0 &= ~(3 << 2);
    PINSEL0 |= (3 << 2);

    // Configure EINT0 for falling edge trigger.
    EXTMODE = (1 << 0);
    EXTPOLAR &= ~(1 << 0);

    // Set EINT0 in the VIC and enable the interrupt.
    VICIntSelect &= ~(1 << 14);
    VICVectAddr0 = (unsigned int)MENU_ISR;
    VICVectCntl0 = (1 << 5) | 14;
    VICIntEnable = (1 << 14);
}
