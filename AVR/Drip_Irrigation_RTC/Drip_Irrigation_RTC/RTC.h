#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>     // Include standard integer types like uint8_t

#define RTC_ADDRESS 0x68   // Define the I2C 7-bit address of DS3231 / DS1307 RTC

// Structure to hold RTC time and date values
typedef struct
{
	uint8_t seconds;  // Store seconds (0-59)
	uint8_t minutes;  // Store minutes (0-59)
	uint8_t hours;    // Store hours in 24-hour format (0-23)
	uint8_t day;      // Store day of the week (1-7)
	uint8_t date;     // Store date of the month (1-31)
	uint8_t month;    // Store month (1-12)
	uint8_t year;     // Store year (0-99 for 2000-2099)
} RTC_TimeDate;

/* ---------- Function Prototypes ---------- */

// Initialize the RTC by setting up the I2C (TWI) interface
void RTC_Init(void);

// Set the time and date into the RTC registers
// 'time' is a pointer to RTC_TimeDate structure containing desired values
void RTC_SetTime(RTC_TimeDate *time);

// Read the current time and date from the RTC registers
// Stores the values in the RTC_TimeDate structure pointed by 'time'
void RTC_GetTime(RTC_TimeDate *time);

// Convert a decimal value to BCD format
// BCD is required by RTC registers
uint8_t DecimalToBCD(uint8_t val);

// Convert a BCD value from RTC registers to decimal
uint8_t BCDToDecimal(uint8_t val);

#endif /* RTC_H_ */