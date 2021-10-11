#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/drivers/GPIO.h>

#include "Board.h"
//# define Timeout 1000

extern Semaphore_Handle  semaphore0;

Void Task_A(UArg arg0, UArg arg1)
{
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x20)   ;
      SysCtlDelay(13333333);
      GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x00);
      SysCtlDelay(13333333);
    Semaphore_post(semaphore0);
    Task_sleep(1000);
}

Void Task_B(UArg arg0, UArg arg1)
{
    while(1)
    {
    Semaphore_pend(semaphore0,BIOS_WAIT_FOREVER);
    GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x40);
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
