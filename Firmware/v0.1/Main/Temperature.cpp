#include "Configuration.h"
#include "Display.h"
#include "Temperature.h"
#include <Arduino.h>


#ifdef USE_MAX31855
    #include <Adafruit_MAX31855.h>
    Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
#endif

#ifdef USE_MAX6675
    #include <max6675.h>
    MAX6675 thermocouple(MAXCLK, MAXCS, MAXDO);
#endif


void Temperature_Init()
{
    #ifdef USE_MAX31855
        if (thermocouple.begin() == 0)
        {
            Display_Text_Center_Small("THERMOCOUPLE ERR", 0);
        }
    #endif
}

int16_t Temperature_Read_Ambient()
{
    #ifdef USE_MAX31855
        double temp_ambient = thermocouple.readInternal();

        if (isnan(temp_ambient))
        {
            Display_Text_Center_Small("THERMOCOUPLE ERR", 0);
            return 999;
        }

        return round(temp_ambient);
    #endif

    #ifdef USE_MAX6675
        return 21; // MAX6675 does not provide real ambient temperature
    #endif
}

int16_t Temperature_Read_Oven()
{
    double temp_oven = thermocouple.readCelsius();

    if (isnan(temp_oven))
    {
        Display_Text_Center_Small("THERMOCOUPLE ERR", 0);
        return 999;
    }

    return round(temp_oven);
}
