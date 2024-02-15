#include "buzz.h"

// Correct GPIO initialization for the buzzer
void Buzzer_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    // Correct port and pin for the buzzer: GPIOB Pin 10
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // Enable the GPIO Clock for Port B
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure); // Initialize GPIOB instead of GPIOE
    GPIO_ResetBits(GPIOB, GPIO_Pin_10); // Ensure buzzer starts off
}

// Function to turn on the buzzer, adjusted for GPIOB Pin 10
void buzzer_on(void)
{
    PBout(10) = 0; // Turn the buzzer on (assuming 0 turns it on)
}

// Function to turn off the buzzer, adjusted for GPIOB Pin 10
void buzzer_off(void)
{
    PBout(10) = 1; // Turn the buzzer off (assuming 1 turns it off)
}

void buzzer_task(void *pvParameters)
{
    Buzzer_Init(); // Initialize the buzzer GPIO on the correct port and pin
    for(;;)
    {
        buzzer_on();
        vTaskDelay(pdMS_TO_TICKS(7000)); // On for 7 seconds
        buzzer_off();
        vTaskDelay(pdMS_TO_TICKS(7000)); // Off for 7 seconds
    }
}
