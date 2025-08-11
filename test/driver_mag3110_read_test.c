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
 * @file      driver_mag3110_read_test.c
 * @brief     driver mag3110 read test source file
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

#include "driver_mag3110_read_test.h"

static mag3110_handle_t gs_handle;        /**< mag3110 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t mag3110_read_test(uint32_t times)
{
    uint8_t res; 
    int8_t raw_s;
    uint32_t i;
    float degree;
    int16_t raw[3];
    float ut[3];
    mag3110_info_t info;
    
    /* link interface function */
    DRIVER_MAG3110_LINK_INIT(&gs_handle, mag3110_handle_t);
    DRIVER_MAG3110_LINK_IIC_INIT(&gs_handle, mag3110_interface_iic_init);
    DRIVER_MAG3110_LINK_IIC_DEINIT(&gs_handle, mag3110_interface_iic_deinit);
    DRIVER_MAG3110_LINK_IIC_READ(&gs_handle, mag3110_interface_iic_read);
    DRIVER_MAG3110_LINK_IIC_WRITE(&gs_handle, mag3110_interface_iic_write);
    DRIVER_MAG3110_LINK_DELAY_MS(&gs_handle, mag3110_interface_delay_ms);
    DRIVER_MAG3110_LINK_DEBUG_PRINT(&gs_handle, mag3110_interface_debug_print);
    
    /* get mag3110 info */
    res = mag3110_info(&info);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip information */
        mag3110_interface_debug_print("mag3110: chip is %s.\n", info.chip_name);
        mag3110_interface_debug_print("mag3110: manufacturer is %s.\n", info.manufacturer_name);
        mag3110_interface_debug_print("mag3110: interface is %s.\n", info.interface);
        mag3110_interface_debug_print("mag3110: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mag3110_interface_debug_print("mag3110: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mag3110_interface_debug_print("mag3110: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mag3110_interface_debug_print("mag3110: max current is %0.2fmA.\n", info.max_current_ma);
        mag3110_interface_debug_print("mag3110: max temperature is %0.1fC.\n", info.temperature_max);
        mag3110_interface_debug_print("mag3110: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* mag3110 init */
    res = mag3110_init(&gs_handle);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    mag3110_interface_debug_print("mag3110: start read test.\n");
    
    /* set offset x 0x0000 */
    res = mag3110_set_offset_x(&gs_handle, 0x0000);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset x failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set offset y 0x0000 */
    res = mag3110_set_offset_y(&gs_handle, 0x0000);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset y failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set offset z 0x0000 */
    res = mag3110_set_offset_z(&gs_handle, 0x0000);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset z failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable offset correction */
    res = mag3110_set_disable_offset_correction(&gs_handle, MAG3110_BOOL_TRUE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set disable offset correction failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 10hz, 128 over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_10HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable automatic magnetic sensor reset */
    res = mag3110_set_automatic_magnetic_sensor_reset(&gs_handle, MAG3110_BOOL_FALSE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set automatic magnetic sensor reset failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable trigger mode */
    res = mag3110_set_trigger_mode(&gs_handle, MAG3110_BOOL_FALSE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set trigger mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable fast read mode */
    res = mag3110_set_fast_read_mode(&gs_handle, MAG3110_BOOL_FALSE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set fast read mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set active mode */
    res = mag3110_set_mode(&gs_handle, MAG3110_MODE_ACTIVE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* normal read mode test */
    mag3110_interface_debug_print("mag3110: normal read mode test.\n");
    
    for (i = 0; i < times; i++)
    {
        /* delay 1 s*/
        mag3110_interface_delay_ms(1000);

        /* single read */
        res = mag3110_read(&gs_handle, (int16_t *)raw, ut);
        if (res != 0)
        {
            mag3110_interface_debug_print("mag3110: read failed.\n");
            (void)mag3110_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        mag3110_interface_debug_print("mag3110: x is %.1fuT.\n", ut[0]);
        mag3110_interface_debug_print("mag3110: y is %.1fuT.\n", ut[1]);
        mag3110_interface_debug_print("mag3110: z is %.1fuT.\n", ut[2]);
    }
    
    /* enable fast read mode */
    res = mag3110_set_fast_read_mode(&gs_handle, MAG3110_BOOL_TRUE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set fast read mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* fast read mode test */
    mag3110_interface_debug_print("mag3110: fast read mode test.\n");
    
    for (i = 0; i < times; i++)
    {
        /* delay 1 s*/
        mag3110_interface_delay_ms(1000);

        /* read */
        res = mag3110_read(&gs_handle, (int16_t *)raw, ut);
        if (res != 0)
        {
            mag3110_interface_debug_print("mag3110: read failed.\n");
            (void)mag3110_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        mag3110_interface_debug_print("mag3110: x is %.1fuT.\n", ut[0]);
        mag3110_interface_debug_print("mag3110: y is %.1fuT.\n", ut[1]);
        mag3110_interface_debug_print("mag3110: z is %.1fuT.\n", ut[2]);
    }
    
    /* disable fast read mode */
    res = mag3110_set_fast_read_mode(&gs_handle, MAG3110_BOOL_FALSE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set fast read mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable trigger mode */
    res = mag3110_set_trigger_mode(&gs_handle, MAG3110_BOOL_TRUE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set trigger mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* trigger mode test */
    mag3110_interface_debug_print("mag3110: trigger mode test.\n");
    
    for (i = 0; i < times; i++)
    {
        /* delay 1 s*/
        mag3110_interface_delay_ms(1000);

        /* read */
        res = mag3110_read(&gs_handle, (int16_t *)raw, ut);
        if (res != 0)
        {
            mag3110_interface_debug_print("mag3110: read failed.\n");
            (void)mag3110_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        mag3110_interface_debug_print("mag3110: x is %.1fuT.\n", ut[0]);
        mag3110_interface_debug_print("mag3110: y is %.1fuT.\n", ut[1]);
        mag3110_interface_debug_print("mag3110: z is %.1fuT.\n", ut[2]);
    }
    
    /* read die temperature test */
    mag3110_interface_debug_print("mag3110: read die temperature test.\n");
    
    for (i = 0; i < times; i++)
    {
        /* delay 1 s*/
        mag3110_interface_delay_ms(1000);

        /* read */
        res = mag3110_read_die_temperature(&gs_handle, &raw_s, &degree);
        if (res != 0)
        {
            mag3110_interface_debug_print("mag3110: read die temperature failed.\n");
            (void)mag3110_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        mag3110_interface_debug_print("mag3110: die temperature is %.1fC.\n", degree + 30.0f);
    }
    
    /* finish read test */
    mag3110_interface_debug_print("mag3110: finish read test.\n");
    (void)mag3110_deinit(&gs_handle);
    
    return 0;
}
