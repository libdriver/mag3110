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
 * @file      driver_mag3110.h
 * @brief     driver mag3110 header file
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

#ifndef DRIVER_MAG3110_H
#define DRIVER_MAG3110_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup mag3110_driver mag3110 driver function
 * @brief    mag3110 driver modules
 * @{
 */

/**
 * @addtogroup mag3110_base_driver
 * @{
 */

/**
 * @brief mag3110 bool enumeration definition
 */
typedef enum
{
    MAG3110_BOOL_FALSE = 0x00,        /**< false */
    MAG3110_BOOL_TRUE  = 0x01,        /**< true */
} mag3110_bool_t;

/**
 * @brief mag3110 status enumeration definition
 */
typedef enum
{
    MAG3110_STATUS_ZYX_OVERWRITE = (1 << 7),        /**< x, y, z axis data overwrite */
    MAG3110_STATUS_Z_OVERWRITE   = (1 << 6),        /**< z axis data overwrite */
    MAG3110_STATUS_Y_OVERWRITE   = (1 << 5),        /**< y axis data overwrite */
    MAG3110_STATUS_X_OVERWRITE   = (1 << 4),        /**< x axis data overwrite */
    MAG3110_STATUS_ZYX_READY     = (1 << 3),        /**< x, y, z axis data ready */
    MAG3110_STATUS_Z_READY       = (1 << 2),        /**< z axis data ready */
    MAG3110_STATUS_Y_READY       = (1 << 1),        /**< y axis data ready */
    MAG3110_STATUS_X_READY       = (1 << 0),        /**< x axis data ready */
} mag3110_status_t;

/**
 * @brief mag3110 mode status enumeration definition
 */
typedef enum
{
    MAG3110_MODE_STATUS_STANDBY        = 0x00,        /**< standby mode */
    MAG3110_MODE_STATUS_ACTIVE_RAW     = 0x01,        /**< active mode, raw data mode */
    MAG3110_MODE_STATUS_ACTIVE_NON_RAW = 0x02,        /**< active mode, non-raw user-corrected data */
} mag3110_mode_status_t;

/**
 * @brief mag3110 mode enumeration definition
 */
typedef enum
{
    MAG3110_MODE_STANDBY = 0x00,        /**< standby mode */
    MAG3110_MODE_ACTIVE  = 0x01,        /**< active mode */
} mag3110_mode_t;

/**
 * @brief mag3110 rate over sample enumeration definition
 */
typedef enum
{
    MAG3110_RATE_80HZ_OVER_SAMPLE_16    = 0x00,        /**< 80hz, 16 over sample */
    MAG3110_RATE_40HZ_OVER_SAMPLE_32    = 0x01,        /**< 40hz, 32 over sample */
    MAG3110_RATE_20HZ_OVER_SAMPLE_64    = 0x02,        /**< 20hz, 64 over sample */
    MAG3110_RATE_10HZ_OVER_SAMPLE_128   = 0x03,        /**< 10hz, 128 over sample */
    MAG3110_RATE_40HZ_OVER_SAMPLE_16    = 0x04,        /**< 40hz, 16 over sample */
    MAG3110_RATE_20HZ_OVER_SAMPLE_32    = 0x05,        /**< 20hz, 32 over sample */
    MAG3110_RATE_10HZ_OVER_SAMPLE_64    = 0x06,        /**< 10hz, 64 over sample */
    MAG3110_RATE_5HZ_OVER_SAMPLE_128    = 0x07,        /**< 5hz, 128 over sample */
    MAG3110_RATE_20HZ_OVER_SAMPLE_16    = 0x08,        /**< 20hz, 16 over sample */
    MAG3110_RATE_10HZ_OVER_SAMPLE_32    = 0x09,        /**< 10hz, 32 over sample */
    MAG3110_RATE_5HZ_OVER_SAMPLE_64     = 0x0A,        /**< 5hz, 64 over sample */
    MAG3110_RATE_2P5HZ_OVER_SAMPLE_128  = 0x0B,        /**< 2.5hz, 128 over sample */
    MAG3110_RATE_10HZ_OVER_SAMPLE_16    = 0x0C,        /**< 10hz, 16 over sample */
    MAG3110_RATE_5HZ_OVER_SAMPLE_32     = 0x0D,        /**< 5hz, 32 over sample */
    MAG3110_RATE_2P5HZ_OVER_SAMPLE_64   = 0x0E,        /**< 2.5hz, 64 over sample */
    MAG3110_RATE_1P25HZ_OVER_SAMPLE_128 = 0x0F,        /**< 1.25hz, 128 over sample */
    MAG3110_RATE_5HZ_OVER_SAMPLE_16     = 0x10,        /**< 5hz, 16 over sample */
    MAG3110_RATE_2P5HZ_OVER_SAMPLE_32   = 0x11,        /**< 2.5hz, 32 over sample */
    MAG3110_RATE_1P25HZ_OVER_SAMPLE_64  = 0x12,        /**< 1.25hz, 64 over sample */
    MAG3110_RATE_0P63HZ_OVER_SAMPLE_128 = 0x13,        /**< 0.63hz, 128 over sample */
    MAG3110_RATE_2P5HZ_OVER_SAMPLE_16   = 0x14,        /**< 2.5hz, 16 over sample */
    MAG3110_RATE_1P25HZ_OVER_SAMPLE_32  = 0x15,        /**< 1.25hz, 32 over sample */
    MAG3110_RATE_0P63HZ_OVER_SAMPLE_64  = 0x16,        /**< 0.63hz, 64 over sample */
    MAG3110_RATE_0P31HZ_OVER_SAMPLE_128 = 0x17,        /**< 0.31hz, 128 over sample */
    MAG3110_RATE_1P25HZ_OVER_SAMPLE_16  = 0x18,        /**< 1.25hz, 16 over sample */
    MAG3110_RATE_0P63HZ_OVER_SAMPLE_32  = 0x19,        /**< 0.63hz, 32 over sample */
    MAG3110_RATE_0P31HZ_OVER_SAMPLE_64  = 0x1A,        /**< 0.31hz, 64 over sample */
    MAG3110_RATE_0P16HZ_OVER_SAMPLE_128 = 0x1B,        /**< 0.16hz, 128 over sample */
    MAG3110_RATE_0P63HZ_OVER_SAMPLE_16  = 0x1C,        /**< 0.63hz, 16 over sample */
    MAG3110_RATE_0P31HZ_OVER_SAMPLE_32  = 0x1D,        /**< 0.31hz, 32 over sample */
    MAG3110_RATE_0P16HZ_OVER_SAMPLE_64  = 0x1E,        /**< 0.16hz, 64 over sample */
    MAG3110_RATE_0P08HZ_OVER_SAMPLE_128 = 0x1F,        /**< 0.08hz, 128 over sample */
} mag3110_rate_over_sample_t;

/**
 * @brief mag3110 handle structure definition
 */
typedef struct mag3110_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
} mag3110_handle_t;

/**
 * @brief mag3110 information structure definition
 */
typedef struct mag3110_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} mag3110_info_t;

/**
 * @}
 */

/**
 * @defgroup mag3110_link_driver mag3110 link driver function
 * @brief    mag3110 link driver modules
 * @ingroup  mag3110_driver
 * @{
 */

/**
 * @brief     initialize mag3110_handle_t structure
 * @param[in] HANDLE pointer to a mag3110 handle structure
 * @param[in] STRUCTURE mag3110_handle_t
 * @note      none
 */
#define DRIVER_MAG3110_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to a mag3110 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_MAG3110_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to a mag3110 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_MAG3110_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE pointer to a mag3110 handle structure
 * @param[in] FUC pointer to an iic_read function address
 * @note      none
 */
#define DRIVER_MAG3110_LINK_IIC_READ(HANDLE, FUC)    (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to a mag3110 handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_MAG3110_LINK_IIC_WRITE(HANDLE, FUC)   (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a mag3110 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_MAG3110_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a mag3110 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_MAG3110_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup mag3110_base_driver mag3110 base driver function
 * @brief    mag3110 base driver modules
 * @ingroup  mag3110_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a mag3110 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mag3110_info(mag3110_info_t *info);

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
uint8_t mag3110_init(mag3110_handle_t *handle);

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
uint8_t mag3110_deinit(mag3110_handle_t *handle);

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
uint8_t mag3110_read(mag3110_handle_t *handle, int16_t raw[3], float ut[3]);

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
uint8_t mag3110_reset(mag3110_handle_t *handle);

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
uint8_t mag3110_read_die_temperature(mag3110_handle_t *handle, int8_t *raw, float *degree);

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
uint8_t mag3110_get_data_ready_status(mag3110_handle_t *handle, uint8_t *status);

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
uint8_t mag3110_get_mode_status(mag3110_handle_t *handle, mag3110_mode_status_t *mode);

/**
 * @brief     set offset x
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] offset set offset
 * @return    status code
 *            - 0 success
 *            - 1 set offset x failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 abs(offset) > 10000
 * @note      none
 */
uint8_t mag3110_set_offset_x(mag3110_handle_t *handle, int16_t offset);

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
uint8_t mag3110_get_offset_x(mag3110_handle_t *handle, int16_t *offset);

/**
 * @brief     set offset y
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] offset set offset
 * @return    status code
 *            - 0 success
 *            - 1 set offset y failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 abs(offset) > 10000
 * @note      none
 */
uint8_t mag3110_set_offset_y(mag3110_handle_t *handle, int16_t offset);

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
uint8_t mag3110_get_offset_y(mag3110_handle_t *handle, int16_t *offset);

/**
 * @brief     set offset z
 * @param[in] *handle pointer to a mag3110 handle structure
 * @param[in] offset set offset
 * @return    status code
 *            - 0 success
 *            - 1 set offset z failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 abs(offset) > 10000
 * @note      none
 */
uint8_t mag3110_set_offset_z(mag3110_handle_t *handle, int16_t offset);

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
uint8_t mag3110_get_offset_z(mag3110_handle_t *handle, int16_t *offset);

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
uint8_t mag3110_set_rate_over_sample(mag3110_handle_t *handle, mag3110_rate_over_sample_t rate_over_sample);

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
uint8_t mag3110_get_rate_over_sample(mag3110_handle_t *handle, mag3110_rate_over_sample_t *rate_over_sample);

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
uint8_t mag3110_set_fast_read_mode(mag3110_handle_t *handle, mag3110_bool_t enable);

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
uint8_t mag3110_get_fast_read_mode(mag3110_handle_t *handle, mag3110_bool_t *enable);

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
uint8_t mag3110_set_trigger_mode(mag3110_handle_t *handle, mag3110_bool_t enable);

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
uint8_t mag3110_get_trigger_mode(mag3110_handle_t *handle, mag3110_bool_t *enable);

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
uint8_t mag3110_set_mode(mag3110_handle_t *handle, mag3110_mode_t mode);

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
uint8_t mag3110_get_mode(mag3110_handle_t *handle, mag3110_mode_t *mode);

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
uint8_t mag3110_set_automatic_magnetic_sensor_reset(mag3110_handle_t *handle, mag3110_bool_t enable);

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
uint8_t mag3110_set_disable_offset_correction(mag3110_handle_t *handle, mag3110_bool_t enable);

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
uint8_t mag3110_get_disable_offset_correction(mag3110_handle_t *handle, mag3110_bool_t *enable);

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
uint8_t mag3110_offset_convert_to_register(mag3110_handle_t *handle, float ut, int16_t *reg);

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
uint8_t mag3110_offset_convert_to_data(mag3110_handle_t *handle, int16_t reg, float *ut);

/**
 * @}
 */

/**
 * @defgroup mag3110_extend_driver mag3110 extend driver function
 * @brief    mag3110 extend driver modules
 * @ingroup  mag3110_driver
 * @{
 */

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
uint8_t mag3110_set_reg(mag3110_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

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
uint8_t mag3110_get_reg(mag3110_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif
