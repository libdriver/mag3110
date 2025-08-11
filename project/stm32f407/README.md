### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MAG3110

#### 3.1 Command Instruction

1. Show mag3110 chip and driver information.

   ```shell
   mag3110 (-i | --information)
   ```

2. Show mag3110 help.

   ```shell
   mag3110 (-h | --help)
   ```

3. Show mag3110 pin connections of the current board.

   ```shell
   mag3110 (-p | --port)
   ```

4. Run mag3110 register test.

   ```shell
   mag3110 (-t reg | --test=reg)
   ```

5. Run mag3110 read test, num means test times.

   ```shell
   mag3110 (-t read | --test=read) [--times=<num>]
   ```

6. Run mag3110 read function, num means read times.

   ```shell
   mag3110 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
mag3110 -i

mag3110: chip is NXP MAG3110.
mag3110: manufacturer is NXP.
mag3110: interface is IIC.
mag3110: driver version is 1.0.
mag3110: min supply voltage is 2.0V.
mag3110: max supply voltage is 3.6V.
mag3110: max current is 0.90mA.
mag3110: max temperature is 85.0C.
mag3110: min temperature is -40.0C.
```

```shell
mag3110 -p

mag3110: SCL connected to GPIOB PIN8.
mag3110: SDA connected to GPIOB PIN9.
```

```shell
mag3110 -t reg

mag3110: chip is NXP MAG3110.
mag3110: manufacturer is NXP.
mag3110: interface is IIC.
mag3110: driver version is 1.0.
mag3110: min supply voltage is 2.0V.
mag3110: max supply voltage is 3.6V.
mag3110: max current is 0.90mA.
mag3110: max temperature is 85.0C.
mag3110: min temperature is -40.0C.
mag3110: start register test.
mag3110: mag3110_get_data_ready_status test.
mag3110: data status is 0x00.
mag3110: mag3110_get_mode_status test.
mag3110: mode status is 0x00.
mag3110: mag3110_set_offset_x/mag3110_get_offset_x test.
mag3110: set offset x 0x4D40.
mag3110: check offset x ok.
mag3110: mag3110_set_offset_y/mag3110_get_offset_y test.
mag3110: set offset y 0x04CD.
mag3110: check offset y ok.
mag3110: mag3110_set_offset_z/mag3110_get_offset_z test.
mag3110: set offset z 0x3A73.
mag3110: check offset z ok.
mag3110: mag3110_set_rate_over_sample/mag3110_get_rate_over_sample test.
mag3110: set rate 80hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 40hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 20hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 10hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 40hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 20hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 10hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 5hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 20hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 10hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 5hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 2.5hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 10hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 5hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 2.5hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 1.25hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 5hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 2.5hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 1.25hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.63hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 2.5hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 1.25hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.63hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.31hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 1.25hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.63hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.31hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.16hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.63hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.31hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.16hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.08hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: mag3110_set_fast_read_mode/mag3110_get_fast_read_mode test.
mag3110: enable fast read mode.
mag3110: check mode ok.
mag3110: disable fast read mode.
mag3110: check mode ok.
mag3110: mag3110_set_trigger_mode/mag3110_get_trigger_mode test.
mag3110: enable trigger mode.
mag3110: check trigger mode error.
mag3110: disable trigger mode.
mag3110: check trigger mode ok.
mag3110: mag3110_set_mode/mag3110_get_mode test.
mag3110: set active mode.
mag3110: check mode ok.
mag3110: set standby mode.
mag3110: check mode ok.
mag3110: mag3110_set_automatic_magnetic_sensor_reset test.
mag3110: enable automatic magnetic sensor reset.
mag3110: check reset ok.
mag3110: disable automatic magnetic sensor reset.
mag3110: check reset ok.
mag3110: mag3110_set_disable_offset_correction/mag3110_get_disable_offset_correction test.
mag3110: disable offset correction.
mag3110: check disable offset correction ok.
mag3110: enable offset correction.
mag3110: check disable offset correction ok.
mag3110: mag3110_offset_convert_to_register/mag3110_offset_convert_to_data test.
mag3110: set ut 160.0.
mag3110: check ut 160.0.
mag3110: set ut -583.0.
mag3110: check ut -583.0.
mag3110: mag3110_reset test.
mag3110: check reset ok.
mag3110: finish register test.
```

```shell
mag3110 -t read --times=3

mag3110: chip is NXP MAG3110.
mag3110: manufacturer is NXP.
mag3110: interface is IIC.
mag3110: driver version is 1.0.
mag3110: min supply voltage is 2.0V.
mag3110: max supply voltage is 3.6V.
mag3110: max current is 0.90mA.
mag3110: max temperature is 85.0C.
mag3110: min temperature is -40.0C.
mag3110: start read test.
mag3110: normal read mode test.
mag3110: x is 58.6uT.
mag3110: y is 13.7uT.
mag3110: z is -116.8uT.
mag3110: x is 58.6uT.
mag3110: y is 13.7uT.
mag3110: z is -116.8uT.
mag3110: x is 58.6uT.
mag3110: y is 13.7uT.
mag3110: z is -117.1uT.
mag3110: fast read mode test.
mag3110: x is 58.5uT.
mag3110: y is 13.5uT.
mag3110: z is -116.9uT.
mag3110: x is 58.7uT.
mag3110: y is 13.9uT.
mag3110: z is -117.2uT.
mag3110: x is 51.4uT.
mag3110: y is 64.7uT.
mag3110: z is -117.6uT.
mag3110: trigger mode test.
mag3110: x is 58.7uT.
mag3110: y is 13.3uT.
mag3110: z is -117.4uT.
mag3110: x is 58.7uT.
mag3110: y is 13.3uT.
mag3110: z is -117.4uT.
mag3110: x is 58.7uT.
mag3110: y is 13.3uT.
mag3110: z is -117.4uT.
mag3110: read die temperature test.
mag3110: die temperature is 27.0C.
mag3110: die temperature is 27.0C.
mag3110: die temperature is 27.0C.
mag3110: finish read test.
```

```shell
mag3110 -e read --times=3

1/3
x is 58.200uT.
y is 13.800uT.
z is -117.000uT.
2/3
x is 58.900uT.
y is 13.700uT.
z is -116.700uT.
3/3
x is 58.600uT.
y is 13.700uT.
z is -116.600uT.
```

```shell
mag3110 -h

Usage:
  mag3110 (-i | --information)
  mag3110 (-h | --help)
  mag3110 (-p | --port)
  mag3110 (-t reg | --test=reg)
  mag3110 (-t read | --test=read) [--times=<num>]
  mag3110 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>
                                 Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

