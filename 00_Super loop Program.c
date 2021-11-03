/*   Author: Kushal Nesarkar
     Date : 09 August 2021
     Description :
                  Blinking of LED without Real Time Opertating System (RTOS).
*/

#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int main()
{

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , 0X0F);

    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, 0X0F, 0x02);
        SysCtlDelay(13333333);

        GPIOPinWrite(GPIO_PORTF_BASE, 0X0F, 0x00);
        SysCtlDelay(13333333);

    }
}
