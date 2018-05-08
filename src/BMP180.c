/*
 * BME180.c
 *
 *  Created on: 08.11.2017
 *      Author: MJamil
 */
#include "hal_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "BMP180.h"
#include "I2C1.h"
#include "Timer.h"
#include "UART1.h"
#include "math.h"

ssp_err_t BMP180Initialize(uint8_t const deviceAddress)
{
    SSP_PARAMETER_NOT_USED(deviceAddress);

    return SSP_SUCCESS;
}

ssp_err_t BMP180GetChipId(uint8_t const deviceAddress, uint8_t * const chipId)
{
    ssp_err_t error;

    error = I2CWriteByte (deviceAddress, BMP180_CHIP_ID_ADDRESS, true);
    if (error != SSP_SUCCESS)
    {
        return error;
    }

    error = I2CReadByte (deviceAddress, chipId, false);
    if (error != SSP_SUCCESS)
    {
        return error;
    }

    return SSP_SUCCESS;
}

    ssp_err_t BMP180Open(uint8_t const deviceAddress)
    {
        ssp_err_t error;
        uint8_t chipId;

        error = BMP180GetChipId (deviceAddress, &chipId);
        if (error != SSP_SUCCESS)
        {
            return error;
        }

        if (chipId != BMP180_CHIP_ID)
        {
            return -1;
        }

        return SSP_SUCCESS;
    }

    ssp_err_t BMP180Close(void)
    {
        return SSP_SUCCESS;
    }

    ssp_err_t BMP180GetCalibrationFactors(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors)
    {
        // The BMP180 includes factory calibration data stored on the device.
        // Each device has different numbers, these must be retrieved and
       // used in the calculations when taking pressure measurements.
       // memory chunks.
       // The memory chunk starts at 0xAA
       uint8_t calibrationData_TEMP[22];



       ssp_err_t error;

       // Send calibration starting  memory address
       error = I2CWriteByte (deviceAddress, BMP180_CALIBRATION_DATA_START, true);
       if (error != SSP_SUCCESS)
           return error;

       // Read calibration data
       error = I2CRead (deviceAddress, calibrationData_TEMP, sizeof(calibrationData_TEMP), false);
       if (error != SSP_SUCCESS)
           return error;


       // Move data from the data buffers to the calibration factors and cast to the correct data type.

       calibrationFactors->R_AC1 =(int16_t) ((int16_t) (calibrationData_TEMP[0] << 8) | (int16_t) calibrationData_TEMP[1]);
       calibrationFactors->R_AC2 = (int16_t) ((int16_t) (calibrationData_TEMP[2] << 8) | (int16_t) calibrationData_TEMP[3]);
       calibrationFactors->R_AC3 = (int16_t) ((int16_t) (calibrationData_TEMP[4] << 8) | (int16_t) calibrationData_TEMP[5]);
       calibrationFactors->R_AC4 =(uint16_t) ((uint16_t) (calibrationData_TEMP[6] << 8) | (uint16_t) calibrationData_TEMP[7]);
       calibrationFactors->R_AC5 = (uint16_t) ((uint16_t) (calibrationData_TEMP[8] << 8) | (uint16_t) calibrationData_TEMP[9]);
       calibrationFactors->R_AC6 = (uint16_t) ((uint16_t) (calibrationData_TEMP[10] << 8) | (uint16_t) calibrationData_TEMP[11]);
       calibrationFactors->R_B1 =(int16_t) ((int16_t) (calibrationData_TEMP[12] << 8) | (int16_t) calibrationData_TEMP[13]);
       calibrationFactors->R_B2 = (int16_t) ((int16_t) (calibrationData_TEMP[14] << 8) | (int16_t) calibrationData_TEMP[15]);
       calibrationFactors->R_MB = (int16_t) ((int16_t) (calibrationData_TEMP[16] << 8) | (int16_t) calibrationData_TEMP[17]);
       calibrationFactors->R_MC =(int16_t) ((int16_t) (calibrationData_TEMP[18] << 8) | (int16_t) calibrationData_TEMP[19]);
       calibrationFactors->R_MD = (int16_t) ((int16_t) (calibrationData_TEMP[20] << 8) | (int16_t) calibrationData_TEMP[21]);


      return SSP_SUCCESS;
   }

    ssp_err_t BMP180StartTemperature(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors)
    {
        ssp_err_t error;


        const uint8_t data[] ={ BMP180_CTRL_REG, BMP180_TEMP_MEASUREMENT_ADDRESS };
            error = I2CWrite (deviceAddress, (uint8_t * const ) data, sizeof(data), false);
            if (error != SSP_SUCCESS)
            {
                return error;
            }
            else

                TimerSleepMs (5);
               return SSP_SUCCESS;
    }

    ssp_err_t BMP180GetTemperature(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors, float * const temperature)
    {
        ssp_err_t error;
        uint8_t data[2];
        int32_t UT;
        int32_t  X1, X2;
        int32_t T_REAL, T_IMAG;

         uint16_t AC5 = calibrationFactors->R_AC5;
         uint16_t AC6 = calibrationFactors->R_AC6;
         int16_t MC = calibrationFactors->R_MC;
         int16_t MD = calibrationFactors->R_MD;

        // Send Temperature Measurement Address
            error = I2CWriteByte (deviceAddress, BMP180_CONVERSION_REGISTER_MSB, true);
            if (error != SSP_SUCCESS)
                return error;

            // Read Temperature ADC Value
            error = I2CRead (deviceAddress, data, sizeof(data), false);
            if (error != SSP_SUCCESS)
                return error;

            // Convert ADC value to temperature
             UT = (((int32_t)data[0] << 8) | ((int32_t)data[1] << 0));
             printf("The value of  temperature register UT is : %d",UT);
             printf ("\r\n");
             X1 = (UT-AC6)*AC5*pow(2,-15);
             printf("The value of X1  is : %d",X1);
             printf ("\r\n");

             X2 = (MC*pow(2,11))/(X1+MD);
             printf("The value of X2  is : %d",X2);
             printf ("\r\n");

             T_REAL = (X1+X2)/160.0;
             printf("The final temperature Real part  is  : %d",T_REAL);
             printf ("\r\n");
             T_IMAG = (((X1+X2)/160.0)*1000) - (T_REAL*1000);
             printf("The final temperature imaginory part is  : %d",T_IMAG);
             printf ("\r\n");
             printf("The value of final temperature is %d.%d",T_REAL,T_IMAG);
             printf ("\r\n");

            return SSP_SUCCESS;
    }

    ssp_err_t BMP180StartPressureFine(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors)
    {
        ssp_err_t error;


                const uint8_t data[] ={ BMP180_CTRL_REG,BMP180_PRESSURE_MEASUREMENT_ADDRESS_3};
                    error = I2CWrite (deviceAddress, (uint8_t * const ) data, sizeof(data), false);
                    if (error != SSP_SUCCESS)
                    {
                        return error;
                    }
                    else

                        TimerSleepMs (26);
                       return SSP_SUCCESS;


    }
    ssp_err_t BMP180GetPressure(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors, float * const pressure)
    {
        ssp_err_t error;
        uint8_t data[3];
        int32_t UP;



        int16_t P_AC1 = calibrationFactors->R_AC1;
        int16_t P_AC2 = calibrationFactors->R_AC2;
        int16_t P_AC3 = calibrationFactors->R_AC3;
        uint16_t P_AC4 = calibrationFactors->R_AC4;
        uint16_t P_AC5 = calibrationFactors->R_AC5;
        uint16_t P_AC6 = calibrationFactors->R_AC6;
        int16_t P_B1 = calibrationFactors->R_B1;
        int16_t P_B2 = calibrationFactors->R_B2;
        int16_t P_MB = calibrationFactors->R_MB;
        int16_t P_MC = calibrationFactors->R_MC;
        int16_t P_MD = calibrationFactors->R_MD;
        printf("P_AC1:%d", P_AC1);
        printf ("\r\n");
        printf("P_AC2:%d", P_AC2);
        printf ("\r\n");
        printf("P_AC3:%d", P_AC3);
        printf ("\r\n");
        printf("P_AC4:%d", P_AC4);
        printf ("\r\n");
        printf("P_AC5:%d", P_AC5);
        printf ("\r\n");
        printf("P_AC6:%d", P_AC6);
        printf ("\r\n");
        printf("P_B1:%d", P_B1);
        printf ("\r\n");
        printf("P_B2:%d", P_B2);
        printf ("\r\n");
        printf("P_MB:%d", P_MB);
        printf ("\r\n");
        printf("P_MC:%d", P_MC);
        printf ("\r\n");
        printf("P_MD:%d", P_MD);
        printf ("\r\n");

        // Send Pressure Measurement Address
                    error = I2CWriteByte (deviceAddress, BMP180_CONVERSION_REGISTER_MSB, true);
                    if (error != SSP_SUCCESS)
                        return error;

                    // Read Pressure ADC Value
                    error = I2CRead (deviceAddress, data, sizeof(data), false);
                    if (error != SSP_SUCCESS)
                        return error;
      printf ("The value of data is %d and %d and %d", data[0],data[1],data[2]);
      printf ("\r\n");
                    // Convert ADC value to pressure
                     UP = ((data[0]<<16) | (data[1] << 8)| (data[2]>>0))>>4;
                     printf("The value of  pressure  register UP is : %d",UP);
                     printf ("\r\n");
                     printf ("\r\n");
                     printf ("\r\n");
                     printf ("\r\n");
                     printf ("\r\n");
                     int64_t x,y,z,p,p0,p1,p2;
                     int32_t s,c3,c4,b1,c5,c6,mc,md,T;
                     int32_t x0,x1,x2,y0,y1,y2;
                     int32_t P;


 T = 19.52;
 s = T - 25.0;
       c3 = 160.0 * pow(2,-15) * P_AC3;
        c4 = pow(10,-3) * pow(2,-15) * P_AC4;
        b1 = pow(160,2) * pow(2,-30) * P_B1;
        c5 = (pow(2,-15) / 160) * P_AC5;
        c6 = P_AC6;
        mc = (pow(2,11) / pow(160,2)) * P_MC;
        md = P_MD / 160.0;
        x0 = P_AC1;
        x1 = 160.0 * pow(2,-13) * P_AC2;
        x2 = pow(160,2) * pow(2,-25) * P_B2;
        y0 = c4 * pow(2,15);
        y1 = c4 * c3;
        y2 = c4 * b1;
        p0 = (3791.0 - 8.0) / 1600.0;
        p1 = 1.0 - 7357.0 * pow(2,-20);
        p2 = 3038.0 * 100.0 * pow(2,-36);
        x = (x2 * pow(s,2)) + (x1 * s) + x0;
        y = (y2 * pow(s,2)) + (y1 * s) + y0;
        z = (UP - x) / y;
        P = (p2 * pow(z,2)) + (p1 * z) + p0;

        printf("The value of  pressure   is : %d",P);
        printf ("\r\n");

        return SSP_SUCCESS;


    }










