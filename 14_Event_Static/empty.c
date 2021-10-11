/*Author: Kushal Nesarkar
  Date : 18 August 2021
  Description :
                 Implementing Event Module for synchronization communication Statically.
 *
 * Synchronization Module : Event
 *
 *  Event is a part of Synchronization module , which is used for communication between different
 *  task thread.
 *
 *  Configuration of Event module in TI-RTOS requires Semaphore as well, using the Event ID we can
 *  communicate with multiple task
 *
 *  In this program There are two task thread where they need to communicate with each other .
 *  from RED Task Thread we are sending the event id and in Green task thread we are receiving the event
 *  id and depending on event id I am running appropriate function.
 *
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Event.h>



/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>

#include "Board.h"

extern  Semaphore_Handle semaphore0;
extern Event_Handle event0;

int i;
void RED(UArg arg0, UArg arg1)
{
    while(1)
    {

        Event_post(event0,Event_Id_30);
        System_printf("RED");
        System_printf("\n");
        Task_sleep(1000);
    }
}

void Blue(UArg arg0, UArg arg1)
{
    while(1)
    {
        Event_post(event0,Event_Id_00);
        System_printf("Blue");
        System_printf("\n");
        Task_sleep(1000);
    }
}

void GREEN(UArg arg0, UArg arg1)
{
    uint16_t Event_post_0;

    while (1)
    {
        Event_post_0 = Event_pend(event0,Event_Id_NONE,Event_Id_00 + Event_Id_01 + Event_Id_02+Event_Id_30,BIOS_WAIT_FOREVER);

        System_printf("ID=%X",&Event_post_0);

        System_printf("\n");

      System_flush();

        if(Event_post_0 & Event_Id_00)
        {
                        GPIO_write(Board_LED2, Board_LED_ON);  //red
                     for( i=0;i<40000000;i++);
                        GPIO_write(Board_LED2, Board_LED_OFF);
                        for( i=0;i<40000000;i++);



        }

        else if(Event_post_0 & Event_Id_01)
        {
                                   GPIO_write(Board_LED1, Board_LED_ON); //green
                                   for( i=0;i<40000000;i++);

                                  GPIO_write(Board_LED1, Board_LED_OFF);
                                  for(i=0;i<40000000;i++);

        }

        else if(Event_post_0 & Event_Id_30)
             {
                                   GPIO_write(Board_LED0, Board_LED_ON); //blue
                                   for(i=0;i<40000000;i++);
                                  GPIO_write(Board_LED0, Board_LED_OFF);
                                  for(i=0;i<40000000;i++);

             }

        else
        {
            GPIO_write(Board_LED0, Board_LED_OFF);
            GPIO_write(Board_LED2, Board_LED_OFF);
            GPIO_write(Board_LED1, Board_LED_OFF);

        }
    }
}

int main(void)
{
    Board_initGeneral();
    Board_initGPIO();

    GPIO_write(Board_LED0, Board_LED_OFF);
    GPIO_write(Board_LED1, Board_LED_OFF);
    GPIO_write(Board_LED2, Board_LED_OFF);

    BIOS_start();

    return (0);
}
