/*
 * Critical section is a part of the program where resourses are accessed by various process
 */


#include<stdint.h>
#include<stdbool.h>
#include "driverlib/sysctl.h"

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>


#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <ti/sysbios/knl/Mailbox.h>
#include <ti/drivers/GPIO.h>

#include "Board.h"

#define timeout 12
extern Semaphore_Handle  semaphore0;

int data=1;


void Sender(UArg arg0, UArg arg1)
{
    while(1)
     {
        System_printf("Producer init\n");
        System_flush();
        data=2;
        Semaphore_post(semaphore0);
     }
}


void Critical_Section(UArg arg0, UArg arg1)
{

        System_printf("*************************\n");
        System_printf("Progress\n");
        System_printf("************************* \n");

    while(1)
    {
        Semaphore_pend(semaphore0,BIOS_WAIT_FOREVER);
        System_printf("Critical Condition=%d \n",data);
        System_flush();
        Task_sleep(1000);


    }
}


void Receiver(UArg arg0, UArg arg1)
{
    while(1)
    {
    System_printf("Consumer init\n");
    System_flush();
     data=5;
     Semaphore_post(semaphore0);

    }
}


int main(void)
{
    Board_initGeneral();
    Board_initGPIO();

    BIOS_start();

    return (0);
}
