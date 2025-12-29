#include "rtc.h"

/* ===========================
   Helper functions (private)
   =========================== */
static uint8_t BCDToDec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

static uint8_t DecToBCD(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

static void RTC_WriteRegister(I2C_Handle_t *hi2c, uint8_t reg, uint8_t data) {
    I2C_MasterSendData(hi2c, &reg, 1, DS3231_ADDR, I2C_ENABLE_SR);
    I2C_MasterSendData(hi2c, &data, 1, DS3231_ADDR, I2C_DISABLE_SR);
}

static uint8_t RTC_ReadRegister(I2C_Handle_t *hi2c, uint8_t reg) {
    uint8_t data;
    I2C_MasterSendData(hi2c, &reg, 1, DS3231_ADDR, I2C_ENABLE_SR);
    I2C_MasterReceiveData(hi2c, &data, 1, DS3231_ADDR, I2C_DISABLE_SR);
    return data;
}

/* ===========================
   Public functions
   =========================== */

void RTC_Init(I2C_Handle_t *hi2c) {
    // Nothing special for DS3231, just ensure I2C is initialized
    I2C_PeripheralControl(hi2c->pI2Cx, ENABLE);
    I2C_ManageAcking(hi2c->pI2Cx, I2C_ACK_ENABLE);
}

void RTC_SetTime(I2C_Handle_t *hi2c, RTC_Time *time) {
    RTC_WriteRegister(hi2c, 0x00, DecToBCD(time->sec));
    RTC_WriteRegister(hi2c, 0x01, DecToBCD(time->min));
    RTC_WriteRegister(hi2c, 0x02, DecToBCD(time->hour));
    RTC_WriteRegister(hi2c, 0x04, DecToBCD(time->date));
    RTC_WriteRegister(hi2c, 0x05, DecToBCD(time->month));
    RTC_WriteRegister(hi2c, 0x06, DecToBCD(time->year));
}

void RTC_GetTime(I2C_Handle_t *hi2c, RTC_Time *time) {
    time->sec   = BCDToDec(RTC_ReadRegister(hi2c, 0x00));
    time->min   = BCDToDec(RTC_ReadRegister(hi2c, 0x01));
    time->hour  = BCDToDec(RTC_ReadRegister(hi2c, 0x02));
    time->date  = BCDToDec(RTC_ReadRegister(hi2c, 0x04));
    time->month = BCDToDec(RTC_ReadRegister(hi2c, 0x05));
    time->year  = BCDToDec(RTC_ReadRegister(hi2c, 0x06));
}
