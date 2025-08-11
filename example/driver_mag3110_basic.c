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
 * @file      driver_mag3110_basic.c
 * @brief     driver mag3110 basic source file
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

#include "driver_mag3110_basic.h"

static mag3110_handle_t gs_handle;        /**< mag3110 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t mag3110_basic_init(void)
{
    uint8_t res;
    uint16_t offset;
    
    /* link interface function */
    DRIVER_MAG3110_LINK_INIT(&gs_handle, mag3110_handle_t);
    DRIVER_MAG3110_LINK_IIC_INIT(&gs_handle, mag3110_interface_iic_init);
    DRIVER_MAG3110_LINK_IIC_DEINIT(&gs_handle, mag3110_interface_iic_deinit);
    DRIVER_MAG3110_LINK_IIC_READ(&gs_handle, mag3110_interface_iic_read);
    DRIVER_MAG3110_LINK_IIC_WRITE(&gs_handle, mag3110_interface_iic_write);
    DRIVER_MAG3110_LINK_DELAY_MS(&gs_handle, mag3110_interface_delay_ms);
    DRIVER_MAG3110_LINK_DEBUG_PRINT(&gs_handle, mag3110_interface_debug_print);
    
    /* mag3110 init */
    res = mag3110_init(&gs_handle);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: init failed.\n");
        
        return 1;
    }
    
    /* convert offset */
    res = mag3110_offset_convert_to_register(&gs_handle, MAG3110_BASIC_DEFAULT_OFFSET, &offset);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: offset convert to register failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default offset x */
    res = mag3110_set_offset_x(&gs_handle, offset);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset x failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default offset y */
    res = mag3110_set_offset_y(&gs_handle, offset);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset y failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default offset z */
    res = mag3110_set_offset_z(&gs_handle, offset);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset z failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default disable offset correction */
    res = mag3110_set_disable_offset_correction(&gs_handle, MAG3110_BASIC_DEFAULT_DISABLE_OFFSET_CORRECTION);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set disable offset correction failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_BASIC_DEFAULT_RATE_OVER_SAMPLE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set the default fast read mode */
    res = mag3110_set_fast_read_mode(&gs_handle, MAG3110_BASIC_DEFAULT_FAST_READ);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set fast read mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default trigger mode */
    res = mag3110_set_trigger_mode(&gs_handle, MAG3110_BASIC_DEFAULT_TRIGGER_MODE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set trigger mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default automatic magnetic sensor reset */
    res = mag3110_set_automatic_magnetic_sensor_reset(&gs_handle, MAG3110_BASIC_DEFAULT_AUTO_RESET);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set automatic magnetic sensor reset failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* active mode */
    res = mag3110_set_mode(&gs_handle, MAG3110_MODE_ACTIVE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *ut pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t mag3110_basic_read(float ut[3])
{
    int16_t raw[3];
    
    /* read x,y,z data */
    if (mag3110_read(&gs_handle, (int16_t *)raw, ut) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mag3110_basic_deinit(void)
{
    /* close mag3110 */
    if (mag3110_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
