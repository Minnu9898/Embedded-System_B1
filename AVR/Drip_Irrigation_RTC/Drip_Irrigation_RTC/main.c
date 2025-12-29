#define F_CPU 16000000UL  // Define the CPU clock frequency (16 MHz) for delay calculations

#include <avr/io.h>       // AVR input/output register definitions
#include <util/delay.h>   // Delay functions like _delay_ms()
#include "rtc.h"          // Include RTC header for time/date structures and functions

#define LED PD6           // Define LED pin (Port D, Pin 6)

RTC_TimeDate rtc;         // Create a structure variable to hold RTC time and date

int main(void)
{
	// Initialize the RTC (sets up I2C/TWI communication)
	RTC_Init();

	// Configure LED pin as output
	DDRD |= (1 << LED);   // Set PD6 as output by writing 1 to its DDRD bit

	while (1)  // Infinite loop to continuously check the time
	{
		// Read the current time from RTC and store it in the 'rtc' structure
		RTC_GetTime(&rtc);

		// Check if the current time is 5:00 PM (17:00 hours, 0 minutes)
		if (rtc.hours == 17 && rtc.minutes == 0)
		{
			// Blink LED 5 times to indicate 5 PM
			for (int i = 0; i < 5; i++)
			{
				PORTD |= (1 << LED);   // Turn LED ON by setting PD6 high
				_delay_ms(500);        // Wait for 500 milliseconds
				PORTD &= ~(1 << LED);  // Turn LED OFF by setting PD6 low
				_delay_ms(500);        // Wait for 500 milliseconds
			}
		}
		else
		{
			PORTD &= ~(1 << LED);      // Keep LED OFF if it is not 5 PM
		}

		_delay_ms(1000);  // Wait for 1 second before reading the RTC again
		// This reduces unnecessary I2C polling
	}
}