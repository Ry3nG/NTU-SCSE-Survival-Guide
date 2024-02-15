#include "show.h"

// Global variable to keep track of time
static long seconds = 0;

void show_task(void *pvParameters)
{
   u32 lastWakeTime = getSysTickCnt();
   while(1)
    {	

			vTaskDelayUntil(&lastWakeTime, F2T(RATE_1_HZ));

			oled_show();    
    }
}  


void oled_show(void)
{
    char buffer[30]; // Buffer to hold the timer string

    // Clear the OLED display
    //OLED_Clear();
	
    OLED_ShowString(0, 10, (uint8_t *)"Gong Zerui");

    // Display the timer
    sprintf(buffer, "Time: %lu s", seconds++);
    OLED_ShowString(0, 40, (uint8_t *)buffer);

    // Refresh the OLED RAM to update the display
    OLED_Refresh_Gram(); 
}

