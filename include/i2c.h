#pragma once
#include "common.h"
#include "peripherals/i2c.h"

typedef enum _i2c_status{
    I2CS_SUCCESS,
    I2CS_ACK_ERR,
    I2CS_DATA_LOSS,
    I2CS_CLCK_TIMEOUT
}i2c_status;

void i2c_init();
i2c_status i2c_send(u8 addr,u8 *buf,u32 size);
i2c_status i2c_recv(u8 addr,u8 *buf,u32 size);