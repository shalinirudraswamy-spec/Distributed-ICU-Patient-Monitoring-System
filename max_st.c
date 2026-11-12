#include <lpc21xx.h>

#include "max30102.h"

/* Register Write */

void MAX30102_WriteReg(u8 reg,u8 value)
{

    i2c_send(MAX30102_ADDR, reg, value);

}

/* Register Read */

u8 MAX30102_ReadReg(u8 reg)

{

    return i2c_read(MAX30102_ADDR, reg);

}

/* Software Reset */

void MAX30102_Reset(void)

{

    MAX30102_WriteReg(REG_MODE_CONFIG,0x40);

    while(MAX30102_ReadReg(REG_MODE_CONFIG) & 0x40);

    delay_ms(10);
}

/* Initialization */

void MAX30102_st(void)
{

    MAX30102_Reset();

    /* Disable interrupts */

    MAX30102_WriteReg(REG_INTR_ENABLE1,0x00);

    MAX30102_WriteReg(REG_INTR_ENABLE2,0x00);

    /* Clear FIFO */

    MAX30102_WriteReg(REG_FIFO_WR_PTR,0x00);

    MAX30102_WriteReg(REG_OVF_COUNTER,0x00);

    MAX30102_WriteReg(REG_FIFO_RD_PTR,0x00);

    /* FIFO Config */

    MAX30102_WriteReg(REG_FIFO_CONFIG,0x40);

    /* SPO2 Config

       ADC Range = 4096nA

       Sample Rate = 100Hz

       Pulse Width = 411us

    */

    MAX30102_WriteReg(REG_SPO2_CONFIG,0x27);


    /* LED Current */

    MAX30102_WriteReg(REG_LED1_PA,0x24);

    MAX30102_WriteReg(REG_LED2_PA,0x24);
 
    /* SPO2 Mode */

    MAX30102_WriteReg(REG_MODE_CONFIG,0x03);


    delay_ms(100);


    /* Clear interrupt flags */

    MAX30102_ReadReg(REG_INTR_STATUS1);

    MAX30102_ReadReg(REG_INTR_STATUS2);

}

/* FIFO Read */

void MAX30102_ReadFIFO(MAX30102_Data *sample)
{
    u8 data[6];

    i2c_read_buf(MAX30102_ADDR, REG_FIFO_DATA, data, 6);

    sample->red =

        (((u32)data[0]<<16) |

         ((u32)data[1]<<8) |

          data[2]) & 0x03FFFF;

    sample->ir =

        (((u32)data[3]<<16) |

         ((u32)data[4]<<8) |

          data[5]) & 0x03FFFF;

}