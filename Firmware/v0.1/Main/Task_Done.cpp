#include "Task_Done.h"
#include "Display.h"
#include "Input.h"
#include "State.h"
#include "Temperature.h"
#include "Output.h"
#include <Arduino.h>


void Task_Done()
{
    bool quit = 0;

    uint64_t current_millis = 0;
    uint64_t last_millis_process = 0;
    uint64_t last_millis_temp = 0;

    Output_1_Set(0);
    Output_2_Set(0);
    
    Display_Text_Center_Small("    DONE!   ", 1);
    Display_Option_C("RETURN");

    while (quit == 0)
    {
        current_millis = millis();

        if (current_millis >= (last_millis_process + 10))
        {
            last_millis_process = current_millis;

            Input_Process();
            Output_Process();

            if (Input_Read_C() == 1)
            {
                State_Set(MENU);
                quit = 1;
            }
        }

        if (current_millis >= (last_millis_temp + 1000))
        {
            last_millis_temp = current_millis;

            int16_t temp = Temperature_Read_Oven();

            Display_Temperature(temp, 3, COLOR_RED);
        }
    }
}
