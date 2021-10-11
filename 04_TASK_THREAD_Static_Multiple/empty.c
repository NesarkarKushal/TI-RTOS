/*   Author: Kushal Nesarkar
     Date : 09 August 2021
     Description :
                  Creating Multiple Task Thread
     About Using Multiple Task Thread:
                   If you are using Multiple Task thread without any Syncronization /communication only
                   one THread Which is having highest priority will work and then lowest priotity thread will work.
                   But if you are using SysctlDelay() API to provide delay only highest priority thread will work,
                   and other thread will not work. If you are using Task_Sleep() API other lowest priority thread
                   will work, because Task_Sleep() is configured with timer.
*/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>

/* Board Header file */
#include "Board.h"

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

Void Task_A(UArg arg0, UArg arg1)
{
    while(1)
    {
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x20)   ;
    SysCtlDelay(13333333);
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);
    SysCtlDelay(13333333);
    }
}

Void Task_B(UArg arg0, UArg arg1)
{
    while(1)
    {
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x40)   ;
    SysCtlDelay(13333333);
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);
    SysCtlDelay(13333333);
    }
}

Void Task_C(UArg arg0, UArg arg1)
{
    while(1)
    {
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x80)   ;
    SysCtlDelay(13333333);
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);
    SysCtlDelay(13333333);
    }
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
