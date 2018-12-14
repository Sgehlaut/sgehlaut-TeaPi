#include "ds18b20.h"
#include "printf.h"
#include "gpio.h"
#include "temperature.h"


int getCurrTemp(ds18b20_t dev) 
{
    int currTemp16 = ds18b20_read_temperature(&dev); //Replace with the temperature read from the sensor
    int tempint = currTemp16 / 16;
    int tempfrac = currTemp16 & 0x0f;
    return ((double) tempint + (double) tempfrac / 16.0);
}

int main_test(void)
{
    int temp16;
    int tempint;
    int tempfrac;
    int found;
    double tempfloat;
    ds18b20_t dev;

    dev.pin = GPIO_PIN4;
    found = ds18b20_init(&dev);
    if (!found)
    {
        printf("DS18B20 not present\n");
        return -1;
    }

    temp16 = ds18b20_read_temperature(&dev);

    if (temp16 < TEMP_MIN || temp16 > TEMP_MAX)
    {
        switch(temp16)
        {
            case ENOTPRESENT:
                printf("DS18B20 not present\n");
                break;

            case ENAVAIL:
                printf("Temperature reading not available\n");
                break;

            case EBADCRC:
                printf("CRC error\n");
                break;

            default:
                printf("Unknown error: %d\n", temp16);
                break;
        }

        return -1;
    }

    /* temperature is within range so continue processing */
    tempint = temp16 / 16;
    tempfrac = temp16 & 0x0f;
    tempfloat = (double) tempint + (double) tempfrac / 16.0;
    printf("%d", (int)tempfloat);
    // printf("%d:%d\n", tempint, tempfrac);

    return 0;
}