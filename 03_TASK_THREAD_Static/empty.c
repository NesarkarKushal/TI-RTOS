/*   Author: Kushal Nesarkar
     Date : 09 August 2021
     Description :
                  Creating Task Thread Statically
     About Using Idle Thread:

                  Task thread is 2nd lowest priority thread in TI-RTOS and runs after Highest priority thread.
                  Task thread will executes only once if there is no while(1) or any infinite loop. So if you want to run for infinite
                  times then we should go for while(1) or any infinite loop.
                  In this program there is only one Task Thread which will execute continuously ( Blinking of LED ) 
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
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x20);   //LED ON
    SysCtlDelay(13333333);                        // Approx 1 sec delay
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);   //LED OFF
    SysCtlDelay(13333333);                        // Approx 1 sec delay
    }
}


int main(void)
{
    Board_initGeneral();
    Board_initGPIO();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);  // Configure GPIO Periheral of Tiva Microcontroller using Tivaware library File.
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE ,0xF0); // Configuring GPIO Pins of the Peripheral.

    BIOS_start();

    return (0);
}
