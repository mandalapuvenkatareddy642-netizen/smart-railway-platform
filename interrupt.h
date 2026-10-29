//interrupt.h
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "types.h"

// 'extern' allows main.c to read this variable without recreating it
extern volatile u8 admin_menu_flag; 

void EINT0_INIT(void);
void MENU_ISR(void) __irq;

#endif
