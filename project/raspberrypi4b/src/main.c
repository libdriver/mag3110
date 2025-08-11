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
 * @file      main.c
 * @brief     main source file
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
#include "driver_mag3110_register_test.h"
#include "driver_mag3110_read_test.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     mag3110 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t mag3110(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);
    
    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (mag3110_register_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (mag3110_read_test(times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float ut[3];
        
        /* basic init */
        res = mag3110_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            mag3110_interface_delay_ms(1000);
            
            /* read data */
            res = mag3110_basic_read((float *)ut);
            if (res != 0)
            {
                (void)mag3110_basic_deinit();
                
                return 1;
            }
            
            /* output */
            mag3110_interface_debug_print("%d/%d\n", (uint32_t)(i + 1), (uint32_t)times);
            mag3110_interface_debug_print("x is %0.3fuT.\n", ut[0]);
            mag3110_interface_debug_print("y is %0.3fuT.\n", ut[1]);
            mag3110_interface_debug_print("z is %0.3fuT.\n", ut[2]);
        }
        
        /* deinit */
        (void)mag3110_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        mag3110_interface_debug_print("Usage:\n");
        mag3110_interface_debug_print("  mag3110 (-i | --information)\n");
        mag3110_interface_debug_print("  mag3110 (-h | --help)\n");
        mag3110_interface_debug_print("  mag3110 (-p | --port)\n");
        mag3110_interface_debug_print("  mag3110 (-t reg | --test=reg)\n");
        mag3110_interface_debug_print("  mag3110 (-t read | --test=read) [--times=<num>]\n");
        mag3110_interface_debug_print("  mag3110 (-e read | --example=read) [--times=<num>]\n");
        mag3110_interface_debug_print("\n");
        mag3110_interface_debug_print("Options:\n");
        mag3110_interface_debug_print("  -e <read>, --example=<read>\n");
        mag3110_interface_debug_print("                                 Run the driver example.\n");
        mag3110_interface_debug_print("  -h, --help                     Show the help.\n");
        mag3110_interface_debug_print("  -i, --information              Show the chip information.\n");
        mag3110_interface_debug_print("  -p, --port                     Display the pin connections of the current board.\n");
        mag3110_interface_debug_print("  -t <reg | read>, --test=<reg | read>\n");
        mag3110_interface_debug_print("                                 Run the driver test.\n");
        mag3110_interface_debug_print("      --times=<num>              Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        mag3110_info_t info;
        
        /* print mag3110 info */
        mag3110_info(&info);
        mag3110_interface_debug_print("mag3110: chip is %s.\n", info.chip_name);
        mag3110_interface_debug_print("mag3110: manufacturer is %s.\n", info.manufacturer_name);
        mag3110_interface_debug_print("mag3110: interface is %s.\n", info.interface);
        mag3110_interface_debug_print("mag3110: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mag3110_interface_debug_print("mag3110: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mag3110_interface_debug_print("mag3110: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mag3110_interface_debug_print("mag3110: max current is %0.2fmA.\n", info.max_current_ma);
        mag3110_interface_debug_print("mag3110: max temperature is %0.1fC.\n", info.temperature_max);
        mag3110_interface_debug_print("mag3110: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        mag3110_interface_debug_print("mag3110: SCL connected to GPIO3(BCM).\n");
        mag3110_interface_debug_print("mag3110: SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = mag3110(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        mag3110_interface_debug_print("mag3110: run failed.\n");
    }
    else if (res == 5)
    {
        mag3110_interface_debug_print("mag3110: param is invalid.\n");
    }
    else
    {
        mag3110_interface_debug_print("mag3110: unknown status code.\n");
    }

    return 0;
}