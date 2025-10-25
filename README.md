[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAG3110

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mag3110/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

Freescale’s MAG3110 is a small, low-power, digital 3-axis magnetometer.The device can be used in conjunction with a 3-axis accelerometer to realize an orientation independent electronic compass that can provide accurate heading information. It features a standard I2C serial interface output and smart embedded functions.The MAG3110 is capable of measuring magnetic fields with an Output Data Rate(ODR) up to 80 Hz; these output data rates correspond to sample intervals from 12 ms to several seconds.

LibDriver MAG3110 is a full-featured driver for MAG3110, launched by LibDriver.It provides magnetic field reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MAG3110 source files.

/interface includes LibDriver MAG3110 IIC platform independent template.

/test includes LibDriver MAG3110 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MAG3110 sample code.

/doc includes LibDriver MAG3110 offline document.

/datasheet includes MAG3110 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_mag3110_basic.h"

uint8_t res;
uint32_t i;
float ut[3];

/* basic init */
res = mag3110_basic_init();
if (res != 0)
{
    return 1;
}

...

/* loop */
for (i = 0; i < 3; i++)
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
    mag3110_interface_debug_print("%d/%d\n", (uint32_t)(i + 1), (uint32_t)3);
    mag3110_interface_debug_print("x is %0.3fuT.\n", ut[0]);
    mag3110_interface_debug_print("y is %0.3fuT.\n", ut[1]);
    mag3110_interface_debug_print("z is %0.3fuT.\n", ut[2]);
    
    ...
}

...
    
/* deinit */
(void)mag3110_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/mag3110/index.html](https://www.libdriver.com/docs/mag3110/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.