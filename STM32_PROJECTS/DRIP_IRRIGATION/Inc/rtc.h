#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "stm32f446xx_i2c_driver.h"

// DS3231 I2C address
#define DS3231_ADDR 0x68

// RTC Time structure
typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} RTC_Time;

// Initialize RTC (I2C peripheral should already be initialized)
void RTC_Init(I2C_Handle_t *hi2c);

// Set time
void RTC_SetTime(I2C_Handle_t *hi2c, RTC_Time *time);

// Get time
void RTC_GetTime(I2C_Handle_t *hi2c, RTC_Time *time);

#endif /* INC_RTC_H_ */
