/*   Author: Kushal Nesarkar
     Date : 10 August 2021
     Description :
                  Creating Multipl Hardware Thread Statically
     About Using Hardware Thread:
                   This program is about creating a Hardware Thread statically. 
                   Hardware Thread is a Highest priority thread in TI-RTOS.
                   To configure the Hardware thread first we need to configure Timer, Because timer will trigger HWI Thread.
                   In this program hardware_thread() has higest priority and hardware_thread_1() has lowest priority 
                   hardware_thread() is triggered by Timer_Init() and it blinks led_0 and triggers lowest priority thread,
                   in lowest priority thread led_1 will blink.The execution of these two thread will carry out through preemption manner.             
*/

#include<stdint.h>
#include<stdbool.h>
#include"driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/hal/Timer.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/drivers/GPIO.h>


#include "Board.h"

extern Timer_Handle timer0;
extern Timer_Handle timer1;

unsigned int period;

void Timer_Init(UArg arg0)
{
    period=Timer_getPeriod(timer0);
    Hwi_post(51);
}

void hardware_thread(UArg arg0)
{
       GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x40);
       SysCtlDelay(13333333);
       GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);
       SysCtlDelay(13333333);
       Hwi_post(86);

}

void hardware_thread_1(UArg arg0)
{
       GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x80);
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


    BIOS_start();

    return (0);
}

