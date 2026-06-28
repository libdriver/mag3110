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
 * @file      driver_mag3110_register_test.c
 * @brief     driver mag3110 register test source file
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

#include "driver_mag3110_register_test.h"
#include <stdlib.h>

static mag3110_handle_t gs_handle;        /**< mag3110 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t mag3110_register_test(void)
{
    uint8_t res;
    uint8_t status;
    int16_t offset;
    int16_t offset_check;
    uint16_t reg;
    int16_t reg2;
    float ut;
    float ut_check;
    mag3110_info_t info;
    mag3110_mode_t mode;
    mag3110_mode_status_t mode_status;
    mag3110_rate_over_sample_t rate_over_sample;
    mag3110_bool_t enable;
    
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
    
    /* start register test */
    mag3110_interface_debug_print("mag3110: start register test.\n");
    
    /* mag3110_get_data_ready_status test */
    mag3110_interface_debug_print("mag3110: mag3110_get_data_ready_status test.\n");
    
    /* get data ready status */
    res = mag3110_get_data_ready_status(&gs_handle, &status);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get data ready status failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: data status is 0x%02X.\n", status);
    
    /* mag3110_get_mode_status test */
    mag3110_interface_debug_print("mag3110: mag3110_get_mode_status test.\n");
    
    /* get mode status */
    res = mag3110_get_mode_status(&gs_handle, &mode_status);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get mode status failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: mode status is 0x%02X.\n", (uint8_t)mode_status);
    
    /* mag3110_set_offset_x/mag3110_get_offset_x test */
    mag3110_interface_debug_print("mag3110: mag3110_set_offset_x/mag3110_get_offset_x test.\n");
    
    offset = rand() % 10000;
    res = mag3110_set_offset_x(&gs_handle, offset);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset x failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set offset x 0x%04X.\n", offset);
    res = mag3110_get_offset_x(&gs_handle, &offset_check);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get offset x failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check offset x %s.\n", (offset == offset_check) ? "ok" : "error");
    
    /* mag3110_set_offset_y/mag3110_get_offset_y test */
    mag3110_interface_debug_print("mag3110: mag3110_set_offset_y/mag3110_get_offset_y test.\n");
    
    offset = rand() % 10000;
    res = mag3110_set_offset_y(&gs_handle, offset);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset y failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set offset y 0x%04X.\n", offset);
    res = mag3110_get_offset_y(&gs_handle, &offset_check);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get offset y failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check offset y %s.\n", (offset == offset_check) ? "ok" : "error");
    
    /* mag3110_set_offset_z/mag3110_get_offset_z test */
    mag3110_interface_debug_print("mag3110: mag3110_set_offset_z/mag3110_get_offset_z test.\n");
    
    offset = rand() % 10000;
    res = mag3110_set_offset_z(&gs_handle, offset);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set offset z failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set offset z 0x%04X.\n", offset);
    res = mag3110_get_offset_z(&gs_handle, &offset_check);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get offset z failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check offset z %s.\n", (offset == offset_check) ? "ok" : "error");
    
    /* mag3110_set_rate_over_sample/mag3110_get_rate_over_sample test */
    mag3110_interface_debug_print("mag3110: mag3110_set_rate_over_sample/mag3110_get_rate_over_sample test.\n");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_80HZ_OVER_SAMPLE_16);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 80hz, 16 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_80HZ_OVER_SAMPLE_16) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_40HZ_OVER_SAMPLE_32);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 40hz, 32 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_40HZ_OVER_SAMPLE_32) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_20HZ_OVER_SAMPLE_64);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 20hz, 64 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_20HZ_OVER_SAMPLE_64) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_10HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 10hz, 128 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_10HZ_OVER_SAMPLE_128) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_40HZ_OVER_SAMPLE_16);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 40hz, 16 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_40HZ_OVER_SAMPLE_16) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_20HZ_OVER_SAMPLE_32);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 20hz, 32 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_20HZ_OVER_SAMPLE_32) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_10HZ_OVER_SAMPLE_64);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 10hz, 64 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_10HZ_OVER_SAMPLE_64) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_5HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 5hz, 128 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_5HZ_OVER_SAMPLE_128) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_20HZ_OVER_SAMPLE_16);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 20hz, 16 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_20HZ_OVER_SAMPLE_16) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_10HZ_OVER_SAMPLE_32);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 10hz, 32 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_10HZ_OVER_SAMPLE_32) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_5HZ_OVER_SAMPLE_64);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 5hz, 64 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_5HZ_OVER_SAMPLE_64) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_2P5HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 2.5hz, 128 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_2P5HZ_OVER_SAMPLE_128) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_10HZ_OVER_SAMPLE_16);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 10hz, 16 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_10HZ_OVER_SAMPLE_16) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_5HZ_OVER_SAMPLE_32);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 5hz, 32 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_5HZ_OVER_SAMPLE_32) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_2P5HZ_OVER_SAMPLE_64);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 2.5hz, 64 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_2P5HZ_OVER_SAMPLE_64) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_1P25HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 1.25hz, 128 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_1P25HZ_OVER_SAMPLE_128) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_5HZ_OVER_SAMPLE_16);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 5hz, 16 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_5HZ_OVER_SAMPLE_16) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_2P5HZ_OVER_SAMPLE_32);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 2.5hz, 32 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_2P5HZ_OVER_SAMPLE_32) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_1P25HZ_OVER_SAMPLE_64);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 1.25hz, 64 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_1P25HZ_OVER_SAMPLE_64) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P63HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.63hz, 128 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P63HZ_OVER_SAMPLE_128) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_2P5HZ_OVER_SAMPLE_16);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 2.5hz, 16 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_2P5HZ_OVER_SAMPLE_16) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_1P25HZ_OVER_SAMPLE_32);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 1.25hz, 32 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_1P25HZ_OVER_SAMPLE_32) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P63HZ_OVER_SAMPLE_64);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.63hz, 64 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P63HZ_OVER_SAMPLE_64) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P31HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.31hz, 128 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P31HZ_OVER_SAMPLE_128) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_1P25HZ_OVER_SAMPLE_16);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 1.25hz, 16 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_1P25HZ_OVER_SAMPLE_16) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P63HZ_OVER_SAMPLE_32);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.63hz, 32 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P63HZ_OVER_SAMPLE_32) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P31HZ_OVER_SAMPLE_64);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.31hz, 64 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P31HZ_OVER_SAMPLE_64) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P16HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.16hz, 128 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P16HZ_OVER_SAMPLE_128) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P63HZ_OVER_SAMPLE_16);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.63hz, 16 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P63HZ_OVER_SAMPLE_16) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P31HZ_OVER_SAMPLE_32);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.31hz, 32 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P31HZ_OVER_SAMPLE_32) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P16HZ_OVER_SAMPLE_64);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.16hz, 64 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P16HZ_OVER_SAMPLE_64) ? "ok" : "error");
    
    /* set rate over sample */
    res = mag3110_set_rate_over_sample(&gs_handle, MAG3110_RATE_0P08HZ_OVER_SAMPLE_128);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set rate 0.08hz, 128 over sample.\n");
    res = mag3110_get_rate_over_sample(&gs_handle, &rate_over_sample);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get rate over sample failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check rate over sample z %s.\n", (rate_over_sample == MAG3110_RATE_0P08HZ_OVER_SAMPLE_128) ? "ok" : "error");
    
    /* mag3110_set_fast_read_mode/mag3110_get_fast_read_mode test */
    mag3110_interface_debug_print("mag3110: mag3110_set_fast_read_mode/mag3110_get_fast_read_mode test.\n");
    
    /* enable fast read mode */
    res = mag3110_set_fast_read_mode(&gs_handle, MAG3110_BOOL_TRUE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set fast read mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: enable fast read mode.\n");
    res = mag3110_get_fast_read_mode(&gs_handle, &enable);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get fast read mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check mode %s.\n", (enable == MAG3110_BOOL_TRUE) ? "ok" : "error");
    
    /* disable fast read mode */
    res = mag3110_set_fast_read_mode(&gs_handle, MAG3110_BOOL_FALSE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set fast read mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: disable fast read mode.\n");
    res = mag3110_get_fast_read_mode(&gs_handle, &enable);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get fast read mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check mode %s.\n", (enable == MAG3110_BOOL_FALSE) ? "ok" : "error");
    
    /* mag3110_set_trigger_mode/mag3110_get_trigger_mode test */
    mag3110_interface_debug_print("mag3110: mag3110_set_trigger_mode/mag3110_get_trigger_mode test.\n");
    
    /* enable trigger mode */
    res = mag3110_set_trigger_mode(&gs_handle, MAG3110_BOOL_TRUE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set trigger mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: enable trigger mode.\n");
    res = mag3110_get_trigger_mode(&gs_handle, &enable);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get trigger mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check trigger mode %s.\n", (enable == MAG3110_BOOL_TRUE) ? "ok" : "error");
    
    /* disable trigger mode */
    res = mag3110_set_trigger_mode(&gs_handle, MAG3110_BOOL_FALSE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set trigger mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: disable trigger mode.\n");
    res = mag3110_get_trigger_mode(&gs_handle, &enable);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get trigger mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check trigger mode %s.\n", (enable == MAG3110_BOOL_FALSE) ? "ok" : "error");
    
    /* mag3110_set_mode/mag3110_get_mode test */
    mag3110_interface_debug_print("mag3110: mag3110_set_mode/mag3110_get_mode test.\n");
    
    /* set active mode */
    res = mag3110_set_mode(&gs_handle, MAG3110_MODE_ACTIVE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set active mode.\n");
    res = mag3110_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check mode %s.\n", (mode == MAG3110_MODE_ACTIVE) ? "ok" : "error");
    
    /* set standby mode */
    res = mag3110_set_mode(&gs_handle, MAG3110_MODE_STANDBY);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set standby mode.\n");
    res = mag3110_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get mode failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check mode %s.\n", (mode == MAG3110_MODE_STANDBY) ? "ok" : "error");
    
    /* mag3110_set_automatic_magnetic_sensor_reset test */
    mag3110_interface_debug_print("mag3110: mag3110_set_automatic_magnetic_sensor_reset test.\n");
    
    /* enable automatic magnetic sensor reset */
    res = mag3110_set_automatic_magnetic_sensor_reset(&gs_handle, MAG3110_BOOL_TRUE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set automatic magnetic sensor reset failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: enable automatic magnetic sensor reset.\n");
    mag3110_interface_debug_print("mag3110: check reset %s.\n", (res == 0) ? "ok" : "error");
    
    /* disable automatic magnetic sensor reset */
    res = mag3110_set_automatic_magnetic_sensor_reset(&gs_handle, MAG3110_BOOL_FALSE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set automatic magnetic sensor reset failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: disable automatic magnetic sensor reset.\n");
    mag3110_interface_debug_print("mag3110: check reset %s.\n", (res == 0) ? "ok" : "error");
    
    /* mag3110_set_disable_offset_correction/mag3110_get_disable_offset_correction test */
    mag3110_interface_debug_print("mag3110: mag3110_set_disable_offset_correction/mag3110_get_disable_offset_correction test.\n");
    
    /* enable disable offset correction */
    res = mag3110_set_disable_offset_correction(&gs_handle, MAG3110_BOOL_TRUE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set disable offset correction failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: disable offset correction.\n");
    res = mag3110_get_disable_offset_correction(&gs_handle, &enable);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get disable offset correction failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check disable offset correction %s.\n", (enable == MAG3110_BOOL_TRUE) ? "ok" : "error");
    
    /* disable disable offset correction */
    res = mag3110_set_disable_offset_correction(&gs_handle, MAG3110_BOOL_FALSE);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: set disable offset correction failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: enable offset correction.\n");
    res = mag3110_get_disable_offset_correction(&gs_handle, &enable);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: get disable offset correction failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check disable offset correction %s.\n", (enable == MAG3110_BOOL_FALSE) ? "ok" : "error");
    
    /* mag3110_offset_convert_to_register/mag3110_offset_convert_to_data test */
    mag3110_interface_debug_print("mag3110: mag3110_offset_convert_to_register/mag3110_offset_convert_to_data test.\n");
    
    ut = (float)(rand() % 1000);
    res = mag3110_offset_convert_to_register(&gs_handle, ut, &reg2);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: offset convert to register failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set ut %0.1f.\n", ut);
    res = mag3110_offset_convert_to_data(&gs_handle, reg2, &ut_check);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: offset convert to data failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check ut %0.1f.\n", ut_check);
    
    ut = -(float)(rand() % 1000);
    res = mag3110_offset_convert_to_register(&gs_handle, ut, &reg2);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: offset convert to register failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: set ut %0.1f.\n", ut);
    res = mag3110_offset_convert_to_data(&gs_handle, reg2, &ut_check);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: offset convert to data failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check ut %0.1f.\n", ut_check);
    
    /* mag3110_reset test */
    mag3110_interface_debug_print("mag3110: mag3110_reset test.\n");
    
    /* reset */
    res = mag3110_reset(&gs_handle);
    if (res != 0)
    {
        mag3110_interface_debug_print("mag3110: reset failed.\n");
        (void)mag3110_deinit(&gs_handle);
        
        return 1;
    }
    mag3110_interface_debug_print("mag3110: check reset %s.\n", (res == 0) ? "ok" : "error");
    
    /* finish register test */
    mag3110_interface_debug_print("mag3110: finish register test.\n");
    (void)mag3110_deinit(&gs_handle);
    
    return 0;
}
