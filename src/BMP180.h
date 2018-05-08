/*
 * BMW180.h
 *
 *  Created on: 08.11.2017
 *      Author: MJamil
 */

#ifndef BMP180_H_
#define BMP180_H_


#define BMP180_CHIP_ID                  0x55
#define BMP180_CHIP_ID_ADDRESS          0xD0
#define BMP180_CALIBRATION_DATA_START   0xAA
#define BMP180_CALIBRATION_DATA_LENGTH  11   /* 16 bit values */
#define BMP180_VERSION_REG                        0xD1
#define BMP180_CTRL_REG                           0xF4
#define BMP180_TEMP_MEASUREMENT_ADDRESS           0x2E
#define BMP180_PRESSURE_MEASUREMENT_ADDRESS       0x34
#define BMP180_PRESSURE_MEASUREMENT_ADDRESS_1     0x74
#define BMP180_PRESSURE_MEASUREMENT_ADDRESS_2     0xB4
#define BMP180_PRESSURE_MEASUREMENT_ADDRESS_3     0xF4
#define BMP180_CONVERSION_REGISTER_MSB            0xF6
#define BMP180_CONVERSION_REGISTER_LSB            0xF7
#define BMP180_CONVERSION_REGISTER_XLSB           0xF8
#define BMP180_TEMP_CONVERSION_TIME                  5
#define BMP180_VENDORID                           0x0001



typedef struct tBMP180_calibration_t
{
    int16_t R_AC1;
    int16_t R_AC2;
    int16_t R_AC3;
    uint16_t R_AC4;
    uint16_t R_AC5;
    uint16_t R_AC6;
    int16_t R_B1;
    int16_t R_B2;
    int16_t R_MB;
    int16_t R_MC;
    int16_t R_MD;
    double c5,c6,mc,md;

} tBMP180_calibration_t;


ssp_err_t BMP180Initialize(uint8_t const deviceAddress);
ssp_err_t BMP180GetChipId(uint8_t const deviceAddress, uint8_t * const chipId);
ssp_err_t BMP180Open(uint8_t const deviceAddress);
ssp_err_t BMP180Close(void);
ssp_err_t BMP180GetCalibrationFactors(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors);
ssp_err_t BMP180StartTemperature(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors);
ssp_err_t BMP180GetTemperature(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors, float * const temperature);
ssp_err_t BMP180StartPressureFine(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors);
//ssp_err_t BMP180StartPressureFine(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors, uint8_t const sampling);
ssp_err_t BMP180GetPressure(uint8_t const deviceAddress, tBMP180_calibration_t * const calibrationFactors, float * const pressure);



#endif /* BMP180_H_ */
