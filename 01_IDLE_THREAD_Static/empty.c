/*   Author: Kushal Nesarkar
     Date : 09 August 2021
     Description :
                  Creating Idle Thread Statically
     About Using Idle Thread:
                  Idle Thread is a also called background thread.
                  Idle thread is lowest priority thread in TI-RTOS and runs if no Highest priority is running.
*/

#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>

/* Board Header file */
#include "Board.h"


Void IDLE_1(UArg arg0, UArg arg1)
{
    SysCtlDelay(13333333);
    GPIO_toggle(Board_LED1);

}


int main(void)
{
    Board_initGeneral();
    Board_initGPIO();

    BIOS_start();

    return (0);
}
