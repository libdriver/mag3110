/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_mag3110.c
 * @brief     driver mag3110 source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-08-18
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/08/18  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_mag3110.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "NXP MAG3110"        /**< chip name */
#define MANUFACTURER_NAME         "NXP"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.95f                /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                 /**< chip max supply voltage */
#define MAX_CURRENT               0.9f                 /**< chip max current */
#define TEMPERATURE_MIN           -40.0f               /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                /**< chip max operating temperature */
#define DRIVER_VERSION            1000                 /**< driver version */

/**
 * @brief iic address definition
 */
#define MAG3110_ADDRESS           (0x0E << 1)        /**< iic address */

/**
 * @brief chip register definition
 */
#define MAG3110_REG_DR_STATUS        0x00      /**< status register */
#define MAG3110_REG_OUT_X_MSB        0x01      /**< out x msb register */
#define MAG3110_REG_OUT_X_LSB        0x02      /**< out x lsb register */
#define MAG3110_REG_OUT_Y_MSB        0x03      /**< out y msb register */
#define MAG3110_REG_OUT_Y_LSB        0x04      /**< out y lsb register */
#define MAG3110_REG_OUT_Z_MSB        0x05      /**< out z msb register */
#define MAG3110_REG_OUT_Z_LSB        0x06      /**< out z lsb register */
#define MAG3110_REG_WHO_AM_I         0x07      /**< who am i register */
#define MAG3110_REG_SYSMOD           0x08      /**< sysmod register */
#define MAG3110_REG_OFF_X_MSB        0x09      /**< off x msb register */
#define MAG3110_REG_OFF_X_LSB        0x0A      /**< off x lsb register */
#define MAG3110_REG_OFF_Y_MSB        0x0B      /**< off y msb register */
#define MAG3110_REG_OFF_Y_LSB        0x0C      /**< off y lsb register */
#define MAG3110_REG_OFF_Z_MSB        0x0D      /**< off z msb register */
#define MAG3110_REG_OFF_Z_LSB        0x0E      /**< off z lsb register */
#define MAG3110_REG_DIE_TEMP         0x0F      /**< die temp register */
#define MAG3110_REG_CTRL_REG1        0x10      /**< ctrl reg1 register */
#define MAG3110_REG_CTRL_REG2        0x11      /**< ctrl reg2 register */

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[in]  reg register
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_mag3110_iic_read(mag3110_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_read(MAG3110_ADDRESS, reg, (uint8_t *)buf, len) != 0)        /* read data */
    {
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] reg register
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_mag3110_iic_write(mag3110_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_write(MAG3110_ADDRESS, reg, (uint8_t *)buf, len) != 0)        /* write data */
    {
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

/**
 * @brief      get data ready status
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get data ready status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_data_ready_status(mag3110_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_DR_STATUS, status, 1);        /* read status config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("mag3110: read status failed.\n");                 /* read status failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

/**
 * @brief      get mode status
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *mode pointer to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_mode_status(mag3110_handle_t *handle, mag3110_mode_status_t *mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_SYSMOD, &prev, 1);         /* read mode config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                           /* return error */
    }
    *mode = (mag3110_mode_status_t)((prev >> 0) & 0x03);                    /* set mode */
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      convert the offset to the register raw data
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[in]  ut offset threshold
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_offset_convert_to_register(mag3110_handle_t *handle, float ut, uint16_t *reg)
{
    int16_t r;
    
    if (handle == NULL)              /* check handle */
    {
        return 2;                    /* return error */
    }
    if (handle->inited != 1)         /* check handle initialization */
    {
        return 3;                    /* return error */
    }
    
    r = (int16_t)(ut / 0.1f);        /* convert real data to register data */
    r &= ~(1 << 15);                 /* clear bit */
    *reg = (uint16_t)(r);            /* set register */
    
    return 0;                        /* success return 0 */
}

/**
 * @brief      convert the register raw data to the offset threshold
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[in]  reg register raw data
 * @param[out] *ut pointer to an offset threshold buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_offset_convert_to_data(mag3110_handle_t *handle, uint16_t reg, float *ut)
{
    int16_t r;
    
    if (handle == NULL)              /* check handle */
    {
        return 2;                    /* return error */
    }
    if (handle->inited != 1)         /* check handle initialization */
    {
        return 3;                    /* return error */
    }
    
    r = (int16_t)reg;                /* set register */
    if ((r & (1 << 14)) != 0)        /* check bit 14 */
    {
        r |= (1 << 15);              /* set bit 15 */
    }
    *ut = (float)(r) * 0.1f;         /* convert raw data to real data */
    
    return 0;                        /* success return 0 */
}

/**
 * @brief     set offset x
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] offset set offset
 * @return    status code
 *            - 0 success
 *            - 1 set offset x failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 offset > 0x8000
 * @note      none
 */
uint8_t mag3110_set_offset_x(mag3110_handle_t *handle, uint16_t offset)
{
    uint8_t res;
    uint16_t prev;
    uint8_t buf[2];
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (offset > 0x8000U)                                                   /* check offset */
    {
        handle->debug_print("mag3110: offset > 0x8000.\n");                 /* offset > 0x8000 */
        
        return 4;                                                           /* return error */
    }
    
    prev = offset << 1;                                                     /* set offset */
    buf[0] = (prev >> 8) & 0xFF;                                            /* set msb */
    buf[1] = (prev >> 0) & 0xFF;                                            /* set lsb */
    res = a_mag3110_iic_write(handle, MAG3110_REG_OFF_X_MSB, buf, 2);       /* write offset */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write offset failed.\n");             /* write offset failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      get offset x
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *offset pointer to an offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get offset x failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_offset_x(mag3110_handle_t *handle, uint16_t *offset)
{
    uint8_t res;
    uint16_t prev;
    uint8_t buf[2];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_OFF_X_MSB, buf, 2);       /* read offset */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("mag3110: read offset failed.\n");             /* read offset failed */
        
        return 1;                                                          /* return error */
    }
    prev = ((uint16_t)buf[0] << 8) | buf[1];                               /* set prev */
    *offset = prev >> 1;                                                   /* set offset */
    
    return 0;                                                              /* success return 0 */
}

/**
 * @brief     set offset y
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] offset set offset
 * @return    status code
 *            - 0 success
 *            - 1 set offset y failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 offset > 0x8000
 * @note      none
 */
uint8_t mag3110_set_offset_y(mag3110_handle_t *handle, uint16_t offset)
{
    uint8_t res;
    uint16_t prev;
    uint8_t buf[2];
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (offset > 0x8000U)                                                   /* check offset */
    {
        handle->debug_print("mag3110: offset > 0x8000.\n");                 /* offset > 0x8000 */
        
        return 4;                                                           /* return error */
    }
    
    prev = offset << 1;                                                     /* set offset */
    buf[0] = (prev >> 8) & 0xFF;                                            /* set msb */
    buf[1] = (prev >> 0) & 0xFF;                                            /* set lsb */
    res = a_mag3110_iic_write(handle, MAG3110_REG_OFF_Y_MSB, buf, 2);       /* write offset */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write offset failed.\n");             /* write offset failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      get offset y
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *offset pointer to an offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get offset y failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_offset_y(mag3110_handle_t *handle, uint16_t *offset)
{
    uint8_t res;
    uint16_t prev;
    uint8_t buf[2];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_OFF_Y_MSB, buf, 2);       /* read offset */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("mag3110: read offset failed.\n");             /* read offset failed */
        
        return 1;                                                          /* return error */
    }
    prev = ((uint16_t)buf[0] << 8) | buf[1];                               /* set prev */
    *offset = prev >> 1;                                                   /* set offset */
    
    return 0;                                                              /* success return 0 */
}

/**
 * @brief     set offset z
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] offset set offset
 * @return    status code
 *            - 0 success
 *            - 1 set offset z failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 offset > 0x8000
 * @note      none
 */
uint8_t mag3110_set_offset_z(mag3110_handle_t *handle, uint16_t offset)
{
    uint8_t res;
    uint16_t prev;
    uint8_t buf[2];
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (offset > 0x8000U)                                                   /* check offset */
    {
        handle->debug_print("mag3110: offset > 0x8000.\n");                 /* offset > 0x8000 */
        
        return 4;                                                           /* return error */
    }
    
    prev = offset << 1;                                                     /* set offset */
    buf[0] = (prev >> 8) & 0xFF;                                            /* set msb */
    buf[1] = (prev >> 0) & 0xFF;                                            /* set lsb */
    res = a_mag3110_iic_write(handle, MAG3110_REG_OFF_Z_MSB, buf, 2);       /* write offset */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write offset failed.\n");             /* write offset failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      get offset z
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *offset pointer to an offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get offset z failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_offset_z(mag3110_handle_t *handle, uint16_t *offset)
{
    uint8_t res;
    uint16_t prev;
    uint8_t buf[2];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_OFF_Z_MSB, buf, 2);       /* read offset */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("mag3110: read offset failed.\n");             /* read offset failed */
        
        return 1;                                                          /* return error */
    }
    prev = ((uint16_t)buf[0] << 8) | buf[1];                               /* set prev */
    *offset = prev >> 1;                                                   /* set offset */
    
    return 0;                                                              /* success return 0 */
}

/**
 * @brief      read die temperature
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *raw pointer to a raw buffer
 * @param[out] *degree pointer to a converted degree buffer
 * @return     status code
 *             - 0 success
 *             - 1 read die temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_read_die_temperature(mag3110_handle_t *handle, int8_t *raw, float *degree)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_DIE_TEMP, &prev, 1);       /* read die temp */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read die temp failed.\n");            /* read die temp failed */
        
        return 1;                                                           /* return error */
    }
    *raw = (int8_t)prev;                                                    /* set raw */
    *degree = (float)(*raw);                                                /* set degree */
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     set rate over sample
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] rate_over_sample rate over sample
 * @return    status code
 *            - 0 success
 *            - 1 set rate over sample failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mag3110_set_rate_over_sample(mag3110_handle_t *handle, mag3110_rate_over_sample_t rate_over_sample)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(0x1F << 3);                                                   /* clear settings */
    prev |= (rate_over_sample << 3);                                        /* set settings */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG1, &prev, 1);     /* write ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");               /* write ctrl failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      get rate over sample
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *rate_over_sample pointer to a rate over sample buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rate over sample failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_rate_over_sample(mag3110_handle_t *handle, mag3110_rate_over_sample_t *rate_over_sample)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    *rate_over_sample = (mag3110_rate_over_sample_t)((prev >> 3) & 0x1F);   /* set rate over sample */
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     enable or disable fast read mode
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set fast read mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mag3110_set_fast_read_mode(mag3110_handle_t *handle, mag3110_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(1 << 2);                                                      /* clear settings */
    prev |= (enable << 2);                                                  /* set bool */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG1, &prev, 1);     /* write ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");               /* write ctrl failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      get fast read mode status
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fast read mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_fast_read_mode(mag3110_handle_t *handle, mag3110_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    *enable = (mag3110_bool_t)((prev >> 2) & 0x01);                         /* set bool */
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     enable or disable trigger mode
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set trigger mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mag3110_set_trigger_mode(mag3110_handle_t *handle, mag3110_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(1 << 1);                                                      /* clear settings */
    prev |= (enable << 1);                                                  /* set bool */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG1, &prev, 1);     /* write ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");               /* write ctrl failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      get trigger mode status
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get trigger mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_trigger_mode(mag3110_handle_t *handle, mag3110_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    *enable = (mag3110_bool_t)((prev >> 1) & 0x01);                         /* set bool */
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     set mode
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mag3110_set_mode(mag3110_handle_t *handle, mag3110_mode_t mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(1 << 0);                                                      /* clear settings */
    prev |= (mode << 0);                                                    /* set mode */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG1, &prev, 1);     /* write ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");               /* write ctrl failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      get mode
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *mode pointer to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_mode(mag3110_handle_t *handle, mag3110_mode_t *mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    *mode = (mag3110_mode_t)((prev >> 0) & 0x01);                           /* set mode */
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     enable or disable automatic magnetic sensor reset
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set automatic magnetic sensor reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mag3110_set_automatic_magnetic_sensor_reset(mag3110_handle_t *handle, mag3110_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG2, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(1 << 7);                                                      /* clear settings */
    prev |= (enable << 7);                                                  /* set bool */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG2, &prev, 1);     /* write ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");               /* write ctrl failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     enable or disable offset correction
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set disable offset correction failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mag3110_set_disable_offset_correction(mag3110_handle_t *handle, mag3110_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG2, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(1 << 5);                                                      /* clear settings */
    prev |= (enable << 5);                                                  /* set bool */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG2, &prev, 1);     /* write ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");               /* write ctrl failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief      get offset correction status
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get disable offset correction failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_disable_offset_correction(mag3110_handle_t *handle, mag3110_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG2, &prev, 1);      /* read ctrl config */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                /* read ctrl failed */
        
        return 1;                                                           /* return error */
    }
    *enable = (mag3110_bool_t)((prev >> 5) & 0x01);                         /* set bool */
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     reset
 * @param[in] *handle pointer to a mag3110 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 reset timeout
 * @note      none
 */
uint8_t mag3110_reset(mag3110_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    uint16_t timeout = 1000;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG2, &prev, 1);            /* read ctrl config */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                      /* read ctrl failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(1 << 4);                                                            /* clear settings */
    prev |= (1 << 4);                                                             /* set bool */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG2, &prev, 1);           /* write ctrl config */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");                     /* write ctrl failed */
        
        return 1;                                                                 /* return error */
    }
    while (timeout != 0)                                                          /* check timeout */
    {
        handle->delay_ms(1);                                                      /* delay 1ms */
        res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG2, &prev, 1);        /* read ctrl config */
        if (res != 0)                                                             /* check result */
        {
            handle->debug_print("mag3110: read ctrl failed.\n");                  /* read ctrl failed */
            
            return 1;                                                             /* return error */
        }
        if ((prev & (1 << 4)) == 0)                                               /* check the flag */
        {
            return 0;                                                             /* success return 0 */
        }
        timeout--;                                                                /* timeout-- */
    }
    handle->debug_print("mag3110: reset failed.\n");                              /* reset failed */
    
    return 4;                                                                     /* return error */
}

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a mag3110 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 id is invalid
 *            - 5 reset timeout
 * @note      none
 */
uint8_t mag3110_init(mag3110_handle_t *handle)
{
    uint8_t res;
    uint8_t id;
    uint8_t prev;
    uint8_t done;
    uint16_t timeout = 1000;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->debug_print == NULL)                                              /* check debug_print */
    {
        return 3;                                                                 /* return error */
    }
    if (handle->iic_init == NULL)                                                 /* check iic_init */
    {
        handle->debug_print("mag3110: iic_init is null.\n");                      /* iic_init is null */
        
        return 3;                                                                 /* return error */
    }
    if (handle->iic_deinit == NULL)                                               /* check iic_deinit */
    {
        handle->debug_print("mag3110: iic_deinit is null.\n");                    /* iic_deinit is null */
        
        return 3;                                                                 /* return error */
    }
    if (handle->iic_read == NULL)                                                 /* check iic_read */
    {
        handle->debug_print("mag3110: iic_read is null.\n");                      /* iic_read is null */
        
        return 3;                                                                 /* return error */
    }
    if (handle->iic_write == NULL)                                                /* check iic_write */
    {
        handle->debug_print("mag3110: iic_write is null.\n");                     /* iic_write is null */
        
        return 3;                                                                 /* return error */
    }
    if (handle->delay_ms == NULL)                                                 /* check delay_ms */
    {
        handle->debug_print("mag3110: delay_ms is null.\n");                      /* delay_ms is null */
        
        return 3;                                                                 /* return error */
    }
    
    if (handle->iic_init() != 0)                                                  /* iic init */
    {
        handle->debug_print("mag3110: iic init failed.\n");                       /* iic init failed */
        
        return 1;                                                                 /* return error */
    }
    if (handle->iic_read(MAG3110_ADDRESS, MAG3110_REG_WHO_AM_I,
                        (uint8_t *)&id, 1) != 0)                                  /* read id failed */
    {
        handle->debug_print("mag3110: read id failed.\n");                        /* read id failed */
        (void)handle->iic_deinit();                                               /* iic deinit */
        
        return 1;                                                                 /* return error */
    }
    if (id != 0xC4)                                                               /* check id */
    {
        handle->debug_print("mag3110: id is invalid.\n");                         /* id is invalid */
        (void)handle->iic_deinit();                                               /* iic deinit */
        
        return 4;                                                                 /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG2, &prev, 1);            /* read ctrl config */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                      /* read ctrl failed */
        (void)handle->iic_deinit();                                               /* iic deinit */
        
        return 5;                                                                 /* return error */
    }
    prev |= (1 << 4);                                                             /* set bool */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG2, &prev, 1);           /* write ctrl config */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");                     /* write ctrl failed */
        (void)handle->iic_deinit();                                               /* iic deinit */
        
        return 5;                                                                 /* return error */
    }
    done = 0;                                                                     /* init 0 */
    while (timeout != 0)                                                          /* check timeout */
    {
        handle->delay_ms(1);                                                      /* delay 1ms */
        res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG2, &prev, 1);        /* read ctrl config */
        if (res != 0)                                                             /* check result */
        {
            handle->debug_print("mag3110: read ctrl failed.\n");                  /* read ctrl failed */
            (void)handle->iic_deinit();                                           /* iic deinit */
            
            return 5;                                                             /* return error */
        }
        if ((prev & (1 << 4)) == 0)                                               /* check the flag */
        {
            done = 1;                                                             /* set done */
            
            break;                                                                /* break */
        }
        timeout--;                                                                /* timeout-- */
    }
    if (done == 0)                                                                /* check done */
    {
        handle->debug_print("mag3110: reset timeout.\n");                         /* reset timeout */
        (void)handle->iic_deinit();                                               /* iic deinit */
        
        return 5;                                                                 /* return error */
    }
    handle->inited = 1;                                                           /* flag finish initialization */
    
    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a mag3110 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t mag3110_deinit(mag3110_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);         /* read ctrl config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                   /* read ctrl failed */
        
        return 4;                                                              /* return error */
    }
    prev &= ~(1 << 0);                                                         /* clear settings */
    res = a_mag3110_iic_write(handle, MAG3110_REG_CTRL_REG1, &prev, 1);        /* write ctrl config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("mag3110: write ctrl failed.\n");                  /* write ctrl failed */
        
        return 4;                                                              /* return error */
    }
    if (handle->iic_deinit() != 0)                                             /* iic deinit */
    {
        handle->debug_print("mag3110: iic deinit failed.\n");                  /* return error */
        
        return 1;                                                              /* iic deinit failed */
    }   
    handle->inited = 0;                                                        /* flag close */
    
    return 0;                                                                  /* success return 0 */
}

/**
 * @brief      read data
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[out] *raw pointer to a raw data buffer
 * @param[out] *ut pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 read timeout
 * @note       none
 */
uint8_t mag3110_read(mag3110_handle_t *handle, int16_t raw[3], float ut[3])
{
    uint8_t res;
    uint8_t prev;
    uint8_t status;
    uint8_t buf[6];
    uint16_t timeout = 1000;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_mag3110_iic_read(handle, MAG3110_REG_CTRL_REG1, &prev, 1);                  /* read ctrl config */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("mag3110: read ctrl failed.\n");                            /* read ctrl failed */
        
        return 1;                                                                       /* return error */
    }
    if ((prev & (1 << 1)) != 0)                                                         /* check trigger mode */
    {
        while (timeout != 0)                                                            /* check timeout */
        {
            handle->delay_ms(1);                                                        /* delay 1ms */
            timeout--;                                                                  /* timeout-- */
            res = a_mag3110_iic_read(handle, MAG3110_REG_DR_STATUS, &status, 1);        /* read status config */
            if (res != 0)                                                               /* check result */
            {
                handle->debug_print("mag3110: read status failed.\n");                  /* read status failed */
                
                return 1;                                                               /* return error */
            }
            if ((status & (1 << 3)) != 0)                                               /* check date ready */
            {
                break;                                                                  /* break */
            }
        }
        if (timeout == 0)                                                               /* check timeout */
        {
            handle->debug_print("mag3110: read timeout.\n");                            /* read timeout */
            
            return 4;                                                                   /* return error */
        }
    }
    if ((prev & (1 << 2)) != 0)                                                         /* fast read */
    {
        res = a_mag3110_iic_read(handle, MAG3110_REG_OUT_X_MSB, buf, 3);                /* read data config */
        if (res != 0)                                                                   /* check result */
        {
            handle->debug_print("mag3110: read data failed.\n");                        /* read data failed */
            
            return 1;                                                                   /* return error */
        }
        raw[0] = (int16_t)(((uint16_t)buf[0] << 8) | 0x00);                             /* set x raw */
        raw[1] = (int16_t)(((uint16_t)buf[1] << 8) | 0x00);                             /* set y raw */
        raw[2] = (int16_t)(((uint16_t)buf[2] << 8) | 0x00);                             /* set z raw */
        ut[0] = (float)(raw[0]) * 0.1f;                                                 /* calculate x */
        ut[1] = (float)(raw[1]) * 0.1f;                                                 /* calculate y */
        ut[2] = (float)(raw[2]) * 0.1f;                                                 /* calculate z */
    }
    else                                                                                /* full */
    {
        res = a_mag3110_iic_read(handle, MAG3110_REG_OUT_X_MSB, buf, 6);                /* read data config */
        if (res != 0)                                                                   /* check result */
        {
            handle->debug_print("mag3110: read data failed.\n");                        /* read data failed */
            
            return 1;                                                                   /* return error */
        }
        raw[0] = (int16_t)(((uint16_t)buf[0] << 8) | buf[1]);                           /* set x raw */
        raw[1] = (int16_t)(((uint16_t)buf[2] << 8) | buf[3]);                           /* set y raw */
        raw[2] = (int16_t)(((uint16_t)buf[4] << 8) | buf[5]);                           /* set z raw */
        ut[0] = (float)(raw[0]) * 0.1f;                                                 /* calculate x */
        ut[1] = (float)(raw[1]) * 0.1f;                                                 /* calculate y */
        ut[2] = (float)(raw[2]) * 0.1f;                                                 /* calculate z */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mag3110_set_reg(mag3110_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                       /* check handle */
    {
        return 2;                                             /* return error */
    }
    if (handle->inited != 1)                                  /* check handle initialization */
    {
        return 3;                                             /* return error */
    } 
    
    return a_mag3110_iic_write(handle, reg, buf, len);        /* write data */
}

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a mag3110 handle structure
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mag3110_get_reg(mag3110_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                      /* check handle */
    {
        return 2;                                            /* return error */
    }
    if (handle->inited != 1)                                 /* check handle initialization */
    {
        return 3;                                            /* return error */
    } 
    
    return a_mag3110_iic_read(handle, reg, buf, len);        /* read data */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a mag3110 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mag3110_info(mag3110_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(mag3110_info_t));                        /* initialize mag3110 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
