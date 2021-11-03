/*   Author: Kushal Nesarkar
     Date : 10 August 2021
     Description :
                  Creating Hardware Thread Statically
     About Using Hardware Thread:
                   This program is about creating a Hardware Thread statically. 
                   Hardware Thread is a Highest priority thread in TI-RTOS.
                   To configure the Hardware thread first we need to configure Timer, Because timer will trigger HWI Thread.
                   In this program HWI thread is configured to Blink LED of Tiva Microcontroller.
*/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/drivers/GPIO.h>
#include "Board.h"


void Timer2A_Interrupt_Init(void);


void hwi_thread(UArg arg1)
{
        TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
        GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x80)   ;
        SysCtlDelay(13333333);
        GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);
        SysCtlDelay(13333333);
}

int main(void)
{
    Board_initGeneral();
    Board_initGPIO();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE ,0xF0);

    Timer2A_Interrupt_Init();

    BIOS_start();
    return (0);
}

void Timer2A_Interrupt_Init(void)
{
    uint32_t ui32Period;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerConfigure(TIMER2_BASE,TIMER_CFG_PERIODIC);
    ui32Period = (SysCtlClockGet()/ 2);
    TimerLoadSet(TIMER2_BASE, TIMER_A, ui32Period -1);
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER2_BASE,TIMER_A);
}
