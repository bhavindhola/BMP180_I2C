/* HAL-only entry function */
#include "hal_data.h"
#include <stdio.h>

#include "UART1.h"
#include "I2C1.h"
#include "BMP180.h"
#include "Timer.h"

void hal_entry(void)
{
    ssp_err_t error;
        uint8_t const bmp180Address = 0x77;
        uint8_t chipId;
        tBMP180_calibration_t calibrationFactors;
        float temperature;
        float pressure;


        /************************************
         * Init UART
         ************************************/
        error = UartInitialize ();
        if (error != SSP_SUCCESS)
        {
            while (true)
            {
            }
        }

        error = UartOpen ();
        if (error != SSP_SUCCESS)
        {
            while (true)
            {
            }
        }

        /************************************
         * Clear Console
         ************************************/
    #ifdef USE_VT100
        {
            // Use TTY100 commands to clear screen and reset screen pointer
            printf ("\033[2J"); // Clear Screen
            printf ("\033[H"); // Return Home
            printf ("\033[3J"); // Clear Back Buffer
        }
    #endif
        /************************************
         * Init Timer
         ************************************/
        printf ("Initializing Timer: ");
        error = TimerInitialize ();
        if (error != SSP_SUCCESS)
        {
            printf ("Failed.\r\n");
            while (true)
            {
            }
        }
        printf ("OK.\r\n");

        /************************************
         * Init I2C
         ************************************/
        printf ("Initializing I2C: ");
        error = I2CInitialize ();
        if (error != SSP_SUCCESS)
        {
            printf ("Failed.\r\n");
            while (true)
            {
            }
        }
        printf ("OK.\r\n");

        printf ("Opening I2C: ");
        error = I2COpen ();
        if (error != SSP_SUCCESS)
        {
            printf ("Failed.\r\n");
            while (true)
            {
            }
        }
        printf ("OK.\r\n");



        /************************************
         * Init BME280
         ************************************/
        printf ("Initializing BMP180: ");
        error = BMP180Initialize(bmp180Address);
        if (error != SSP_SUCCESS)
        {
            printf ("Failed.\r\n");
            while (true)
            {
            }
        }
        printf ("OK.\r\n");

        printf ("Opening BMP180: ");
        error = BMP180Open(bmp180Address);
        if (error != SSP_SUCCESS)
        {
            printf ("Failed.\r\n");
            while (true)
            {
            }
        }
        printf ("OK.\r\n");

        printf ("Chip ID: ");
        error = BMP180GetChipId(bmp180Address, &chipId);
        if (error != SSP_SUCCESS)
        {
            printf ("Failed.\r\n");
            while (true)
            {
            }
        }
        printf ("0x%02x\r\n", chipId);

        printf ("Retrieving BME280 Calibration Factors: ");
        // Get Calibration Factors
        error = BMP180GetCalibrationFactors(bmp180Address, &calibrationFactors);
        if (error != SSP_SUCCESS)
        {
            printf ("Failed.\r\n");
            while (true)
            {
            }
        }
        printf ("OK.\r\n");

        printf ("\r\n");



#ifdef USE_VT100
    {
        // Save Cursor Position
        printf ("\0337");
    }
#endif

    while (true)
    {
        // Get Temperature
        BMP180StartTemperature(bmp180Address, &calibrationFactors);
        BMP180GetTemperature(bmp180Address, &calibrationFactors, &temperature);
        BMP180StartPressureFine(bmp180Address, &calibrationFactors);
        BMP180GetPressure(bmp180Address, &calibrationFactors, &pressure);


        // Get Barometric Pressure
       // Bme280GetPressure (bme280Address, &calibrationFactors, &pressure);



        // Print Results To Screen
       // printf ("    Current Temp: %lf\r\n", temperature) ;
        //printf ("Current Pressure: %fhPa\r\n", pressure);

#ifdef USE_VT100
        {
            // Restore Cursor Position
            printf ("\0338");
        }
#endif

        TimerSleepMs (500);
    }
}




