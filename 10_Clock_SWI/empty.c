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
#include <ti/sysbios/knl/Swi.h>
#include <ti/drivers/GPIO.h>

extern Swi_Handle swi0;

#include "Board.h"

void POST()
{
    Swi_post(swi0);
}


Void RED_LED(UArg arg0, UArg arg1)
{
   GPIOPinWrite(GPIO_PORTA_BASE, 0XF0 , 0x20);
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
