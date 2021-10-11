/*
 * Case 1
 */

#include<stdint.h>
#include<stdbool.h>
#include "driverlib/sysctl.h"

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>


#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <ti/sysbios/knl/Mailbox.h>
#include <ti/drivers/GPIO.h>

#include "Board.h"

#define timeout 12
extern Semaphore_Handle  semaphore0;
int n=8;
int buffer[8];
int count=0;

void Producer(UArg arg0, UArg arg1)
{
    int itemP=0;
    int in=0;

    while(1)
    {
        while(count==n) // check whether buffer is full or no
        {
            Task_sleep(1000);
        }

        buffer[in]=itemP;
        System_printf("Producing=%d\n",buffer[in]);
        System_flush();
        itemP+=1;
        in=(in+1);
        in=in%n;
        count=count+1;
//        System_printf("count=%d\n",count);
//        System_flush();
//        Task_sleep(1000);
    }
}



void Consumer(UArg arg0, UArg arg1)
{
    int itemC=0;
    int out=0;

    while(1)
    {
        while(count==0) //Check whether buffer is empty or not
        {
            Task_sleep(1000);
        }

        System_printf("Customer=%d\n",buffer[out]);
        System_flush();
        itemC=buffer[out];
        out=(out+1);
        out=out%n;
        count=count-1;

    }
}



int main(void)
{
    BIOS_start();

    return (0);
}
