#include "platform.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

uint8_t VL53L4CD_RdDWord(Dev_t dev, uint16_t RegisterAdress, uint32_t *value) {
    uint8_t buffer[4];
    if (HAL_I2C_Mem_Read(&hi2c1, dev, RegisterAdress, I2C_MEMADD_SIZE_16BIT, buffer, 4, 100) != HAL_OK) return 255;
    *value = ((uint32_t)buffer[0] << 24) | ((uint32_t)buffer[1] << 16) | ((uint32_t)buffer[2] << 8) | (uint32_t)buffer[3];
    return 0;
}

uint8_t VL53L4CD_RdWord(Dev_t dev, uint16_t RegisterAdress, uint16_t *value) {
    uint8_t buffer[2];
    if (HAL_I2C_Mem_Read(&hi2c1, dev, RegisterAdress, I2C_MEMADD_SIZE_16BIT, buffer, 2, 100) != HAL_OK) return 255;
    *value = ((uint16_t)buffer[0] << 8) | (uint16_t)buffer[1];
    return 0;
}

uint8_t VL53L4CD_RdByte(Dev_t dev, uint16_t RegisterAdress, uint8_t *value) {
    if (HAL_I2C_Mem_Read(&hi2c1, dev, RegisterAdress, I2C_MEMADD_SIZE_16BIT, value, 1, 100) != HAL_OK) return 255;
    return 0;
}

uint8_t VL53L4CD_WrByte(Dev_t dev, uint16_t RegisterAdress, uint8_t value) {
    if (HAL_I2C_Mem_Write(&hi2c1, dev, RegisterAdress, I2C_MEMADD_SIZE_16BIT, &value, 1, 100) != HAL_OK) return 255;
    return 0;
}

uint8_t VL53L4CD_WrWord(Dev_t dev, uint16_t RegisterAdress, uint16_t value) {
    uint8_t buffer[2];
    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;
    if (HAL_I2C_Mem_Write(&hi2c1, dev, RegisterAdress, I2C_MEMADD_SIZE_16BIT, buffer, 2, 100) != HAL_OK) return 255;
    return 0;
}

uint8_t VL53L4CD_WrDWord(Dev_t dev, uint16_t RegisterAdress, uint32_t value) {
    uint8_t buffer[4];
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
    if (HAL_I2C_Mem_Write(&hi2c1, dev, RegisterAdress, I2C_MEMADD_SIZE_16BIT, buffer, 4, 100) != HAL_OK) return 255;
    return 0;
}

uint8_t VL53L4CD_WaitMs(Dev_t dev, uint32_t TimeMs) {
    HAL_Delay(TimeMs);
    return 0;
}
