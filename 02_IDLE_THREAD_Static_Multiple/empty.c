/*   Author: Kushal Nesarkar
     Date : 09 August 2021
     Description :
                  Creating Multiple Idle Thread Statically
     About Using Idle Thread:
                  Idle Thread is a also called background thread.
                  Idle thread is lowest priority thread in TI-RTOS and runs if no Highest priority is running.
                  In this program there are Three Idle Thread , the thread which has created first runs first,
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

Void IDLE_1(UArg arg0, UArg arg1)
{
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x20)   ;
    SysCtlDelay(13333333);
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);
    SysCtlDelay(13333333);

}

Void IDLE_2(UArg arg0, UArg arg1)
{
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x40)   ;
      SysCtlDelay(13333333);
      GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);
      SysCtlDelay(13333333);


}

Void IDLE_3(UArg arg0, UArg arg1)
{
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

    BIOS_start();

    return (0);
}
